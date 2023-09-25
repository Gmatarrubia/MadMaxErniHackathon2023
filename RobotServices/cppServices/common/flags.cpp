#include "common/flags.hpp"

DEFINE_string(file_name, "/dev/i2c-1", "i2c filename");
DEFINE_int32(reg_chn, 0x20, "REG channel_");
DEFINE_int32(reg_fre, 0x30, "REG Frequency");
DEFINE_int32(reg_psc, 0x40, "REG Prescaler");
DEFINE_int32(reg_arr, 0x44, "REG Auto reload register");
DEFINE_int32(clock, 72000000, "System clock freq");
DEFINE_int32(slave_addr, 0x14, "smbus slave addr");
DEFINE_int32(channel_servo_cam_yaw, 0, "");
DEFINE_int32(channel_servo_cam_pitch, 1, "");
DEFINE_int32(channel_servo_dir, 2, "");
DEFINE_int32(channel_left_rear_dir, 4, "");
DEFINE_int32(channel_right_rear_dir, 5, "");
DEFINE_int32(channel_left_rear_speed, 13, "");
DEFINE_int32(channel_right_rear_speed, 12, "");
DEFINE_int32(servo_freq, 50, "servo prescaled frequency");
DEFINE_int32(servo_period, 4096, "servo period, i.e. arr + 1");
DEFINE_int32(motor_prescaler, 10, "motor prescaler, i.e. psc + 1");
DEFINE_int32(motor_period, 4096, "motor period, i.e. arr + 1");
DEFINE_double(cam_yaw_max_angle, 60.0, "max yaw of cam");
DEFINE_double(cam_pitch_max_angle, 60.0, "max pitch of cam");
DEFINE_double(dir_max_angle, 35.0, "max dir of vehicle");
DEFINE_double(servo_angle_to_percent_k, 1.0 / 18.0, "percent = k * angle + b");
DEFINE_double(servo_angle_to_percent_b, 7.5, "percent = k * angle + b");
DEFINE_string(joystick_filename, "/dev/input/js0", "joystick filename");