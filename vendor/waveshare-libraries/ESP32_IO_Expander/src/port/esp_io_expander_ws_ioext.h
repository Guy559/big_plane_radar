/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Port driver for the Waveshare "IO Extension" chip
 *
 * Used on the Waveshare ESP32-S3-Touch-LCD-7B (and related "B" revision boards), this is a
 * small companion MCU (CH32V003) programmed to expose a simple I2C register interface. It is
 * not compatible with any standard IO expander chip (CH422G/TCA95xx/HT8574), so it needs its
 * own driver. Register map, from Waveshare's own example firmware:
 *   0x02 mode   (bit=1 output, bit=0 input)
 *   0x03 output (bit=1 high, bit=0 low)
 *   0x04 input
 *   0x05 pwm    (backlight duty cycle, not exposed through this driver)
 *   0x06 adc    (battery voltage, not exposed through this driver)
 */

#pragma once

#include <stdint.h>

#include "driver/i2c.h"
#include "esp_err.h"

#include "esp_io_expander.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_IO_EXPANDER_WS_IOEXT_VER_MAJOR    (1)
#define ESP_IO_EXPANDER_WS_IOEXT_VER_MINOR    (0)
#define ESP_IO_EXPANDER_WS_IOEXT_VER_PATCH    (0)

/**
 * @brief Create a new Waveshare IO Extension driver
 *
 * @note The I2C communication should be initialized before use this function
 *
 * @param i2c_num: I2C port num
 * @param i2c_address: I2C address of chip
 * @param handle: IO expander handle
 *
 * @return
 *      - ESP_OK: Success, otherwise returns ESP_ERR_xxx
 */
esp_err_t esp_io_expander_new_i2c_ws_ioext(i2c_port_t i2c_num, uint32_t i2c_address, esp_io_expander_handle_t *handle);

/**
 * @brief I2C address of the Waveshare IO Extension chip (fixed, no address pins)
 */
#define ESP_IO_EXPANDER_I2C_WS_IOEXT_ADDRESS    (0x24)

#ifdef __cplusplus
}
#endif
