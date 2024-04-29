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

#define CTLEISU LCTL_T(EISU)
#define CTLKANA RCTL_T(KANA2)
#define MOLOWER MO(_LOWER)
#define MORAISE MO(_RAISE)
#define SFTENT LSFT_T(KC_ENT)
#define SFTSPC LSFT_T(KC_SPC)
#define VOLUP KC_AUDIO_VOL_UP
#define VOLDN KC_AUDIO_VOL_DOWN

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_HOME,    KC_PGUP,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_END,    KC_PGDN,    KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LWIN,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, JP_COMM,  JP_DOT, JP_SLSH, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          MOLOWER,  SFTSPC, CTLEISU,    CTLKANA,  SFTENT, MOLOWER
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAGINATA] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_ESC,    NG_Q,    NG_W,    NG_E,    NG_R,    NG_T, KC_HOME,    KC_PGUP,    NG_Y,    NG_U,    NG_I,    NG_O,   NG_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    NG_A,    NG_S,    NG_D,    NG_F,    NG_G,  KC_END,    KC_PGDN,    NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN,    NG_N,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LWIN,    NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,                         NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          MOLOWER, NG_SHFT, CTLEISU,    CTLKANA, NG_SHFT2, MOLOWER
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       JP_DLR, JP_PERC,    KC_7,    KC_8,    KC_9, JP_MINS,   KC_F4,      VOLUP,   JP_AT, JP_HASH,   KC_UP, JP_LCBR, JP_RCBR,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      JP_CIRC, JP_QUOT,    KC_4,    KC_5,    KC_6, JP_DQUO,  KC_F11,      VOLDN, JP_UNDS, KC_LEFT, KC_DOWN,KC_RIGHT, JP_LBRC, JP_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LWIN,    KC_0,    KC_1,    KC_2,    KC_3,  JP_EQL,                      JP_AMPR, JP_LPRN, JP_RPRN, JP_BSLS, JP_EXLM, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______,  SFTSPC, CTLEISU,    CTLKANA, SFTENT,  _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
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
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->tap.count) {
    switch (keycode) {
      case CTLEISU:
        if (record->event.pressed) {
          naginata_off();
        }
        return false;
        break;
      case CTLKANA:
        if (record->event.pressed) {
          naginata_on();
        }
        return false;
        break;
    }
  }

  if (!process_naginata(keycode, record))
    return false;

  return true;
}
