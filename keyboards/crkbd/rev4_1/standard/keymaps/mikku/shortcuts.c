#include "shortcuts.h"
#include "os_detection.h"

static bool is_switching_windows = false;

// Track whether we're on macOS for modifier selection.
static bool is_mac(void) {
    os_variant_t os = detected_host_os();
    return (os == OS_MACOS || os == OS_IOS);
}

// Release the app-switcher modifier (Alt or Cmd) when we're done cycling.
static void release_switcher_mod(void) {
    if (is_switching_windows) {
        if (is_mac()) {
            unregister_code(KC_LGUI);
        } else {
            unregister_code(KC_LALT);
        }
        is_switching_windows = false;
    }
}

// Helper: tap a key combo (register on press, unregister on release).
static void handle_shortcut(uint16_t mod_keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(mod_keycode);
    } else {
        unregister_code16(mod_keycode);
    }
}

bool process_shortcuts(uint16_t keycode, keyrecord_t *record) {
    // If we're in window-switching mode and a non-switcher key is pressed,
    // release the held modifier to confirm the selection.
    if (is_switching_windows && keycode != NXT_WND && keycode != PRV_WND) {
        release_switcher_mod();
    }

    switch (keycode) {

        //  Niri/hyprland window management (Linux only)
        case WM_MOVL:
            if (!is_mac()) {
                handle_shortcut(LGUI(LCTL(KC_H)), record);
                return false;
            }
            return true;

        case WM_MOVR:
            if (!is_mac()) {
                handle_shortcut(LGUI(LCTL(KC_L)), record);
                return false;
            }
            return true;

        case WM_WSL:
            if (!is_mac()) {
                handle_shortcut(LGUI(LSFT(LCTL(KC_H))), record);
                return false;
            }
            return true;

        case WM_WSR:
            if (!is_mac()) {
                handle_shortcut(LGUI(LSFT(LCTL(KC_L))), record);
                return false;
            }
            return true;

        // Stateful app switcher (OS-aware)
        // Holds Alt (or Cmd on Mac) while you keep tapping. The OS
        // switcher UI stays open so you can cycle through windows.
        // Releasing the layer key (or pressing any other key) confirms.
        case NXT_WND:
            if (record->event.pressed) {
                if (!is_switching_windows) {
                    if (is_mac()) {
                        register_code(KC_LGUI);
                    } else {
                        register_code(KC_LALT);
                    }
                    is_switching_windows = true;
                }
                tap_code16(KC_TAB);
            }
            return false;

        case PRV_WND:
            if (record->event.pressed) {
                if (!is_switching_windows) {
                    if (is_mac()) {
                        register_code(KC_LGUI);
                    } else {
                        register_code(KC_LALT);
                    }
                    is_switching_windows = true;
                }
                tap_code16(S(KC_TAB));
            }
            return false;

        default:
            return true;
    }
}

// Call from layer_state_set_user() to release the switcher modifier
// when the user releases the EXT layer key.
void shortcuts_layer_state_update(layer_state_t state) {
    release_switcher_mod();
}
