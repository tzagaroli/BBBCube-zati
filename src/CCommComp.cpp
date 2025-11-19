#include "CCommComp.hpp"

#include <iostream>
#include <chrono>
#include <unistd.h>

CCommComp::CCommComp(CContainer& container)
    : container_(container)
    , server_()
{
    server_.init();
}

void CCommComp::init()
{
    std::cout << "Waiting for client connection..." << std::endl;
    
    if(server_.waitForClient())
    {
        std::cout << "Client connected!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to connect to client!" << std::endl;
    }
}

void CCommComp::run()
{
    SContent content;

    while(true)
    {
        auto startTime = std::chrono::steady_clock::now();
        
        // Wait for new data from container (blocking)
        if(!container_.getContent(true, content))
        {
            std::cerr << "Error: Failed to get content from container!" << std::endl;
            continue;
        }
        
        // Transmit data using CServer
        if(!server_.transmitMessage(content))
        {
            std::cerr << "Error: Failed to transmit data!" << std::endl;
            // Client disconnected, wait for new connection
            std::cout << "Waiting for new client connection..." << std::endl;
            if(!server_.waitForClient())
            {
                std::cerr << "Failed to reconnect to client!" << std::endl;
                return;
            }
            std::cout << "Client reconnected!" << std::endl;
        }
        
        // Calculate elapsed time and required sleep time
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        auto sleepTime = (cycleTime / 2) - elapsedTime;
        
        // Only sleep if there's time left in the cycle
        if(sleepTime.count() > 0)
        {
            // More explicit and safer conversion:
            auto sleepMicros = std::chrono::duration_cast<std::chrono::microseconds>(sleepTime);
            usleep(sleepMicros.count());
        }
    }
}