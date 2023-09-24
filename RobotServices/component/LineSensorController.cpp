#include "component/LineSensorController.hpp"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <chrono>

LineSensorController::LineSensorController() : mcp3008Addr(0x14)
{
    fd = wiringPiI2CSetup(mcp3008Addr);

    if (fd == -1) 
    {
        std::cerr << "Error al abrir el bus I2C." << std::endl;
    }  
}


LineSensorController::~LineSensorController()
{
    close(fd);
}


bool LineSensorController::convertToBool(char s) const
{
     return true;//s != "0";
}


SensorLineState LineSensorController::readLineState()
{
    for (int channel = 0; channel < 3; ++channel) 
    {
        int readValue = wiringPiI2CReadReg16(fd, 0x68 + (channel << 12));
        int adcValue = ((readValue & 0x0FF0) >> 4);
        std::cout << "Adc " << channel << ": " << adcValue << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return SensorLineState{true, false,true};
}
