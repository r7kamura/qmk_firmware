/* Copyright 2018-2019 eswai <@eswai>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "keymap_japanese.h"
#include "naginata.h"

NGKEYS naginata_keys;

enum keymap_layers {
  _QWERTY,
  _NAGINATA,
  _LOWER,
  _RAISE,
};

enum custom_keycodes {
  EISU = NG_SAFE_RANGE,
  KANA2,
};

uint32_t oled_sleep_timer;

#define CTLENT CTL_T(KC_ENT)
#define CTLSPC CTL_T(KC_SPC)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SKCDOWN S(KC_DOWN)
#define SKCLEFT S(KC_LEFT)
#define SKCRGHT S(KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LCTL,    KC_RCTL,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LALT,    KC_RALT,    KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, JP_COMM,  JP_DOT, JP_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            LOWER, KC_LSFT,  CTLSPC,     CTLENT, KC_RSFT,   RAISE
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAGINATA] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______,    NG_Q,    NG_W,    NG_E,    NG_R,    NG_T, _______,    _______,    NG_Y,    NG_U,    NG_I,    NG_O,   NG_P,  _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,    NG_A,    NG_S,    NG_D,    NG_F,    NG_G, _______,    _______,    NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN, _______,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______,    NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,                         NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, NG_SHFT, _______,    _______, NG_SHFT, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, JP_TILD,   JP_AT, JP_HASH,  JP_DLR, JP_PERC, _______,    _______, JP_SLSH,    KC_7,    KC_8,    KC_9, JP_MINS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, JP_CIRC, JP_AMPR, JP_EXLM, JP_QUES, JP_BSLS, _______,    _______, JP_ASTR,    KC_4,    KC_5,    KC_6, JP_PLUS,  JP_DOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, JP_PIPE,  JP_GRV, JP_QUOT, JP_DQUO, JP_UNDS,                         KC_0,    KC_1,    KC_2,    KC_3,  JP_EQL, JP_COMM,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   KANA2, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      NG_TAYO,NGSW_WIN, NG_SHOS, _______, _______, _______, _______,    _______, _______, _______,   KC_UP, _______, KC_PGUP,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       NG_MLV,NGSW_MAC, JP_LBRC, JP_LCBR, JP_LPRN,   KC_LT, _______,    _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      NG_KOTI,NGSW_LNX, JP_RBRC, JP_RCBR, JP_RPRN,   KC_GT,                       KC_END, SKCLEFT, SKCDOWN, SKCRGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______,    EISU, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
};

void keyboard_post_init_user(void) {
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);

  wait_ms(400);
  switch (detected_host_os()) {
    case OS_WINDOWS:
      switchOS(NG_WIN);
      break;
    case OS_MACOS:
    case OS_IOS:
      switchOS(NG_MAC);
      break;
    case OS_LINUX:
      switchOS(NG_LINUX);
      break;
    default:
      switchOS(NG_WIN);
  }

  oled_sleep_timer = timer_read32() + OLED_TIMEOUT;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  oled_sleep_timer = timer_read32() + OLED_TIMEOUT;

  switch (keycode) {
    case EISU:
      if (record->event.pressed) {
        naginata_off();
      }
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        naginata_on();
      }
      return false;
      break;
  }

  if (!process_naginata(keycode, record))
    return false;

  return true;
}
