#pragma once 
#include <string>

struct SensorLineState
{
    bool rightSensor;
    bool centralSensor;
    bool leftSensor;
};

class LineSensorController
{
private:
    int fd;
    uint32_t mcp3008Addr;
public:
    LineSensorController();
    ~LineSensorController();
    SensorLineState readLineState();
    bool convertToBool(char s) const;
};
