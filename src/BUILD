licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])

cc_binary(
    name = "mcl",
    srcs = ["mcl_api.h", "mcl_core.cc", "mcl_core.h", "mcl_basic_holistic.cc", "mcl_basic_holistic.h"],
    deps = [
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",

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
        "//mediapipe/util:resource_util",

        ":face_detection_calculators",
        ":face_mesh_calculators",
        ":iris_calculators",
        ":hands_calculators",
        ":pose_calculators",
        ":holistic_calculators",
        # ":selfie_segmentation_calculators",
        # ":hair_segmentation_calculators",
        # ":object_detection_calculators",
        # ":box_tracking_calculators",
        # ":instant_motion_tracking_calculators",
        # ":objectron_calculators",

        ":ImageFrameToMatCalculator",

    ] + select({
        "//mediapipe/gpu:disable_gpu": [],
        "//conditions:default": [
            "//mediapipe/gpu:gl_calculator_helper",
            "//mediapipe/gpu:gpu_buffer",
            "//mediapipe/gpu:gpu_shared_data_internal",
            "//mediapipe/gpu:gpu_buffer_to_image_frame_calculator",
            "//mediapipe/gpu:image_frame_to_gpu_buffer_calculator",
        ],
    }),
    copts = select({
        "//mediapipe/gpu:disable_gpu": [],
        "//conditions:default": [
            "-D ENABLE_GPU",
        ],
    }),
    linkopts = ["-Wl,-soname,libmcl.so"],
    linkshared = True,
)

cc_library(
    name = "ImageFrameToMatCalculator",
    srcs = ["ImageFrameToMatCalculator.cc"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame_opencv",
    ],
    alwayslink = 1,
)

cc_library(
    name = "face_detection_calculators",
    deps = [
        "//mediapipe/framework/tool:switch_mux_calculator",
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/face_detection:desktop_live_calculators",
            "//mediapipe/graphs/face_detection:face_detection_full_range_desktop_live_deps",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/face_detection:desktop_live_gpu_calculators",
            "//mediapipe/graphs/face_detection:face_detection_full_range_mobile_gpu_deps",
        ],
    }),
)

cc_library(
    name = "face_mesh_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/face_mesh:desktop_live_calculators",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/face_mesh:desktop_live_gpu_calculators",
        ],
    }),
)

cc_library(
    name = "iris_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/modules/iris_landmark:iris_landmark_cpu",
            "//mediapipe/graphs/iris_tracking:iris_tracking_cpu_deps",
        ],
        "//conditions:default": [
            "//mediapipe/modules/iris_landmark:iris_landmark_gpu",
            "//mediapipe/graphs/iris_tracking:iris_tracking_gpu_deps",
        ],
    }),
)

cc_library(
    name = "hands_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/hand_tracking:mobile_calculators",
        ],
    }),
)

cc_library(
    name = "pose_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/pose_tracking:pose_tracking_cpu_deps",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/pose_tracking:pose_tracking_gpu_deps",
        ],
    }),
)

cc_library(
    name = "holistic_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/holistic_tracking:holistic_tracking_cpu_graph_deps",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/holistic_tracking:holistic_tracking_gpu_deps",
        ],
    }),
)

cc_library(
    name = "selfie_segmentation_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/selfie_segmentation:selfie_segmentation_cpu_deps",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/selfie_segmentation:selfie_segmentation_gpu_deps",
        ],
    }),
)

cc_library(
    name = "hair_segmentation_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/hair_segmentation:desktop_calculators",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/hair_segmentation:mobile_calculators",
        ],
    }),
)

cc_library(
    name = "object_detection_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/object_detection:desktop_tflite_calculators",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/object_detection:mobile_calculators",
        ],
    }),
)

cc_library(
    name = "box_tracking_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/tracking:desktop_calculators",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/tracking:mobile_calculators",
        ],
    }),
)

cc_library(
    name = "instant_motion_tracking_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/instant_motion_tracking/subgraphs:region_tracking_cpu",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/instant_motion_tracking:instant_motion_tracking_deps",
        ],
    }),
)

cc_library(
    name = "objectron_calculators",
    deps = [
    ] + select({
        "//mediapipe/gpu:disable_gpu": [
            "//mediapipe/graphs/object_detection_3d:desktop_cpu_calculators",
        ],
        "//conditions:default": [
            "//mediapipe/graphs/object_detection_3d:mobile_calculators",
        ],
    }),
)
