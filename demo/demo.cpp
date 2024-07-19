#include<iostream>
#include<functional>
#include<typeinfo>

#include "mcl_api.h"
#include "mediapipe/framework/formats/landmark.pb.h"

int main(){

    // FACE MESH
    mcl_basic::ITracking* test = mcl_basic::CreateFaceLandmark();

    // FACE DETECTION
    // mcl_basic::ITracking* test = mcl_basic::CreateFaceDetection();

    // Holistic
    // mcl_basic::ITracking* test = mcl_basic::CreateHolistic();

    test->Setup(0, 640, 480, 30, 0);

    test->Start();

    // To make sure the program does not quit running
    while(true){
    }
    return 0;
}
