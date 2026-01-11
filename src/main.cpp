#include <iostream>

#include <thread>
#include <chrono>

#include "BBBCube_Globals.hpp"

#include "CContainer.h"
#include "CThread.h"
#include "ControlComp.hpp"
#include "CCommComp.hpp"

#include "SignalHandler.hpp"


int main()
{
	std::signal(SIGINT, sigintHandler);

    CContainer container;

    ControlComp control(container);
    CCommComp commComp(container);

    CThread controlCompThread(&control, CThread::PRIORITY_ABOVE_NORM);

    CThread commCompThread(&commComp, CThread::PRIORITY_LOW);

    commCompThread.start();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    controlCompThread.start();
    

    controlCompThread.join();
    commCompThread.join();

    return 0;
}
