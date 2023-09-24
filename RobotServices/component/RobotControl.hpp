#pragma once

#include "common/flags.hpp"
#include "common/log.hpp"
#include "component/motor.hpp"
#include "component/servo.hpp"
#include "component/UltrasonicSensor.hpp"
#include "component/PidController.hpp"	
#include "component/LineSensor.hpp"
#include "component/LineSensorController.hpp"

#include <memory>
class RobotControl
{
private:
    std::shared_ptr<Motor> m_leftMotor;
    std::shared_ptr<Motor> m_rightMotor;
    std::shared_ptr<Servo> m_frontServo;
    std::shared_ptr<UltrasonicSensor> m_distanceSensor;
    std::shared_ptr<LineSensor> m_lineSensor;
    double m_currentAngle;
    bool m_controlRobot;
    std::thread m_controlThread;

public:
    RobotControl();
    RobotControl(const std::shared_ptr<Motor>& leftMotor, const std::shared_ptr<Motor>& rightMotor, const std::shared_ptr<Servo> frontServo, const std::shared_ptr<UltrasonicSensor>& distanceSensor, const std::shared_ptr<LineSensor>& lineSensor);
    ~RobotControl();
    void init();
    void forward(const int32_t speed);
    void turnLeft(const int32_t speed);
    void turnRight(const int32_t speed);
    void controlRobot(const std::chrono::milliseconds& controlPeriod);
    void stop();
    void startRobotControl(const std::chrono::milliseconds& controlPeriod);
    void stopRobotControl();
};


