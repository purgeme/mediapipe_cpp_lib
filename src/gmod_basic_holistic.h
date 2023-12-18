#pragma once

#include "gmod_core.h"

namespace mcl_basic {

class Holistic : public IHolistic
{
    public:
        virtual void Setup(int cam_id, int cam_resx, int cam_resy, int cam_fps, bool gpu) override;
        virtual void Start() override;
        virtual void Stop() override;
        virtual std::vector<std::vector<float>>* GetData() override;
        std::vector<std::vector<float>> _data;
    private:
        mcl::GMOD* _gmod;
        bool _gpu;
        std::vector<mcl::IObserver*> _observers;
};

} // namespace mcl_basic