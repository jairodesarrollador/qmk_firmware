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
    JX_PULA, 
    JX_PCPA, 
    JX_CDCS, 
    JX_COMA, 
    JX_BSID, 
    JX_UP, 
    JX_DOWN, 
    JX_LEFT, 
    JX_RGHT, 
    JX_QUES, 
    JX_AMPR, 
    JX_CORC, 
    JX_VIGU 
};

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
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,  RAISE,  KC_RALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_P0,                      JX_COMA,   KC_P7,   JX_UP,   KC_P9, KC_PPLS, KC_PAST,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_HOME,                      JX_CDCS, JX_LEFT, JX_DOWN, JX_RGHT, JX_QUES,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_END,                      JX_BSID,   KC_P1,   KC_P2,   KC_P3, KC_SLSH, JX_AMPR,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_MPLY, KC_VOLU,  KC_INS, KC_PGUP, KC_PSCR,                      JX_CORC, KC_COPY, KC_PSTE,  KC_CUT, KC_FIND, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, KC_VOLD,  KC_DEL, KC_PGDN, KC_CAPS,                      JX_VIGU, KC_PLUS, KC_LPRN, KC_BSLS, KC_LBRC, KC_TILD,\
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

void IG2P_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        SEND_STRING(SS_UP(X_DOT) SS_UP(X_LSFT));
    }
}

void IG2P_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        SEND_STRING(SS_UP(X_0) SS_UP(X_LSFT));
    }
}

void PULA_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        unregister_code(KC_QUOT);
    }
}

void PULA_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        unregister_code(KC_DOT);
    }
}

void PCPA_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        SEND_STRING(SS_UP(X_8) SS_UP(X_LSFT));
    }
}

void PCPA_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        SEND_STRING(SS_UP(X_COMM) SS_UP(X_LSFT));
    }
}

void COMA_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        SEND_STRING(SS_UP(X_NUHS) SS_UP(X_RALT));
    }
}

void COMA_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        unregister_code(KC_COMM);
    }
}

void CDCS_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        unregister_code(KC_MINS);
    }
}

void CDCS_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        SEND_STRING(SS_UP(X_2) SS_UP(X_LSFT));
    }
}

void BSID_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        SEND_STRING(SS_UP(X_MINS) SS_UP(X_RALT));
    }
}

void BSID_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        unregister_code(KC_PSLS);
    }
}

void JXUP_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        unregister_code(KC_P8);
    }
}

void JXUP_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        unregister_code(KC_UP);
    }
}

void DOWN_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        unregister_code(KC_P5);
    }
}

void DOWN_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        unregister_code(KC_DOWN);
    }
}

void LEFT_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        unregister_code(KC_P4);
    }
}

void LEFT_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        unregister_code(KC_LEFT);
    }
}

void RGHT_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        unregister_code(KC_P6);
    }
}

void RGHT_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        unregister_code(KC_RGHT);
    }
}

void QUES_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        unregister_code(KC_EQL);
    }
}

void QUES_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        SEND_STRING(SS_UP(X_MINS) SS_UP(X_LSFT));
    }
}

void CORC_up_secundario(uint8_t *rastreador) {
    if (*rastreador == 1) {
        SEND_STRING(SS_UP(X_NUHS) SS_UP(X_LSFT));
    }
}

