#pragma once

#include "SStateVectorData.h"

// Feedback controller computing a control value from the system state
class CFeedBack
{
public:
    CFeedBack() = default;

    float calculate(SStateVectorData& data) const;

private:
    // Indices for feedback gain coefficients
    enum
    {
        K_phi = 0,  // Angle gain
        K_phi_d,    // Angular velocity gain
        K_psi_d     // Yaw rate gain
    };

    // Feedback gain vector
    const float K_[3] = {
        -9.252424633236345f,    // Angle gain
        -0.575309331966650f,    // Angular velocity gain
        -0.004664999794325f     // Yaw rate gain
    };
};
