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

For now, the exposed functions can be seen in godot/gmod_core.h. Documentation will be added when more functionality is added.
