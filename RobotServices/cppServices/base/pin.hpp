#pragma once
#include <string>
#include <wiringPi.h>

#include "common/log.hpp"

enum PinValue : int {
  PinHigh = 1,
  PinLow = 0,
};

class Pin {
public:
  Pin(int channel, const std::string &name) : channel_(channel), name_(name) {}
  void Write(bool high) { SetValue(high ? PinHigh : PinLow); }

  int Read() {
    pinMode(channel_, INPUT);
    return digitalRead(channel_);
  }
  std::string Name() const { return name_; }

private:
  void SetValue(int val) {
    pinMode(channel_, OUTPUT);
    digitalWrite(channel_, val);
    LOG_INFO << name_ << " channel " << channel_ << " set to " << val;
  }
  int channel_;
  std::string name_;
};
