#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"
#include "macro_str.h"

#define FWD KC_BTN5
#define BACK KC_BTN4
#define SPACE_L A(G(KC_LEFT))
#define SPACE_R A(G(KC_RGHT))
#define KC_VOLU KC_KB_VOLUME_UP
#define KC_VOLD KC_KB_VOLUME_DOWN
#define KC_MUTE KC_KB_MUTE
// lead keys should have higher priority over shotcuts
#define APPMENU G(KC_A)

enum layers
{
  DEF,
  SYM, // lower
  NAV, // upper
  NUM, // adjust
};

enum custom_keycodes
{
  // Custom oneshot mod implementation with no timers.
  OS_SHFT = QK_KB_0,
  OS_CTRL,
  OS_ALT,
  OS_CMD,

  SW_WIN,   // Switch to next window         (cmd-tab)
  SW_LANG,  // Switch to next input language (ctl-spc)
  SW_TAB_L, // Switch to prev tab            (ctl-tab)
  SW_TAB_R, // Switch to next tab            (ctl-tab)

  MACRO1,
};

// clang-format off
#ifdef LAYOUT_split_3x6_3_ex2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEF] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G, XXXXXXX,    XXXXXXX,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D, XXXXXXX,    XXXXXXX,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      SW_LANG,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, TL_UPPR,  KC_TAB,     KC_SPC, TL_LOWR, KC_RSFT
                                      //`--------------------------'  `--------------------------'
  ),

  [SYM] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, XXXXXXX, KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, _______,    _______, KC_HASH, KC_RPRN, KC_RCBR, KC_RBRC,  KC_GRV, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, KC_MINS, KC_ASTR,  KC_EQL, KC_UNDS, KC_CIRC, _______,    _______,  KC_DLR, OS_CTRL, OS_SHFT,  OS_ALT,  OS_CMD, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, KC_PLUS, KC_PIPE,   KC_AT, KC_SLSH, KC_PERC,                      XXXXXXX, KC_BSLS, KC_AMPR, KC_EXLM, KC_QUES, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ 
                                      //`--------------------------'  `--------------------------'
  ),

  [NAV] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       MACRO1, XXXXXXX,  SW_WIN,SW_TAB_L,SW_TAB_R, KC_VOLU, _______,    _______, KC_DOWN, KC_RGHT, KC_HOME,  KC_END,  KC_DEL, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,  OS_CMD,  OS_ALT, OS_SHFT, OS_CTRL, KC_VOLD, _______,    _______, KC_LEFT, XXXXXXX, XXXXXXX, APPMENU, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, SPACE_L, SPACE_R,    BACK,     FWD, KC_MUTE,                        KC_UP, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ 
                                      //`--------------------------'  `--------------------------'
  ),

  [NUM] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, XXXXXXX,    XXXXXXX,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG,  OS_CMD,  OS_ALT, OS_SHFT, OS_CTRL,  KC_F11, XXXXXXX,    XXXXXXX,  KC_F12, OS_CTRL, OS_SHFT,  OS_ALT,  OS_CMD, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ 
                                      //`--------------------------'  `--------------------------'
  )
};
#else
#endif
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [1] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [2] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [3] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
};
#endif
// clang-format on


bool is_oneshot_cancel_key(uint16_t keycode)
{
  switch (keycode)
  {
  case TL_LOWR:
  case TL_UPPR:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode)
{
  switch (keycode)
  {
  case TL_LOWR:
  case TL_UPPR:
  case OS_SHFT:
  case OS_CTRL:
  case OS_ALT:
  case OS_CMD:
    return true;
  default:
    return false;
  }
}

bool sw_win_active = false;
bool sw_lang_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (keycode == MACRO1 && record->event.pressed)
  {
    SEND_STRING(MACRO1_STR);
    return false;
  }

  update_swapper(
      &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
      keycode, record);
  update_swapper(
      &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
      keycode, record);
  update_swapper2(
      &sw_tab_active, KC_LCTL, S(KC_TAB), KC_TAB, SW_TAB_L, SW_TAB_R,
      keycode, record);

  update_oneshot(
      &os_shft_state, KC_LSFT, OS_SHFT,
      keycode, record);
  update_oneshot(
      &os_ctrl_state, KC_LCTL, OS_CTRL,
      keycode, record);
  update_oneshot(
      &os_alt_state, KC_LALT, OS_ALT,
      keycode, record);
  update_oneshot(
      &os_cmd_state, KC_LCMD, OS_CMD,
      keycode, record);

  return true;
}

