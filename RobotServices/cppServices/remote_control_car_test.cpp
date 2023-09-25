#include "common/flags.hpp"
#include "common/log.hpp"
#include "component/servo.hpp"
#include "remote_control_car.hpp"

int main(int argc, char **argv) {
  FLAGS_alsologtostderr = true;
  google::InitGoogleLogging(argv[0]);
  wiringPiSetup();

  RemoteControlCar car;
  CHECK(car.Init() == 0) << "remote control car init err";

  car.Run();
  return 0;
}
