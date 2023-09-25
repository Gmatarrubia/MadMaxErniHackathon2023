#pragma once
#include <algorithm>
#include <cmath>
#include <string>

#include "base/pin.hpp"
#include "base/pwm.hpp"
#include "common/flags.hpp"
#include "common/log.hpp"

class Motor : protected PWM {
public:
  Motor(int speed_chan, int dir_chan, const std::string &name)
      : PWM(FLAGS_file_name, FLAGS_slave_addr, speed_chan, name),
        direction_pin_(dir_chan, name) {}

  virtual int Init() {
    int ret = PWM::Init();
    if (ret != 0) {
      LOG_ERROR << Name() << " pwm init err: " << ret;
      return ret;
    }

    ret = SetPrescalerAndPeriod(FLAGS_motor_prescaler, FLAGS_motor_period);
    if (ret != 0) {
      LOG_ERROR << Name() << " set freq and period err: " << ret;
      return ret;
    }

    return SetSpeed(0);
  }

  double GetSpeed() const { return speed_; }

  int SetSpeed(double s) {
    direction_pin_.Write(s > 0);
    speed_ = s;
    return PulseWidthPercent(std::min(std::fabs(s), 100.0));
  }
  int Stop() { return SetSpeed(0); }

private:
  double speed_ = 0;
  Pin direction_pin_;
};
