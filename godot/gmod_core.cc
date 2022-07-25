// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// An example of sending OpenCV webcam frames into a MediaPipe graph.
#include <cstdlib>
#include <string>

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

int face_landmarks_count = 468;
int hand_right_landmarks_count = 21;
int hand_left_landmarks_count = 21;
int pose_landmarks_count = 33;

// Variables to share data
double** face_landmarks = new double*[face_landmarks_count];
double** hand_right_landmarks = new double*[hand_right_landmarks_count];
double** hand_left_landmarks = new double*[hand_left_landmarks_count];
double** pose_landmarks = new double*[pose_landmarks_count];

bool grab_frames = false;
bool show_camera = false;
bool show_detection = false;

bool enable_face = false;
bool enable_hand_right = false;
bool enable_hand_left = false;
bool enable_pose = false;

std::string graph_name;

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "output_video";
constexpr char kWindowName[] = "MediaPipe";

absl::Status RunMPPGraph() {
  std::string calculator_graph_config_contents;
  MP_RETURN_IF_ERROR(mediapipe::file::GetContents(
      graph_name,
      &calculator_graph_config_contents));
  LOG(INFO) << "Get calculator graph config contents: "
            << calculator_graph_config_contents;
  mediapipe::CalculatorGraphConfig config =
      mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
          calculator_graph_config_contents);

  LOG(INFO) << "Initialize the calculator graph.";
  mediapipe::CalculatorGraph graph;
  MP_RETURN_IF_ERROR(graph.Initialize(config));

  LOG(INFO) << "Initialize the camera";
  cv::VideoCapture capture;
  capture.open(0);
  RET_CHECK(capture.isOpened());

  cv::namedWindow(kWindowName, /*flags=WINDOW_AUTOSIZE*/ 1);
