#include "CCalibration.hpp"

CCalibration::CCalibration()
    : sData_{}
{
}

sCalibData CCalibration::calibrate(SContent& content)
{
    sData_.fFlywheelOmega = csADC.a * static_cast<float>(content.mADCValue) + csADC.b;

    sData_.sIMU1.fAccelerationX = csAccel1X.a * static_cast<float>(content.mSensor1Data.mA_x) + csAccel1X.b;
    sData_.sIMU1.fAccelerationY = csAccel1Y.a * static_cast<float>(content.mSensor1Data.mA_y) + csAccel1Y.b;

    sData_.sIMU2.fAccelerationX = csAccel2X.a * static_cast<float>(content.mSensor2Data.mA_x) + csAccel2X.b;
    sData_.sIMU2.fAccelerationY = csAccel2Y.a * static_cast<float>(content.mSensor2Data.mA_y) + csAccel2Y.b;

    sData_.sIMU1.fAngularSpeedZ = csGyro1Z.a * static_cast<float>(content.mSensor1Data.mPhi_d) + csGyro1Z.b;
    sData_.sIMU2.fAngularSpeedZ = csGyro2Z.a * static_cast<float>(content.mSensor2Data.mPhi_d) + csGyro2Z.b;

    return sData_;
}