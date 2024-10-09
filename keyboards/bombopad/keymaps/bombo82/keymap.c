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
    _BASE = 0,
    _XPP,
    _DPP,
    _SCH,
    _PCB,
    _XXX,
    _NUM,
    _OBS
} layer_names;
const uint8_t layer_size = 8;

typedef enum custom_keycodes {
    CYCLE_L         = SAFE_RANGE,
    CYCLE_LH,
    FULL_SCREEN     = KC_F11,
    MIC_MUTE        = LGUI(KC_KB_MUTE),
    MIC_VOL_DOWN    = LGUI(KC_KB_VOLUME_DOWN),
    MIC_VOL_UP      = LGUI(KC_KB_VOLUME_UP),
    MM_DRW          = LGUI(KC_LSFT),            // KDE mouse mark: draw
    MM_CLR_A        = LALT(LSFT(KC_MINUS)),     // KDE mouse mark: clear all marks
    MM_CLR_L        = LALT(LSFT(KC_EQUAL)),     // KDE mouse mark: clear last mark
    MOUSE_CA        = LGUI(KC_ASTERISK),        // KDE click animations
    MOUSE_TRACK     = LGUI(KC_LCTL),            // KDE track mouse
    SLIDE_SHOW      = LCTL(KC_F5),              // Google Slides: start slideshow
    XPP_ERASER      = LCTL(LSFT(KC_E)),         // Xournal++: eraser tool
    XPP_HILTR       = LCTL(LSFT(KC_H)),         // Xournal++: highlighter tool
    XPP_PEN         = LCTL(LSFT(KC_P)),         // Xournal++: pen tool
    XPP_REDO        = LCTL(KC_Y),
    XPP_S_REG       = LCTL(LSFT(KC_G)),         // Xournal++: select region
    XPP_S_RET       = LCTL(LSFT(KC_R)),         // Xournal++: select rectangular
    XPP_TEXT        = LCTL(LSFT(KC_T)),         // Xournal++: text tool
    XPP_UNDO        = LCTL(KC_Z),
    DPP_CHECK       = LSFT(LCMD(KC_RIGHT)),     // Canon DPP: quick check window
    DPP_EDIT        = LCMD(KC_RIGHT),           // Canon DPP: edit image window
    DPP_MAIN        = LCMD(KC_LEFT),            // Canon DPP: return to main window
    DPP_REDO        = LCMD(LSFT(KC_Z)),
    DPP_REV_SVD     = LCMD(LCTL(KC_Z)),         // Canon DPP: revert to last saved settings
    DPP_REV_SHT     = LCMD(LOPT(KC_Z)),         // Canon DPP: revert to shot settings
    DPP_SAVE        = LCMD(KC_S),
    DPP_UNDO        = LCMD(KC_Z),
    SCH_LINE        = KC_GRAVE,                 // KiCad Schematics: show conencted line
    SCH_N_CONN      = KC_Q,                     // KiCad Schematics: add not connected pin
    SCH_A_LBL       = KC_L,                     // KiCad Schematics: add label
    SCH_A_PWR       = KC_P,                     // KiCad Schematics: add power symbol
    SCH_A_SYM       = KC_A,                     // KiCad Schematics: add symbol
    SCH_A_WIRE      = KC_W,                     // KiCad Schematics: add wire
    SCH_REDO        = LCTL(KC_Y),
    SCH_UNDO        = LCTL(KC_Z),
    PCB_TRACKS      = KC_X,                     // KiCad PCB: route tracks
    PCB_SEL_TRACKS  = KC_GRAVE,                 // KiCad PCB: select track
    PCB_DEL_TRACKS  = LSFT(KC_DEL),             // KiCad PCB: delete track
    PCB_ROUTE_AREA  = LCTL(LSFT(KC_K)),         // KiCad PCB: add route area
    PCB_VIAS        = LCTL(LSFT(KC_V)),         // KiCad PCB: add vias
    PCB_PROP        = KC_E,                     // KiCad PCB: open properties
    PCB_REL_POS     = LSFT(KC_P),               // KiCad PCB: position relative to...
    PCB_ABS_POS     = LSFT(KC_M),               // KiCad PCB: move exactly
    OBS_PRS         = LGUI(LCTL(LALT(1))),
    OBS_DSK         = LGUI(LCTL(LALT(2))),
    OBS_DSK_PRS     = LGUI(LCTL(LALT(3))),
    OBS_CPT         = LGUI(LCTL(LALT(4))),
    OBS_DSK_CPT     = LGUI(LCTL(LALT(5))),
    OBS_PRS_CPT     = LGUI(LCTL(LALT(6))),
    OBS_STREAM_T    = LGUI(LCTL(LALT(7))),
    OBS_REC_T       = LGUI(LCTL(LALT(8))),
    OBS_CAMERA_T    = LGUI(LCTL(LALT(9)))
} custom_keycodes;

