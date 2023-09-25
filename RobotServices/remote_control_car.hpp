#pragma once
#include "car/picar.hpp"
#include "common/log.hpp"
#include "joystick/joystick_pi.hpp"

constexpr int16_t kAxisMax = 32767;
constexpr int16_t kAxisMin = -32767;

class RemoteControlCar : public JoyStickPi {
public:
  RemoteControlCar() = default;

  int Init() {
    CHECK(JoyStickPi::Init() == 0) << "joystick init err";
    CHECK(picar_.Init() == 0) << "picar init err";
    return 0;
  }

  virtual void HandleButton(ButtonName btn, int16_t val, uint32_t t) {
    JoyStickPi::HandleButton(btn, val, t);
    switch (btn) {
    case ButtonB:
      picar_.Reset();
    }
  }

  virtual void HandleAxis(AxisName axis, int16_t val, uint32_t t) {
    JoyStickPi::HandleAxis(axis, val, t);
    switch (axis) {
    case AxisLeftHandleHorizontal:
      picar_.SetDirection(ratio(val) * FLAGS_dir_max_angle);
      break;
    case AxisRightHandleVertical:
      picar_.Forward(-ratio(val) * 100.0);
      break;
    case AxisDirLeftRight:
      if (val == kAxisMax) {
        picar_.SetCamYaw(picar_.GetCamYaw() + 5.0);
      } else if (val == kAxisMin) {
        picar_.SetCamYaw(picar_.GetCamYaw() - 5.0);
      }
      break;
    case AxisDirUpDown:
      if (val == kAxisMin) {
        picar_.SetCamPitch(picar_.GetCamPitch() + 5.0);
      } else if (val == kAxisMax) {
        picar_.SetCamPitch(picar_.GetCamPitch() - 5.0);
      }
      break;
    case AxisLeftHandleVertical:
      picar_.SetCamPitch(-ratio(val) * FLAGS_cam_pitch_max_angle);
      break;
    case AxisRightHandleHorizontal:
      picar_.SetCamYaw(ratio(val) * FLAGS_cam_yaw_max_angle);
      break;
    }
  }

  static double ratio(double val) { return val / kAxisMax; }

private:
  Picar picar_;
};