#include QMK_KEYBOARD_H
#include "oneshot.h"

// Layer definitions
enum custom_layers {
    _BASE,
    _NUM,
    _SYM,
    _EXT,
    _FUNC,
};

// Layer keys
#define LA_SYM MO(_SYM)
#define LA_EXT MO(_EXT)

// Callum one-shot mod keycodes
enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUIC,
};

// ── Combos ──────────────────────────────────────────────────────────────────

enum combos {
    DF_NUM,
    JK_NUM,
    BN_CAPSWORD,
};

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM bn_combo[] = {KC_B, KC_N, COMBO_END};

combo_t key_combos[] = {
    [DF_NUM]       = COMBO(df_combo, MO(_NUM)),
    [JK_NUM]       = COMBO(jk_combo, MO(_NUM)),
    [BN_CAPSWORD]  = COMBO(bn_combo, CW_TOGG),
};

// D+F and J+K must be held to activate (not tap)
bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case DF_NUM:
        case JK_NUM:
            return true;
        default:
            return false;
    }
}

// ── Keymaps ─────────────────────────────────────────────────────────────────

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ BASE                                                               │
    // └─────────────────────────────────────────────────────────────────────┘
    [_BASE] = LAYOUT_split_3x6_3_ex2(
        KC_NO,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,       KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
        KC_NO,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,       KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_NO,
        KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
                                   LA_EXT,  OSM(MOD_LSFT), KC_SPC,        KC_ENT,  LA_SYM,  KC_BSPC
    ),

    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ NUM — numbers + nav (activated via D+F or J+K combo hold)          │
    // └─────────────────────────────────────────────────────────────────────┘
    [_NUM] = LAYOUT_split_3x6_3_ex2(
        KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,       KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
        KC_NO,   RALT(KC_Q), RALT(KC_W), RALT(KC_P), XXXXXXX, XXXXXXX, KC_NO,  KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_NO,
        KC_NO,   XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  KC_TAB,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NO,
                                   KC_DEL,  KC_TAB,  KC_SPC,                        KC_ENT,  KC_BSPC, KC_BSPC
    ),

    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ SYM — symbols + Callum mods on right home row                      │
    // └─────────────────────────────────────────────────────────────────────┘
    [_SYM] = LAYOUT_split_3x6_3_ex2(
        KC_NO,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,       KC_NO,   KC_CIRC, KC_AMPR, KC_ASTR, KC_EQL,  KC_TILD, KC_NO,
        KC_NO,   KC_GRV,  KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_NO,       KC_NO,   KC_COLN, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUIC, KC_NO,
        KC_NO,   KC_PIPE, KC_LABK, KC_RABK, KC_LBRC, KC_RBRC,                       KC_SCLN, KC_MINS, KC_UNDS, KC_PLUS, KC_BSLS, KC_NO,
                               _______, _______, KC_SPC,                         KC_ENT,  _______, _______
    ),

    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ EXT — navigation + Callum mods on left home row                    │
    // └─────────────────────────────────────────────────────────────────────┘
    [_EXT] = LAYOUT_split_3x6_3_ex2(
        KC_NO,   KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_NO,       KC_NO,   KC_INS,  KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, KC_NO,
        KC_NO,   OS_GUIC, OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX, KC_NO,       KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_NO,
        KC_NO,   XXXXXXX, XXXXXXX, KC_TAB,  KC_ESC,  XXXXXXX,                       XXXXXXX, KC_BSPC, KC_HOME, KC_END,  KC_PSCR, KC_NO,
                                   _______, _______, _______,                        KC_ENT,  _______, _______
    ),

    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ FUNC — F-keys + media (tri-layer: EXT + SYM)                       │
    // └─────────────────────────────────────────────────────────────────────┘
    [_FUNC] = LAYOUT_split_3x6_3_ex2(
        KC_NO,   KC_STOP, KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO,       KC_NO,   XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
        KC_NO,   OS_GUIC, OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX, KC_NO,       KC_NO,   KC_BRIU, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_NO,
        KC_NO,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_BRID, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_NO,
                                   _______, _______, _______,                        KC_ENT,  _______, _______
    ),
};
// clang-format on

// ── Tri-layer: EXT + SYM = FUNC ────────────────────────────────────────────

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _EXT, _SYM, _FUNC);
}

// ── Caps Word: which keys continue caps word ────────────────────────────────

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

// ── Callum One-Shot Mods ────────────────────────────────────────────────────

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

    return true;
}

// ── RGB per layer ───────────────────────────────────────────────────────────

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Set all LEDs to a colour based on the highest active layer
    uint8_t layer = get_highest_layer(layer_state);

    HSV hsv = {0, 0, 0};

    switch (layer) {
        case _BASE:
            // Default animation — don't override
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
        default:
            return false;
    }

    // Scale brightness to current RGB matrix value
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
