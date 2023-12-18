#include "gmod_basic_holistic.h"

namespace mcl_basic {

void Holistic::Setup(int cam_id, int cam_resx, int cam_resy, int cam_fps, bool gpu){ // pass the camera properties

    // Create IGMOD
    _gmod = new mcl::GMOD();

    _gmod->set_camera(true);
    _gmod->set_overlay(true);

    // Set camera props
    _gmod->set_camera_props(cam_id, cam_resx, cam_resy, cam_fps);
    _gpu = gpu;

    // Create observers
    _observers.push_back(_gmod->create_observer("face_landmarks"));
    // _observers.push_back(_gmod->create_observer("face_landmarks"));
    _observers.push_back(_gmod->create_observer("pose_landmarks"));
    // _observers.push_back(_gmod->create_observer("pose_world_landmarks"));
    _observers.push_back(_gmod->create_observer("left_hand_landmarks"));
    _observers.push_back(_gmod->create_observer("right_hand_landmarks"));

    _data.resize(543);
    for(int i=0; i<543; i++) _data.at(i).resize(3);

    // Add callback functions
    // Face Landmarks
    _observers[0]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    _observers[0]->SetPacketCallback([this](class mcl::IObserver* observer){ 
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        for(int i=0; i<468; i++){
            this->_data[i][0] = data->landmark(0).x();
            this->_data[i][1] = data->landmark(1).y();
            this->_data[i][2] = data->landmark(2).z();
        }
    });
    // Pose Landmarks
    _observers[1]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    _observers[1]->SetPacketCallback([](class mcl::IObserver* observer){ });
    // Left Hand Landmarks
    _observers[2]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    _observers[2]->SetPacketCallback([](class mcl::IObserver* observer){ });
    // Right Hand Landmarks
    _observers[3]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    _observers[3]->SetPacketCallback([](class mcl::IObserver* observer){ });
    // Pose World Landmarks
    // _observers[2]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    // _observers[2]->SetPacketCallback([](class mcl::IObserver* observer){ });
}

void Holistic::Start(){
    std::fstream file;
    if(_gpu){
        file.open("mediapipe_graphs/holistic_tracking/holistic_tracking_gpu.pbtxt");
        if(file.is_open()){
            file.close();
            _gmod->start("mediapipe_graphs/holistic_tracking/holistic_tracking_gpu.pbtxt");
        }
        else {
            std::cout << "Error: ";
            std::cout << "mediapipe_graphs/holistic_tracking/holistic_tracking_gpu.pbtxt";
            std::cout << ": Graph file not found;";
        }
    } else {
        file.open("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");
        if(file.is_open()){
            file.close();
            _gmod->start("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");
        }
        else {
            std::cout << "Error: ";
            std::cout << "mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt";
            std::cout << ": Graph file not found;";
        }
    }
}

void Holistic::Stop(){
    _gmod->stop();
}

std::vector<std::vector<float>>* Holistic::GetData(){
    return &_data;
}

IHolistic* CreateHolistic(){
    return new Holistic();
}

} // namespace mcl_basic