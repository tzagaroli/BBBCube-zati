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

    const float K_[3] = {-2.5539f, -0.5038f, -0.1573f};
};