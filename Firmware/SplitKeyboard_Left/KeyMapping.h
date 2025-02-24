#ifndef KEYMAP_H
#define KEYMAP_H

#include "HID-Project.h"

#include "SplitKeyboard_Cfg.h"

typedef struct {
    KeyboardKeycode Keycode;
    bool isShifted;
    bool isAMacro;
    bool isText;
    char Text[10];
    KeyboardKeycode MacroKey1;
    KeyboardKeycode MacroKey2;
    KeyboardKeycode MacroKey3;
} strKeyCode;

typedef struct {
    strKeyCode LayerMap[3];
} strKeyMapping;

const strKeyMapping keyMapingLeftPress[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
       {{{ KEY_ESC, false, true, false, "Password", KEY_A, KEY_A, KEY_A },{ KEY_TAB, false, false, false, "Password", KEY_A, KEY_A, KEY_A },{ KEY_TILDE, false, true, false, "Password", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Q, false, true, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_1, true, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F1, false, true, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_W, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_2, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F2, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_E, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_3, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F3, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_R, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_4, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F4, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_T, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_5, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F5, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_SHIFT, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_CAPS_LOCK, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LEFT_SHIFT, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_A, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_A, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F6, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_S, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_S, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F7, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_D, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_D, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F8, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_F, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F9, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_G, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_G, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F10, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_CTRL, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Z, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_Z, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F11, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_X, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_X, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F12, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_C, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_C, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_C, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_V, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_V, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_V, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_B, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_B, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_B, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}}
    }
};

const strKeyMapping keyMapingRightPress[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
       {{{ KEY_Y, false, false, false, "Password", NULL, NULL, NULL },{ KEY_6, false, false, false, "Password", NULL, NULL, NULL },{ KEY_6, false, false, false, "Password", NULL, NULL, NULL }}},
       {{{ KEY_U, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_7, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_7, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_I, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_8, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_8, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_O, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_9, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_9, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_P, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_SUBTRACT, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_BACKSPACE, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_DELETE, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_BACKSPACE, false, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_H, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_H, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_H, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_J, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_J, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_4, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_K, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_UP_ARROW, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_5, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_L, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_BRACE, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_6, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_SEMICOLON, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_RIGHT_BRACE, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_ADD, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_HOME, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_HOME, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_DIVIDE, false, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_N, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_N, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_5, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_M, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_ARROW, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_1, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_COMMA, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_DOWN_ARROW, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_2, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_PERIOD, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_RIGHT_ARROW, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_3, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_QUOTE, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_SLASH, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_EQUAL, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_END, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_END, false, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_DIVIDE, false, false, false, "NULL", NULL, NULL, NULL }}}
    }
};

strKeyMapping thumbMapingLeftPress[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LEFT_WINDOWS, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LEFT_ALT, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_RETURN, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_LANG2, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LANG2, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LANG2, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_SPACE, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_SPACE, false, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_SPACE, false, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}}
    };
strKeyMapping thumbMapingLeftHold[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LEFT_WINDOWS, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_ALT, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_RETURN, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_LANG2, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_LANG2, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_LANG2, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_SPACE, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_SPACE, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_SPACE, false, false, false, "NULL", NULL, NULL, NULL }}}
    };
strKeyMapping thumbMapingRightPress[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL }}}
    };
strKeyMapping thumbMapingRightHold[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, false, false, false, "NULL", NULL, NULL, NULL }}}
    };
#endif // KEYMAP_H
