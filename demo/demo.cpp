#include<iostream>
#include<functional>
#include<typeinfo>
// #include <opencv2/opencv.hpp>

#include "gmod_api.h"
#include "mediapipe/framework/formats/landmark.pb.h"

int main(){

    IGMOD* test = CreateGMOD();

    test->set_camera_props(0, 640, 480, 30);
    test->set_camera(true);
    test->set_overlay(true);

    // FOR GRAPHS THAT RETURN IMAGES
    // The current frame is stored as demo.png in the folder
    // This requires the graph to have ecoded_output_video ( or whatever stream name you put here ) as an output stream
    // Normally mediapipe graphs return mediapipe::ImageFrame as output, you can use the ImageFrameToOpenCVMatCalculator
    // to do convert it to a cv::Mat.
    //////////////////////////////////
    // auto obs = test->create_observer("encoded_output_video");
    // obs->SetPresenceCallback([](class IObserver* observer, bool present){});
    // obs->SetPacketCallback([](class IObserver* observer){ 
    //     cv::Mat* test;
    //     test = (cv::Mat*)(observer->GetData()); 
    //     cv::imwrite("testing.png", *test);
    //     std::string message_type = observer->GetMessageType(); 
    //     std::cout << message_type << std::endl;
    // });
    //////////////////////////////////

    // FOR GRAPH THAT RETURN NORMALIZED LANDMARK LIST
    auto obs = test->create_observer("face_landmarks");
    obs->SetPresenceCallback([](class IObserver* observer, bool present){});
    obs->SetPacketCallback([](class IObserver* observer){ 
        mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        std::cout << data->landmark(0).x() << std::endl;
        std::string message_type = observer->GetMessageType(); 
        std::cout << message_type << std::endl;
    });
    
    // These are the graphs that have been tested and work

    // HOLISTIC TRACKING
    test->start("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");
    // HAND TRACKING
    // test->start("mediapipe_graphs/hand_tracking/hand_detection_desktop_live.pbtxt");
    // test->start("mediapipe_graphs/hand_tracking/hand_tracking_desktop_live.pbtxt");
    // POSE TRACKING
    // test->start("mediapipe_graphs/pose_tracking/pose_tracking_cpu.pbtxt");
    // IRIS TRACKING
    // test->start("mediapipe_graphs/iris_tracking/iris_tracking_cpu.pbtxt");
    // test->start("mediapipe_graphs/iris_tracking/iris_tracking_gpu.pbtxt");
    // FACE DETECTION
    // test->start("mediapipe_graphs/face_detection/face_detection_desktop_live.pbtxt");
    // test->start("mediapipe_graphs/face_detection/face_detection_full_range_desktop_live.pbtxt");
    // FACE MESH
    // test->start("mediapipe_graphs/face_mesh/face_mesh_desktop_live.pbtxt");
    // SELFIE SEGMENTATION
    // test->start("mediapipe_graphs/selfie_segmentation/selfie_segmentation_cpu.pbtxt");
    // HAIR SEGMENTATION
    // test->start("mediapipe_graphs/hair_segmentation/hair_segmentation_desktop_live.pbtxt");

    // To make sure the program does not quit running
    while(true){
    }
    return 0;
}
