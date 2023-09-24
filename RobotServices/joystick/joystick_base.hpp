#pragma once
#include <string>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common/log.hpp"

struct JsEvent {
  uint32_t time;  // event timestamp in milliseconds
  int16_t value;  // value
  uint8_t type;   // event type
  uint8_t number; // axis/button number
};

enum EventType : uint8_t {
  JsEventButton = 0x01, // Button pressed/released
  JsEventAxis = 0x02,   // joystick moved
  JsEventInit = 0x80,   // initial state of the device
};

class JoyStickBase {
public:
  JoyStickBase(const std::string &filename) : filename_(filename) {}
  virtual ~JoyStickBase() {
    if (fd_ > 0) {
      close(fd_);
    }
  }

  virtual void Handler(const JsEvent &e) {
    LOG_INFO << "js event: type " << int(e.type) << ", number " << int(e.number)
             << ", value " << e.value << ", time " << e.time;
  }

  int Init() {
    fd_ = open(filename_.c_str(), O_RDONLY);
    if (fd_ < 0) {
      LOG_ERROR << "joystick " << filename_ << " init err: " << fd_;
      return fd_;
    }
    return 0;
  }

  void Run() {
    JsEvent e;
    while (true) {
      auto n = read(fd_, &e, sizeof(e));
      if (n < 0) {
        LOG_ERROR << "read err: " << n;
      }
      Handler(e);
    }
  }

private:
  std::string filename_;
  int fd_;
};