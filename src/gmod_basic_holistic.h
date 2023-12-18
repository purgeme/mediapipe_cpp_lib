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


    private:
        std::unique_ptr<mcl::GMOD> _gmod;
        bool _gpu;
        std::vector<std::shared_ptr<mcl::IObserver>> _observers;
        std::vector<std::vector<float>> _data;
};

} // namespace mcl_basic