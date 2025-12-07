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

    // Keep trying to connect until a client connects or we receive stop signal
    while(!g_stop.load())
    {
        if(server_.waitForClient())
        {
            std::cout << "Client connected!" << std::endl;
            return;
        }
        // waitForClient timed out or was interrupted, check g_stop and retry
    }

    std::cout << "Connection wait interrupted by shutdown signal" << std::endl;
}

void CCommComp::run()
{
    SContent content;

    while(!g_stop.load())
    {
        auto startTime = std::chrono::steady_clock::now();
        
        // Wait for new data from container (non-blocking)
        if(!container_.getContent(false, content))
        {
            // No data available, sleep briefly to avoid busy-wait
            usleep(1000); // 1ms sleep
            continue;
        }
        
        // Transmit data using CServer
        if(!server_.transmitMessage(content))
        {
            std::cerr << "Error: Failed to transmit data!" << std::endl;
            // Client disconnected, wait for new connection
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
                // waitForClient timed out or was interrupted, check g_stop and retry
            }

            if(!reconnected)
            {
                std::cout << "Reconnection aborted due to shutdown signal" << std::endl;
                return;
            }
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