#include "mcl_basic_facelandmark.h"

namespace mcl_basic {

void FaceLandmark::Setup(int cam_id, int cam_resx, int cam_resy, int cam_fps, bool gpu){ // pass the camera properties

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

    _data.resize(468);
    for(int i=0; i<468; i++) _data.at(i).resize(3);

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
}

void FaceLandmark::Start(){
    std::fstream file;
    if(_gpu){
        file.open("mediapipe_graphs/face_mesh/face_mesh_desktop_live_gpu.pbtxt");
        if(file.is_open()){
            file.close();
            _mcl->start("mediapipe_graphs/face_mesh/face_mesh_desktop_live_gpu.pbtxt");
        }
        else {
            std::cout << "Error: ";
            std::cout << "mediapipe_graphs/face_mesh/face_mesh_desktop_live_gpu.pbtxt";
            std::cout << ": Graph file not found;";
        }
    } else {
        file.open("mediapipe_graphs/face_mesh/face_mesh_desktop_live.pbtxt");
        if(file.is_open()){
            file.close();
            _mcl->start("mediapipe_graphs/face_mesh/face_mesh_desktop_live.pbtxt");
        }
        else {
            std::cout << "Error: ";
            std::cout << "mediapipe_graphs/face_mesh/face_mesh_desktop_live.pbtxt";
            std::cout << ": Graph file not found;";
        }
    }
}

void FaceLandmark::Stop(){
    _mcl->stop();
}

std::vector<std::vector<float>>* FaceLandmark::GetData(){
    return &_data;
}

ITracking* CreateFaceLandmark(){
    return new FaceLandmark();
}

} // namespace mcl_basic