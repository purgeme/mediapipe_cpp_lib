#!/bin/bash

# Build the library
echo "Building library..."
echo ""
cd mediapipe
bazel build -c opt --define DISASBLE_MEDIAPIPE_GPU=1 cpp_library:gmod

# Copying library
cd ..
mkdir library
cp mediapipe/bazel-bin/cpp_library/libgmod.so library/

# Copy import files
mkdir import_files
cp -r mediapipe/bazel-bin/mediapipe import_files/