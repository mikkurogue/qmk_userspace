#pragma once

#include QMK_KEYBOARD_H

enum shortcut_keycodes {
    WM_MOVL = SAFE_RANGE + 4,
    WM_MOVR,
    WM_WSL,
    WM_WSR,
    NXT_WND,
    PRV_WND,
    SHORTCUTS_SAFE_RANGE,
};

bool process_shortcuts(uint16_t keycode, keyrecord_t *record);
void shortcuts_layer_state_update(layer_state_t state);
