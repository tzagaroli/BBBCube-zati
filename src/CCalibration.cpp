#include "CCalibration.hpp"

CCalibration::CCalibration()
{
}

sCalibData CCalibration::calibrate(SContent& content) const
{
    sCalibData sDataRet;
    
    sDataRet.fFlywheelOmega = csADC.a * static_cast<float>(content.mADCValue) + csADC.b;

    sDataRet.sIMU1.fAccelerationX = csAccel1X.a * static_cast<float>(content.mSensor1Data.mA_x) + csAccel1X.b;
    sDataRet.sIMU1.fAccelerationY = csAccel1Y.a * static_cast<float>(content.mSensor1Data.mA_y) + csAccel1Y.b;

    sDataRet.sIMU2.fAccelerationX = csAccel2X.a * static_cast<float>(content.mSensor2Data.mA_x) + csAccel2X.b;
    sDataRet.sIMU2.fAccelerationY = csAccel2Y.a * static_cast<float>(content.mSensor2Data.mA_y) + csAccel2Y.b;

    sDataRet.sIMU1.fAngularSpeedZ = -(csGyro1Z.a * static_cast<float>(content.mSensor1Data.mPhi_d) + csGyro1Z.b);
    sDataRet.sIMU2.fAngularSpeedZ = -(csGyro2Z.a * static_cast<float>(content.mSensor2Data.mPhi_d) + csGyro2Z.b);

    return sDataRet;
}
