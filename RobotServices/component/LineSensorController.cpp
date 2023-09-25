#include "component/LineSensorController.hpp"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <chrono>

LineSensorController::LineSensorController() : mcp3008Addr(0x14), detectionThreshold(400)
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
    SensorLineState sensorLineState;
    int channel = 0;
    int readValue = wiringPiI2CReadReg16(fd, 0x68 + (channel << 12));

    int adcValue = ((readValue & 0x0FF0) >> 4);
    if(adcValue >= detectionThreshold) sensorLineState.rightSensor = true;
    std::cout << "Adc " << channel << ": " << adcValue << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    channel++;
    readValue = wiringPiI2CReadReg16(fd, 0x68 + (channel << 12));
    adcValue = ((readValue & 0x0FF0) >> 4);
    if(adcValue >= detectionThreshold) sensorLineState.centralSensor = true;
    std::cout << "Adc " << channel << ": " << adcValue << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    channel++;
    readValue = wiringPiI2CReadReg16(fd, 0x68 + (channel << 12));
    adcValue = ((readValue & 0x0FF0) >> 4);
    std::cout << "Adc " << channel << ": " << adcValue << std::endl;
    if(adcValue >= detectionThreshold) sensorLineState.leftSensor = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return sensorLineState;
}


SensorLineState LineSensorController::readLineState2()
{
    SensorLineState sensorLineState;
    int channel = 0;
    uint8_t buffer[3];
    uint8_t commandout = ((1) << 7) | (channel << 4);

    wiringPiI2CWrite(fd, 0x17); // Read CH0
    int readValue = wiringPiI2CRead(fd);
    if (readValue == -1) {
        perror("Error al leer datos desde el dispositivo I2C");
    } else {
        std::cout << "readValue:" << readValue << std::endl;
    }
    std::cout << "readValue:" << readValue << std::endl;
    int adcValue = ((readValue & 0x0FF0) >> 4);
    if(adcValue >= detectionThreshold) sensorLineState.rightSensor = true;
    std::cout << "Adc " << channel << ": " << adcValue << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    return sensorLineState;
}