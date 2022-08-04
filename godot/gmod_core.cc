#include <cstdlib>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"

#include "mediapipe/framework/formats/landmark.pb.h"

#include "gmod_core.h"

const int face_landmarks_count = 468;

absl::Status GMOD::_runMPPGraph() {

  constexpr char kInputStream[] = "input_video";
  constexpr char kOutputStream[] = "output_video";
  constexpr char kWindowName[] = "MediaPipe";

  std::string calculator_graph_config_contents;
  MP_RETURN_IF_ERROR(mediapipe::file::GetContents(
      _graph_filename,
      &calculator_graph_config_contents));

  LOG(INFO) << "Get calculator graph config contents: "
            << calculator_graph_config_contents;

  mediapipe::CalculatorGraphConfig config =
      mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
          calculator_graph_config_contents);

  LOG(INFO) << "Initialize the calculator graph.";
  _graph.reset(new mediapipe::CalculatorGraph());
  MP_RETURN_IF_ERROR(_graph->Initialize(config));

  for (auto& iter : _observers)
	{
    std::cout << _graph << std::endl;
		RET_CHECK_OK(iter->AddOutputStream(_graph));
	}

  LOG(INFO) << "Initialize the camera";
  cv::VideoCapture capture;
  capture.open(_cam_id);
  RET_CHECK(capture.isOpened());

  cv::namedWindow(kWindowName, /*flags=WINDOW_AUTOSIZE*/ 1);
#if (CV_MAJOR_VERSION >= 3) && (CV_MINOR_VERSION >= 2)
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    capture.set(cv::CAP_PROP_FPS, 30);
#endif

  LOG(INFO) << "Start running the calculator graph.";

  std::unique_ptr<mediapipe::OutputStreamPoller> output_poller;
	auto output_poller_sop = _graph->AddOutputStreamPoller(kOutputStream);
	RET_CHECK(output_poller_sop.ok());
	output_poller = std::make_unique<mediapipe::OutputStreamPoller>(std::move(output_poller_sop.value()));

  MP_RETURN_IF_ERROR(_graph->StartRun({}));

  LOG(INFO) << "Start grabbing and processing frames.";

  while (_run_flag) {

    // Capture opencv camera or video frame.
    cv::Mat camera_frame_raw;
    capture >> camera_frame_raw;

    cv::Mat camera_frame;
    cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);

    cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);

    // Wrap Mat into an ImageFrame.
    auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
        mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
        mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
    camera_frame.copyTo(input_frame_mat);

    // Send image packet into the graph.
    size_t frame_timestamp_us =
        (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;
    MP_RETURN_IF_ERROR(_graph->AddPacketToInputStream(
        kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us))));

    // Get the graph result packet, or stop if that fails.
    mediapipe::Packet packet;

    if (!output_poller->Next(&packet)) break;
    // poller.Next(&packet);

    // Only show camera output if enabled ( disabled by default )
    if(_show_camera){
      auto& output_frame = packet.Get<mediapipe::ImageFrame>();

      // Convert back to opencv for display or saving.
      cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
      cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

      // Only show detections if enabled ( disabled by default )
      if(_show_overlay){
        cv::imshow(kWindowName, output_frame_mat);
      } else {
        cv::imshow(kWindowName, camera_frame_raw);
      }
      // Press any key to exit.
    }
    const int pressed_key = cv::waitKey(5);
    if (pressed_key >= 0 && pressed_key != 255) _run_flag = false;
  }

  MP_RETURN_IF_ERROR(_graph->CloseInputStream(kInputStream));
  return _graph->WaitUntilDone();
}

bool GMOD::get_camera() {
  return _show_camera;
}
void GMOD::set_camera(bool x) {
  if(_show_camera && !x){
    cv::destroyAllWindows();
  }
  _show_camera = x;
}

bool GMOD::get_overlay(){
  return _show_overlay;
}
void GMOD::set_overlay(bool x){
  _show_overlay = x;
}

void GMOD::set_camera_props(int cam_id, int cam_resx, int cam_resy, int cam_fps){
  _cam_id = cam_id;
  _cam_resx = cam_resx;
  _cam_resy = cam_resy;
  _cam_fps = cam_fps;
}

void GMOD::start(const char* filename){
  _graph_filename = filename;
  _run_flag = true;
  _worker = std::make_unique<std::thread>([this]() { this->_workerThread(); });
}

IObserver* GMOD::create_observer(const char* stream_name){
  auto* observer = new Observer(stream_name);
	// observer->AddRef();
	_observers.emplace_back(observer);
	return observer;
}

void GMOD::_workerThread(){
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

void GMOD::_shutMPPGraph()
{
	// log_i("UmpPipeline::Shutdown");

	_graph.reset();
	_observers.clear();

	if (_show_camera)
		cv::destroyAllWindows();

	// ReleaseFramePool();

	// log_i("UmpPipeline::Shutdown OK");
}

void GMOD::stop(){
  _run_flag = false;
  if(_worker){
    _worker->join();
    _worker.reset();
  }
}

void hello() {
  printf("Hello World!");
}

IGMOD* CreateGMOD(){
    return new GMOD();
}