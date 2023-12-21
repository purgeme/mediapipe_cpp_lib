#include "mcl_basic_holistic.h"

namespace mcl_basic {

void Holistic::Setup(int cam_id, int cam_resx, int cam_resy, int cam_fps, bool gpu){ // pass the camera properties

    // Create IMCL
    _mcl = std::make_unique<mcl::MCL>();

    _mcl->set_camera(true);
    _mcl->set_overlay(true);
    _mcl->set_gpu(gpu);
    _gpu = gpu;

    // Set camera props
    _mcl->set_camera_props(cam_id, cam_resx, cam_resy, cam_fps);

    // Create observers
    _observers.push_back(_mcl->create_observer("face_landmarks"));
    _observers.push_back(_mcl->create_observer("pose_landmarks"));
    _observers.push_back(_mcl->create_observer("left_hand_landmarks"));
    _observers.push_back(_mcl->create_observer("right_hand_landmarks"));

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
    _observers[1]->SetPacketCallback([this](class mcl::IObserver* observer){
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        for(int i=0; i<33; i++){
            this->_data[i][0] = data->landmark(0).x();
            this->_data[i][1] = data->landmark(1).y();
            this->_data[i][2] = data->landmark(2).z();
        }
    });
    // Left Hand Landmarks
    _observers[2]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    _observers[2]->SetPacketCallback([this](class mcl::IObserver* observer){
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        for(int i=0; i<21; i++){
            this->_data[i][0] = data->landmark(0).x();
            this->_data[i][1] = data->landmark(1).y();
            this->_data[i][2] = data->landmark(2).z();
        }
    });
    // Right Hand Landmarks
    _observers[3]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    _observers[3]->SetPacketCallback([this](class mcl::IObserver* observer){
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        for(int i=0; i<21; i++){
            this->_data[i][0] = data->landmark(0).x();
            this->_data[i][1] = data->landmark(1).y();
            this->_data[i][2] = data->landmark(2).z();
        }
    });
}

void Holistic::Start(){
    std::fstream file;
    if(_gpu){
        file.open("mediapipe_graphs/holistic_tracking/holistic_tracking_gpu.pbtxt");
        if(file.is_open()){
            file.close();
            _mcl->start("mediapipe_graphs/holistic_tracking/holistic_tracking_gpu.pbtxt");
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
            _mcl->start("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");
        }
        else {
            std::cout << "Error: ";
            std::cout << "mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt";
            std::cout << ": Graph file not found;";
        }
    }
}

void Holistic::Stop(){
    _mcl->stop();
}

std::vector<std::vector<float>>* Holistic::GetData(){
    return &_data;
}

ITracking* CreateHolistic(){
    return new Holistic();
}

} // namespace mcl_basic