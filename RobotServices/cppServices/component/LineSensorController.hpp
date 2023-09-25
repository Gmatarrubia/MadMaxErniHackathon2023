#pragma once 
#include <string>

struct SensorLineState
{
    bool rightSensor = false;
    bool centralSensor = false;
    bool leftSensor = false;
};

class LineSensorController
{
private:
    int fd;
    uint32_t mcp3008Addr;
    uint32_t detectionThreshold;
public:
    LineSensorController();
    ~LineSensorController();
    SensorLineState readLineState();
    SensorLineState readLineState2();
    bool convertToBool(char s) const;
};
