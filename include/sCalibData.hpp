#pragma once

struct sDataIMU
{
    float fAccelerationX;
    float fAccelerationY;
    float fAngularSpeedZ;
};


struct sCalibData
{
    float fFlywheelOmega;
    sDataIMU sIMU1;
    sDataIMU sIMU2;
};
