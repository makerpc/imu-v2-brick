/* imu-v2-brick
 * Copyright (C) 2015 Olaf Lüke <olaf@tinkerforge.com>
 *
 * imu.h: Inertial Measurement Unit readout implementation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include "config.h"

#include "bricklib/drivers/twi/twid.h"

#define IMU_PERIOD_TYPE_ACC  0
#define IMU_PERIOD_TYPE_MAG  1
#define IMU_PERIOD_TYPE_ANG  2
#define IMU_PERIOD_TYPE_ALL  3
#define IMU_PERIOD_TYPE_ORI  4
#define IMU_PERIOD_TYPE_QUA  5

#define IMU_PERIOD_NUM       6

#define IMU_STARTUP_TIME     650 // see 1.2 (POR time)

#define BMO055_ADDRESS_HIGH  0x29
#define BMO055_ADDRESS_LOW   0x28

#define REG_PAGE_ID          0x07

// Page 0
#define REG_CHIP_ID          0x00
#define REG_ACC_ID           0x01
#define REG_MAG_ID           0x02
#define REG_GYR_ID           0x03
#define REG_SW_REV_ID_LSB    0x04
#define REG_SW_REV_ID_MSB    0x05
#define REG_BL_REV_ID        0x06
#define REG_ACC_DATA_X_LSB   0x08
#define REG_ACC_DATA_X_MSB   0x09
#define REG_ACC_DATA_Y_LSB   0x0A
#define REG_ACC_DATA_Y_MSB   0x0B
#define REG_ACC_DATA_Z_LSB   0x0C
#define REG_ACC_DATA_Z_MSB   0x0D
#define REG_MAG_DATA_X_LSB   0x0E
#define REG_MAG_DATA_X_MSB   0x0F
#define REG_MAG_DATA_Y_LSB   0x10
#define REG_MAG_DATA_Y_MSB   0x11
#define REG_MAG_DATA_Z_LSB   0x12
#define REG_MAG_DATA_Z_MSB   0x13
#define REG_GYR_DATA_X_LSB   0x14
#define REG_GYR_DATA_X_MSB   0x15
#define REG_GYR_DATA_Y_LSB   0x16
#define REG_GYR_DATA_Y_MSB   0x17
#define REG_GYR_DATA_Z_LSB   0x18
#define REG_GYR_DATA_Z_MSB   0x19
#define REG_EUL_HEADING_LSB  0x1A
#define REG_EUL_HEADING_MSB  0x1B
#define REG_EUL_ROLL_LSB     0x1C
#define REG_EUL_ROLL_MSB     0x1D
#define REG_EUL_PITCH_LSB    0x1E
#define REG_EUL_PITCH_MSB    0x1F
#define REG_QUA_DATA_W_LSB   0x20
#define REG_QUA_DATA_W_MSB   0x21
#define REG_QUA_DATA_X_LSB   0x22
#define REG_QUA_DATA_X_MSB   0x23
#define REG_QUA_DATA_Y_LSB   0x24
#define REG_QUA_DATA_Y_MSB   0x25
#define REG_QUA_DATA_Z_LSB   0x26
#define REG_QUA_DATA_Z_MSB   0x27
#define REG_LIA_DATA_X_LSB   0x28
#define REG_LIA_DATA_X_MSB   0x29
#define REG_LIA_DATA_Y_LSB   0x2A
#define REG_LIA_DATA_Y_MSB   0x2B
#define REG_LIA_DATA_Z_LSB   0x2C
#define REG_LIA_DATA_Z_MSB   0x2D
#define REG_GRV_DATA_X_LSB   0x2E
#define REG_GRV_DATA_X_MSB   0x2F
#define REG_GRV_DATA_Y_LSB   0x30
#define REG_GRV_DATA_Y_MSB   0x31
#define REG_GRV_DATA_Z_LSB   0x32
#define REG_GRV_DATA_Z_MSB   0x33
#define REG_TEMP             0x34
#define REG_CALIB_START      0x35
#define REG_ST_RESULT        0x36
#define REG_INT_STA          0x37
#define REG_SYS_CLK_STATUS   0x38
#define REG_SYS_STATUS       0x39
#define REG_SYS_ERR          0x3A
#define REG_UNIT_SEL         0x3B
#define REG_OPR_MODE         0x3D
#define REG_PWR_MODE         0x3E
#define REG_SYS_TRIGGER      0x3F
#define REG_TEMP_SOURCE      0x40
#define REG_AXIS_MAP_CONFIG  0x41
#define REG_AXIS_MAP_SIGN    0x42
#define REG_ACC_OFFSET_X_LSB 0x55
#define REG_ACC_OFFSET_X_MSB 0x56
#define REG_ACC_OFFSET_Y_LSB 0x57
#define REG_ACC_OFFSET_Y_MSB 0x58
#define REG_ACC_OFFSET_Z_LSB 0x59
#define REG_ACC_OFFSET_Z_MSB 0x5A
#define REG_MAG_OFFSET_X_LSB 0x5B
#define REG_MAG_OFFSET_X_MSB 0x5C
#define REG_MAG_OFFSET_Y_LSB 0x5D
#define REG_MAG_OFFSET_Y_MSB 0x5E
#define REG_MAG_OFFSET_Z_LSB 0x5F
#define REG_MAG_OFFSET_Z_MSB 0x60
#define REG_GYR_OFFSET_X_LSB 0x61
#define REG_GYR_OFFSET_X_MSB 0x62
#define REG_GYR_OFFSET_Y_LSB 0x63
#define REG_GYR_OFFSET_Y_MSB 0x64
#define REG_GYR_OFFSET_Z_LSB 0x65
#define REG_GYR_OFFSET_Z_MSB 0x66
#define REG_ACC_RADIUS_LSB   0x67
#define REG_ACC_RADIUS_MSB   0x68
#define REG_MAG_RADIUS_LSB   0x69
#define REG_MAG_RADIUS_MSB   0x6A

// Page 1
#define REG_ACC_CONFIG       0x08
#define REG_MAG_CONFIG       0x09
#define REG_GYR_CONFIG_0     0x0A
#define REG_GYR_CONFIG_1     0x0B
#define REG_ACC_SLEEP_CONFIG 0x0C
#define REG_GYR_SLEEP_CONFIG 0x0D
#define REG_INT_MSK          0x0F
#define REG_INT_EN           0x10
#define REG_ACC_AM_THRES     0x11
#define REG_ACC_INT_SETTINGS 0x12
#define REG_ACC_HG_DURATION  0x13
#define REG_ACC_HG_THRES     0x14
#define REG_ACC_NM_THRES     0x15
#define REG_ACC_NM_SET       0x16
#define REG_GYR_INT_SETTINGS 0x17
#define REG_GYR_HR_X_SET     0x18
#define REG_GYR_DUR_X        0x19
#define REG_GYR_HR_Y_SET     0x1A
#define REG_GYR_DUR_Y        0x1B
#define REG_GYR_HR_Z_SET     0x1C
#define REG_GYR_DUR_Z        0x1D
#define REG_GYR_AM_THRES     0x1E
#define REG_GYR_AM_SET       0x1F
#define REG_UNIQUE_ID_0      0x50
#define REG_UNIQUE_ID_1      0x51
#define REG_UNIQUE_ID_2      0x52
#define REG_UNIQUE_ID_3      0x53
#define REG_UNIQUE_ID_4      0x54
#define REG_UNIQUE_ID_5      0x55
#define REG_UNIQUE_ID_6      0x56
#define REG_UNIQUE_ID_7      0x57
#define REG_UNIQUE_ID_8      0x58
#define REG_UNIQUE_ID_9      0x59
#define REG_UNIQUE_ID_A      0x5A
#define REG_UNIQUE_ID_B      0x5B
#define REG_UNIQUE_ID_C      0x5C
#define REG_UNIQUE_ID_D      0x5D
#define REG_UNIQUE_ID_E      0x5E
#define REG_UNIQUE_ID_F      0x5F

typedef struct {
	int16_t acc_x; // 1m/s^2 = 100 LSB
	int16_t acc_y;
	int16_t acc_z;
	int16_t mag_x; // 1µT = 16 LSB
	int16_t mag_y;
	int16_t mag_z;
	int16_t gyr_x; // 1dps (degree-per-second) = 16 LSB
	int16_t gyr_y;
	int16_t gyr_z;
	int16_t eul_heading; // 1° = 16 LSB
	int16_t eul_roll;
	int16_t eul_pitch;
	uint16_t qua_w; // 1 Quaternion = 2^14 LSB
	uint16_t qua_x;
	uint16_t qua_y;
	uint16_t qua_z;
	int16_t lia_x; // 1m/s^2 = 100 LSB
	int16_t lia_y;
	int16_t lia_z;
	int16_t grv_x; // 1m/s^2 = 100 LSB
	int16_t grv_y;
	int16_t grv_z;
	int8_t temperature; // 1°C = 1 LSB
	uint8_t calibration_status;
} __attribute__((packed)) SensorData;

void tick_task(const uint8_t tick_type);
void make_period_callback(const uint8_t type);

void update_gyr_temperature_aprox(void);
void update_sensor_data(void);
void callback_accelerometer(Async *a);
void callback_magnetometer(Async *a);
void callback_gyroscope(Async *a);

void imu_blinkenlights(void);
void imu_leds_on(const bool on);
void bmo_read_register(const uint8_t reg, uint8_t *data, const uint8_t length);
void bmo_write_register(const uint8_t reg, const uint8_t value);

void imu_init(void);
#endif