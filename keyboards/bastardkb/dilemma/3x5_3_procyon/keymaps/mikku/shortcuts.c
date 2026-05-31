#include "shortcuts.h"
#include "os_detection.h"

static bool is_switching_windows = false;

static bool is_mac(void) {
    os_variant_t os = detected_host_os();
    return (os == OS_MACOS || os == OS_IOS);
}

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

static void handle_shortcut(uint16_t mod_keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(mod_keycode);
    } else {
        unregister_code16(mod_keycode);
    }
}

bool process_shortcuts(uint16_t keycode, keyrecord_t *record) {
    if (is_switching_windows && keycode != NXT_WND && keycode != PRV_WND) {
        release_switcher_mod();
    }

    switch (keycode) {
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

void shortcuts_layer_state_update(layer_state_t state) {
    release_switcher_mod();
}