typedef enum tap_dance_names {
    MOUSE_CA_T,     // KDE mouse: toggle click animation on tap, track mouse on hold
    MM_CLR_L_A      // KDE mouse mark: clear last mark on tap, clear all marks on hold
} tap_dance_names;

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,         FULL_SCREEN,    KC_PGUP,        KC_KB_MUTE,
        TD(MOUSE_CA_T), SLIDE_SHOW,     KC_PGDN,        MIC_MUTE,
        KC_LCTL,        MM_DRW,         TD(MM_CLR_L_A), CYCLE_LH
    ),
    [_XPP] = LAYOUT(
        XPP_S_REG,      XPP_S_RET,      KC_DEL,         _______,
        XPP_PEN,        XPP_HILTR,      XPP_ERASER,     _______,
        XPP_TEXT,       XPP_UNDO,       XPP_REDO,       _______
    ),
    [_DPP] = LAYOUT(
        DPP_CHECK,      DPP_MAIN,       DPP_EDIT,       _______,
        DPP_REV_SHT,    DPP_SAVE,       DPP_UNDO,       _______,
        DPP_REV_SVD,    XXXXXXX,        DPP_REDO,       _______
    ),
    [_SCH] = LAYOUT(
        SCH_LINE,       SCH_N_CONN,     SCH_A_PWR,      _______,
        SCH_A_LBL,      SCH_A_SYM,      SCH_A_WIRE,     _______,
        KC_LSFT,        SCH_UNDO,       SCH_REDO,       _______
    ),
    [_PCB] = LAYOUT(
        PCB_TRACKS,     PCB_SEL_TRACKS, PCB_DEL_TRACKS, _______,
        PCB_ROUTE_AREA, PCB_VIAS,       XXXXXXX,        _______,
        PCB_PROP,       PCB_REL_POS,    PCB_ABS_POS,    _______
    ),
    [_XXX] = LAYOUT(
        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______
    ),
    [_NUM] = LAYOUT(
        KC_7,           KC_8,           KC_9,           KC_0,
        KC_4,           KC_5,           KC_6,           KC_ENTER,
        KC_1,           KC_2,           KC_3,           _______
    ),
    [_OBS] = LAYOUT(
        OBS_STREAM_T,   OBS_REC_T,      OBS_CAMERA_T,   _______,
        OBS_PRS,        OBS_DSK,        OBS_DSK_PRS,    _______,
        OBS_CPT,        OBS_DSK_CPT,    OBS_PRS_CPT,    _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) },
    [_XPP]  = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) },
    [_DPP]  = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) },
    [_SCH]  = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) },
    [_PCB]  = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) },
    [_XXX]  = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) },
    [_NUM]  = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) },
    [_OBS]  = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(MIC_VOL_UP, MIC_VOL_DOWN) }
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

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (
            state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
{ .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [MOUSE_CA_T] = ACTION_TAP_DANCE_TAP_HOLD(MOUSE_CA, MOUSE_TRACK),
    [MM_CLR_L_A] = ACTION_TAP_DANCE_TAP_HOLD(MM_CLR_L, MM_CLR_A)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case CYCLE_L:
            cycle_layers(record);
            return false;
        case CYCLE_LH:
            cycle_layers_hold(record);
            return false;
        case TD(MOUSE_CA_T):
        case TD(MM_CLR_L_A):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return true;
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
