#include "Exercices/Exercice3.hpp"
#include "BBBCube_Globals.hpp"

#include "SignalHandler.hpp"

#include "CThread.h"

#include <iostream>

int main_ex3()
{
    std::signal(SIGINT, sigintHandler);

    CContainer container;

    ControlComp control(container);
    CCommComp commComp(container);

    CThread controlCompThread(&control, CThread::PRIORITY_ABOVE_NORM);

    CThread commCompThread(&commComp, CThread::PRIORITY_LOW);

    controlCompThread.start();
    commCompThread.start();

    controlCompThread.join();
    commCompThread.join();

    std::cout << "I was there" << std::endl;

    return 0;
}