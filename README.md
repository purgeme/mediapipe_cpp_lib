# MediapipeModule_library

This project creates a shared object library to use with mediapipe module for Godot.
Though since it is just a library, it can be used with any program like Unreal engine too.

## Getting started:

Step 1: Run setup.sh.

This downloads mediapipe and sets it up to build the library.

`Note: Some changes are made to paths of models so other mediapipe projects can be built in the downloaded repo but they won't be able to run directly.`

Step 2: Run build.sh.

Builds the library and copies it to library folder.

That's it.

For now, the exposed functions can be seen in godot/gmod_api.h.

The demo folder contains a demo cpp file.

Notes:

To run any program using the library in the parent directory of the project i.e. one directory above, you must have the mediapipe repo cloned so the library can access the machine learning models from it, for now the paths are hard coded in the patch. If you are familier with mediapipe, you are welcome to change them.

To get the landmarks from from the raw data, they need to be casted to NormalizedLandmarkList, that is their data type as shown in demo file, this is derived from landmark.pb.h from mediapipe. Mediapipe does not provide this file directly as it is generated after compilation, for now these files are provided in the mediapipe folder inside demo.
Since these files were compiled by mediapipe with protobuf version 3.19.1, make sure you have the same version installed on system or download it and include it include directories.