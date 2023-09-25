#include <chrono>
#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <vector>
#include <wiringPi.h>

#include "component/RobotControl.hpp"

#define LEFT 0
#define RIGHT 1
#define CAMERA 0
#define WHEELS 1
#define trigPin  27
#define echoPin  22

using namespace std::chrono_literals;

void selfTest()
{
  std::vector<Motor> motors;
  motors.emplace_back(FLAGS_channel_left_rear_speed,
                      FLAGS_channel_left_rear_dir, "left_rear");
  motors.emplace_back(FLAGS_channel_right_rear_speed,
                      FLAGS_channel_right_rear_dir, "right_rear");

  std::cout << "motor instance" << std::endl;
  for (int i = 0; i < motors.size(); i++) {
    int ret = motors[i].Init();
    std::cout << "motor init" << std::endl;
    if (ret != 0) {
      LOG_ERROR << "motor " << i << " init err: " << ret;
      return;
    }
  }

  std::vector<Servo> servos;
  servos.emplace_back(FLAGS_channel_servo_dir, FLAGS_dir_max_angle, "dir");

  for (int i = 0; i < servos.size(); i++) {
    int ret = servos[i].Init();
    if (ret != 0) {
      LOG_ERROR << "servo " << i << " init err: " << ret;
      return;
    }
  }

  motors[0].SetSpeed(50);
  motors[1].SetSpeed(50);
  std::this_thread::sleep_for(2000ms);
  motors[0].SetSpeed(0);
  motors[1].SetSpeed(50);
  std::this_thread::sleep_for(2000ms);
  motors[0].SetSpeed(50);
  motors[1].SetSpeed(0);
  std::this_thread::sleep_for(2000ms);  
  motors[0].SetSpeed(0);
  motors[1].SetSpeed(0);
  std::this_thread::sleep_for(2000ms);
}

void selfTest2()
{
  auto leftMotor = std::make_shared<Motor>(FLAGS_channel_left_rear_speed, FLAGS_channel_left_rear_dir, "left_rear");
  auto rightMotor = std::make_shared<Motor>(FLAGS_channel_right_rear_speed, FLAGS_channel_right_rear_dir, "right_rear");
  auto wheelsServo = std::make_shared<Servo>(FLAGS_channel_servo_dir, FLAGS_dir_max_angle, "dir");
  auto distanceSensor = std::make_shared<UltrasonicSensor>(trigPin, echoPin); 
  auto pidController = std::make_shared<PIDController>(); 
  auto lineSensor  = std::make_shared<LineSensor>();
  auto lineSensorController = std::make_shared<LineSensorController>();

  bool res = leftMotor->Init();
  if(res !=0)std::cout << "leftMotor error initialization" << std::endl;
  res = rightMotor->Init();
  if(res !=0)std::cout << "rightMotor error initialization" << std::endl;
  res = wheelsServo->Init();
  if(res !=0)std::cout << "wheelsServo error initialization" << std::endl;
  leftMotor->SetSpeed(50);
  rightMotor->SetSpeed(50);
  std::this_thread::sleep_for(2000ms);
  leftMotor->SetSpeed(0);
  rightMotor->SetSpeed(50);
  std::this_thread::sleep_for(2000ms);
  leftMotor->SetSpeed(0);
  rightMotor->SetSpeed(0);
  std::this_thread::sleep_for(2000ms);
  lineSensorController->readLineState();
/*
  for(int i = 0; i< 5; i++)
  {
    auto distance = distanceSensor->read();
    std::cout << "distance: " << distance << std::endl;
    auto lineSensorState = lineSensor->readLineState();
    std::cout << "lineSensorState: " << lineSensorState.leftSensor << "," << lineSensorState.centralSensor << "," << lineSensorState.rightSensor << std::endl;
    std::this_thread::sleep_for(500ms);
  }
  */

}

int main(int argc, char **argv) 
{
  FLAGS_alsologtostderr = false;
  google::InitGoogleLogging(argv[0]);
  if (wiringPiSetup() == -1) 
  {
      std::cerr << "Error al inicializar WiringPi." << std::endl;
      return 1;
  }
  selfTest2();
  return 1;
/*
  try
  {
    auto robotController  = std::make_shared<RobotControl>();
    robotController->init();
    robotController->startRobotControl(std::chrono::milliseconds(500));
  }
  catch(const std::exception& e)
  {
    std::cerr << "exception during robot initialization: " << e.what() << '\n';
  }
  */

  
 
 return 0;
}
