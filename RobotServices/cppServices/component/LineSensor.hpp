#pragma once 
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <fstream>
#include <string>

struct LineState
{
    bool rightSensor;
    bool centralSensor;
    bool leftSensor;
};

class LineSensor
{
private:
    LineState convertToBool(const std::string& sensorValues) const;
    std::string m_cmd;
    int sockfd;
    struct sockaddr_un addr;
    char buffer[1024];    
public:
    LineSensor(/* args */);
    ~LineSensor();
    LineState readLineState();
    LineState readState();
};
