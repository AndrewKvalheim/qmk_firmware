#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

//
// Names
//

// Layers
#define COL 0
#define LSYM 1
#define RSYM 2
#define NUM 3
#define FUN 4
#define NAV 5
#define VIM 6

// Software Colemak
#define CO_A KC_A
#define CO_B KC_B
#define CO_C KC_C
#define CO_D KC_G
#define CO_E KC_K
#define CO_F KC_E
#define CO_G KC_T
#define CO_H KC_H
#define CO_I KC_L
#define CO_J KC_Y
#define CO_K KC_N
#define CO_L KC_U
#define CO_M KC_M
#define CO_N KC_J
#define CO_O KC_SCLN
#define CO_P KC_R
#define CO_Q KC_Q
#define CO_R KC_S
#define CO_S KC_D
#define CO_T KC_F
#define CO_U KC_I
#define CO_V KC_V
#define CO_W KC_W
#define CO_X KC_X
#define CO_Y KC_O
#define CO_Z KC_Z
#define CO_COMM KC_COMM
#define CO_DOT KC_DOT
#define CO_SCLN KC_P
#define CO_SLSH KC_SLSH

// Aliased
#define _______ KC_TRNS
#define ___X___ KC_NO
#define ALTGR   KC_RALT
#define COMPOSE KC_APP
#define CTLGUIL LCTL(LGUI(KC_LEFT))
#define CTLGUIR LCTL(LGUI(KC_RGHT))
#define CTLSFTU LSFT(LCTL(CO_U))
#define LSYM_T(kc) LT(LSYM, kc)
#define RSYM_T(kc) LT(RSYM, kc)

// Custom
enum custom_keycodes {
  ARW_EQ = SAFE_RANGE,
  ARW_HY
};

//
// State
//

// Activity light
uint8_t activity = 0;
uint16_t activity_smooth = 0;
uint16_t activity_timer = 0;

// Autocontrol
uint16_t autocontrol_pending_key = KC_NO;
uint16_t autocontrol_timer = 0;

//
// Functions
//

// Flush activity light state
void activity_set(void) {
  rgblight_sethsv_noeeprom(0, 255, activity_smooth * activity_smooth / 255);
}

// Decay activity
void activity_decay(void) {
  if (timer_elapsed(activity_timer) > 1000 / 48) {
    if (activity >= 2) {
      activity -= 2;
    }

    if (activity_smooth != activity) {
      if (activity_smooth < activity) {
        activity_smooth += (activity - activity_smooth) / 24;
      } else {
        activity_smooth -= (activity_smooth - activity) / 12;
      }

      activity_set();
    }

    activity_timer = timer_read();
  }
}

// Initialize activity lights
void activity_init(void) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);

  activity_set();
}

// Activity keypress
void activity_keypress(void) {
  if (activity < 255 - 12) {
    activity += 12;
  }
}

// Flush autocontrol
void autocontrol_flush(void) {
  if (autocontrol_pending_key != KC_NO) {
    if (timer_elapsed(autocontrol_timer) > TAPPING_TERM) {
      tap_code16(LCTL(autocontrol_pending_key));
    } else {
      tap_code(autocontrol_pending_key);
    }

    autocontrol_pending_key = KC_NO;
    autocontrol_timer = 0;
  }
}

// Receive autocontrol keypress
void autocontrol_pressed(uint16_t keycode) {
  autocontrol_pending_key = keycode;
  autocontrol_timer = timer_read();
}

//
// Hooks
//

// Initialization
void keyboard_post_init_user(void) {
  activity_init();
}

// Matrix scan
void matrix_scan_user(void) {
  activity_decay();
}

// Process record
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  autocontrol_flush();

  if (record->event.pressed) {
    activity_keypress();

    switch (keycode) {
      // Custom
      case ARW_EQ:
        SEND_STRING("=>");
        break;
      case ARW_HY:
        SEND_STRING("->");
        break;

      // Autocontrol
      case CO_C:
      case CO_V:
      case CO_X:
      case CO_Z:
        if (!get_mods()) {
          autocontrol_pressed(keycode);
          return false;
        }
        break;
    }
  }

  return true;
};

