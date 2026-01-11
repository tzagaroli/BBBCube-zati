#pragma once

#include "SContent.h"
#include "sCalibData.hpp"

// a * x + b
struct sPolynom
{
    // Slope coefficient
    float a;

    // Offset coefficient
    float b;
};


class CCalibration
{
public:
    CCalibration();

    sCalibData calibrate(SContent& content) const;

private:
    // ADC calibration polynomial
    const sPolynom csADC = {0.07666f, (-156.0f-0.1238204619f)};

    // Accelerometer 1 calibration polynomials
    const sPolynom csAccel1X = {0.001195539868064f, 0.069921487820418f};
    const sPolynom csAccel1Y = {-0.001194484949983f, 0.230998563678049f};

    // Accelerometer 2 calibration polynomials
    const sPolynom csAccel2X = {0.001194404539810f, -0.354379498201718f};
    const sPolynom csAccel2Y = {-0.001194280700135f, 0.280185521539719f};

    // Gyroscope calibration polynomials (Z axis)
    const sPolynom csGyro1Z = {0.00106f, 0.00218184638109306f};
    const sPolynom csGyro2Z = {0.00106f, -0.0905728508124077f};
};
