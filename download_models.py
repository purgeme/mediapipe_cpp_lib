#!/usr/bin/python
import os
import sys
import requests

tflite_names = [
    ### [Face Detection](https://google.github.io/mediapipe/solutions/face_detection
    "face_detection_short_range.tflite",
    "face_detection_full_range.tflite",
    "face_detection_full_range_sparse.tflite",
    ### [Face Mesh](https://google.github.io/mediapipe/solutions/face_mesh

    "face_landmark.tflite",
    "face_landmark_with_attention.tflite",

    ### [Iris](https://google.github.io/mediapipe/solutions/iris
    "iris_landmark.tflite",

    ### [Hands](https://google.github.io/mediapipe/solutions/hands
    "palm_detection_lite.tflite",
    "palm_detection_full.tflite",
    "hand_landmark_lite.tflite",
    "hand_landmark_full.tflite",

    ### [Pose](https://google.github.io/mediapipe/solutions/pose
    "pose_detection.tflite",
    "pose_landmark_lite.tflite",
    "pose_landmark_full.tflite",
    "pose_landmark_heavy.tflite",
    ### [Holistic](https://google.github.io/mediapipe/solutions/holistic
    "hand_recrop.tflite",

    ### [Selfie Segmentation](https://google.github.io/mediapipe/solutions/selfie_segmentation
    "selfie_segmentation.tflite",
    "selfie_segmentation_landscape.tflite",

    ### [Hair Segmentation](https://google.github.io/mediapipe/solutions/hair_segmentation
    "hair_segmentation.tflite",

    ### [Object Detection](https://google.github.io/mediapipe/solutions/object_detection
    "ssdlite_object_detection.tflite",

    ### [Objectron](https://google.github.io/mediapipe/solutions/objectron
    "object_detection_3d_sneakers.tflite",
    "object_detection_3d_chair.tflite",
    "object_detection_3d_camera.tflite",
    "object_detection_3d_cup.tflite",
    "object_detection_3d_sneakers_1stage.tflite",
    "object_detection_3d_chair_1stage.tflite",

    ### [KNIFT](https://google.github.io/mediapipe/solutions/knift
    "knift_float.tflite",
    "knift_float_400.tflite",
    "knift_float_1k.tflite"
]

txt_names = {
    ### [Hands](https://google.github.io/mediapipe/solutions/hands
    "handedness.txt" : "https://raw.githubusercontent.com/google/mediapipe/master/mediapipe/modules/hand_landmark/handedness.txt",

    ### [Objectron](https://google.github.io/mediapipe/solutions/objectron
    "object_detection_oidv4_labelmap.txt" : "https://raw.githubusercontent.com/google/mediapipe/master/mediapipe/modules/objectron/object_detection_oidv4_labelmap.txt"
}

current_dir = os.path.dirname(__file__)

mediapipe_models_dir = os.path.join(current_dir, "mediapipe_models")

if os.path.isdir(mediapipe_models_dir) == False:
    os.mkdir(mediapipe_models_dir)
os.chdir(mediapipe_models_dir)

print("##########")
print("Downloading tflite models...\n")

for name in tflite_names:
    if os.path.isfile(name) == True:
        print("File already exists:" + " " + name)
    else:
        print("Downloading: "+name)
        response = requests.get("https://storage.googleapis.com/mediapipe-assets/"+name)
        with open(name, "wb") as f:
            f.write(response.content)
print("##########")

print("\n##########")
print("Downloading txt files...\n")
for name in txt_names:
    if os.path.isfile(name) == True:
        print("File already exists:" + " " + name)
    else:
        print("Downloading: "+name)
        response = requests.get(txt_names[name])
        with open(name, "wb") as f:
            f.write(response.content)
print("##########")