#!/bin/bash

# Get the mediapipe library
echo "Cloning mediapipe repo..."
git clone https://github.com/google/mediapipe.git

# Apply patch
cd mediapipe
git am ../0001-mediapipe_module.patch
cd ..

# Copy the project files
echo "Copying project files..."
cp -r godot mediapipe/mediapipe/godot