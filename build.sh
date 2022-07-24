#!/bin/bash

# Build the library
echo "Building library..."
echo ""
cd mediapipe
bazel build -c opt --define DISASBLE_MEDIAPIPE_GPU=1 mediapipe/godot:gmod

# Copying library
cd ..
mkdir library
cp mediapipe/bazel-bin/mediapipe/godot/libgmod.so library/