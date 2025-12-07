#include "CStateEstimation.hpp"
#include "cmath"

CStateEstimation::CStateEstimation()
    : fR1_R2_(fDistanceSensor1_/fDistanceSensor2_)
{
}

SStateVectorData CStateEstimation::estimate(const sCalibData& sData) const
{
    SStateVectorData sRetData{};
    
    sRetData.mPsi_d = sData.fFlywheelOmega;

    sRetData.mPhi_d = (sData.sIMU1.fAngularSpeedZ + sData.sIMU2.fAngularSpeedZ) / 2.0f;

    sRetData.mPhi_A = atan2((sData.sIMU1.fAccelerationX - fR1_R2_ * sData.sIMU2.fAccelerationX), (sData.sIMU1.fAccelerationY - fR1_R2_ * sData.sIMU2.fAccelerationY)) + 0.0283074436299669f;

    return sRetData;
}