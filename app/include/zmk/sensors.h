/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <drivers/sensor.h>

#define _SENSOR_CHILD_LEN(node) 1 +
#define ZMK_KEYMAP_SENSORS_NODE DT_INST(0, zmk_keymap_sensors)
#define ZMK_KEYMAP_HAS_SENSORS DT_NODE_HAS_STATUS(ZMK_KEYMAP_SENSORS_NODE, okay)
#define ZMK_KEYMAP_SENSORS_BY_IDX(idx) DT_PHANDLE_BY_IDX(ZMK_KEYMAP_SENSORS_NODE, sensors, idx)

#if ZMK_KEYMAP_HAS_SENSORS
#define ZMK_KEYMAP_SENSORS_LEN DT_PROP_LEN(ZMK_KEYMAP_SENSORS_NODE, sensors)
#else
#define ZMK_KEYMAP_SENSORS_LEN 0
#endif

const struct zmk_sensor_config *zmk_sensors_get_config_at_position(uint8_t sensor_position);

struct zmk_sensor_config {
    uint16_t triggers_per_rotation;
};

struct zmk_sensor_channel_data {
    enum sensor_channel channel;
    struct sensor_value value;
};
