#pragma once

#include QMK_KEYBOARD_H

// Custom keycodes for OS-aware shortcuts.
// These must be defined after the oneshot keycodes in the keycode enum.
enum shortcut_keycodes {
    // Start after the last oneshot keycode (OS_GUIC).
    // The keymap's enum must set OS_GUIC = SAFE_RANGE + 3,
    // so we start at SAFE_RANGE + 4.
    WM_MOVL = SAFE_RANGE + 4, // Move window left   (Linux: Super+Ctrl+H)
    WM_MOVR,                   // Move window right  (Linux: Super+Ctrl+L)
    WM_WSL,                    // Move to workspace left  (Linux: Super+Shift+Ctrl+H)
    WM_WSR,                    // Move to workspace right (Linux: Super+Shift+Ctrl+L)
    NXT_WND,                   // Next window (Linux: Alt+Tab, macOS: Cmd+Tab) — stateful
    PRV_WND,                   // Prev window (Linux: Alt+Shift+Tab, macOS: Cmd+Shift+Tab) — stateful
    SHORTCUTS_SAFE_RANGE,      // Use this if you need more custom keycodes after shortcuts
};

// Call this from process_record_user().
// Returns false if the keycode was handled (swallow it), true otherwise.
bool process_shortcuts(uint16_t keycode, keyrecord_t *record);

// Call this from layer_state_set_user() to release the app switcher
// modifier when leaving the EXT layer.
void shortcuts_layer_state_update(layer_state_t state);
