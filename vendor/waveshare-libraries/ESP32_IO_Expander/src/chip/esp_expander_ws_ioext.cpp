/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_expander_utils.h"
#include "port/esp_io_expander_ws_ioext.h"
#include "esp_expander_ws_ioext.hpp"

namespace esp_expander {

WS_IOExtension::~WS_IOExtension()
{
    ESP_UTILS_LOG_TRACE_ENTER_WITH_THIS();

    ESP_UTILS_CHECK_FALSE_EXIT(del(), "Delete failed");

    ESP_UTILS_LOG_TRACE_EXIT_WITH_THIS();
}

bool WS_IOExtension::begin(void)
{
    ESP_UTILS_LOG_TRACE_ENTER_WITH_THIS();

    ESP_UTILS_CHECK_FALSE_RETURN(!isOverState(State::BEGIN), false, "Already begun");

    // Initialize the device if not initialized
    if (!isOverState(State::INIT)) {
        ESP_UTILS_CHECK_FALSE_RETURN(init(), false, "Init failed");
    }

    ESP_UTILS_CHECK_ERROR_RETURN(
        esp_io_expander_new_i2c_ws_ioext(
            static_cast<i2c_port_t>(getConfig().host_id), getConfig().device.address, &device_handle
        ), false, "Create WS_IOExtension failed"
    );
    ESP_UTILS_LOGD("Create WS_IOExtension @%p", device_handle);

    setState(State::BEGIN);

    ESP_UTILS_LOG_TRACE_EXIT_WITH_THIS();

    return true;
}

} // namespace esp_expander
