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
	// Register handler for Ctrl+C to allow graceful shutdown
	std::signal(SIGINT, sigintHandler);

    CContainer container;

    ControlComp control(container);
    CCommComp commComp(container);

	// Create threads with different priorities
    CThread controlCompThread(&control, CThread::PRIORITY_REALTIME);
    CThread commCompThread(&commComp, CThread::PRIORITY_NORM);

	// Start communication thread first (waits for client connection)
    commCompThread.start();
	// Delay to allow the communication server to initialize
    std::this_thread::sleep_for(std::chrono::seconds(5));

	// Start control loop thread
    controlCompThread.start();
    
	// Wait for both threads to finish before exiting
    controlCompThread.join();
    commCompThread.join();

    return 0;
}
