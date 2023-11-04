/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include <zmk/keys.h>
#include <dt-bindings/zmk/hid_usage.h>
#include <dt-bindings/zmk/hid_usage_pages.h>

#define ZMK_HID_KEYBOARD_NKRO_MAX_USAGE HID_USAGE_KEY_KEYPAD_EQUAL

#define COLLECTION_REPORT 0x03

#define ZMK_REPORT_ID_KEYBOARD 0x01
#define ZMK_REPORT_ID_LEDS 0x01
#define ZMK_REPORT_ID_CONSUMER 0x02

#define ZMK_REPORT_ID_TOUCHPAD_MOUSE 0x05

static const uint8_t zmk_hid_report_desc[] = {
    HID_USAGE_PAGE(HID_USAGE_GEN_DESKTOP),
    HID_USAGE(HID_USAGE_GD_KEYBOARD),
    HID_COLLECTION(HID_COLLECTION_APPLICATION),
    HID_REPORT_ID(ZMK_REPORT_ID_KEYBOARD),
    HID_USAGE_PAGE(HID_USAGE_KEY),
    HID_USAGE_MIN8(HID_USAGE_KEY_KEYBOARD_LEFTCONTROL),
    HID_USAGE_MAX8(HID_USAGE_KEY_KEYBOARD_RIGHT_GUI),
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX8(0x01),

    HID_REPORT_SIZE(0x01),
    HID_REPORT_COUNT(0x08),
    /* INPUT (Data,Var,Abs) */
    HID_INPUT(0x02),

    HID_USAGE_PAGE(HID_USAGE_KEY),
    HID_REPORT_SIZE(0x08),
    HID_REPORT_COUNT(0x01),
    /* INPUT (Cnst,Var,Abs) */
    HID_INPUT(0x03),

    HID_USAGE_PAGE(HID_USAGE_LED),
    HID_USAGE_MIN8(HID_USAGE_LED_NUM_LOCK),
    HID_USAGE_MAX8(HID_USAGE_LED_KANA),
    HID_REPORT_SIZE(0x01),
    HID_REPORT_COUNT(0x05),
    /* OUTPUT (Data,Var,Abs) */
    HID_OUTPUT(0x02),

    HID_USAGE_PAGE(HID_USAGE_LED),
    HID_REPORT_SIZE(0x03),
    HID_REPORT_COUNT(0x01),
    /* OUTPUT (Cnst,Var,Abs) */
    HID_OUTPUT(0x03),

    HID_USAGE_PAGE(HID_USAGE_KEY),

#if IS_ENABLED(CONFIG_ZMK_HID_REPORT_TYPE_NKRO)
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX8(0x01),
    HID_USAGE_MIN8(0x00),
    HID_USAGE_MAX8(ZMK_HID_KEYBOARD_NKRO_MAX_USAGE),
    HID_REPORT_SIZE(0x01),
    HID_REPORT_COUNT(ZMK_HID_KEYBOARD_NKRO_MAX_USAGE + 1),
    /* INPUT (Data,Ary,Abs) */
    HID_INPUT(0x02),
#elif IS_ENABLED(CONFIG_ZMK_HID_REPORT_TYPE_HKRO)
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX16(0xFF, 0x00),
    HID_USAGE_MIN8(0x00),
    HID_USAGE_MAX8(0xFF),
    HID_REPORT_SIZE(0x08),
    HID_REPORT_COUNT(CONFIG_ZMK_HID_KEYBOARD_REPORT_SIZE),
    /* INPUT (Data,Ary,Abs) */
    HID_INPUT(0x00),
#else
#error "A proper HID report type must be selected"
#endif

    HID_END_COLLECTION,
    HID_USAGE_PAGE(HID_USAGE_CONSUMER),
    HID_USAGE(HID_USAGE_CONSUMER_CONSUMER_CONTROL),
    HID_COLLECTION(HID_COLLECTION_APPLICATION),
    HID_REPORT_ID(ZMK_REPORT_ID_CONSUMER),
    HID_USAGE_PAGE(HID_USAGE_CONSUMER),

#if IS_ENABLED(CONFIG_ZMK_HID_CONSUMER_REPORT_USAGES_BASIC)
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX16(0xFF, 0x00),
    HID_USAGE_MIN8(0x00),
    HID_USAGE_MAX8(0xFF),
    HID_REPORT_SIZE(0x08),
#elif IS_ENABLED(CONFIG_ZMK_HID_CONSUMER_REPORT_USAGES_FULL)
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX16(0xFF, 0x0F),
    HID_USAGE_MIN8(0x00),
    HID_USAGE_MAX16(0xFF, 0x0F),
    HID_REPORT_SIZE(0x10),
#else
#error "A proper consumer HID report usage range must be selected"
#endif
    HID_REPORT_COUNT(CONFIG_ZMK_HID_CONSUMER_REPORT_SIZE),
    /* INPUT (Data,Ary,Abs) */
    HID_INPUT(0x00),
    HID_END_COLLECTION,
#if IS_ENABLED(CONFIG_ZMK_TRACKPAD)
    HID_USAGE_PAGE(HID_USAGE_GD),
    HID_USAGE(HID_USAGE_GD_MOUSE),
    HID_COLLECTION(HID_COLLECTION_APPLICATION),
    HID_REPORT_ID(ZMK_REPORT_ID_TOUCHPAD_MOUSE),
    HID_USAGE(HID_USAGE_GD_POINTER),
    HID_COLLECTION(HID_COLLECTION_PHYSICAL),
    // Button
    HID_USAGE_PAGE(HID_USAGE_GEN_BUTTON),
    HID_USAGE_MIN8(1),
    HID_USAGE_MAX8(2),
    HID_LOGICAL_MIN8(0),
    HID_LOGICAL_MAX8(1),
    HID_REPORT_SIZE(1),
    HID_REPORT_COUNT(2),
    HID_INPUT(0x02),
    HID_REPORT_COUNT(6),
    HID_INPUT(0x03),
    // Axes
    HID_USAGE_PAGE(HID_USAGE_GD),
    HID_USAGE(HID_USAGE_GD_X),
    HID_USAGE(HID_USAGE_GD_Y),
    HID_USAGE(HID_USAGE_GD_WHEEL),
    // -127 -> 127
    HID_LOGICAL_MIN8(0x81),
    HID_LOGICAL_MAX8(0x7f),
    HID_REPORT_SIZE(8),
    HID_REPORT_COUNT(3),
    // Var rel input
    HID_INPUT(0x06),
    HID_END_COLLECTION,
    HID_END_COLLECTION,
#endif

};

