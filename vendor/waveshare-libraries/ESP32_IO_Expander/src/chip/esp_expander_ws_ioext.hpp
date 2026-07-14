/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_expander_base.hpp"

namespace esp_expander {

/**
 * @brief The Waveshare "IO Extension" device class
 *
 * @note  This class is a derived class of `esp_expander::Base`, user can use it directly
 * @note  Used on Waveshare "B" revision boards (e.g. ESP32-S3-Touch-LCD-7B) in place of a
 *        standard IO expander chip. It is a companion MCU (CH32V003) exposing a simple I2C
 *        register interface, fixed at address 0x24.
 * @note  Pin map:
 *        | Pin Number   | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   |
 *        | ------------ | --- | --- | --- | --- | --- | --- | --- | --- |
 *        | Function     | IO0 | IO1 | IO2 | IO3 | IO4 | IO5 | IO6 | IO7 |
 */
class WS_IOExtension: public Base {
public:
    /**
     * @brief Construct a WS_IOExtension device. With this function, call `init()` will initialize I2C by using the
     *        host configuration.
     *
     * @param[in] scl_io  I2C SCL pin number
     * @param[in] sda_io  I2C SDA pin number
     * @param[in] address I2C device 7-bit address. Should be like `ESP_IO_EXPANDER_I2C_<chip name>_ADDRESS`.
     */
    WS_IOExtension(int scl_io, int sda_io, uint8_t address): Base(scl_io, sda_io, address) {}

    /**
     * @brief Construct a WS_IOExtension device. With this function, call `init()` will not initialize I2C, and users
     *        should initialize it manually.
     *
     * @param[in] host_id I2C host ID.
     * @param[in] address I2C device 7-bit address. Should be like `ESP_IO_EXPANDER_I2C_<chip name>_ADDRESS`.
     */
    WS_IOExtension(int host_id, uint8_t address): Base(host_id, address) {}

    /**
     * @brief Construct a WS_IOExtension device.
     *
     * @param[in] config Configuration for the object
     */
    WS_IOExtension(const Config &config): Base(config) {}

    /**
     * @brief Desutruct object. This function will call `del()` to delete the object.
     */
    ~WS_IOExtension() override;

    /**
     * @brief Begin object
     *
     * @note  This function sets all IO0-7 pins to output high-level mode by default.
     *
     * @return true if success, otherwise false
     */
    bool begin(void) override;
};

} // namespace esp_expander
