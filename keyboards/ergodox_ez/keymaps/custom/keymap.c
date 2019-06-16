#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

// Software Colemak keycodes
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

// Layer names
#define COL 0
#define LSYM 1
#define RSYM 2
#define NUM 3
#define FUN 4
#define NAV 5
#define VIM 6
#define HDW 7

// Keycode names
#define _______ KC_TRNS
#define ___X___ KC_NO
#define ALTGR   KC_RALT
#define COMPOSE KC_APP
#define CTLSFTU LSFT(LCTL(CO_U))
#define LSYM_T(kc) LT(LSYM, kc)
#define RSYM_T(kc) LT(RSYM, kc)

enum custom_keycodes {
  AUTOC_C = SAFE_RANGE,
  AUTOC_V,
  AUTOC_X,
  AUTOC_Z
};

void tap_hold(keyrecord_t *record, const char *tap, const char *hold) {
  static uint16_t timer;

  if (record->event.pressed) {
    timer = timer_read();
  } else {
    if (timer_elapsed(timer) < TAPPING_TERM) {
      send_string(tap);
    } else {
      send_string(hold);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case AUTOC_C:
      tap_hold(record, "c", SS_LCTRL("c"));
      break;
    case AUTOC_V:
      tap_hold(record, "v", SS_LCTRL("v"));
      break;
    case AUTOC_X:
      tap_hold(record, "x", SS_LCTRL("x"));
      break;
    case AUTOC_Z:
      tap_hold(record, "z", SS_LCTRL("z"));
      break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [COL] = LAYOUT_ergodox(
    // Left Colemak
    TG(HDW),      ___X___,     ___X___,      ___X___,      ___X___, ___X___, ___X___,
     KC_DEL,         CO_Q,        CO_W,         CO_F,         CO_P,    CO_G, KC_HOME,
    KC_BSPC, LSYM_T(CO_A), ALT_T(CO_R), LCTL_T(CO_S), LSFT_T(CO_T),    CO_D,
     KC_ESC,      AUTOC_Z,     AUTOC_X,      AUTOC_C,      AUTOC_V,    CO_B,  KC_END,
    ___X___,      ___X___,     ___X___,      KC_LGUI,        ALTGR,
                                                                                      ___X___, ___X___,
                                                                                               ___X___,
                                                                              KC_ENT,  KC_SPC,  KC_TAB,

    // Right Colemak
                      ___X___, ___X___,      ___X___,      ___X___,     ___X___,      ___X___, KC_PSCR,
                      KC_PGUP,    CO_J,         CO_L,         CO_U,        CO_Y,      CO_SCLN, ___X___,
                                  CO_H, RSFT_T(CO_N), RCTL_T(CO_E), ALT_T(CO_I), RSYM_T(CO_O),  KC_TAB,
                      KC_PGDN,    CO_K,         CO_M,      CO_COMM,      CO_DOT,      CO_SLSH, COMPOSE,
                                             MO(NAV),      MO(NUM),     ___X___,      ___X___, ___X___,
    ___X___, ___X___,
    ___X___,
     KC_TAB, KC_ENT, KC_SPC
  ),
  [LSYM] = LAYOUT_ergodox(
    // Left symbol (left button held)
    _______, _______, _______, _______, _______, _______, _______,
    _______, KC_PERC, KC_PLUS, KC_ASTR, KC_AMPR, ___X___, _______,
    _______, _______,  KC_EQL, KC_UNDS, KC_MINS, KC_TILD,
    _______, ___X___, ___X___, KC_HASH, KC_PIPE, ___X___, _______,
    _______, _______, _______, _______, _______,
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right symbol (left button held)
                      _______, _______, _______, _______, _______, _______, _______,
                      _______, ___X___, KC_LCBR, KC_RCBR,  KC_GRV, KC_CIRC, _______,
                                 KC_AT, KC_LPRN, KC_RPRN, KC_QUOT, KC_DQUO, _______,
                      _______, ___X___, KC_LBRC, KC_RBRC, KC_EXLM, KC_BSLS, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [RSYM] = LAYOUT_ergodox(
    // Left symbol (right button held)
    _______, _______, _______, _______, _______, _______, _______,
    _______, KC_PERC, KC_PLUS, KC_ASTR, KC_AMPR, ___X___, _______,
    _______,  KC_DLR,  KC_EQL, KC_UNDS, KC_MINS, KC_TILD,
    _______, ___X___, ___X___, KC_HASH, KC_PIPE, ___X___, _______,
    _______, _______, _______, _______, _______,
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right symbol (right button held)
                      _______, _______, _______, _______, _______, _______, _______,
                      _______, ___X___, KC_LCBR, KC_RCBR,  KC_GRV, KC_CIRC, _______,
                                 KC_AT, KC_LPRN, KC_RPRN, KC_QUOT, _______, _______,
                      _______, ___X___, KC_LBRC, KC_RBRC, KC_EXLM, KC_BSLS, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [NUM] = LAYOUT_ergodox(
    // Left number
    _______, _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
    _______, _______, _______, _______, MO(FUN),
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right number
                      _______, _______, _______, _______, _______, _______, _______,
                      _______, ___X___,    KC_7,    KC_8,    KC_9, CO_COMM, _______,
                               CTLSFTU,    KC_4,    KC_5,    KC_6,    KC_0, _______,
                      _______, ___X___,    KC_1,    KC_2,    KC_3,  CO_DOT, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [FUN] = LAYOUT_ergodox(
    // Left function
    _______, _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
    _______, _______, _______, _______, _______,
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right function
                      _______, _______, _______, _______, _______, _______, _______,
                      _______, ___X___,   KC_F7,   KC_F8,   KC_F9,  KC_F12, _______,
                               ___X___,   KC_F4,   KC_F5,   KC_F6,  KC_F11, _______,
                      _______, ___X___,   KC_F1,   KC_F2,   KC_F3,  KC_F10, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [NAV] = LAYOUT_ergodox(
    // Left navigation
    _______, _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, KC_PGUP, ___X___, ___X___, _______,
    _______, ___X___, KC_HOME, KC_PGDN,  KC_END, ___X___,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
    _______, _______, _______, _______, MO(VIM),
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right navigation
                      _______, _______, _______, _______, _______, _______, _______,
                      _______, ___X___, ___X___,   KC_UP, ___X___, ___X___, _______,
                               ___X___, KC_LEFT, KC_DOWN, KC_RGHT, ___X___, _______,
                      _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [VIM] = LAYOUT_ergodox(
    // Left Vim navigation
    _______, _______, _______, _______, _______, _______, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
    _______, _______, _______, _______, _______,
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right Vim navigation
                      _______, _______, _______, _______, _______, _______, _______,
                      _______, ___X___, ___X___,    CO_K, ___X___, ___X___, _______,
                               ___X___,    CO_H,    CO_J,    CO_L, ___X___, _______,
                      _______, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [HDW] = LAYOUT_ergodox(
    // Left hardware Colemak
    _______,      _______,     _______,      _______,      _______, _______, _______,
    _______,         KC_Q,        KC_W,         KC_F,         KC_P,    KC_G, _______,
    _______, LSYM_T(KC_A), ALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T),    KC_D,
    _______,         KC_Z,        KC_X,         KC_C,         KC_V,    KC_B, _______,
    _______,      _______,     _______,      _______,      _______,
                                                                                      _______, _______,
                                                                                               _______,
                                                                             _______, _______, _______,

    // Right hardware Colemak
                      _______, _______,      _______,      _______,     _______,      _______, _______,
                      _______,    KC_J,         KC_L,         KC_U,        KC_Y,      KC_SCLN, _______,
                                  KC_H, RSFT_T(KC_N), RCTL_T(KC_E), ALT_T(KC_I), RSYM_T(KC_O), _______,
                      _______,    KC_K,         KC_M,      KC_COMM,      KC_DOT,      KC_SLSH, _______,
                                             _______,      _______,     _______,      _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
};
