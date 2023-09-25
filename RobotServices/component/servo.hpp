#pragma once
#include <cstdlib>
#include <string>

#include "base/pwm.hpp"
#include "common/flags.hpp"
#include "common/log.hpp"

class Servo : protected PWM {
public:
  Servo(int channel, double max_angle, const std::string &name)
      : PWM(FLAGS_file_name, FLAGS_slave_addr, channel, name),
        max_angle_(std::abs(max_angle)) {}
  virtual int Init() {
    int ret = PWM::Init();
    if (ret != 0) {
      LOG_ERROR << Name() << " pwm init err: " << ret;
      return ret;
    }

    ret = SetFreqAndPeriod(FLAGS_servo_freq, FLAGS_servo_period);
    if (ret != 0) {
      LOG_ERROR << Name() << " set freq and period err: " << ret;
      return ret;
    }

    return SetAngle(0);
  }

  double GetAngle() const { return angle_; }

  int SetAngle(int angle) {
    if (angle < -max_angle_) {
      angle = -max_angle_;
    } else if (angle > max_angle_) {
      angle = max_angle_;
    }

    angle_ = angle;

    return PulseWidthPercent(FLAGS_servo_angle_to_percent_k * angle +
                             FLAGS_servo_angle_to_percent_b);
  }

private:
  double max_angle_;
  double angle_ = 0.0;
};