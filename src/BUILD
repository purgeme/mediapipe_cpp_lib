licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])

cc_binary(
    name = "gmod",
    srcs = ["gmod_core.cc", "gmod_core.h", "gmod_api.h"],
    deps = [
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",

        "//mediapipe/gpu:gl_calculator_helper",
        "//mediapipe/gpu:gpu_buffer",
        "//mediapipe/gpu:gpu_shared_data_internal",
        "//mediapipe/gpu:gpu_buffer_to_image_frame_calculator",
        "//mediapipe/gpu:image_frame_to_gpu_buffer_calculator",

        "//mediapipe/calculators/core:constant_side_packet_calculator",
        "//mediapipe/calculators/core:packet_presence_calculator",
        "//mediapipe/calculators/core:pass_through_calculator",
        "//mediapipe/calculators/core:split_vector_calculator",
        "//mediapipe/calculators/core:flow_limiter_calculator",
        "//mediapipe/calculators/core:gate_calculator",
        "//mediapipe/calculators/core:merge_calculator",
        "//mediapipe/calculators/core:immediate_mux_calculator",
        "//mediapipe/calculators/core:packet_inner_join_calculator",
        "//mediapipe/calculators/core:previous_loopback_calculator",
        "//mediapipe/calculators/util:annotation_overlay_calculator",
        "//mediapipe/calculators/util:detections_to_render_data_calculator",
        "//mediapipe/calculators/image:image_file_properties_calculator",
        "//mediapipe/calculators/image:opencv_encoded_image_to_image_frame_calculator",
        "//mediapipe/calculators/image:opencv_image_encoder_calculator",
        "//mediapipe/calculators/video:opencv_video_decoder_calculator",
        "//mediapipe/calculators/video:opencv_video_encoder_calculator",

        "//mediapipe/framework:calculator_framework",

        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/formats:landmark_cc_proto",

        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/port:logging",
        "//mediapipe/framework/port:map_util",

        "//mediapipe/graphs/face_detection:face_detection_full_range_desktop_live_deps",
        "//mediapipe/graphs/face_detection:desktop_live_calculators",
        "//mediapipe/graphs/face_detection:desktop_live_gpu_calculators",

        "//mediapipe/graphs/face_mesh:desktop_calculators",
        "//mediapipe/graphs/face_mesh:desktop_live_calculators",
        "//mediapipe/graphs/face_mesh:desktop_live_gpu_calculators",
        "//mediapipe/modules/face_detection:face_detection_full_range_cpu",
        "//mediapipe/modules/face_detection:face_detection_full_range_gpu",

        "//mediapipe/graphs/pose_tracking:pose_tracking_cpu_deps",
        "//mediapipe/graphs/pose_tracking:pose_tracking_gpu_deps",

        "//mediapipe/graphs/iris_tracking/calculators:update_face_landmarks_calculator",
        "//mediapipe/graphs/iris_tracking/subgraphs:iris_and_depth_renderer_cpu",
        "//mediapipe/graphs/iris_tracking:iris_depth_cpu_deps",
        "//mediapipe/graphs/iris_tracking:iris_tracking_cpu_video_input_deps",
        "//mediapipe/graphs/iris_tracking:iris_tracking_cpu_deps",
        "//mediapipe/graphs/iris_tracking:iris_tracking_gpu_deps",

        "//mediapipe/graphs/selfie_segmentation:selfie_segmentation_cpu_deps",
        "//mediapipe/graphs/selfie_segmentation:selfie_segmentation_gpu_deps",

        "//mediapipe/graphs/hair_segmentation:mobile_calculators",
        "//mediapipe/graphs/hair_segmentation:desktop_calculators",

        "//mediapipe/graphs/holistic_tracking:holistic_tracking_cpu_graph_deps",
        "//mediapipe/graphs/holistic_tracking:holistic_tracking_gpu_deps",

        "//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
        "//mediapipe/modules/hand_landmark:hand_landmark_tracking_gpu",

        ":test_calculator",
    ],
    linkshared = True,
)

cc_library(
    name = "test_calculator",
    srcs = ["test_calculator.cc"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame_opencv",
    ],
    alwayslink = 1,
)