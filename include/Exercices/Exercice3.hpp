#pragma once

#include "CContainer.h"
#include "AComponentBase.h"
#include "CBBBHardware.h"
#include "CThread.h"

int main_ex3();

// -------------------------
// -------------------------
// Class ControlComp
// -------------------------
// -------------------------
class ControlComp : public AComponentBase
{
public:
    ControlComp(CContainer& container);

    void init() override;
    void run() override;

private:
    void vPrintData(CIMUData& data);

    CContainer& container_;
    CBBBHardware hardware_;
};