#include <chrono>
#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <vector>
#include <wiringPi.h>

#include "common/flags.hpp"
#include "common/log.hpp"
#include "component/motor.hpp"
#include "component/servo.hpp"

#define LEFT 0
#define RIGHT 1
#define CAMERA 0
#define WHEELS 1

using namespace std::chrono_literals;


class UltrasonicSensor {
public:
    UltrasonicSensor(int trigPin, int echoPin, float timeout = 1) {
        this->trigPin = trigPin;
        this->echoPin = echoPin;
        this->timeout = timeout;
        std::cout << "trigPin: " << trigPin << "echoPin: " << echoPin << std::endl;
        //wiringPiSetup();
        wiringPiSetupGpio();
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
        std::cout << "trigPin: " << trigPin << "echoPin: " << echoPin << std::endl;
    }

    float read(int times = 10) {
        for (int i = 0; i < times; ++i) {
            float result = _read();
            if (result != -1) {
                return result;
            }
        }
        return -1;
    }

private:
    int trigPin;
    int echoPin;
    float timeout;
    float _read() {
    //Pin triggerPin = Pin(trigPin, "trigger");
    //Pin echoP = Pin(echoPin, "echo");
	//triggerPin.Write(false);//digitalWrite(trigPin, LOW);
	digitalWrite(trigPin, LOW);
        usleep(10000);
         //triggerPin.Write(true);//digitalWrite(trigPin, HIGH);
         digitalWrite(trigPin, HIGH);
        usleep(10);
        //triggerPin.Write(false);//digitalWrite(trigPin, LOW);
        digitalWrite(trigPin, LOW);
        time_t pulseEnd = 0;
        time_t pulseStart = 0;
        time_t timeoutStart = time(nullptr);
        while (digitalRead(echoPin) == LOW) {
        //while (echoP.Read() == LOW) {
            pulseStart = micros();//time(nullptr);
            if (pulseStart - timeoutStart > timeout) {
       std::cout << "return -1" << std::endl;

                return -1;
            }
        }

        while (digitalRead(echoPin) == HIGH) {
        //while (echoP.Read() == HIGH) {
            pulseEnd = micros();//time(nullptr);
            if (pulseEnd - timeoutStart > timeout) {
       std::cout << "return -11" << std::endl;
                return -1;
            }
        }

        double during = difftime(pulseEnd, pulseStart);
        std::cout << "pulseEnd: " << pulseEnd << "pulseStart" << pulseStart << std::endl;
        //double during = pulseEnd - pulseStart;

        double cm = std::round(during * 340 / 2 * 100);
        std::cout << "during: " << during << "cm:" << cm << std::endl;
        return cm;
    }
};


int main() {
    int trigPin = 27;
    int echoPin = 22;
    UltrasonicSensor sensor(trigPin, echoPin);

    while (true) {
        float distance = sensor.read();
        if (distance != -1) {
            std::cout << "Distancia: " << distance << " cm" << std::endl;
        } else {
            std::cout << "Tiempo de espera agotado" << std::endl;
        }
        usleep(500000); // Espera 0.5 segundos antes de la próxima lectura
    }

    return 0;
}

