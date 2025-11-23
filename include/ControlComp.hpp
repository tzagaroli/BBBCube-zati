#pragma once

#include "CContainer.h"
#include "AComponentBase.h"
#include "CBBBHardware.h"

#include "BBBCube_Globals.hpp"

#include "CCalibration.hpp"
#include "CStateEstimation.hpp"
#include "CFilter.hpp"

class ControlComp : public AComponentBase
{
public:
    ControlComp(CContainer& container);

    void init() override;
    void run() override;

private:
    void vPrintDataIMU(CIMUData& data);

    void vPrintValue(const std::string& label, UInt16 value, int indent = 0);

    CContainer& container_;
    CBBBHardware hardware_;

    CCalibration calibration_;
    CStateEstimation estimation_;
    CFilter filter_;
};