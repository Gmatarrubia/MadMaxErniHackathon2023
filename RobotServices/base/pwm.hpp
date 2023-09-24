#pragma once
#include <arpa/inet.h>
#include <string>

#include "base/i2c.hpp"
#include "common/flags.hpp"
#include "common/log.hpp"

class PWM : protected I2C {
public:
  PWM(const std::string &filename, int addr, int channel,
      const std::string &name)
      : I2C(filename, addr), channel_(channel), timer_(channel / 4),
        name_(name) {}

  int PulseWidth(uint16_t w) {
    CHECK(w < arr_) << name_ << " w = " << w << ", arr_ = " << arr_;
    LOG_INFO << name_ << " pwm w = " << w;
    return WriteUInt16(FLAGS_reg_chn + channel_, w);
  }
  int PulseWidthPercent(double p) {
    CHECK(p <= 100.0 && p >= 0) << name_ << " p = " << p;
    return PulseWidth(p / 100.0 * (arr_ - 1));
  }

  int SetFreqAndPeriod(int freq, int period) {
    int psc = static_cast<double>(FLAGS_clock) / (freq * period);
    return SetFreqPscArr(freq, psc, period);
  }

  int SetFreqAndPrescaler(int freq, int psc) {
    int arr = static_cast<double>(FLAGS_clock) / (freq * psc);
    return SetFreqPscArr(freq, psc, arr);
  }

  int SetPrescalerAndPeriod(int psc, int period) {
    int freq = static_cast<double>(FLAGS_clock) / (psc * period);
    return SetFreqPscArr(freq, psc, period);
  }

  std::string Name() const { return name_; }

private:
  int SetPrescaler(uint16_t psc) {
    return WriteUInt16(FLAGS_reg_psc + timer_, psc);
  }
  int SetAutoReload(uint16_t arr) {
    return WriteUInt16(FLAGS_reg_arr + timer_, arr);
  }
  int SetFreqPscArr(int freq, int psc, int arr) {
    LOG_INFO << name_ << " set freq/psc/arr = " << freq << "/" << psc << "/"
             << arr;
    freq_ = freq;
    psc_ = psc;
    arr_ = arr;

    int ret = SetPrescaler(psc_ - 1);
    if (ret != 0) {
      LOG_ERROR << "set prescaler to " << psc_ - 1 << " err: " << ret;
      return ret;
    }

    ret = SetAutoReload(arr_ - 1);
    if (ret != 0) {
      LOG_ERROR << "set arr to " << arr_ - 1 << " err: " << ret;
      return ret;
    }

    return 0;
  }

  int WriteUInt16(uint8_t command, uint16_t data) {
    return WriteWordData(command, htons(data));
  }

  int channel_;
  int timer_;
  int freq_;
  int psc_;
  int arr_;
  std::string name_;
};