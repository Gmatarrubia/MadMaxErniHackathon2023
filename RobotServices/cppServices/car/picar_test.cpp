#include <chrono>
#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <vector>
#include <wiringPi.h>

#include "car/picar.hpp"
#include "common/flags.hpp"
#include "common/log.hpp"

enum PicarAction {
  Forward = 0,
  Backward = 1,
  Turn = 2,
  CamYaw = 3,
  CamPitch = 4,
};

int main(int argc, char **argv) {
  FLAGS_alsologtostderr = true;
  google::InitGoogleLogging(argv[0]);
  wiringPiSetup();

  Picar car;
  car.Init();

  int action, val;
  while (std::cin >> action >> val) {
    switch (action) {
    case Forward:
      LOG_INFO << "forward " << val;
      car.Forward(val);
      break;
    case Backward:
      LOG_INFO << "backward " << val;
      car.Backward(val);
      break;
    case Turn:
      LOG_INFO << "turn " << val;
      car.SetDirection(val);
      break;
    case CamYaw:
      LOG_INFO << "cam yaw " << val;
      car.SetCamYaw(val);
      break;
    case CamPitch:
      LOG_INFO << "cam pitch " << val;
      car.SetCamPitch(val);
      break;
    default:
      car.Reset();
      return 0;
    }
  }

  return 0;
}