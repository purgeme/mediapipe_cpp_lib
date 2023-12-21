#include <cstdlib>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

#include "mcl_core.h"

namespace mcl {

absl::Status MCL::_runMPPGraph() {

  constexpr char kInputStream[] = "input_video";
  constexpr char kOutputStream[] = "output_video";
  constexpr char kWindowName[] = "MediaPipe";

  std::string calculator_graph_config_contents;
  MP_RETURN_IF_ERROR(mediapipe::file::GetContents(
      _graph_filename,
      &calculator_graph_config_contents));

  // LOG(INFO) << "Get calculator graph config contents: ";
            // << calculator_graph_config_contents;

  mediapipe::CalculatorGraphConfig config =
      mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
          calculator_graph_config_contents);

  if(_enable_gpu){
    #ifndef ENABLE_GPU
      return absl::FailedPreconditionError("Only CPU graphs supported");
    #endif
  } else {
    #ifdef ENABLE_GPU
      return absl::FailedPreconditionError("Only GPU graphs supported");
    #endif
  }

  LOG(INFO) << "Initialize the calculator graph.";
  _graph.reset(new mediapipe::CalculatorGraph());
  MP_RETURN_IF_ERROR(_graph->Initialize(config));

  #ifdef ENABLE_GPU
    ABSL_LOG(INFO) << "Initialize the GPU.";
    MP_ASSIGN_OR_RETURN(auto gpu_resources, mediapipe::GpuResources::Create());
    MP_RETURN_IF_ERROR(_graph->SetGpuResources(std::move(gpu_resources)));
    mediapipe::GlCalculatorHelper gpu_helper;
    gpu_helper.InitializeForTest(_graph->GetGpuResources().get());
  #endif

  for (auto& iter : _observers)
	{
		RET_CHECK_OK(iter->AddOutputStream(_graph));
	}

  LOG(INFO) << "Initialize the camera";
  cv::VideoCapture capture;
  capture.open(_cam_id);
  RET_CHECK(capture.isOpened());

  cv::namedWindow(kWindowName, /*flags=WINDOW_AUTOSIZE*/ 1);
  capture.set(cv::CAP_PROP_FRAME_WIDTH, _cam_resx);
  capture.set(cv::CAP_PROP_FRAME_HEIGHT, _cam_resy);
  capture.set(cv::CAP_PROP_FPS, _cam_fps);

  LOG(INFO) << "Start running the calculator graph.";

  std::unique_ptr<mediapipe::OutputStreamPoller> output_poller;
	auto output_poller_sop = _graph->AddOutputStreamPoller(kOutputStream);
	RET_CHECK(output_poller_sop.ok());
	output_poller = std::make_unique<mediapipe::OutputStreamPoller>(std::move(output_poller_sop.value()));

  MP_RETURN_IF_ERROR(_graph->StartRun({}));

  LOG(INFO) << "Start grabbing and processing frames.";

  _run_flag = true;

  cv::Mat camera_frame_raw;
  cv::Mat camera_frame;
  cv::Mat output_frame_mat;

  while (_run_flag) {

    // Capture opencv camera or video frame.
    capture >> camera_frame_raw;

    #ifdef ENABLE_GPU
      cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGBA);
    #else
      cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
    #endif

    cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);

    // Wrap Mat into an ImageFrame.
    #ifdef ENABLE_GPU
      auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
          mediapipe::ImageFormat::SRGBA, camera_frame.cols, camera_frame.rows,
          mediapipe::ImageFrame::kGlDefaultAlignmentBoundary);
    #else
      auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
          mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
          mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    #endif

    cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
    camera_frame.copyTo(input_frame_mat);

    // Send image packet into the graph.
    size_t frame_timestamp_us =
        (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;

    #ifdef ENABLE_GPU
      MP_RETURN_IF_ERROR(
          gpu_helper.RunInGlContext([&input_frame, &frame_timestamp_us,
                                     &gpu_helper, &kInputStream, this]() -> absl::Status {
            // Convert ImageFrame to GpuBuffer.
            auto texture = gpu_helper.CreateSourceTexture(*input_frame.get());
            auto gpu_frame = texture.GetFrame<mediapipe::GpuBuffer>();
            glFlush();
            texture.Release();
            // Send GPU image packet into the graph.
            MP_RETURN_IF_ERROR(this->_graph->AddPacketToInputStream(
                kInputStream, mediapipe::Adopt(gpu_frame.release())
                                  .At(mediapipe::Timestamp(frame_timestamp_us))));
            return absl::OkStatus();
          }));
    #else
      MP_RETURN_IF_ERROR(_graph->AddPacketToInputStream(
          kInputStream, mediapipe::Adopt(input_frame.release())
                            .At(mediapipe::Timestamp(frame_timestamp_us))));
    #endif

    // Get the graph result packet, or stop if that fails.
    mediapipe::Packet packet;

    if (!output_poller->Next(&packet)) break;
    // poller.Next(&packet);

    // Only show camera output if enabled ( disabled by default )
    if(_show_camera){

      #ifdef ENABLE_GPU
        std::unique_ptr<mediapipe::ImageFrame> output_frame;

        // Convert GpuBuffer to ImageFrame.
        MP_RETURN_IF_ERROR(gpu_helper.RunInGlContext(
            [&packet, &output_frame, &gpu_helper]() -> absl::Status {
              auto& gpu_frame = packet.Get<mediapipe::GpuBuffer>();
              auto texture = gpu_helper.CreateSourceTexture(gpu_frame);
              output_frame = absl::make_unique<mediapipe::ImageFrame>(
                  mediapipe::ImageFormatForGpuBufferFormat(gpu_frame.format()),
                  gpu_frame.width(), gpu_frame.height(),
                  mediapipe::ImageFrame::kGlDefaultAlignmentBoundary);
              gpu_helper.BindFramebuffer(texture);
              const auto info = mediapipe::GlTextureInfoForGpuBufferFormat(
                  gpu_frame.format(), 0, gpu_helper.GetGlVersion());
              glReadPixels(0, 0, texture.width(), texture.height(), info.gl_format,
                           info.gl_type, output_frame->MutablePixelData());
              glFlush();
              texture.Release();
              return absl::OkStatus();
            }));

        // Convert back to opencv for display or saving.
        output_frame_mat = mediapipe::formats::MatView(output_frame.get());
        if (output_frame_mat.channels() == 4)
          cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGBA2BGR);
        else
          cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);
      #else
          auto& output_frame = packet.Get<mediapipe::ImageFrame>();

          output_frame_mat = mediapipe::formats::MatView(&output_frame);
          // Convert back to opencv for display or saving.
          cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);
      #endif

      // Only show detections if enabled ( disabled by default )
      if(_show_overlay){
        cv::imshow(kWindowName, output_frame_mat);
      } else {
        cv::imshow(kWindowName, camera_frame_raw);
      }
      // Press any key to exit.
    }
    const int pressed_key = cv::waitKey(5);
    if (pressed_key >= 0 && pressed_key != 255) MCL::stop();

    // This is set here to make sure the first packets are sent so that their message type can be found out.
    // A temporary fix for a problem, might become permanent_graph.
    _load_flag = true; 
  }

  MP_RETURN_IF_ERROR(_graph->CloseInputStream(kInputStream));
  return _graph->WaitUntilDone();
}

bool MCL::get_camera() {
  return _show_camera;
}
void MCL::set_camera(bool x) {
  if(_show_camera && !x){
    cv::destroyAllWindows();
  }
  _show_camera = x;
}

bool MCL::get_overlay(){
  return _show_overlay;
}
void MCL::set_overlay(bool x){
  _show_overlay = x;
}

bool MCL::get_gpu(){
  return _enable_gpu;
}
void MCL::set_gpu(bool x){
  _enable_gpu = x;
}

void MCL::set_camera_props(int cam_id, int cam_resx, int cam_resy, int cam_fps){
  _cam_id = cam_id;
  _cam_resx = cam_resx;
  _cam_resy = cam_resy;
  _cam_fps = cam_fps;
}

bool MCL::is_loaded(){
  return _load_flag;
}

void MCL::start(const char* filename){
  _graph_filename = filename;
  _load_flag = false;
  _worker = std::make_unique<std::thread>([this]() { this->_workerThread(); });
}


void MCL::_workerThread(){
  LOG(INFO) << "Enter WorkerThread";
	// RUN
	try
	{
		auto status = this->_runMPPGraph();
		if (!status.ok())
		{
			std::string msg(status.message());
			LOG(ERROR) << (msg);
		}
	}
	catch (const std::exception& ex)
	{
    std::cout << ex.what() << std::endl;
	}
	// SHUTDOWN
	try
	{
		_shutMPPGraph();
	}
	catch (const std::exception& ex)
	{
    std::cout << ex.what() << std::endl;
	}
}

void MCL::_shutMPPGraph()
{
	_graph.reset();
	_observers.clear();

	if (_show_camera)
		cv::destroyAllWindows();
}

void MCL::stop(){
  _run_flag = false;
  if(_worker){
    _worker->join();
    _worker.reset();
  }
}

std::shared_ptr<IObserver> MCL::create_observer(const char* stream_name){
  std::shared_ptr<Observer> observer = std::make_unique<Observer>(stream_name);
	_observers.emplace_back(observer);
	return observer;
}

IMCL* CreateMCL(){
    return new MCL();
}

} // namespace mcl

void hello() {
  printf("Hello World!");
}