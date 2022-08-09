#include<iostream>
#include<typeinfo>

#include "gmod_api.h"
#include "mediapipe/framework/formats/landmark.pb.h"

int main(){

    IGMOD* test = CreateGMOD();

    test->set_camera_props(1, 640, 480, 30);
    test->set_camera(true);
    test->set_overlay(false);

    auto obs = test->create_observer("face_landmarks");
    // obs->SetPresenceCallback([](class IObserver* observer, bool present){ std::cout << present << std::endl; });
    obs->SetPresenceCallback([](class IObserver* observer, bool present){});
    // obs->SetPacketCallback([](class IObserver* observer){ std::cout << observer->GetData() << std::endl; });
    obs->SetPacketCallback([](class IObserver* observer){ 
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        size_t message_type = observer->GetMessageType(); 
        std::cout << typeid(message_type).name() << std::endl;
        std::cout << data->landmark(0).x() << " ; " << message_type << std::endl; 
    });

    test->start("/home/purg3me/Projects/MediapipeModule/MediapipeModule_module/MediapipeModule_library/mediapipe/mediapipe/graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");

    while(true){
    }
    return 0;
}