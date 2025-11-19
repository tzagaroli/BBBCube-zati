#pragma once

#include "CContainer.h"
#include "AComponentBase.h"
#include "CServer.h"

#include "BBBCube_Globals.hpp"

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
