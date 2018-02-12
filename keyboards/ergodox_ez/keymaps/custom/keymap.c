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
#define BAS 0
#define LSY 1
#define RSY 2
#define NUM 3
#define FUN 4
#define NAV 5
#define HDW 6

// Keycode names
#define _______ KC_TRNS
#define ___X___ KC_NO
#define ALTGR   KC_RALT
#define COMPOSE KC_APP
#define CTLSFTU LSFT(LCTL(CO_U))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BAS] = LAYOUT_ergodox(
    // Left base
    ___X___,     ___X___,     ___X___,       ___X___,     ___X___, ___X___, ___X___,
    COMPOSE,        CO_Q,        CO_W,          CO_F,        CO_P,    CO_G, KC_HOME,
    KC_BSPC, ALT_T(CO_A), CTL_T(CO_R), LT(LSY, CO_S), SFT_T(CO_T),    CO_D,
    ___X___,        CO_Z,        CO_X,          CO_C,        CO_V,    CO_B,  KC_END,
    ___X___,     ___X___,     ___X___,         ALTGR,     KC_LGUI,
                                                                                     ___X___, KC_PSCR,
                                                                                               KC_TAB,
                                                                             KC_ENT,  KC_ESC,  KC_SPC,

    // Right base
                      ___X___, ___X___,     ___X___,       ___X___,     ___X___,     ___X___, ___X___,
                      KC_PGUP,    CO_J,        CO_L,          CO_U,        CO_Y,     CO_SCLN, ___X___,
                                  CO_H, SFT_T(CO_N), LT(RSY, CO_E), CTL_T(CO_I), ALT_T(CO_O),  KC_DEL,
                      KC_PGDN,    CO_K,        CO_M,       CO_COMM,      CO_DOT,     CO_SLSH, ___X___,
                                            MO(NAV),       MO(NUM),     ___X___,     ___X___, ___X___,
    KC_RCTL, ___X___,
     KC_ESC,
     KC_ENT, KC_TAB, KC_SPC
  ),
  [LSY] = LAYOUT_ergodox(
    // Left symbol (left button held)
    _______, _______, _______, _______, _______, _______, _______,
    _______, KC_PERC, KC_PLUS, KC_ASTR, KC_AMPR, ___X___, _______,
    _______,  KC_DLR,  KC_EQL, _______, KC_MINS, KC_TILD,
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
  [RSY] = LAYOUT_ergodox(
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
                                 KC_AT, KC_LPRN, _______, KC_QUOT, KC_DQUO, _______,
                      _______, ___X___, KC_LBRC, KC_RBRC, KC_EXLM, KC_BSLS, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [NUM] = LAYOUT_ergodox(
    // Left number
    _______, _______, _______, _______, _______, _______, _______,
    MO(FUN), KC_PERC, KC_PLUS, KC_ASTR, KC_AMPR, ___X___, _______,
    _______,  KC_DLR,  KC_EQL, KC_UNDS, KC_MINS, KC_TILD,
    _______, KC_LPRN, KC_RPRN, KC_HASH, KC_PIPE, ___X___, _______,
    _______, _______, _______, _______, _______,
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right number
                      _______, _______, _______, _______, _______, _______, _______,
                      _______, ___X___,    KC_7,    KC_8,    KC_9, CO_COMM, CTLSFTU,
                                  KC_0,    KC_4,    KC_5,    KC_6,  CO_DOT, KC_BSPC,
                      _______, ___X___,    KC_1,    KC_2,    KC_3, CO_SLSH, _______,
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
                      _______, ___X___,   KC_F7,   KC_F8,   KC_F9,  KC_F12, TG(HDW),
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
    _______, ___X___, ___X___,    CO_W, ___X___, ___X___,    CO_H,
    _______, ___X___,    CO_A,    CO_S,    CO_D, ___X___,
    _______, ___X___, ___X___, ___X___, ___X___, ___X___,    CO_L,
    _______, _______, _______, _______, _______,
                                                                   _______, _______,
                                                                            _______,
                                                          _______, _______, _______,

    // Right navigation
                      _______, _______, _______, _______, _______, _______, _______,
                         CO_K, ___X___, ___X___,   KC_UP, ___X___, ___X___, _______,
                               ___X___, KC_LEFT, KC_DOWN, KC_RGHT, ___X___, _______,
                         CO_J, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
                                        _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [HDW] = LAYOUT_ergodox(
    // Left hardware Colemak
    _______,     _______,     _______,       _______,     _______, _______, _______,
    _______,        KC_Q,        KC_W,          KC_F,        KC_P,    KC_G, _______,
    _______, ALT_T(KC_A), CTL_T(KC_R), LT(LSY, KC_S), SFT_T(KC_T),    KC_D,
    _______,        KC_Z,        KC_X,          KC_C,        KC_V,    KC_B, _______,
    _______,     _______,     _______,       _______,     _______,
                                                                                     _______, _______,
                                                                                              _______,
                                                                            _______, _______, _______,

    // Right hardware Colemak
                      _______, _______,     _______,       _______,     _______,     _______, _______,
                      _______,    KC_J,        KC_L,          KC_U,        KC_Y,     KC_SCLN, _______,
                                  KC_H, SFT_T(KC_N), LT(RSY, KC_E), CTL_T(KC_I), ALT_T(KC_O), _______,
                      _______,    KC_K,        KC_M,       KC_COMM,      KC_DOT,     KC_SLSH, _______,
                                            _______,       _______,     _______,     _______, _______,
    TG(HDW), _______,
    _______,
    _______, _______, _______
  ),
};
