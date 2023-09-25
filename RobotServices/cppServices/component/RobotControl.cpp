#include "RobotControl.hpp"
#include <cstdlib>
#include <thread>

RobotControl::RobotControl()
{
  m_leftMotor = std::make_shared<Motor>(FLAGS_channel_left_rear_speed, FLAGS_channel_left_rear_dir, "left_rear");
  m_rightMotor = std::make_shared<Motor>(FLAGS_channel_right_rear_speed, FLAGS_channel_right_rear_dir, "right_rear");
  m_frontServo = std::make_shared<Servo>(FLAGS_channel_servo_dir, FLAGS_dir_max_angle, "dir");
  m_distanceSensor = std::make_shared<UltrasonicSensor>(); 
  m_lineSensor  = std::make_shared<LineSensor>();

}

RobotControl::RobotControl(const std::shared_ptr<Motor>& leftMotor, const std::shared_ptr<Motor>& rightMotor, const std::shared_ptr<Servo> frontServo, const std::shared_ptr<UltrasonicSensor>& distanceSensor, const std::shared_ptr<LineSensor>& lineSensor) 
                           : m_leftMotor(leftMotor),m_rightMotor(rightMotor),m_frontServo(frontServo),m_distanceSensor(distanceSensor),m_lineSensor(lineSensor)
{
}

RobotControl::~RobotControl()
{
}


void RobotControl::init()
{
    try
    {
        auto result = m_leftMotor->Init();
        if(result != 0)
        {
            std::cerr << "Error during initialization Left motor" << std::endl;
        }

        result = m_rightMotor->Init();
        if(result != 0)
        {
            std::cerr << "Error during initialization Right motor" << std::endl;
        }

        m_frontServo->Init();
        if(result != 0)
        {
            std::cerr << "Error during initialization Front servo" << std::endl;
        }         
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
   
}

void RobotControl::forward(const int32_t speed)
{
    
    const auto currentAngle = m_frontServo->GetAngle();
    if(currentAngle !=0)
    {
        auto absCurrentAngle = std::abs(currentAngle);
        if(absCurrentAngle > 40) 
            absCurrentAngle = 40;

        auto power = (100 - absCurrentAngle) / 100.0;
        if ((currentAngle / absCurrentAngle) > 0)
        {
            m_leftMotor->SetSpeed(speed * power);
            m_rightMotor->SetSpeed(-speed);            
        }
        else
        {
            m_leftMotor->SetSpeed(speed);
            m_rightMotor->SetSpeed(-speed * power);           
        }
    }
    else
    {
        m_leftMotor->SetSpeed(speed);
        m_rightMotor->SetSpeed(-speed);          
    }
}

void RobotControl::turnLeft(const int32_t speed)
{
    m_frontServo->SetAngle(20);
    forward(speed);    
}

void RobotControl::turnRight(const int32_t speed)
{
    m_frontServo->SetAngle(-20);
    forward(speed);    
}

void RobotControl::stop()
{
    m_leftMotor->SetSpeed(0);
    m_rightMotor->SetSpeed(0);

}

void RobotControl::controlRobot(const std::chrono::milliseconds& pollingInterval)
{
    while (m_controlRobot)
    {
        auto distance = m_distanceSensor->read();
        std::cout << "distance: " << distance << std::endl;
        auto currentLineSensor = m_lineSensor->readLineState();
        std::cout << "lineSensorState: " << currentLineSensor.leftSensor << "," << currentLineSensor.centralSensor << "," << currentLineSensor.rightSensor << std::endl;

        if(currentLineSensor.centralSensor == 1)
        {
            m_frontServo->SetAngle(0);
            forward(20);
        }
        else if (currentLineSensor.leftSensor == 1)
        {
            turnLeft(20);
        }
        else if (currentLineSensor.rightSensor == 1)
        {
            turnRight(20);
        } 

        std::this_thread::sleep_for(pollingInterval);
    }

}

void RobotControl::startRobotControl(const std::chrono::milliseconds& pollingInterval)
{
    try
    {
        m_controlRobot = true;
        m_controlThread = std::thread([this, pollingInterval] { controlRobot(pollingInterval); });
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error starting control thread" << e.what() << std::endl;
    }
}

void RobotControl::stopRobotControl()
{
    try
    {
        m_controlRobot = false;
        if (m_controlThread.joinable())
        {
            m_controlThread.join();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error stoping control thread" << e.what() << std::endl;
    }
}