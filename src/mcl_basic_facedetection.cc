#include "mcl_basic_facedetection.h"

namespace mcl_basic {

void FaceDetection::Setup(int cam_id, int cam_resx, int cam_resy, int cam_fps, bool gpu){ // pass the camera properties

    // Create IMCL
    _mcl = std::make_unique<mcl::MCL>();

    _mcl->set_camera(true);
    _mcl->set_overlay(true);
    _mcl->set_gpu(gpu);
    _gpu = gpu;

    // Set camera props
    _mcl->set_camera_props(cam_id, cam_resx, cam_resy, cam_fps);

    // Create observers
    _observers.push_back(_mcl->create_observer("face_detections"));

    _data.resize(3);
    _data.at(0).resize(0);
    _data.at(1).resize(4);

    // Add callback functions
    // Face Landmarks
    _observers[0]->SetPresenceCallback([](class mcl::IObserver* observer, bool present){});
    _observers[0]->SetPacketCallback([this](class mcl::IObserver* observer){ 
        const std::vector<mediapipe::Detection>* data = (std::vector<mediapipe::Detection>*)(observer->GetData()); 
        this->_data[0][0] = data->size();
        this->_data[1][0] = data->at(0).location_data().relative_bounding_box().xmin();
        this->_data[1][1] = data->at(0).location_data().relative_bounding_box().ymin();
        this->_data[1][2] = data->at(0).location_data().relative_bounding_box().width();
        this->_data[1][3] = data->at(0).location_data().relative_bounding_box().height();
    });
}

void FaceDetection::Start(){
    std::fstream file;
    if(_gpu){
        file.open("mediapipe_graphs/face_detection/face_detection_mobile_gpu.pbtxt");
        if(file.is_open()){
            file.close();
            _mcl->start("mediapipe_graphs/face_detection/face_detection_mobile_gpu.pbtxt");
        }
        else {
            std::cout << "Error: ";
            std::cout << "mediapipe_graphs/face_detection/face_detection_mobile_gpu.pbtxt";
            std::cout << ": Graph file not found;";
        }
    } else {
        file.open("mediapipe_graphs/face_detection/face_detection_desktop_live.pbtxt");
        if(file.is_open()){
            file.close();
            _mcl->start("mediapipe_graphs/face_detection/face_detection_desktop_live.pbtxt");
        }
        else {
            std::cout << "Error: ";
            std::cout << "mediapipe_graphs/face_detection/face_detection_desktop_live.pbtxt";
            std::cout << ": Graph file not found;";
        }
    }
}

void FaceDetection::Stop(){
    _mcl->stop();
}

std::vector<std::vector<float>>* FaceDetection::GetData(){
    return &_data;
}

ITracking* CreateFaceDetection(){
    return new FaceDetection();
}

} // namespace mcl_basic