void CORC_up_principal(uint8_t *rastreador) {
    if (*rastreador == 2) {
        SEND_STRING(SS_UP(X_QUOT) SS_UP(X_LSFT));
    }
}

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
                    IG2P_up_principal(&rastreadorDeCaracter);
                    del_mods(saved_mods);
                    /**ENVIAMOS : **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_DOT));
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    IG2P_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS = **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_0));
                    rastreadorDeCaracter = 2;
                }
            } else {
                IG2P_up_principal(&rastreadorDeCaracter);
                IG2P_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_PULA:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    PULA_up_principal(&rastreadorDeCaracter);
                    del_mods(saved_mods);
                    /**ENVIAMOS { **/
                    register_code(KC_QUOT);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    PULA_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS . **/
                    register_code(KC_DOT);
                    rastreadorDeCaracter = 2;
                }
            } else {
                PULA_up_principal(&rastreadorDeCaracter);
                PULA_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_PCPA:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    PCPA_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS ( **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_8));
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    PCPA_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS ; **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_COMM));
                    rastreadorDeCaracter = 2;
                }
            } else {
                PCPA_up_principal(&rastreadorDeCaracter);
                PCPA_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_COMA:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    COMA_up_principal(&rastreadorDeCaracter);
                    del_mods(saved_mods);
                    /**ENVIAMOS ` **/
                    SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_NUHS));
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    COMA_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS , **/
                    register_code(KC_COMM);
                    rastreadorDeCaracter = 2;
                }
            } else {
                COMA_up_principal(&rastreadorDeCaracter);
                COMA_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_CDCS:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    CDCS_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS ' **/
                    register_code(KC_MINS);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    CDCS_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS " **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_2));
                    rastreadorDeCaracter = 2;
                }
            } else {
                CDCS_up_principal(&rastreadorDeCaracter);
                CDCS_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_BSID:
            saved_mods = get_mods() & MOD_MASK_SHIFT;
            if (record->event.pressed) {
                if (saved_mods) {
                    BSID_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS \ **/
                    SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_MINS));
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    BSID_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS / **/
                    register_code(KC_PSLS);
                    rastreadorDeCaracter = 2;
                }
            } else {
                BSID_up_principal(&rastreadorDeCaracter);
                BSID_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_UP:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    JXUP_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS EL NUMERO 8**/
                    register_code(KC_P8);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    JXUP_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS UP**/
                    register_code(KC_UP);
                    rastreadorDeCaracter = 2;
                }
            } else {
                JXUP_up_principal(&rastreadorDeCaracter);
                JXUP_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_DOWN:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    DOWN_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS EL NUMERO 5**/
                    register_code(KC_P5);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    DOWN_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS DOWN**/
                    register_code(KC_DOWN);
                    rastreadorDeCaracter = 2;
                }
            } else {
                DOWN_up_principal(&rastreadorDeCaracter);
                DOWN_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_LEFT:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    LEFT_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS EL NUMERO 4**/
                    register_code(KC_P4);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    LEFT_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS DOWN**/
                    register_code(KC_LEFT);
                    rastreadorDeCaracter = 2;
                }
            } else {
                LEFT_up_principal(&rastreadorDeCaracter);
                LEFT_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_RGHT:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    RGHT_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS EL NUMERO 6**/
                    register_code(KC_P6);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    RGHT_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS DOWN**/
                    register_code(KC_RGHT);
                    rastreadorDeCaracter = 2;
                }
            } else {
                RGHT_up_principal(&rastreadorDeCaracter);
                RGHT_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_QUES:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    QUES_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS ¿ **/
                    register_code(KC_EQL);
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    QUES_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS ? **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_MINS));
                    rastreadorDeCaracter = 2;
                }
            } else {
                QUES_up_principal(&rastreadorDeCaracter);
                QUES_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_AMPR:
            if (record->event.pressed) {
                /**ENVIAMOS & **/
                SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_6));
            } else {
                SEND_STRING(SS_UP(X_6) SS_UP(X_LSFT));
            }
            return false;
        case JX_CORC:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;
                if (saved_mods) {
                    CORC_up_principal(&rastreadorDeCaracter);

                    del_mods(saved_mods);
                    /**ENVIAMOS ] **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_NUHS));
                    rastreadorDeCaracter = 1;
                    add_mods(saved_mods);
                } else {
                    CORC_up_secundario(&rastreadorDeCaracter);
                    /**ENVIAMOS [ **/
                    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_QUOT));
                    rastreadorDeCaracter = 2;
                }
            } else {
                CORC_up_principal(&rastreadorDeCaracter);
                CORC_up_secundario(&rastreadorDeCaracter);
                rastreadorDeCaracter = 0;
            }
            return false;
        case JX_VIGU:
            if (record->event.pressed) {
                /**ENVIAMOS ~ **/
                SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_4));
            } else {
                SEND_STRING(SS_UP(X_4) SS_UP(X_RALT));
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
