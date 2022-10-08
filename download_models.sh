#! /bin/bash
# Download mediapipe models from github and place them in mediapipe_models directory.
# This can also be used to update to new models as they come with bettery accuracy or such without recompiling the whole library.

mkdir mediapipe_models
cd  mediapipe_models

https://storage.googleapis.com/mediapipe-assets/face_detection_short_range.tflite

mkdir face_detection
cd face_detection
### [Face Detection](https://google.github.io/mediapipe/solutions/face_detection
wget https://storage.googleapis.com/mediapipe-assets/face_detection_short_range.tflite
wget https://storage.googleapis.com/mediapipe-assets/face_detection_full_range.tflite
wget https://storage.googleapis.com/mediapipe-assets/face_detection_full_range_sparse.tflite
cd ..

mkdir face_landmark
cd face_landmark
### [Face Mesh](https://google.github.io/mediapipe/solutions/face_mesh
wget https://storage.googleapis.com/mediapipe-assets/face_landmark.tflite
wget https://storage.googleapis.com/mediapipe-assets/face_landmark_with_attention.tflite
cd ..

mkdir iris_landmark
cd iris_landmark
### [Iris](https://google.github.io/mediapipe/solutions/iris
wget https://storage.googleapis.com/mediapipe-assets/iris_landmark.tflite
cd ..

mkdir palm_detection
cd palm_detection
### [Hands](https://google.github.io/mediapipe/solutions/hands
wget https://storage.googleapis.com/mediapipe-assets/palm_detection_lite.tflite
wget https://storage.googleapis.com/mediapipe-assets/palm_detection_full.tflite
cd ..
mkdir hand_landmark
cd hand_landmark
wget https://storage.googleapis.com/mediapipe-assets/hand_landmark_lite.tflite
wget https://storage.googleapis.com/mediapipe-assets/hand_landmark_full.tflite
wget https://raw.githubusercontent.com/google/mediapipe/master/mediapipe/modules/hand_landmark/handedness.txt
cd ..

mkdir pose_detection
cd pose_detection
### [Pose](https://google.github.io/mediapipe/solutions/pose
wget https://storage.googleapis.com/mediapipe-assets/pose_detection.tflite
cd ..
mkdir pose_landmark
cd pose_landmark
wget https://storage.googleapis.com/mediapipe-assets/pose_landmark_lite.tflite
wget https://storage.googleapis.com/mediapipe-assets/pose_landmark_full.tflite
wget https://storage.googleapis.com/mediapipe-assets/pose_landmark_heavy.tflite
cd ..

mkdir holistic_landmark
cd holistic_landmark
### [Holistic](https://google.github.io/mediapipe/solutions/holistic
wget https://storage.googleapis.com/mediapipe-assets/hand_recrop.tflite
cd ..

mkdir selfie_segmentation
cd selfie_segmentation
### [Selfie Segmentation](https://google.github.io/mediapipe/solutions/selfie_segmentation
wget https://storage.googleapis.com/mediapipe-assets/selfie_segmentation.tflite
wget https://storage.googleapis.com/mediapipe-assets/selfie_segmentation_landscape.tflite
cd ..

mkdir hair_segmentation
cd hair_segmentation
### [Hair Segmentation](https://google.github.io/mediapipe/solutions/hair_segmentation
wget https://storage.googleapis.com/mediapipe-assets/hair_segmentation.tflite
cd ..

mkdir object_detection
cd object_detection
### [Object Detection](https://google.github.io/mediapipe/solutions/object_detection
wget https://storage.googleapis.com/mediapipe-assets/ssdlite_object_detection.tflite
cd ..

mkdir objectron
cd objectron
### [Objectron](https://google.github.io/mediapipe/solutions/objectron
wget https://storage.googleapis.com/mediapipe-assets/object_detection_3d_sneakers.tflite
wget https://storage.googleapis.com/mediapipe-assets/object_detection_3d_chair.tflite
wget https://storage.googleapis.com/mediapipe-assets/object_detection_3d_camera.tflite
wget https://storage.googleapis.com/mediapipe-assets/object_detection_3d_cup.tflite
wget https://storage.googleapis.com/mediapipe-assets/object_detection_3d_sneakers_1stage.tflite
wget https://storage.googleapis.com/mediapipe-assets/object_detection_3d_chair_1stage.tflite
wget https://raw.githubusercontent.com/google/mediapipe/master/mediapipe/modules/objectron/object_detection_oidv4_labelmap.txt
cd ..

mkdir knift
cd knift
### [KNIFT](https://google.github.io/mediapipe/solutions/knift
wget https://storage.googleapis.com/mediapipe-assets/knift_float.tflite
wget https://storage.googleapis.com/mediapipe-assets/knift_float_400.tflite
wget https://storage.googleapis.com/mediapipe-assets/knift_float_1k.tflite