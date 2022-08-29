#!/bin/bash

# Build the library
echo "Building library..."
echo ""
cd mediapipe
bazel build -c opt --define DISASBLE_MEDIAPIPE_GPU=1 godot:gmod

# Copying library
cd ..
mkdir library
cp mediapipe/bazel-bin/godot/libgmod.so library/

# Copy import files
mkdir import_files
cp -r mediapipe/bazel-bin/mediapipe import_files/