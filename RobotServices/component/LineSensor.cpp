#include "component/LineSensor.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>


LineSensor::LineSensor()
{
    
}


LineSensor::~LineSensor()
{
    
}


LineState LineSensor::convertToBool(const std::string& sensorValues) const
{
    LineState sensorState;
    sensorState.rightSensor = sensorValues[0] == '1';
    sensorState.centralSensor = sensorValues[1] == '1';
    sensorState.leftSensor = sensorValues[2] == '1';
     return sensorState;
}

LineState LineSensor::readState()
{
    std::ifstream file("/home/madmax/ErniHackathon2023/RobotServices/component/sensorLine/data.txt");
    std::string sensorState;
    getline(file, sensorState);
    std::cout << "Received data: " << sensorState << std::endl;
    file.close();
    return convertToBool(sensorState);
}

LineState LineSensor::readLineState()
{
    char buffer[1024];
    std::cout << "sockfd: " << sockfd << std::endl;
    ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) 
    {
        std::cerr << "Error reading sensor line state: " << strerror(errno) << std::endl;
        perror("recv");
        close(sockfd);
    } 
    else if (bytesRead == 0) 
    {
        std::cerr << "Connection closed by the other end" << std::endl;
        close(sockfd);
    } 
    else 
    {
        buffer[bytesRead] = '\0';
        std::cout << "SensorLine state: " << buffer << std::endl;
    }

    std::cout.write(buffer, bytesRead);

    return LineState{};//{convertToBool(buffer[0]), convertToBool(buffer[1]), convertToBool(buffer[2])};
}
