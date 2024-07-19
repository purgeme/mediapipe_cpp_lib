#pragma once

#include "mcl_core.h"

namespace mcl_basic {

class FaceLandmark : public ITracking
{
    public:
        virtual void Setup(int cam_id, int cam_resx, int cam_resy, int cam_fps, bool gpu) override;
        virtual void Start() override;
        virtual void Stop() override;
        std::vector<std::vector<std::vector<float>>>* GetData();


    private:
        std::unique_ptr<mcl::MCL> _mcl;
        bool _gpu;
        std::vector<std::shared_ptr<mcl::IObserver>> _observers;
        std::vector<std::vector<std::vector<float>>> _data;
};

} // namespace mcl_basic