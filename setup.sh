#!/bin/bash

# Get the mediapipe library
echo "Cloning mediapipe repo..."
git clone https://github.com/google/mediapipe.git

# Apply patch
cd mediapipe
git am ../patch/0001-mediapipe_module.patch
cd ..

# Copy the project files
mkdir mediapipe/cpp_library/
echo "Copying project files..."
\cp -r src/* mediapipe/cpp_library/

# Copy packet.h file ( to be moved to patch file)
mv mediapipe/mediapipe/framework/packet.h mediapipe/mediapipe/framework/packet.h.old
cp patch/packet.h mediapipe/mediapipe/framework/packet.h