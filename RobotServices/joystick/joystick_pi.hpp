#pragma once
#include <iostream>
#include <string>

#include "common/flags.hpp"
#include "common/log.hpp"
#include "joystick/joystick_base.hpp"

enum ButtonName : uint8_t {
  ButtonA = 0,
  ButtonB = 1,
  ButtonX = 3,
  ButtonY = 4,
  ButtonL1 = 6,
  ButtonR1 = 7,
  ButtonL2 = 8,
  ButtonR2 = 9,
  ButtonSelect = 10,
  ButtonStart = 11,
  ButtonLeftHandle = 13,
  ButtonRightHandle = 14,
};

enum AxisName : uint8_t {
  AxisLeftHandleHorizontal = 0,  // left: -32767 right: 32767
  AxisLeftHandleVertical = 1,    // up: -32767 down: 32767
  AxisRightHandleHorizontal = 2, // left: -32767 right: 32767
  AxisRightHandleVertical = 3,   // up: -32767 down: 32767
  AxisR2 = 4,                    // pressed: 32767, released: -32767
  AxisL2 = 5,                    // pressed: 32767, released: -32767
  AxisDirLeftRight = 6,          // left: -32767 right: 32767
  AxisDirUpDown = 7,             // up: -32767 down: 32767
};

class JoyStickPi : public JoyStickBase {
public:
  JoyStickPi() : JoyStickBase(FLAGS_joystick_filename) {}

  virtual void Handler(const JsEvent &e) {
    switch (e.type) {
    case JsEventButton:
      HandleButton(static_cast<ButtonName>(e.number), e.value, e.time);
      break;
    case JsEventAxis:
      HandleAxis(static_cast<AxisName>(e.number), e.value, e.time);
      break;
    }
  }

  virtual void HandleButton(ButtonName btn, int16_t val, uint32_t t) {
    LOG_INFO << "button " << btn << " val " << val << " time " << t;
  }

  virtual void HandleAxis(AxisName axis, int16_t val, uint32_t t) {
    LOG_INFO << "axis " << axis << " val " << val << " time " << t;
  }
};