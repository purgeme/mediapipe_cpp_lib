#include <vector>

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"

namespace mediapipe {

//
// Example config:
// node {
//   calculator: "TestCalculator"
//   input_stream: "ImageFrame"
//   output_stream: "cv::Mat"
// }
//
class ImageFrameToOpenCVMatCalculator : public CalculatorBase {
 public:
  static absl::Status GetContract(CalculatorContract* cc) {
    cc->Inputs().Index(0).Set<ImageFrame>();
    // cc->Outputs().Index(0).Set<cv::Mat>();
    cc->Outputs().Index(0).SetAny();
    cc->SetProcessTimestampBounds(true);
    return absl::OkStatus();
  }

  absl::Status Open(CalculatorContext* cc) final {
    // cc->Outputs().Index(0).SetHeader(cc->Inputs().Index(0).Header());
    cc->SetOffset(TimestampDiff(0));
    return absl::OkStatus();
  }

  absl::Status Process(CalculatorContext* cc) final {
    if (!cc->Inputs().Index(0).Value().IsEmpty()) {
        const cv::Mat result = mediapipe::formats::MatView(&(cc->Inputs().Index(0).Get<ImageFrame>()));
        cc->Outputs().Index(0).AddPacket(MakePacket<cv::Mat>(result).At(cc->InputTimestamp()));
    } else {
          cc->Outputs().Index(0).SetNextTimestampBound(
              cc->InputTimestamp().NextAllowedInStream());
    }
    return absl::OkStatus();
  }
};

REGISTER_CALCULATOR(ImageFrameToOpenCVMatCalculator);
}  // namespace mediapipe
