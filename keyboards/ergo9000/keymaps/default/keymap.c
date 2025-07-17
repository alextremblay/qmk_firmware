// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "ergo9000/ergo9000.h"

const uint16_t PROGMEM raise_osl_combo[] = {KC_PSCR,  KC_MENU, COMBO_END};
combo_t key_combos[] = {
  COMBO(raise_osl_combo, OSL(_RAISE)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    _______, _______,  _______,   _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,  KC_MENU,
    _______, _______,  KC_ESC,    KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  XXXXXXX,
    _______, _______,  XXXXXXX,   KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL,
    FLP_TBL, KC_CUT,   KC_COPY,   KC_HYPR,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  XXXXXXX,  KC_HOME,
    SRSLY,   KC_PASTE, KC_UNDO,   KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_PGUP, KC_UP,    KC_PGDN,
    SHRUG,   KC_FIND,  KC_SELECT, KC_LCTL,  KC_LALT, KC_LGUI, TL_LOWR,  KC_SPC,  XXXXXXX,         XXXXXXX, KC_SPC,  TL_UPPR, KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN,  KC_RGHT
),
[_LOWER] = LAYOUT(
    _______, _______,  _______,   _______,  _______, _______, _______, _______, _______,       KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_PSLS, _______, _______, _______,  _______,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, _______,       _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PAST, _______, _______, _______,  XXXXXXX,
    _______, _______,  XXXXXXX,   _______,  _______, _______, _______, _______, _______,       _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS, _______, _______, _______,  KC_INS,
    _______, _______,  _______,   _______,  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,       _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS, _______, _______, XXXXXXX,  KC_END,
    _______, _______,  _______,   _______,  MS_ACL0, MS_ACL1, MS_ACL2, _______, _______,       _______, _______, KC_KP_0, KC_PDOT, KC_PENT, MS_WHLU, MS_BTN1, MS_UP,    MS_BTN2,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, XXXXXXX,       XXXXXXX, _______, _______, _______, _______, MS_WHLD, MS_LEFT, MS_DOWN,  MS_RGHT
),
[_RAISE] = LAYOUT(
    _______, _______,  _______,   _______,  KC_BRID, KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT,       _______, _______, _______, _______, _______, _______, SW_OS,   DB_TOGG,  QK_BOOT,
    _______, _______,  _______,   _______,  WK_PREV, WK_ALL,  WK_NEXT, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  XXXXXXX,
    _______, _______,  XXXXXXX,   _______,  DS_PREV, KC_UP,   DS_NEXT, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______,  _______,   _______,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,       _______, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, _______, _______, XXXXXXX,  _______,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, XXXXXXX,       XXXXXXX, _______, _______, _______, _______, _______, _______, _______,  _______
),
[_ADJUST] = LAYOUT(
    _______, _______,  _______,   _______,  _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  XXXXXXX,
    _______, _______,  XXXXXXX,   _______,  _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, XXXXXXX,  _______,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______,  _______,   _______,  _______, _______, _______, _______, XXXXXXX,       XXXXXXX, _______, _______, _______, _______, _______, _______, _______,  _______
),
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
