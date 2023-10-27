#pragma once

#include "quantum_keycodes.h"

enum LAYERS {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    SW_OS = SAFE_RANGE, // Custom keycode to switch target OS
    WORKSPACE_PREV,     // Custom keycode for workspace left
    WORKSPACE_NEXT,     // Custom keycode for workspace right
    WORKSPACE_ALL,      // Custom keycode for workspace all
    DISPLAY_PREV,       // Custom keycode for desktop left
    DISPLAY_NEXT,       // Custom keycode for desktop right
    FLIP_TABLE,         // Custom keycode to send "(╯°□°)╯︵┻━┻"
    SRSLY,              // Custom keycode to send "ಠ_ಠ"
    SHRUG,              // Custom keycode to send "¯\_(ツ)_/¯"

    // aliases
    WK_PREV = WORKSPACE_PREV,
    WK_NEXT = WORKSPACE_NEXT,
    WK_ALL  = WORKSPACE_ALL,
    DS_PREV = DISPLAY_PREV,
    DS_NEXT = DISPLAY_NEXT,
    FLP_TBL = FLIP_TABLE,
};
