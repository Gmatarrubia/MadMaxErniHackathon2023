#pragma once

#include <string>
#include <vector>

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>

#include "common/log.hpp"

extern "C" {
#include "i2c/smbus.h"
}

class I2C {
public:
  I2C(const std::string &filename, int addr)
      : filename_(filename), addr_(addr) {}
  virtual ~I2C() {
    if (fd_ > 0) {
      close(fd_);
    }
  }
  virtual int Init() {
    fd_ = open(filename_.c_str(), O_RDWR);
    if (fd_ < 0) {
      return fd_;
    }

    int ret = ioctl(fd_, I2C_SLAVE, addr_);
    if (ret < 0) {
      return ret;
    }

    return 0;
  }

  int WriteByte(uint8_t data) { return i2c_smbus_write_byte(fd_, data); }

  int WriteByteData(uint8_t command, uint8_t data) {
    return i2c_smbus_write_byte_data(fd_, command, data);
  }

  int WriteWordData(uint8_t command, uint16_t data) {
    return i2c_smbus_write_word_data(fd_, command, data);
  }

  int WriteI2CBlockData(uint8_t command, uint8_t len, const uint8_t *data) {
    CHECK(len <= 32) << "smbus data oversize: " << len;
    return i2c_smbus_write_i2c_block_data(fd_, command, len, data);
  }

  int WriteI2CBlockData(uint8_t command, const std::vector<uint8_t> &data) {
    CHECK(data.size() <= 32) << "smbus data oversize: " << data.size();
    return WriteI2CBlockData(command, data.size(), data.data());
  }

  int ReadByte() { return i2c_smbus_read_byte(fd_); }

  int ReadByteData(uint8_t command) {
    return i2c_smbus_read_byte_data(fd_, command);
  }

  int ReadWordData(uint8_t command) {
    return i2c_smbus_read_word_data(fd_, command);
  }

  int ReadI2cBlockData(uint8_t command, std::vector<uint8_t> &data) {
    CHECK(data.size() <= 32) << "smbus data oversize: " << data.size();
    return i2c_smbus_read_i2c_block_data(fd_, command, data.size(),
                                         data.data());
  }

private:
  const std::string filename_;
  const int addr_;
  int fd_ = 0;
};