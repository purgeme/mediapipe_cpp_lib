# MediapipeModule_library

This project provides a C++ dynamic library which allows use of mediapipe solutions in any other C++ project.

The primary purpose of this project was to create a mediapipe module for the Godot engine but it can be used in any C++ project as demonstrated in demo.
Mediapipe module for Godot: https://github.com/purgeme/GodotMediapipeModule.

For now GPU graphs are not supported on Windows as mediapipe for windows does not support GPU yet.

## Supported mediapipe solutions and graphs:

-   Holistic Tracking

-   Hand Tracking

-   Pose Tracking

-   Iris Tracking

-   Face Detection

-   Face Mesh

-   Selfie Segmentation

-   Hair Segmentation


## Getting started:

### Dependencies:

- Python ( to run the scripts )

- Setup mediapipe dependencies: https://google.github.io/mediapipe/getting_started/install.html

### Building library:

#### Step 1: Clone repo and update submodules:

Clone the repo:

`git clone --recurse-submodules https://github.com/purgeme/mediapipe_cpp_lib.git`

If you have cloned without `--recursive-submodules`, make sure to update the submodules:

`git submodule init`

`git submodule update`

#### Step 2: Run setup.py.

Applies patch to mediapipe, replaces file where required and copies library source code.

#### Step 3: Run build.py.

Builds the library and copies it to library folder and puts files required to be imported into C++ project in import_files directory

*The requirement of files from mediapipe to be imported in c++ project could be removed in the future, this would make using this library more straight forward and easy but might cost some performance.*

#### Step 4: Download models and extract graph files

Run `download_models.py` and `extract_graphs.py` to download model and graph files in `mediapipe_models` and `mediapipe_graphs` directories respectively.

### Using library:
 
#### Import and copy files

The library uses model files from mediapipe_models folder so it should be present in the parent folder from where gmod_api.h is being used.

To use the library in any C++ project, add the library to system or add path of library to LD_LIBRARY_PATH environment variable. Also, copy and import gmod_api.h, this provides all functions exposed in the library.

To get the landmarks from from the raw data, they need to be casted to NormalizedLandmarkList, that is their data type as shown in demo file, this is derived from landmark.pb.h from mediapipe.

*This was done for performance reasons as otherwise it would require copying all data to a C++ array in the library. If a non-copy method is found, it can be used.*

Mediapipe does not provide this file directly as it is generated after compilation. These files are automatically copied after compilling the library into `import_files` directory.
Since these files were compiled by mediapipe with protobuf version 3.19.1, make sure you have the same version installed on system or download it and add it to include directories while compiling your project.

Download link: https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protobuf-cpp-3.19.1.zip

#### Code:

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
Here is where you can do what you want with data from the graphs.

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
test->start("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");
```

To stop tracking properly:

```c++
test->stop();
```

For now, the exposed functions can be seen in godot/gmod_api.h.

***

If you wish to use the graphs that return images, add an output stream with whatever name, this will carry the output as a cv::Mat as by default the image outputs are mediapipe::ImageFrame. Then add a node with the calculator ImageFrameToOpenCVMatCalculator, this takes in the ImageFrame and outputs a Mat.

## Refs

https://github.com/homuler/MediaPipeUnityPlugin/

https://mediapipe.dev/

https://github.com/wongfei/ue4-mediapipe-plugin

https://github.com/wongfei/mediapipe/tree/unreal
