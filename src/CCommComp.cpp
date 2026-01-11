#include "CCommComp.hpp"

#include <iostream>
#include <chrono>
#include <unistd.h>

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
    SContent content;

    while(!g_stop.load())
    {
        auto startTime = std::chrono::steady_clock::now();
        
        if(!container_.getContent(false, content))
        {
            usleep(1000); // 1ms sleep
            continue;
        }
        
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
        
        // Calculate elapsed time and required sleep time
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        auto sleepTime = (Ts / 2) - elapsedTime;
        
        // Only sleep if there's time left in the cycle
        if(sleepTime.count() > 0)
        {
            // More explicit and safer conversion:
            auto sleepMicros = std::chrono::duration_cast<std::chrono::microseconds>(sleepTime);
            usleep(sleepMicros.count());
        }
    }
}
