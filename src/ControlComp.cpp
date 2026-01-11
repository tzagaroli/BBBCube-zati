#include "ControlComp.hpp"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <unistd.h>
#include <cmath>

#include <thread>

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

    // Timing reference for periodic loop (fixed-rate scheduling)
    auto startTime = std::chrono::steady_clock::now();
    uint32_t n = 0;

    // Enable actuators before entering control loop
    hardware_.enableMotor();
    hardware_.openBrake();
    
    // Main control loop
    while(!g_stop.load())
    {
        // Read hardware measurements (ADC + two IMUs)
        if(!hardware_.fetchValues(adcValue, sensor1Data, sensor2Data))
        {
            std::cerr << "Error: fetchValues() failed!" << std::endl;
            return;
        }

        content.mADCValue = adcValue;
        content.mSensor1Data = sensor1Data;
        content.mSensor2Data = sensor2Data;

        // Publish raw measurements to the shared container (for logging/telemetry)
        container_.writeTime(
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()
        );
        container_.writeADCValue(adcValue);
        container_.writeSensor1Data(sensor1Data);
        container_.writeSensor2Data(sensor2Data);

        // Processing chain: calibration -> state estimation -> filtering -> feedback control
        calib = calibration_.calibrate(content);
        data = estimation_.estimate(calib);
        data = filter_.filter(data);
        fTorque = feedback_.calculate(data);

        // Apply regulation only within +/- 10 degrees (0.174533 rad)
        if(abs(data.mPhi_A) <= 0.174533f)
        {
            hardware_.setTorque(fTorque);
        }
        else
        {
            hardware_.setTorque(0.0f);
        }

        // Publish computed control and state to the container
        container_.writeTorqueValue(fTorque);
        container_.writeStateData(data);

        // Notify consumers that a new sample is available
        container_.signalReader();
        
        // // --- ADC ---
        // vPrintValue("ADC Value", adcValue);

        // // --- IMU Sensor 1 Data ---
        // std::cout << "IMU Sensor 1:" << std::endl;
        // ControlComp::vPrintDataIMU(sensor1Data);

        // // --- IMU Sensor 2 Data ---
        // std::cout << "IMU Sensor 2:" << std::endl;
        // ControlComp::vPrintDataIMU(sensor2Data);
        // std::cout << std::endl;


        // Fixed-rate scheduling: compute next wake-up time based on initial start time
        n++;
        auto currentTime = std::chrono::steady_clock::now();
        auto nextWakeTime = startTime + (Ts * n);
        auto sleepTime = nextWakeTime - currentTime;
        
        // Only sleep if there's time left in the cycle
        if(sleepTime.count() > 0)
        {
            auto sleepMicros = std::chrono::duration_cast<std::chrono::microseconds>(sleepTime);
            std::this_thread::sleep_for(sleepMicros);
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
