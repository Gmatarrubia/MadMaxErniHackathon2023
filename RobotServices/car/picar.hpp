#pragma once
#include <cstdlib>

#include "common/flags.hpp"
#include "component/motor.hpp"
#include "component/servo.hpp"

// speed: 0 - 100
class Picar {
public:
  Picar()
      : left_(FLAGS_channel_left_rear_speed, FLAGS_channel_left_rear_dir,
              "left_motor"),
        right_(FLAGS_channel_right_rear_speed, FLAGS_channel_right_rear_dir,
               "right_motor"),
        cam_yaw_(FLAGS_channel_servo_cam_yaw, FLAGS_cam_yaw_max_angle,
                 "cam_yaw_servo"),
        cam_pitch_(FLAGS_channel_servo_cam_pitch, FLAGS_cam_pitch_max_angle,
                   "cam_pitch_servo"),
        dir_(FLAGS_channel_servo_dir, FLAGS_dir_max_angle, "dir_servo") {}

  int Init() {
    CHECK(left_.Init() == 0) << "left init failed";
    CHECK(right_.Init() == 0) << "right init failed";
    CHECK(cam_yaw_.Init() == 0) << "cam_yaw init failed";
    CHECK(cam_pitch_.Init() == 0) << "cam_pitch init failed";
    CHECK(dir_.Init() == 0) << "dir init failed";
    return 0;
  }

  void Forward(double speed) {
    double angle = dir_.GetAngle();
    double scale = (100.0 - std::abs(angle)) / 100.0;
    if (angle > 0) {
      left_.SetSpeed(-speed);
      right_.SetSpeed(speed * scale);
    } else {
      left_.SetSpeed(-speed * scale);
      right_.SetSpeed(speed);
    }
  }

  void Backward(double speed) { Forward(-speed); }
  void Stop() { Forward(0.0); }

  void SetDirection(double angle) { dir_.SetAngle(angle); }
  void SetCamPitch(double angle) { cam_pitch_.SetAngle(-angle); }
  void SetCamYaw(double angle) { cam_yaw_.SetAngle(-angle); }

  void Reset() {
    Stop();
    SetDirection(0);
    SetCamPitch(0);
    SetCamYaw(0);
  }

  double GetDirection() const { return dir_.GetAngle(); }
  double GetCamYaw() const { return -cam_yaw_.GetAngle(); }
  double GetCamPitch() const { return -cam_pitch_.GetAngle(); }

private:
  Motor left_, right_;
  Servo cam_yaw_, cam_pitch_, dir_;
};