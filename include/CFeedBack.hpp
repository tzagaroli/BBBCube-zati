#pragma once
#include "SStateVectorData.h"

class CFeedBack
{
public:
    CFeedBack() = default;

    float calculate(SStateVectorData& data) const;

private:
    enum
    {
        K_phi = 0,
        K_phi_d,
        K_psi_d
    };

    const float K_[3] = {-9.252424633236345f, -0.575309331966650f, -0.004664999794325f};
};