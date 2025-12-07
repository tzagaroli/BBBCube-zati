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

    const float K_[3] = {-1.576003019639933f, -0.232279270678112f,  -0.052885821505019f};
};