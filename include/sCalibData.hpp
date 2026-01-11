#pragma once

// IMU measurement data
struct sDataIMU
{
    float fAccelerationX;   // Acceleration along X axis
    float fAccelerationY;   // Acceleration along Y axis
    float fAngularSpeedZ;   // Angular velocity around Z axis
};


// Calibrated sensor data container
struct sCalibData
{
    float fFlywheelOmega;   // Flywheel angular velocity
    sDataIMU sIMU1;         // Calibrated data from IMU 1
    sDataIMU sIMU2;         // Calibrated data from IMU 2
};
