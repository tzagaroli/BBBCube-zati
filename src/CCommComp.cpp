#include "CCommComp.hpp"

#include <iostream>
#include <chrono>
#include <unistd.h>

#include <thread>

#include "SignalHandler.hpp"

CCommComp::CCommComp(CContainer& container)
    : container_(container)
    , server_()
{
    server_.init();
}

void CCommComp::init()
{
    std::cout << "Waiting for client connection..." << std::endl;

    // Block until a client connects or shutdown is requested
    while(!g_stop.load())
    {
        if(server_.waitForClient())
        {
            std::cout << "Client connected!" << std::endl;
            return;
        }
    }
}

void CCommComp::run()
{
    // Buffer holding the message to transmit
    SContent content;

    // Periodic communication loop
    while(!g_stop.load())
    {
        // Timestamp at start of the cycle (used to maintain a fixed period)
        auto startTime = std::chrono::steady_clock::now();
        
        // Retrieve latest content from the container; avoid busy-waiting if unavailable
        if(!container_.getContent(false, content))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            continue;
        }
        
        // Send the content to the connected client
        if(!server_.transmitMessage(content))
        {
            std::cerr << "Error: Failed to transmit data!" << std::endl;
            std::cout << "Waiting for new client connection..." << std::endl;

            // Keep trying to reconnect until successful or shutdown requested
            bool reconnected = false;
            while(!g_stop.load() && !reconnected)
            {
                if(server_.waitForClient())
                {
                    std::cout << "Client reconnected!" << std::endl;
                    reconnected = true;
                }
            }
        }
        
        // Compute elapsed time and sleep for the remaining cycle budget
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        auto sleepTime = (Ts / 2) - elapsedTime;
        
        // Only sleep if there's time left in the cycle
        if(sleepTime.count() > 0)
        {
            // More explicit and safer conversion:
            auto sleepMicros = std::chrono::duration_cast<std::chrono::microseconds>(sleepTime);
            std::this_thread::sleep_for(sleepMicros);
        }
    }
}
