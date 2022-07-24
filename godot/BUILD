# Copyright 2019 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])

# cc_binary(
#     name = "gmod",
#     srcs = ["main.cc"],
#     deps = [
#         ":gmod_core",
#     ],
#     # linkopts = ['-static'],    
#     linkshared = True,
# )

# cc_library(
#     name = "gmod_core",
#     srcs = ["gmod_core.cc"],
#     hdrs = ["gmod_core.h"],
#     deps = [
#         "//mediapipe/framework:calculator_framework",
#         "//mediapipe/framework/formats:image_frame",
#         "//mediapipe/framework/formats:image_frame_opencv",
#         "//mediapipe/framework/port:file_helpers",
#         "//mediapipe/framework/port:opencv_highgui",
#         "//mediapipe/framework/port:opencv_imgproc",
#         "//mediapipe/framework/port:opencv_video",
#         "//mediapipe/framework/port:parse_text_proto",
#         "//mediapipe/framework/port:status",
#         "//mediapipe/framework/formats:landmark_cc_proto",
#         "@com_google_absl//absl/flags:flag",
#         "@com_google_absl//absl/flags:parse",

#         "//mediapipe/graphs/holistic_tracking:holistic_tracking_cpu_graph_deps",

#         "//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
#     ],
#     # linkopts = ['-static'],    
#     # linkshared = True,
# )

cc_binary(
    name = "gmod",
    srcs = ["gmod_core.cc", "gmod_core.h"],
    # hdrs = ["gmod_core.h"],
    deps = [
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",

        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",

        "//mediapipe/framework/formats:landmark_cc_proto",

        "//mediapipe/graphs/holistic_tracking:holistic_tracking_cpu_graph_deps",
        "//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
    ],
    # linkopts = ['-static'],    
    linkshared = True,
)