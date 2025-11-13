#include "Exercices/Exercice3.hpp"
#include "BBBCube_Globals.hpp"

#include <iostream>
#include <iomanip>

#include <chrono>
#include <unistd.h>

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


// -------------------------
// -------------------------
// Class ControlComp
// -------------------------
// -------------------------
ControlComp::ControlComp(CContainer& container)
    : container_(container)
    , hardware_()
{
}

void ControlComp::init()
{
}

void ControlComp::run()
{
    UInt16 adcValue;
    CIMUData sensor1Data;
    CIMUData sensor2Data;

    auto startTime = std::chrono::steady_clock::now();
    uint32_t n = 0;
    
    while(true)
    {
        if(!hardware_.fetchValues(adcValue, sensor1Data, sensor2Data))
        {
            std::cerr << "Error: fetchValues() failed!" << std::endl;
            return;
        }

        container_.writeTime(n * cycleTime.count());
        container_.writeADCValue(adcValue);
        container_.writeSensor1Data(sensor1Data);
        container_.writeSensor2Data(sensor2Data);
        container_.signalReader();

        // --- IMU Sensor 1 Data ---
        std::cout << "IMU Sensor 1:" << std::endl;
        ControlComp::vPrintDataIMU(sensor1Data);

        // --- IMU Sensor 2 Data ---
        std::cout << "IMU Sensor 2:" << std::endl;
        ControlComp::vPrintDataIMU(sensor2Data);
        std::cout << std::endl;

        // Increment counter BEFORE sleep calculation
        n++;
        auto currentTime = std::chrono::steady_clock::now();

        // Calculate when the next cycle should start
        auto nextWakeTime = startTime + (cycleTime * n);
        
        // Calculate required sleep time
        auto sleepTime = nextWakeTime - currentTime;
        
        // Only sleep if there's time left in the cycle
        if(sleepTime.count() > 0)
        {
            // Convert to microseconds for usleep
            auto sleepMicros = std::chrono::duration_cast<std::chrono::microseconds>(sleepTime);
            usleep(sleepMicros.count());
        }
        else
        {
            std::cerr << "Warning: Cycle time exceeded by " 
                      << std::chrono::duration_cast<std::chrono::milliseconds>(-sleepTime).count() 
                      << "ms" << std::endl;
        }
    }
}

void ControlComp::vPrintDataIMU(CIMUData& data)
{
    vPrintValue("mPhi_d (Z-Angular Velocity)", data.mPhi_d, 2);
    vPrintValue("mX_dd (X-Acceleration)", data.mX_dd, 2);
    vPrintValue("mY_dd (Y-Acceleration)", data.mY_dd, 2);
}

void ControlComp::vPrintValue(const std::string& label, UInt16 value, int indent)
{
    std::string indentation(indent, ' ');
    std::cout << indentation << label << ": "
              << std::dec << value
              << "  (0x" << std::setw(4) << std::setfill('0')
              << std::hex << value << ")" << std::dec << std::endl;
}


// -------------------------
// -------------------------
// Class CCommComp
// -------------------------
// -------------------------
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