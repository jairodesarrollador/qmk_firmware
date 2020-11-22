/*
Copyright 2020 @jailux
Copyright 2020 Jairo Galvez

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

enum custom_keycodes { 
    QWERTY = SAFE_RANGE, 
    LOWER, 
    RAISE, 
    ADJUST, 
    BACKLIT, 
    RGBRST,
    JX_IG2P,
    JX_PULA, 
    JX_PCPA, 
    JX_CDCS, 
    JX_COMA, 
    JX_BSID, 
    JX_QUES, 
    JX_AMPR, 
    JX_CORC, 
    JX_VIGU,
    JX_ARRO  
};


const uint8_t kc_principal = 2;
const uint8_t kc_secundaria = 1;
const uint8_t kc_indefinido = 0;

static uint8_t saved_mods           = 0;
static uint8_t rastreadorDeCaracter = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_JAILUX] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_NUBS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, JX_PCPA, JX_PULA, JX_IG2P, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,  RAISE,  KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,                      JX_COMA, JX_CORC,   KC_UP, JX_BSID, KC_PPLS, KC_PAST,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_END,                      JX_CDCS, KC_LEFT, KC_DOWN, KC_RGHT, JX_QUES,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_HOME,                      JX_ARRO, KC_PLUS, KC_LPRN, KC_BSLS, KC_SLSH, JX_AMPR,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_MPLY, KC_VOLU, KC_PGUP,  KC_INS, KC_PSCR,                      KC_TILD, KC_COPY, KC_PSTE,  KC_CUT, KC_FIND,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_MUTE, KC_VOLD, KC_PGDN, XXXXXXX, KC_CAPS,                      JX_VIGU, XXXXXXX, XXXXXXX,  XXXXXXX, KC_LBRC, KC_APP,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_LALT \
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
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_LALT \
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
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (saved_mods & MOD_MASK_SHIFT) {
                    /**ENVIAMOS : **/
                    del_mods(get_mods());
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_DOT));
                    rastreadorDeCaracter = kc_secundaria;
                    del_mods(get_mods());
                } else {
                    /**ENVIAMOS = **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_0));
                    rastreadorDeCaracter = kc_principal;
                    del_mods(get_mods());
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    SEND_STRING(SS_UP(X_0));
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    SEND_STRING(SS_UP(X_DOT));
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_PULA:
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    /**ENVIAMOS { **/
                    del_mods(get_mods());
                    register_code(KC_QUOT);
                    rastreadorDeCaracter = kc_secundaria;
                } else {
                    /**ENVIAMOS . **/
                    register_code(KC_DOT);
                    rastreadorDeCaracter = kc_principal;
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    unregister_code(KC_DOT);
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    unregister_code(KC_QUOT);
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_PCPA:
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (saved_mods & MOD_MASK_SHIFT) {
                    /**ENVIAMOS ( **/
                    del_mods(get_mods());
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_8));
                    rastreadorDeCaracter = kc_secundaria;
                    del_mods(get_mods());
                } else {
                    /**ENVIAMOS ; **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_COMM));
                    rastreadorDeCaracter = kc_principal;
                    del_mods(get_mods());
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    SEND_STRING(SS_UP(X_COMM));
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    SEND_STRING(SS_UP(X_8));
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_COMA:
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (saved_mods & MOD_MASK_SHIFT) {
                    /**ENVIAMOS ` **/
                    del_mods(get_mods());
                    SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_NUHS));
                    rastreadorDeCaracter = kc_secundaria;
                    del_mods(get_mods());
                } else {
                    /**ENVIAMOS , **/
                    register_code(KC_COMM);
                    rastreadorDeCaracter = kc_principal;
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    unregister_code(KC_COMM);
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    SEND_STRING(SS_UP(X_NUHS));
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_CDCS:
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (saved_mods & MOD_MASK_SHIFT) {
                    /**ENVIAMOS ' **/
                    del_mods(get_mods());
                    register_code(KC_MINS);
                    rastreadorDeCaracter = kc_secundaria;
                } else {
                    /**ENVIAMOS " **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_2));
                    rastreadorDeCaracter = kc_principal;
                    del_mods(get_mods());
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    SEND_STRING(SS_UP(X_2));
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    unregister_code(KC_MINS);
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_BSID:
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (saved_mods & MOD_MASK_SHIFT) {
                    /**ENVIAMOS \ **/
                    del_mods(get_mods());
                    SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_MINS));
                    rastreadorDeCaracter = kc_secundaria;
                    del_mods(get_mods());
                } else {
                    /**ENVIAMOS / **/
                    register_code(KC_PSLS);
                    rastreadorDeCaracter = kc_principal;
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    unregister_code(KC_PSLS);
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    SEND_STRING(SS_UP(X_MINS));
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_QUES:
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (saved_mods & MOD_MASK_SHIFT) {
                    /**ENVIAMOS ¿ **/
                    del_mods(get_mods());
                    register_code(KC_EQL);
                    rastreadorDeCaracter = kc_secundaria;
                } else {
                    /**ENVIAMOS ? **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_MINS));
                    rastreadorDeCaracter = kc_principal;
                    del_mods(get_mods());
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    SEND_STRING(SS_UP(X_MINS));
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    unregister_code(KC_EQL);
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_ARRO:
            saved_mods = get_mods();
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_2));
                del_mods(get_mods());
            } else {
                SEND_STRING(SS_UP(X_2));
            }
            add_mods(saved_mods);
            return false;    
        case JX_AMPR:
            saved_mods = get_mods();
            if (record->event.pressed) {
                /**ENVIAMOS & **/
                SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_6));
                del_mods(get_mods());
            } else {
                SEND_STRING(SS_UP(X_6));
            }
            add_mods(saved_mods);
            return false;
        case JX_CORC:
            saved_mods = get_mods();
            if (record->event.pressed) {
                if (saved_mods & MOD_MASK_SHIFT) {
                    /**ENVIAMOS ] **/
                    add_mods(get_mods());
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_NUHS));
                    rastreadorDeCaracter = kc_secundaria;
                    del_mods(get_mods());
                } else {
                    /**ENVIAMOS [ **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_QUOT));
                    rastreadorDeCaracter = kc_principal;
                    del_mods(get_mods());
                }
            } else {
                if (rastreadorDeCaracter == kc_principal) {
                    SEND_STRING(SS_UP(X_QUOT));
                }
                if (rastreadorDeCaracter == kc_secundaria) {
                    SEND_STRING(SS_UP(X_NUHS));
                }
                rastreadorDeCaracter = kc_indefinido;
            }
            add_mods(saved_mods);
            return false;
        case JX_VIGU:
            saved_mods = get_mods();
            if (record->event.pressed) {
                /**ENVIAMOS ~ **/
                SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_4));
                del_mods(get_mods());
            } else {
                SEND_STRING(SS_UP(X_4));
            }
            add_mods(saved_mods);
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
