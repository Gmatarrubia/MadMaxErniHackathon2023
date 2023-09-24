#pragma once

#include <gflags/gflags.h>

DECLARE_string(file_name);
DECLARE_int32(reg_chn);
DECLARE_int32(reg_fre);
DECLARE_int32(reg_psc);
DECLARE_int32(reg_arr);
DECLARE_int32(clock);
DECLARE_int32(slave_addr);
DECLARE_int32(channel_servo_cam_yaw);
DECLARE_int32(channel_servo_cam_pitch);
DECLARE_int32(channel_servo_dir);
DECLARE_int32(channel_left_rear_dir);
DECLARE_int32(channel_left_rear_speed);
DECLARE_int32(channel_right_rear_dir);
DECLARE_int32(channel_right_rear_speed);
DECLARE_int32(servo_freq);
DECLARE_int32(servo_period);
DECLARE_int32(motor_period);
DECLARE_int32(motor_prescaler);
DECLARE_double(cam_yaw_max_angle);
DECLARE_double(cam_pitch_max_angle);
DECLARE_double(dir_max_angle);
DECLARE_double(servo_angle_to_percent_k);
DECLARE_double(servo_angle_to_percent_b);
DECLARE_string(joystick_filename);