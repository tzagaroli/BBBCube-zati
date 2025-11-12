#include "Exercices/Exercice3.hpp"
#include <iostream>
#include <iomanip>

int main_ex3()
{
    CContainer container;

    ControlComp control(container);

    control.init();
    control.run();

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
    
    if(!hardware_.fetchValues(adcValue, sensor1Data, sensor2Data))
    {
        std::cerr << "Error: fetchValues() failed!" << std::endl;
        return;
    }

    // --- ADC ---
    std::cout << "ADC Value: "
                << std::dec << adcValue
                << "  (0x" << std::setw(4) << std::setfill('0')
                << std::hex << adcValue << ")" << std::dec << std::endl;

    // --- IMU Sensor 1 Data ---
    std::cout << "IMU Sensor 1:" << std::endl;

    ControlComp::vPrintData(sensor1Data);

    // --- IMU Sensor 2 Data ---
    std::cout << "IMU Sensor 2:" << std::endl;

    ControlComp::vPrintData(sensor2Data);

    std::cout << std::endl;
}

void ControlComp::vPrintData(CIMUData& data)
{
    std::cout << "  mPhi_d (Z-Angular Velocity): "
            << std::dec << data.mPhi_d
            << "  (0x" << std::setw(4) << std::setfill('0')
            << std::hex << static_cast<UInt16>(data.mPhi_d)
            << ")" << std::dec << std::endl;

std::cout << "  mX_dd (X-Acceleration):      "
            << std::dec << data.mX_dd
            << "  (0x" << std::setw(4) << std::setfill('0')
            << std::hex << static_cast<UInt16>(data.mX_dd)
            << ")" << std::dec << std::endl;

std::cout << "  mY_dd (Y-Acceleration):      "
            << std::dec << data.mY_dd
            << "  (0x" << std::setw(4) << std::setfill('0')
            << std::hex << static_cast<UInt16>(data.mY_dd)
            << ")" << std::dec << std::endl;
}
