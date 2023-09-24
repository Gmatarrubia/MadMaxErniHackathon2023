cmake_minimum_required(VERSION 3.10)

project(picar)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-psabi")




add_executable(madmaxRobot
  main.cpp
  component/LineSensor.cpp
  component/PidController.cpp
  component/UltrasonicSensor.cpp
  component/RobotControl.cpp
  component/LineSensorController.cpp
  common/flags.cpp
  i2c/smbus.c
)

target_include_directories(madmaxRobot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(madmaxRobot PUBLIC cxx_std_11)
target_link_libraries(madmaxRobot
  glog
  gflags
  wiringPi
  pthread
)






