/*
 * BomboPad is a macropad with 12 key, 2 encoders, display and, optionally, Li-Po battery and Bluetooth module.
 * Copyright (C) 2024 Gianni Bombelli <bombo82@giannibombelli.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not,
 * see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

#include QMK_KEYBOARD_H


/*
 * keycode equivalence between GNU/Linux and macOS
 * |-----------------------------------|
 * |   Linux   |   macOS   |   alias   |
 * |-----------|-----------|-----------|
 * |  KC_LALT  |  KC_LOPT  |           |
 * |-----------|-----------|-----------|
 * |  KC_RALT  |  KC_ROPT  |  KC_ALGR  |
 * |-----------|-----------|-----------|
 * |  KC_LGUI  |  KC_LCMD  |           |
 * |-----------|-----------|-----------|
 * |  KC_RGUI  |  KC_RCMD  |           |
 * |-----------------------------------|
 */

typedef enum layer_names {
    _BASE = 0
} layer_names;
const uint8_t layer_size = 1;

typedef enum custom_keycodes {
    CYCLE_L         = SAFE_RANGE,
    CYCLE_LH,
    MIC_MUTE        = LGUI(KC_KB_MUTE),
    MIC_VOL_DOWN    = LGUI(KC_KB_VOLUME_DOWN),
    MIC_VOL_UP      = LGUI(KC_KB_VOLUME_UP),
} custom_keycodes;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_7,           KC_8,           KC_9,           KC_KB_MUTE,
        KC_4,           KC_5,           KC_6,           MIC_MUTE,
        KC_1,           KC_2,           KC_3,           CYCLE_LH
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) }
};
#endif

static uint8_t current_layer = _BASE;
static bool hold_layer = false;
static uint16_t my_hash_timer;

void cycle_layers(keyrecord_t *record) {
    if (!record->event.pressed) {
        return;
    }
    current_layer = (current_layer == layer_size - 1) ? 0 : current_layer + 1;
    layer_move(current_layer);
};

void cycle_layers_hold(keyrecord_t *record) {
    if(record->event.pressed) {
        my_hash_timer = timer_read();
        layer_on(layer_size - 1);
        hold_layer = true;
        return;
    } else {
        layer_off(layer_size - 1);
        hold_layer = false;
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            current_layer = (current_layer == layer_size - 1) ? 0 : current_layer + 1;
            layer_move(current_layer);
        }
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CYCLE_L:
            cycle_layers(record);
            return false;
        case CYCLE_LH:
            cycle_layers_hold(record);
            return false;
        default:
            return true;
    }
};

#ifdef OLED_ENABLE
#include <stdio.h>
/*
 * cols: 20
 * rows: 4
 */
bool oled_task_user(void) {
    oled_write_ln_P(PSTR("   BomboPad v0.3"), false);
    oled_write_ln_P(PSTR("LAYER 0: ALWAYS ON"), false);
    switch (current_layer) {
        case 1:
            oled_write_ln_P(PSTR("LAYER 1: ON"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("LAYER 2: ON"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("LAYER 3: ON"), false);
            break;
        case 4:
            oled_write_ln_P(PSTR("LAYER 4: ON"), false);
            break;
        case 5:
            oled_write_ln_P(PSTR("LAYER 5: ON"), false);
            break;
        case 6:
            oled_write_ln_P(PSTR("LAYER 6: ON"), false);
            break;
        case 7:
            oled_write_ln_P(PSTR("LAYER 7: ON"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer NOT managed"), false);
            break;
    }
    oled_write_ln_P(hold_layer && timer_elapsed(my_hash_timer) > TAPPING_TERM ? PSTR("LAST LAYER HOLD") : PSTR(""), false);

    return false;
};
#endif
