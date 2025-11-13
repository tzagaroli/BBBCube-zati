#pragma once

#include "CContainer.h"
#include "AComponentBase.h"
#include "CBBBHardware.h"
#include "CServer.h"
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
    void vPrintDataIMU(CIMUData& data);

    void vPrintValue(const std::string& label, UInt16 value, int indent = 0);

    CContainer& container_;
    CBBBHardware hardware_;
};

// -------------------------
// -------------------------
// Class CCommComp
// -------------------------
// -------------------------
class CCommComp : public AComponentBase
{
public:
    CCommComp(CContainer& container);

    void init() override;
    void run() override;

private:
    CContainer& container_;
    CServer server_;
};
