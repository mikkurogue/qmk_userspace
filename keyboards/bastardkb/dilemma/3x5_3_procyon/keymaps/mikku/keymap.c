#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "shortcuts.h"

enum custom_layers {
    _BASE,
    _NUM,
    _SYM,
    _EXT,
    _FUNC,
    _POINTER,
};

#define BASE _BASE
#define NUM _NUM

// -- Layout selection (uncomment one) --
// #define USE_COLEMAK
#define USE_QWERTY

#define LA_SYM MO(_SYM)
#define LA_EXT MO(_EXT)

#define PT_Z LT(_POINTER, KC_Z)
#define PT_SLSH LT(_POINTER, KC_SLSH)
#define BSP_SYM LT(_SYM, KC_BSPC)

#define QWERTY LAYOUT_split_3x5_3( \
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, \
    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  PT_SLSH, \
              LA_EXT,  KC_LSFT, KC_SPC,              KC_ENT,  LA_SYM, KC_BSPC \
)


#define COLEMAK LAYOUT_split_3x5_3( \
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, \
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
    PT_Z,    KC_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H,    KC_COMM, KC_DOT,  PT_SLSH, \
              LA_EXT,  KC_LSFT, KC_SPC,              KC_ENT,  LA_SYM, KC_BSPC \
)

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUIC,
};

enum combos {
    NUM_LEFT,
    NUM_RIGHT,
    BN_CAPSWORD,
};

#if defined(USE_COLEMAK)
const uint16_t PROGMEM num_left_combo[]  = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM num_right_combo[] = {KC_N, KC_E, COMBO_END};
#elif defined(USE_QWERTY)
const uint16_t PROGMEM num_left_combo[]  = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM num_right_combo[] = {KC_J, KC_K, COMBO_END};
#endif

const uint16_t PROGMEM bn_combo[] = {KC_B, KC_N, COMBO_END};

combo_t key_combos[] = {
    [NUM_LEFT]       = COMBO(num_left_combo, MO(NUM)),
    [NUM_RIGHT]      = COMBO(num_right_combo, MO(NUM)),
    [BN_CAPSWORD]    = COMBO(bn_combo, CW_TOGG),
};

bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case NUM_LEFT:
        case NUM_RIGHT:
            return true;
        default:
            return false;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#if defined(USE_COLEMAK)
    [BASE] = COLEMAK,
#elif defined(USE_QWERTY)
    [BASE] = QWERTY,
#endif

    [NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        RALT(KC_Q), RALT(KC_W), RALT(KC_P), XXXXXXX, XXXXXXX,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  KC_TAB,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                  KC_DEL,  KC_TAB,  KC_SPC,              KC_ENT,  KC_BSPC, KC_DEL
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_UNDS,    KC_CIRC, KC_AMPR, KC_ASTR, KC_EQL,  KC_GRV,
        KC_LCBR, KC_LPRN, KC_LBRC, KC_SCLN, XXXXXXX,    XXXXXXX, KC_COLN, KC_RBRC, KC_RPRN, KC_RCBR,
        XXXXXXX, KC_BSLS, KC_PERC, KC_LBRC, KC_RBRC,    KC_PLUS, KC_MINS, KC_PIPE, XXXXXXX, KC_TILD,
                  _______, _______, KC_SPC,              KC_ENT,  _______, _______
    ),

    [_EXT] = LAYOUT_split_3x5_3(
        KC_ESC,  XXXXXXX, NXT_WND, PRV_WND, KC_INS,     WM_MOVL, WM_MOVR, KC_PGUP, XXXXXXX, XXXXXXX,
        OS_GUIC, OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX,    _______, _______, _______, _______, KC_DEL,
        XXXXXXX, KC_ESC,  KC_ESC,  XXXXXXX, KC_TAB,     WM_WSL,  WM_WSR,  KC_HOME, KC_END,  KC_PSCR,
                  _______, _______, KC_SPC,              KC_ENT,  _______, _______
    ),

    [_FUNC] = LAYOUT_split_3x5_3(
        KC_STOP, KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE,    XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,
        OS_GUIC, OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX,    KC_BRIU, KC_F4,   KC_F5,   KC_F6,   KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_BRID, KC_F1,   KC_F2,   KC_F3,   KC_F12,
                  _______, _______, KC_SPC,              KC_ENT,  _______, _______
    ),

    [_POINTER] = LAYOUT_split_3x5_3(
        QK_BOOT,  EE_CLR,  KC_NO,   DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, KC_NO,   EE_CLR,  QK_BOOT,
        KC_LGUI,  KC_LALT, KC_LSFT, KC_LCTL, KC_NO,      KC_NO,   KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,
        _______,  DRGSCRL, SNIPING, MS_BTN3, KC_NO,      KC_NO,   MS_BTN3, SNIPING, DRGSCRL, _______,
                  MS_BTN3, MS_BTN2, MS_BTN1,              MS_BTN1, MS_BTN2, MS_BTN3
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    shortcuts_layer_state_update(state);
    return update_tri_layer_state(state, _EXT, _SYM, _FUNC);
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_EXT:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_EXT:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_GUIC:
        case DPI_MOD:
        case S_D_MOD:
        case SNIPING:
        case DRGSCRL:
            return true;
        default:
            return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_gui_state  = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state,  KC_LALT, OS_ALT,  keycode, record);
    update_oneshot(&os_gui_state,  KC_LGUI, OS_GUIC, keycode, record);

    if (!process_shortcuts(keycode, record)) {
        return false;
    }

    return true;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    HSV hsv = {0, 0, 0};

    switch (layer) {
        case _BASE:
            return false;
        case _NUM:
            hsv = (HSV){HSV_BLUE};
            break;
        case _SYM:
            hsv = (HSV){HSV_PURPLE};
            break;
        case _EXT:
            hsv = (HSV){HSV_GREEN};
            break;
        case _FUNC:
            hsv = (HSV){HSV_RED};
            break;
        case _POINTER:
            hsv = (HSV){HSV_TEAL};
            break;
        default:
            return false;
    }

    hsv.v = rgb_matrix_get_val();
    RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return false;
}
#endif
