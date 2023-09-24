#pragma once 
#include <string>
#include <sys/socket.h>
#include <sys/un.h>

struct LineState
{
    bool rightSensor;
    bool centralSensor;
    bool leftSensor;
};

class LineSensor
{
private:
    bool convertToBool(char) const;
    std::string m_cmd;
    int sockfd;
    struct sockaddr_un addr;
    char buffer[1024];    
public:
    LineSensor(/* args */);
    ~LineSensor();
    LineState readLineState();
};
