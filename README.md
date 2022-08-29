# MediapipeModule_library

This project provides a C++ dynamic library which allows use of mediapipe solutions in any other C++ project.

The primary purpose of this project was to create a mediapipe module for the Godot engine but it can be used in any C++ project as demonstrated in demo.
Mediapipe module for Godot: https://github.com/purgeme/GodotMediapipeModule.

## Getting started:

### Step 1: Run setup.sh.

This downloads mediapipe and sets it up to build the library.

*Note: Some changes are made to paths of models so other mediapipe projects can be built in the downloaded repo but they won't be able to run directly due to changed model paths.*

### Step 2: Run build.sh.

Builds the library and copies it to library folder and puts files required to be imported into C++ project in import_files directory

### Step 3: Download models and extract graph files

Run `download_models.sh` and `extract_graphs.sh` to download model and graph files in `mediapipe_models` and `mediapipe_graphs` directories respectively.

### Step 4: Import and copy files

The library uses model files from mediapipe_models folder so it should be present in the parent folder from where gmod_api.h is being used.

To use the library in any C++ project, add the library to system or add path of library to LD_LIBRARY_PATH environment variable. Also, copy and import gmod_api.h, this provides all functions exposed in the library.

To get the landmarks from from the raw data, they need to be casted to NormalizedLandmarkList, that is their data type as shown in demo file, this is derived from landmark.pb.h from mediapipe.

*This was done for performance reasons as otherwise it would require copying all data to a C++ array in the library.*

Mediapipe does not provide this file directly as it is generated after compilation. These files are automatically copied after compilling the library into `import_files` directory.
Since these files were compiled by mediapipe with protobuf version 3.19.1, make sure you have the same version installed on system or download it and add it to include directories while compiling your project.

Download link: https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protobuf-cpp-3.19.1.zip


First we include landmark data type.

```c++
#include "mediapipe/framework/formats/landmark.pb.h"
```

Create IGMOD object. We will use this object to do the rest.

```c++
IGMOD* test = CreateGMOD();
```

Set camera properties.

```c++
test->set_camera_props(1, 640, 480, 30);
test->set_camera(true);
test->set_overlay(false);
```

Create an observer for tracking.

```c++
auto obs = test->create_observer("face_landmarks");
```

Add callback functions. It is important to add callback functions for both presence and packet, even if they are empty.

```c++
obs->SetPresenceCallback([](class IObserver* observer, bool present){});
obs->SetPacketCallback([](class IObserver* observer){ 
    const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
    size_t message_type = observer->GetMessageType(); 
    std::cout << typeid(message_type).name() << std::endl;
    std::cout << data->landmark(0).x() << " ; " << message_type << std::endl; 
});
```

Start tracking. Here provide the graph file for tracking.

```c++
test->start("mediapipe_graphs/holistic_tracking_cpu.pbtxt");
```

To stop tracking properly:

```c++
test->stop();
```

For now, the exposed functions can be seen in godot/gmod_api.h.