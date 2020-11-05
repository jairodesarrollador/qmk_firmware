/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
//#include <keymap_spanish.h>
//#include <sendstring_spanish.h>

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _JAILUX 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

//#define KC_JXPU "."
#define KC_JXPC ";"
#define KC_JX2P ":"
#define KC_JXMA ">"
#define KC_JXME "<"
#define KC_JXLA "{"
#define KC_JXPA "("

enum custom_keycodes { 
  QWERTY = SAFE_RANGE, 
  LOWER, 
  RAISE, 
  ADJUST, 
  BACKLIT, 
  RGBRST
};

enum macro_keycodes {
  JX_IG2P, 
  JX_MAME,
  JX_PULA,
  JX_PCPA,
  JX_CDCS,
  JX_COMA,
  JX_BSID
};

//KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
static uint8_t saved_mods = 0;
static uint8_t rastreadorDeCaracter = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_JAILUX] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, JX_MAME,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, JX_PCPA, JX_PULA, JX_IG2P, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,  RAISE,  KC_RALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_P0,                      JX_COMA,   KC_P7,   KC_P8,   KC_P9, KC_PPLS, KC_PAST,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_HOME,                      JX_CDCS,   KC_P4,   KC_P5,   KC_P6, KC_QUES, KC_PIPE,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_END,                      JX_BSID,   KC_P1,   KC_P2,   KC_P3, KC_MINS, KC_AMPR,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,  RGBRST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());  // turns on the display
#endif
}

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) { iota_gfx_task(); }

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        matrix_write_ln(matrix, read_layer_state());
        matrix_write_ln(matrix, read_keylog());
        // matrix_write_ln(matrix, read_keylogs());
        // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        // matrix_write_ln(matrix, read_host_led_state());
        // matrix_write_ln(matrix, read_timelog());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif  // SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef SSD1306OLED
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    switch (keycode) {
        case JX_IG2P:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    if(rastreadorDeCaracter == 2){
                        unregister_code(KC_EQUAL);
                    }
                    del_mods(saved_mods);
                    /**ENVIAMOS LOS DOS PUNTOS (:)**/
                    SEND_STRING(KC_JX2P);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    /**ENVIAMOS El IGUAL (=)**/
                    register_code(KC_EQUAL);
                    rastreadorDeCaracter = 2;
                }
            }else {
              if(rastreadorDeCaracter == 2){
                unregister_code(KC_EQUAL);
              }
              rastreadorDeCaracter = 0;
            }
            return false;
        case JX_MAME:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    del_mods(saved_mods);
                    /**ENVIAMOS MAYOR (>)**/
                    SEND_STRING(KC_JXMA);
                    add_mods(saved_mods);
                } else {
                    /**ENVIAMOS MENOR (<)**/
                    SEND_STRING(KC_JXME);
                }
            }
            return false;
        case JX_PULA:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    if(rastreadorDeCaracter == 2){
                        unregister_code(KC_DOT);
                    }
                    del_mods(saved_mods);
                    /**ENVIAMOS LLAVE ABIERTA({)**/
                    SEND_STRING(KC_JXLA);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    /**ENVIAMOS EL PUNTO (.)**/
                    register_code(KC_DOT);
                    rastreadorDeCaracter = 2;
                }
            }else{
                if(rastreadorDeCaracter == 2){
                    unregister_code(KC_DOT);
                }
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_PCPA:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    del_mods(saved_mods);
                    /**ENVIAMOS PARENTESIS ABIERTO( ( )**/
                    SEND_STRING(KC_JXPA);
                    add_mods(saved_mods);
                } else {
                    /**ENVIAMOS PUNTO Y COMA ABIERTO( ; )**/
                    SEND_STRING(KC_JXPC);
                }
            }
            return false;
        case JX_COMA:
            if (record->event.pressed) {
                /**ENVIAMOS COMA ( , )**/
                SEND_STRING(SS_DOWN(X_COMMA));
            }else{
                SEND_STRING(SS_UP(X_COMMA));
            }
            return false;
        case JX_CDCS:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    if(rastreadorDeCaracter == 2){
                        SEND_STRING(SS_UP(X_QUOTE) SS_UP(X_LSFT));
                    }

                    del_mods(saved_mods);
                    /**ENVIAMOS COMILLAS DOBLES( ' )**/
                    SEND_STRING(SS_DOWN(X_QUOTE));
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    /**ENVIAMOS COMILLAS DOBLES( " )**/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_QUOTE));
                    rastreadorDeCaracter = 2;
                }
            }else{
                if(rastreadorDeCaracter == 2){
                    SEND_STRING(SS_UP(X_QUOTE) SS_UP(X_LSFT));
                }
                if(rastreadorDeCaracter == 1){
                    SEND_STRING(SS_UP(X_QUOTE));
                }
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_BSID:
            saved_mods = get_mods() & MOD_MASK_SHIFT;
            if (record->event.pressed) {
                if (saved_mods) {
                    if(rastreadorDeCaracter == 2){
                        unregister_code(KC_PSLS);
                    }

                    del_mods(saved_mods);
                    /**ENVIAMOS BSLASH ( \ )**/
                    SEND_STRING(SS_DOWN(X_BSLASH));
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    /**ENVIAMOS SLASH ( / )**/
                    register_code(KC_PSLS);
                    rastreadorDeCaracter = 2;
                }
            }else{
                if(rastreadorDeCaracter == 2){
                    unregister_code(KC_PSLS);
                }
                if(rastreadorDeCaracter == 1){
                    SEND_STRING(SS_UP(X_BSLASH));
                }
                rastreadorDeCaracter = 0;
            }
            return false;    
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL << _JAILUX);
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            break;
    }
    return true;
}
