#include "common/flags.hpp"
#include "common/log.hpp"
#include "component/motor.hpp"
#include "component/servo.hpp"
#include "component/UltrasonicSensor.hpp"
#include <chrono>
#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <vector>
#include <wiringPi.h>

#define trigerPinNumber  27
#define echoPinNumber  22

using namespace std::chrono_literals;

UltrasonicSensor::UltrasonicSensor()
{
    this->trigPin = trigerPinNumber;
    this->echoPin = echoPinNumber;
    this->timeout = timeout;
    std::cout << "trigPin: " << trigPin << "echoPin: " << echoPin << std::endl;
    // wiringPiSetup();
    wiringPiSetupGpio();
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    std::cout << "trigPin: " << trigPin << "echoPin: " << echoPin << std::endl;
}

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin, float timeout)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->timeout = timeout;
    std::cout << "trigPin: " << trigPin << "echoPin: " << echoPin << std::endl;
    // wiringPiSetup();
    wiringPiSetupGpio();
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    std::cout << "trigPin: " << trigPin << "echoPin: " << echoPin << std::endl;
}

float UltrasonicSensor::read(int times)
{
    for (int i = 0; i < times; ++i)
    {
        float result = _read();
        if (result != -1)
        {
            return result;
        }
    }
    return -1;
}

float UltrasonicSensor::_read()
{
    digitalWrite(trigPin, LOW);
    usleep(10000);
    digitalWrite(trigPin, HIGH);
    usleep(10);
    digitalWrite(trigPin, LOW);
    time_t pulseEnd = 0;
    time_t pulseStart = 0;
    time_t timeoutStart = time(nullptr);
    while (digitalRead(echoPin) == LOW)
    {
        pulseStart = micros();
        if (pulseStart - timeoutStart > timeout)
        {
            std::cout << "return -1" << std::endl;

            return -1;
        }
    }

    while (digitalRead(echoPin) == HIGH)
    {
        pulseEnd = micros();
        if (pulseEnd - timeoutStart > timeout)
        {
            std::cout << "return -11" << std::endl;
            return -1;
        }
    }

    double during = difftime(pulseEnd, pulseStart);
   // std::cout << "pulseEnd: " << pulseEnd << "pulseStart" << pulseStart << std::endl;
    double distance = std::round(during * 340 / 2 * 100);
    //std::cout << "during: " << during << "cm:" << cm << std::endl;
    std::cout << "Sensor distance:" << distance << "cm" << std::endl;
    return distance;
}
