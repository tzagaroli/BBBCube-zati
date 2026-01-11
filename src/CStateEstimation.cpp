#include "CStateEstimation.hpp"
#include "cmath"

// Precompute ratio between sensor distances
CStateEstimation::CStateEstimation()
    : fR1_R2_(fDistanceSensor1_/fDistanceSensor2_)
{
}

SStateVectorData CStateEstimation::estimate(const sCalibData& sData) const
{
    SStateVectorData sRetData{};
    
    // Flywheel angular speed directly maps to yaw rate
    sRetData.mPsi_d = sData.fFlywheelOmega;

    // Estimate angular velocity as the average of both gyroscopes
    sRetData.mPhi_d = (sData.sIMU1.fAngularSpeedZ + sData.sIMU2.fAngularSpeedZ) / 2.0f;

    // Estimate tilt angle using accelerometer measurements and sensor geometry
    sRetData.mPhi_A = 
        std::atan2(
            (sData.sIMU1.fAccelerationX - fR1_R2_ * sData.sIMU2.fAccelerationX),
            (sData.sIMU1.fAccelerationY - fR1_R2_ * sData.sIMU2.fAccelerationY)
        ) + 0.0283074436299669f; // Empirical offset correction

    return sRetData;
}
