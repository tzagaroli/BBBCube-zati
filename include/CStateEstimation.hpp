#pragma once

#include "CCalibration.hpp"
#include "sCalibData.hpp"

#include "SStateVectorData.h"

// Computes the system state from calibrated sensor measurements
class CStateEstimation
{
public:
    CStateEstimation();

    SStateVectorData estimate(const sCalibData& sData) const;

private:
    float fDistanceSensor1_ = 0.14f;
    float fDistanceSensor2_ = 0.061f;

    float fR1_R2_;
};
