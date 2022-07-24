#!/bin/bash

# Get the mediapipe library
echo "Cloning mediapipe repo..."
git clone https://github.com/google/mediapipe.git

# Setup for opencv4
echo "Setting up opencv 4.x..."
sed -i 's/#"include\/opencv4/"include\/opencv4/g' mediapipe/third_party/opencv_linux.BUILD

# Edit the required files
echo "Editing paths for models..."

cd ./mediapipe
path=$(pwd)
cd ./mediapipe/modules/
folders=$(find ./ -maxdepth 1 -type d | tail -n +2)
nfolders=$(find ./ -maxdepth 1 -type d | tail -n +2 | wc -l)
for d in $folders; do
    cd $d
    files=$(find ./ -name "*.pbtxt")
    nfiles=$(find ./ -name "*.pbtxt" | wc -l)
    for f in $files; do
        test=$(grep 'model_path: "mediapipe' $f)
        if [ "$test" != "" ]; then
            sed -n 's/model_path: "mediapipe/model_path: "..\/mediapipe/gi' $f
        fi
    done
    cd ..;
done

cd ../../../

# Copy the project files
echo "Copying project files..."
cp -r godot mediapipe/mediapipe/godot