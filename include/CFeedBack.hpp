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

    const float K_[3] = {-1.223566103950532f, -0.521593685962550f, -0.003697787536415f};
};