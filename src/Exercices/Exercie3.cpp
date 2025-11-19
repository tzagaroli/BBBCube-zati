#include "Exercices/Exercice3.hpp"
#include "BBBCube_Globals.hpp"

#include "CThread.h"

int main_ex3()
{
    CContainer container;

    ControlComp control(container);
    CCommComp commComp(container);

    CThread controlCompThread(&control, CThread::PRIORITY_ABOVE_NORM);

    CThread commCompThread(&commComp, CThread::PRIORITY_LOW);

    controlCompThread.start();
    commCompThread.start();

    controlCompThread.join();
    commCompThread.join();

    return 0;
}