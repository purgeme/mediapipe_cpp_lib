#include<iostream>
#include<functional>
#include<typeinfo>

#include "gmod_api.h"
#include "mediapipe/framework/formats/landmark.pb.h"

int main(){

    IGMOD* test = CreateGMOD();

    test->set_camera_props(0, 640, 480, 30);
    test->set_camera(true);
    test->set_overlay(true);

    auto obs = test->create_observer("face_landmarks");
    obs->SetPresenceCallback([](class IObserver* observer, bool present){});
    obs->SetPacketCallback([](class IObserver* observer){ 
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        std::string message_type = observer->GetMessageType(); 
        std::cout << message_type << std::endl;
        std::cout << data->landmark(0).x() << std::endl; 
    });

    test->start("/home/purg3me/Projects/MediapipeModule/MediapipeModule_module/MediapipeModule_library/mediapipe/mediapipe/graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");

    while(true){
    }
    return 0;
}