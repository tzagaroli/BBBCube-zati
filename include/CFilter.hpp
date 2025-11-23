#pragma once

#include <chrono>

#include "BBBCube_Globals.hpp"

#include "SStateVectorData.h"

class CFilter
{
public:
    CFilter();

    SStateVectorData filter(const SStateVectorData& sData);

private:
    const float fT_ = std::chrono::duration<float>(cycleTime).count();
    const float fAlpha_ = 0.98;

    bool bFirstExecution_;
    float fLastValue_;
};