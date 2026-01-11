#pragma once

#include <chrono>

#include "BBBCube_Globals.hpp"

#include "SStateVectorData.h"

// Complementary filter
class CFilter
{
public:
    CFilter();

    SStateVectorData filter(const SStateVectorData& sData);

private:
    // Sampling period in seconds (converted from Ts)
    const float fT_ = std::chrono::duration<float>(Ts).count();
    const float fAlpha_ = 0.98;

    bool bFirstExecution_;
    float fLastValue_;
};
