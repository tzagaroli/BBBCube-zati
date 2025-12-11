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

    const float K_[3] = {-2.362352477346677f, -0.528939996415684f, -0.003684371163443f};
};