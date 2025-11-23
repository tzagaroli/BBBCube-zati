#pragma once

#include "SContent.h"
#include "sCalibData.hpp"

struct sPolynom
{
    float a;
    float b;
};



class CCalibration
{
public:
    CCalibration();

    sCalibData calibrate(SContent& content);

private:
    sCalibData sData_;

    const sPolynom csADC = {-157.0f, 0.0766602f};

    const sPolynom csAccel1X = {0.001195539868064f, 0.069921487820418f};
    const sPolynom csAccel1Y = {-0.001194484949983f, 0.230998563678049f};

    const sPolynom csAccel2X = {0.001194404539810f, -0.354379498201718f};
    const sPolynom csAccel2Y = {-0.001194280700135f, 0.280185521539719f};

    const sPolynom csGyro1Z = {0.00106f, -0.00218184638109306f};
    const sPolynom csGyro2Z = {0.00106f, 0.0905728508124077f};
};
