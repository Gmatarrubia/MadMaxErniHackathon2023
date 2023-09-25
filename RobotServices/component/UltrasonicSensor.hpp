#include "common/flags.hpp"
#include "common/log.hpp"
#include "component/motor.hpp"
#include "component/servo.hpp"

#include <chrono>
#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <vector>
#include <wiringPi.h>

#define LEFT 0
#define RIGHT 1
#define CAMERA 0
#define WHEELS 1

using namespace std::chrono_literals;

class UltrasonicSensor
{
  public:
    UltrasonicSensor();
    UltrasonicSensor(int trigPin, int echoPin, float timeout = 1);
    float read(int times = 1);

  private:
    float _read();
    int trigPin;
    int echoPin;
    float timeout;
};