//
// Layout
//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [COL] = LAYOUT(
    ___X___,      ___X___,     ___X___,      CTLGUIL,      CTLGUIR, ___X___,                   ___X___,      ___X___,      ___X___,     ___X___,      ___X___, KC_PSCR,
     KC_DEL,         CO_Q,        CO_W,         CO_F,         CO_P,    CO_G,                      CO_J,         CO_L,         CO_U,        CO_Y,      CO_SCLN, ___X___,
    KC_BSPC, LSYM_T(CO_A), ALT_T(CO_R), LCTL_T(CO_S), LSFT_T(CO_T),    CO_D,                      CO_H, RSFT_T(CO_N), RCTL_T(CO_E), ALT_T(CO_I), RSYM_T(CO_O),  KC_TAB,
     KC_ESC,         CO_Z,        CO_X,         CO_C,         CO_V,    CO_B,  KC_SPC,  KC_ENT,    CO_K,         CO_M,      CO_COMM,      CO_DOT,      CO_SLSH, COMPOSE,
                                                           KC_LGUI,   ALTGR,  KC_ENT,  KC_SPC, MO(NAV),      MO(NUM)
  ),
  [LSYM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, KC_PERC, KC_PLUS, KC_ASTR, KC_AMPR,  ARW_EQ,                   ___X___, KC_LCBR, KC_RCBR,  KC_GRV, KC_CIRC, _______,
    _______, _______,  KC_EQL, KC_UNDS, KC_MINS,  ARW_HY,                     KC_AT, KC_LPRN, KC_RPRN, KC_QUOT, KC_DQUO, _______,
    _______, ___X___, ___X___, KC_HASH, KC_PIPE, KC_TILD, _______, _______, ___X___, KC_LBRC, KC_RBRC, KC_EXLM, KC_BSLS, _______,
                                        _______, _______, _______, _______, _______, _______
  ),
  [RSYM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, KC_PERC, KC_PLUS, KC_ASTR, KC_AMPR,  ARW_EQ,                   ___X___, KC_LCBR, KC_RCBR,  KC_GRV, KC_CIRC, _______,
    _______,  KC_DLR,  KC_EQL, KC_UNDS, KC_MINS,  ARW_HY,                     KC_AT, KC_LPRN, KC_RPRN, KC_QUOT, _______, _______,
    _______, ___X___, ___X___, KC_HASH, KC_PIPE, KC_TILD, _______, _______, ___X___, KC_LBRC, KC_RBRC, KC_EXLM, KC_BSLS, _______,
                                        _______, _______, _______, _______, _______, _______
  ),
  [NUM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,                   ___X___,    KC_7,    KC_8,    KC_9, CO_COMM, _______,
    _______, ___X___, ___X___, ___X___, KC_MINS, ___X___,                   CTLSFTU,    KC_4,    KC_5,    KC_6,    KC_0, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______, _______, ___X___,    KC_1,    KC_2,    KC_3,  CO_DOT, _______,
                                        _______, MO(FUN), _______, _______, _______, _______
  ),
  [FUN] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,                   ___X___,   KC_F7,   KC_F8,   KC_F9,  KC_F12, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,                   ___X___,   KC_F4,   KC_F5,   KC_F6,  KC_F11, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______, _______, ___X___,   KC_F1,   KC_F2,   KC_F3,  KC_F10, _______,
                                        _______, _______, _______, _______, _______, _______
  ),
  [NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, KC_PGUP, ___X___, ___X___,                   ___X___, ___X___,   KC_UP, ___X___, ___X___, _______,
    _______, ___X___, KC_HOME, KC_PGDN,  KC_END, ___X___,                   ___X___, KC_LEFT, KC_DOWN, KC_RGHT, ___X___, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______, _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
                                        _______, MO(VIM), _______, _______, _______, _______
  ),
  [VIM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,                   ___X___, ___X___,    CO_K, ___X___, ___X___, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,                   ___X___,    CO_H,    CO_J,    CO_L, ___X___, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______, _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
                                        _______, _______, _______, _______, _______, _______
  )
};