// struct zmk_hid_boot_report
// {
//     uint8_t modifiers;
//     uint8_t _unused;
//     uint8_t keys[6];
// } __packed;

struct zmk_hid_keyboard_report_body {
    zmk_mod_flags_t modifiers;
    uint8_t _reserved;
#if IS_ENABLED(CONFIG_ZMK_HID_REPORT_TYPE_NKRO)
    uint8_t keys[(ZMK_HID_KEYBOARD_NKRO_MAX_USAGE + 1) / 8];
#elif IS_ENABLED(CONFIG_ZMK_HID_REPORT_TYPE_HKRO)
    uint8_t keys[CONFIG_ZMK_HID_KEYBOARD_REPORT_SIZE];
#endif
} __packed;

struct zmk_hid_keyboard_report {
    uint8_t report_id;
    struct zmk_hid_keyboard_report_body body;
} __packed;

struct zmk_hid_led_report_body {
    uint8_t leds;
} __packed;

struct zmk_hid_led_report {
    uint8_t report_id;
    struct zmk_hid_led_report_body body;
} __packed;

struct zmk_hid_consumer_report_body {
#if IS_ENABLED(CONFIG_ZMK_HID_CONSUMER_REPORT_USAGES_BASIC)
    uint8_t keys[CONFIG_ZMK_HID_CONSUMER_REPORT_SIZE];
#elif IS_ENABLED(CONFIG_ZMK_HID_CONSUMER_REPORT_USAGES_FULL)
    uint16_t keys[CONFIG_ZMK_HID_CONSUMER_REPORT_SIZE];
#endif
} __packed;

struct zmk_hid_consumer_report {
    uint8_t report_id;
    struct zmk_hid_consumer_report_body body;
} __packed;

#if IS_ENABLED(CONFIG_ZMK_TRACKPAD)
struct zmk_hid_touchpad_mouse_report_body {
    uint8_t buttons;
    int8_t xDelta;
    int8_t yDelta;
    int8_t scrollDelta;
} __packed;

struct zmk_hid_touchpad_mouse_report {
    uint8_t report_id;
    struct zmk_hid_touchpad_mouse_report_body body;
} __packed;

#endif

zmk_mod_flags_t zmk_hid_get_explicit_mods();
int zmk_hid_register_mod(zmk_mod_t modifier);
int zmk_hid_unregister_mod(zmk_mod_t modifier);
bool zmk_hid_mod_is_pressed(zmk_mod_t modifier);

int zmk_hid_register_mods(zmk_mod_flags_t explicit_modifiers);
int zmk_hid_unregister_mods(zmk_mod_flags_t explicit_modifiers);
int zmk_hid_implicit_modifiers_press(zmk_mod_flags_t implicit_modifiers);
int zmk_hid_implicit_modifiers_release();
int zmk_hid_masked_modifiers_set(zmk_mod_flags_t masked_modifiers);
int zmk_hid_masked_modifiers_clear();

int zmk_hid_keyboard_press(zmk_key_t key);
int zmk_hid_keyboard_release(zmk_key_t key);
void zmk_hid_keyboard_clear();
bool zmk_hid_keyboard_is_pressed(zmk_key_t key);

int zmk_hid_consumer_press(zmk_key_t key);
int zmk_hid_consumer_release(zmk_key_t key);
void zmk_hid_consumer_clear();
bool zmk_hid_consumer_is_pressed(zmk_key_t key);

int zmk_hid_press(uint32_t usage);
int zmk_hid_release(uint32_t usage);
bool zmk_hid_is_pressed(uint32_t usage);

#if IS_ENABLED(CONFIG_ZMK_TRACKPAD)
void zmk_hid_touchpad_mouse_set(uint8_t buttons, int8_t xDelta, int8_t yDelta, int8_t scrollDelta);
#endif

struct zmk_hid_keyboard_report *zmk_hid_get_keyboard_report();
struct zmk_hid_consumer_report *zmk_hid_get_consumer_report();
#if IS_ENABLED(CONFIG_ZMK_TRACKPAD)
struct zmk_hid_touchpad_mouse_report *zmk_hid_get_touchpad_mouse_report();
#endif
