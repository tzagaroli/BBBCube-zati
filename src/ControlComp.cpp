#include "ControlComp.hpp"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <unistd.h>
#include <cmath>

#include "SignalHandler.hpp"

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

    
    SContent content;
    sCalibData calib;
    SStateVectorData data;

    float fTorque = 0;

    auto startTime = std::chrono::steady_clock::now();
    uint32_t n = 0;

    if(hardware_.enableMotor())
        std::cout << "Motor Enabled" << std::endl;
    if(hardware_.openBrake())
        std::cout << "Brake Opened" << std::endl;
    
    while(!g_stop.load())
    {
        if(!hardware_.fetchValues(adcValue, sensor1Data, sensor2Data))
        {
            std::cerr << "Error: fetchValues() failed!" << std::endl;
            return;
        }

        content.mADCValue = adcValue;
        content.mSensor1Data = sensor1Data;
        content.mSensor2Data = sensor2Data;

        container_.writeTime(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
        container_.writeADCValue(adcValue);
        container_.writeSensor1Data(sensor1Data);
        container_.writeSensor2Data(sensor2Data);

        calib = calibration_.calibrate(content);
        data = estimation_.estimate(calib);
        data = filter_.filter(data);
        
        fTorque = feedback_.calculate(data);

        if(abs(data.mPhi_A) <= regulationLimit)
        {
            hardware_.setTorque(fTorque);
        }
        else
        {
            hardware_.setTorque(0.0f);
        }

        container_.writeTorqueValue(fTorque);
        container_.writeStateData(data);

        container_.signalReader();
        
        if(verbose)
        {
            // --- ADC ---
            vPrintValue("ADC Value", adcValue);

            // --- IMU Sensor 1 Data ---
            std::cout << "IMU Sensor 1:" << std::endl;
            ControlComp::vPrintDataIMU(sensor1Data);

            // --- IMU Sensor 2 Data ---
            std::cout << "IMU Sensor 2:" << std::endl;
            ControlComp::vPrintDataIMU(sensor2Data);
            std::cout << std::endl;
        }

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

    hardware_.setTorque(0.0f);
    hardware_.disableMotor();
    hardware_.closeBrake();
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
