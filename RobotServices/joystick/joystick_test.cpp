#include "common/log.hpp"
#include "joystick/joystick_base.hpp"

int main(int argc, char **argv) {
  FLAGS_alsologtostderr = true;
  google::InitGoogleLogging(argv[0]);

  JoyStickBase js("/dev/input/js0");

  CHECK(js.Init() == 0) << "joystick init failed";
  js.Run();
  return 0;
}