#if (CV_MAJOR_VERSION >= 3) && (CV_MINOR_VERSION >= 2)
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    capture.set(cv::CAP_PROP_FPS, 30);
#endif

  LOG(INFO) << "Start running the calculator graph.";
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller,
                   graph.AddOutputStreamPoller(kOutputStream));

  // Added streampoller for Stream Detection
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller face_detection_poller,
                   graph.AddOutputStreamPoller("face_landmarks"));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller face_presence_poller,
                 graph.AddOutputStreamPoller("face_landmark_presence"));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller hand_right_detection_poller,
                   graph.AddOutputStreamPoller("hand_right_landmarks"));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller hand_right_presence_poller,
                 graph.AddOutputStreamPoller("hand_right_landmark_presence"));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller hand_left_detection_poller,
                   graph.AddOutputStreamPoller("hand_left_landmarks"));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller hand_left_presence_poller,
                 graph.AddOutputStreamPoller("hand_left_landmark_presence"));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller pose_detection_poller,
                   graph.AddOutputStreamPoller("pose_landmarks"));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller pose_presence_poller,
                 graph.AddOutputStreamPoller("pose_landmark_presence"));

  MP_RETURN_IF_ERROR(graph.StartRun({}));

  LOG(INFO) << "Start grabbing and processing frames.";
  grab_frames = true;
  bool load_video = false;
  while (grab_frames) {
    // Capture opencv camera or video frame.
    cv::Mat camera_frame_raw;
    capture >> camera_frame_raw;

    LOG(INFO) << "Ignore empty frames from camera.";

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
    MP_RETURN_IF_ERROR(graph.AddPacketToInputStream(
        kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us))));

    // Get the graph result packet, or stop if that fails.
    mediapipe::Packet packet;
    mediapipe::Packet presence_packet;
    mediapipe::Packet detection_packet;

    if (!poller.Next(&packet)) break;

    if(enable_face){
      // Check if landmark is present or not
      if (!face_presence_poller.Next(&presence_packet)) break;
      auto is_landmark_present = presence_packet.Get<bool>();
      // Only get detection packets if landmark is detected, otherwise program crashes
      if (is_landmark_present) {
        if (!face_detection_poller.Next(&detection_packet)) break;
        auto& output_detections = detection_packet.Get<mediapipe::NormalizedLandmarkList>();
        for ( int i=0; i < face_landmarks_count; ++i){
          const mediapipe::NormalizedLandmark& landmark = output_detections.landmark(i);
          face_landmarks[i] = new double[3];
          face_landmarks[i][0] = landmark.x();
          face_landmarks[i][1] = landmark.y();
          face_landmarks[i][2] = landmark.z();
        }
      }
    }
    if(enable_hand_right){
      // Check if landmark is present or not
      if (!hand_right_presence_poller.Next(&presence_packet)) break;
      auto is_landmark_present = presence_packet.Get<bool>();
      // Only get detection packets if landmark is detected, otherwise program crashes
      if (is_landmark_present) {
        if (!hand_right_detection_poller.Next(&detection_packet)) break;
        auto& output_detections = detection_packet.Get<mediapipe::NormalizedLandmarkList>();
        for ( int i=0; i < hand_right_landmarks_count; ++i){
          const mediapipe::NormalizedLandmark& landmark = output_detections.landmark(i);
          hand_right_landmarks[i] = new double[3];
          hand_right_landmarks[i][0] = landmark.x();
          hand_right_landmarks[i][1] = landmark.y();
          hand_right_landmarks[i][2] = landmark.z();
        }
      }
    }
    if(enable_hand_left){
      // Check if landmark is present or not
      if (!hand_left_presence_poller.Next(&presence_packet)) break;
      auto is_landmark_present = presence_packet.Get<bool>();
      // Only get detection packets if landmark is detected, otherwise program crashes
      if (is_landmark_present) {
        if (!hand_left_detection_poller.Next(&detection_packet)) break;
        auto& output_detections = detection_packet.Get<mediapipe::NormalizedLandmarkList>();
        for ( int i=0; i < hand_left_landmarks_count; ++i){
          const mediapipe::NormalizedLandmark& landmark = output_detections.landmark(i);
          hand_left_landmarks[i] = new double[3];
          hand_left_landmarks[i][0] = landmark.x();
          hand_left_landmarks[i][1] = landmark.y();
          hand_left_landmarks[i][2] = landmark.z();
        }
      }
    }
    if(enable_pose){
      // Check if landmark is present or not
      if (!pose_presence_poller.Next(&presence_packet)) break;
      auto is_landmark_present = presence_packet.Get<bool>();
      // Only get detection packets if landmark is detected, otherwise program crashes
      if (is_landmark_present) {
        if (!pose_detection_poller.Next(&detection_packet)) break;
        auto& output_detections = detection_packet.Get<mediapipe::NormalizedLandmarkList>();
        for ( int i=0; i < pose_landmarks_count; ++i){
          const mediapipe::NormalizedLandmark& landmark = output_detections.landmark(i);
          pose_landmarks[i] = new double[3];
          pose_landmarks[i][0] = landmark.x();
          pose_landmarks[i][1] = landmark.y();
          pose_landmarks[i][2] = landmark.z();
        }
      }
    }

    // Only show camera output if enabled ( disabled by default )
    if(show_camera){
      auto& output_frame = packet.Get<mediapipe::ImageFrame>();

      // Convert back to opencv for display or saving.
      cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
      cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

      // Only show detections if enabled ( disabled by default )
      if(show_detection){
        cv::imshow(kWindowName, output_frame_mat);
      } else {
        cv::imshow(kWindowName, input_frame_mat);
      }
      // Press any key to exit.
      const int pressed_key = cv::waitKey(5);
      if (pressed_key >= 0 && pressed_key != 255) grab_frames = false;
    }
  }

  LOG(INFO) << "Shutting down.";
  MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
  return graph.WaitUntilDone();
}

double ** return_face_trackers(){
  return face_landmarks;
}
double ** return_hand_right_trackers(){
  return hand_right_landmarks;
}
double ** return_hand_left_trackers(){
  return hand_left_landmarks;
}
double ** return_pose_trackers(){
  return pose_landmarks;
}

void toggle_face(bool x){
  enable_face = x;
}
void toggle_hand_right(bool x){
  enable_hand_right = x;
}
void toggle_hand_left(bool x){
  enable_hand_left = x;
}
void toggle_pose(bool x){
  enable_pose = x;
}
void toggle_camera(bool x){
  if(show_camera && !x){
    cv::destroyAllWindows();
  }
  show_camera = x;
}
void toggle_detection(bool x){
  show_detection = x;
}

int start(const char* filename){
  LOG(INFO) << "Running the graph";
  graph_name = filename;
  absl::Status run_status = RunMPPGraph();
  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
    return EXIT_FAILURE;
  } else {
    LOG(INFO) << "Success!";
  }
  return EXIT_SUCCESS;
}

void stop(){
  grab_frames = false;
}

void hello() {
  printf("Hello World!");
}