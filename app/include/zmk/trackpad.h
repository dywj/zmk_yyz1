/*
 * Copyright (c) 2023 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr/kernel.h>

typedef uint8_t zmk_trackpad_finger_contacts_t;

struct zmk_trackpad_finger_data_t {
    bool present;
    bool palm;
    uint16_t x, y;
};

void zmk_trackpad_set_mouse_mode(bool mouse_mode);

void zmk_trackpad_set_button_mode(bool button_mode);

void zmk_trackpad_set_surface_mode(bool surface_mode);

struct k_work_q *zmk_trackpad_work_q();