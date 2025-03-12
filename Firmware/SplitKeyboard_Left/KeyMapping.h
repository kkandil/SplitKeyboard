#ifndef KEYMAP_H
#define KEYMAP_H

#include "HID-Project.h"

#include "SplitKeyboard_Cfg.h"

typedef struct {
    KeyboardKeycode Keycode;
    bool isShifted;
    bool isAMacro;
    KeyboardKeycode MacroKey1;
    KeyboardKeycode MacroKey2;
    KeyboardKeycode MacroKey3;
} strKeyCode;

typedef struct {
    strKeyCode LayerMap[3];
} strKeyMapping;

strKeyMapping keyMapingLeftPress[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
       {{{ KEY_ESC, false, false, KEY_A, KEY_A, KEY_A },{ KEY_TAB, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_TAB, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Q, false, false, KEY_A, KEY_A, KEY_A },{ KEY_1, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F1, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_W, false, false, KEY_A, KEY_A, KEY_A },{ KEY_2, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F2, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_E, false, false, KEY_A, KEY_A, KEY_A },{ KEY_3, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F3, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_R, false, false, KEY_A, KEY_A, KEY_A },{ KEY_4, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F4, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_T, false, false, KEY_A, KEY_A, KEY_A },{ KEY_5, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F5, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_SHIFT, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_SHIFT, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_CAPS_LOCK, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_A, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LANG3, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F6, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_S, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LANG4, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F7, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_D, false, false, KEY_A, KEY_A, KEY_A },{ KEY_9, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F8, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_F, false, false, KEY_A, KEY_A, KEY_A },{ KEY_0, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F9, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_G, false, false, KEY_A, KEY_A, KEY_A },{ KEY_1, false, true, KEY_LEFT_SHIFT, KEY_HOME, NULL },{ KEY_F10, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_WINDOWS, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_ALT, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_LEFT_ALT, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Z, false, false, KEY_A, KEY_A, KEY_A },{ KEY_Z, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F11, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_X, false, false, KEY_A, KEY_A, KEY_A },{ KEY_X, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F12, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_C, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_BRACE, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_TILDE, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_V, false, false, KEY_A, KEY_A, KEY_A },{ KEY_RIGHT_BRACE, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_V, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_B, false, false, KEY_A, KEY_A, KEY_A },{ KEY_1, false, true, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ARROW },{ KEY_B, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    }
};
strKeyMapping keyMapingLeftHold[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
       {{{ KEY_ESC, false, false, NULL, NULL, NULL },{ KEY_TAB, false, false, NULL, NULL, NULL },{ KEY_TAB, false, false, NULL, NULL, NULL }}},
       {{{ KEY_Q, false, false, NULL, NULL, NULL },{ KEY_1, true, false, NULL, NULL, NULL },{ KEY_F1, false, false, NULL, NULL, NULL }}},
       {{{ KEY_W, false, false, NULL, NULL, NULL },{ KEY_2, true, false, NULL, NULL, NULL },{ KEY_F2, false, false, NULL, NULL, NULL }}},
       {{{ KEY_E, false, false, NULL, NULL, NULL },{ KEY_3, true, false, NULL, NULL, NULL },{ KEY_F3, false, false, NULL, NULL, NULL }}},
       {{{ KEY_R, false, false, NULL, NULL, NULL },{ KEY_4, true, false, NULL, NULL, NULL },{ KEY_F4, false, false, NULL, NULL, NULL }}},
       {{{ KEY_T, false, false, NULL, NULL, NULL },{ KEY_5, true, false, NULL, NULL, NULL },{ KEY_F5, false, false, NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_LEFT_SHIFT, false, false, NULL, NULL, NULL },{ KEY_LEFT_SHIFT, false, false, NULL, NULL, NULL },{ KEY_CAPS_LOCK, false, false, NULL, NULL, NULL }}},
       {{{ KEY_A, false, false, NULL, NULL, NULL },{ KEY_LANG3, false, false, NULL, NULL, NULL },{ KEY_F6, false, false, NULL, NULL, NULL }}},
       {{{ KEY_S, false, false, NULL, NULL, NULL },{ KEY_LANG4, false, false, NULL, NULL, NULL },{ KEY_F7, false, false, NULL, NULL, NULL }}},
       {{{ KEY_D, false, false, NULL, NULL, NULL },{ KEY_9, true, false, NULL, NULL, NULL },{ KEY_F8, false, false, NULL, NULL, NULL }}},
       {{{ KEY_F, false, false, NULL, NULL, NULL },{ KEY_0, true, false, NULL, NULL, NULL },{ KEY_F9, false, false, NULL, NULL, NULL }}},
       {{{ KEY_G, false, false, NULL, NULL, NULL },{ KEY_1, false, false, NULL, NULL, NULL },{ KEY_F10, false, false, NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_LEFT_WINDOWS, false, false, NULL, NULL, NULL },{ KEY_LEFT_ALT, false, false, NULL, NULL, NULL },{ KEY_LEFT_ALT, false, false, NULL, NULL, NULL }}},
       {{{ KEY_Z, false, false, NULL, NULL, NULL },{ KEY_Z, false, false, NULL, NULL, NULL },{ KEY_F11, false, false, NULL, NULL, NULL }}},
       {{{ KEY_X, false, false, NULL, NULL, NULL },{ KEY_X, false, false, NULL, NULL, NULL },{ KEY_F12, false, false, NULL, NULL, NULL }}},
       {{{ KEY_C, false, false, NULL, NULL, NULL },{ KEY_LEFT_BRACE, true, false, NULL, NULL, NULL },{ KEY_TILDE, false, false, NULL, NULL, NULL }}},
       {{{ KEY_V, false, false, NULL, NULL, NULL },{ KEY_RIGHT_BRACE, true, false, NULL, NULL, NULL },{ KEY_V, false, false, NULL, NULL, NULL }}},
       {{{ KEY_B, false, false, NULL, NULL, NULL },{ KEY_1, false, false, NULL, NULL, NULL },{ KEY_B, false, false, NULL, NULL, NULL }}}
    }
};
strKeyMapping keyMapingRightPress[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
       {{{ KEY_Y, false, false, NULL, NULL, NULL },{ KEY_6, true, false, NULL, NULL, NULL },{ KEY_1, false, true, KEY_LEFT_ALT, KEY_LEFT_ARROW, NULL }}},
       {{{ KEY_U, false, false, NULL, NULL, NULL },{ KEY_7, true, false, NULL, NULL, NULL },{ KEYPAD_7, false, false, NULL, NULL, NULL }}},
       {{{ KEY_I, false, false, NULL, NULL, NULL },{ KEY_8, true, false, NULL, NULL, NULL },{ KEYPAD_8, false, false, NULL, NULL, NULL }}},
       {{{ KEY_O, false, false, NULL, NULL, NULL },{ KEY_9, true, false, NULL, NULL, NULL },{ KEYPAD_9, false, false, NULL, NULL, NULL }}},
       {{{ KEY_P, false, false, NULL, NULL, NULL },{ KEY_0, true, false, NULL, NULL, NULL },{ KEYPAD_SUBTRACT, false, false, NULL, NULL, NULL }}},
       {{{ KEY_BACKSPACE, false, false, NULL, NULL, NULL },{ KEY_DELETE, false, false, NULL, NULL, NULL },{ KEY_BACKSPACE, false, false, NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_H, false, false, NULL, NULL, NULL },{ KEY_BACKSLASH, true, false, NULL, NULL, NULL },{ KEY_1, false, true, KEY_LEFT_ALT, KEY_RIGHT_ARROW, NULL }}},
       {{{ KEY_J, false, false, NULL, NULL, NULL },{ KEY_MINUS, false, false, NULL, NULL, NULL },{ KEYPAD_4, false, false, NULL, NULL, NULL }}},
       {{{ KEY_K, false, false, NULL, NULL, NULL },{ KEY_UP_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_5, false, false, NULL, NULL, NULL }}},
       {{{ KEY_L, false, false, NULL, NULL, NULL },{ KEY_LEFT_BRACE, false, false, NULL, NULL, NULL },{ KEYPAD_6, false, false, NULL, NULL, NULL }}},
       {{{ KEY_SEMICOLON, false, false, NULL, NULL, NULL },{ KEY_RIGHT_BRACE, false, false, NULL, NULL, NULL },{ KEYPAD_ADD, false, false, NULL, NULL, NULL }}},
       {{{ KEY_HOME, false, false, NULL, NULL, NULL },{ KEY_PRINTSCREEN, false, false, NULL, NULL, NULL },{ KEYPAD_MULTIPLY, false, false, NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_N, false, false, NULL, NULL, NULL },{ KEY_BACKSLASH, false, false, NULL, NULL, NULL },{ KEY_EQUAL, false, false, NULL, NULL, NULL }}},
       {{{ KEY_M, false, false, NULL, NULL, NULL },{ KEY_LEFT_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_1, false, false, NULL, NULL, NULL }}},
       {{{ KEY_COMMA, false, false, NULL, NULL, NULL },{ KEY_DOWN_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_2, false, false, NULL, NULL, NULL }}},
       {{{ KEY_PERIOD, false, false, NULL, NULL, NULL },{ KEY_RIGHT_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_3, false, false, NULL, NULL, NULL }}},
       {{{ KEY_QUOTE, false, false, NULL, NULL, NULL },{ KEY_SLASH, false, false, NULL, NULL, NULL },{ KEY_PERIOD, false, false, NULL, NULL, NULL }}},
       {{{ KEY_END, false, false, NULL, NULL, NULL },{ KEY_END, false, false, NULL, NULL, NULL },{ KEYPAD_DIVIDE, false, false, NULL, NULL, NULL }}}
    }
};
strKeyMapping keyMapingRightHold[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
       {{{ KEY_Y, false, false, NULL, NULL, NULL },{ KEY_6, true, false, NULL, NULL, NULL },{ KEY_1, false, false, NULL, NULL, NULL }}},
       {{{ KEY_U, false, false, NULL, NULL, NULL },{ KEY_7, true, false, NULL, NULL, NULL },{ KEYPAD_7, false, false, NULL, NULL, NULL }}},
       {{{ KEY_I, false, false, NULL, NULL, NULL },{ KEY_8, true, false, NULL, NULL, NULL },{ KEYPAD_8, false, false, NULL, NULL, NULL }}},
       {{{ KEY_O, false, false, NULL, NULL, NULL },{ KEY_9, true, false, NULL, NULL, NULL },{ KEYPAD_9, false, false, NULL, NULL, NULL }}},
       {{{ KEY_P, false, false, NULL, NULL, NULL },{ KEY_0, true, false, NULL, NULL, NULL },{ KEYPAD_SUBTRACT, false, false, NULL, NULL, NULL }}},
       {{{ KEY_BACKSPACE, false, false, NULL, NULL, NULL },{ KEY_DELETE, false, false, NULL, NULL, NULL },{ KEY_BACKSPACE, false, false, NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_H, false, false, NULL, NULL, NULL },{ KEY_BACKSLASH, true, false, NULL, NULL, NULL },{ KEY_1, false, false, NULL, NULL, NULL }}},
       {{{ KEY_J, false, false, NULL, NULL, NULL },{ KEY_MINUS, false, false, NULL, NULL, NULL },{ KEYPAD_4, false, false, NULL, NULL, NULL }}},
       {{{ KEY_K, false, false, NULL, NULL, NULL },{ KEY_UP_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_5, false, false, NULL, NULL, NULL }}},
       {{{ KEY_L, false, false, NULL, NULL, NULL },{ KEY_LEFT_BRACE, false, false, NULL, NULL, NULL },{ KEYPAD_6, false, false, NULL, NULL, NULL }}},
       {{{ KEY_SEMICOLON, false, false, NULL, NULL, NULL },{ KEY_RIGHT_BRACE, false, false, NULL, NULL, NULL },{ KEYPAD_ADD, false, false, NULL, NULL, NULL }}},
       {{{ KEY_HOME, false, false, NULL, NULL, NULL },{ KEY_PRINTSCREEN, false, false, NULL, NULL, NULL },{ KEYPAD_MULTIPLY, false, false, NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_N, false, false, NULL, NULL, NULL },{ KEY_BACKSLASH, false, false, NULL, NULL, NULL },{ KEY_EQUAL, false, false, NULL, NULL, NULL }}},
       {{{ KEY_M, false, false, NULL, NULL, NULL },{ KEY_LEFT_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_1, false, false, NULL, NULL, NULL }}},
       {{{ KEY_COMMA, false, false, NULL, NULL, NULL },{ KEY_DOWN_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_2, false, false, NULL, NULL, NULL }}},
       {{{ KEY_PERIOD, false, false, NULL, NULL, NULL },{ KEY_RIGHT_ARROW, false, false, NULL, NULL, NULL },{ KEYPAD_3, false, false, NULL, NULL, NULL }}},
       {{{ KEY_QUOTE, false, false, NULL, NULL, NULL },{ KEY_SLASH, false, false, NULL, NULL, NULL },{ KEY_PERIOD, false, false, NULL, NULL, NULL }}},
       {{{ KEY_END, false, false, NULL, NULL, NULL },{ KEY_END, false, false, NULL, NULL, NULL },{ KEYPAD_DIVIDE, false, false, NULL, NULL, NULL }}}
    }
};
strKeyMapping thumbMapingLeftPress[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LEFT_CTRL, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_LEFT_CTRL, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_LANG1, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LANG1, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_LANG1, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_SPACE, false, false, KEY_A, KEY_A, KEY_A },{ KEY_SPACE, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_SPACE, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    };
strKeyMapping thumbMapingLeftHold[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LEFT_CTRL, false, false, NULL, NULL, NULL },{ KEY_LEFT_CTRL, false, false, NULL, NULL, NULL },{ KEY_LEFT_CTRL, false, false, NULL, NULL, NULL }}},
       {{{ KEY_LANG1, false, false, NULL, NULL, NULL },{ KEY_LANG1, false, false, NULL, NULL, NULL },{ KEY_LANG1, false, false, NULL, NULL, NULL }}},
       {{{ KEY_SPACE, false, false, NULL, NULL, NULL },{ KEY_SPACE, false, false, NULL, NULL, NULL },{ KEY_SPACE, false, false, NULL, NULL, NULL }}}
    };
strKeyMapping thumbMapingRightPress[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_ENTER, false, false, NULL, NULL, NULL },{ KEY_ENTER, false, false, NULL, NULL, NULL },{ KEY_ENTER, false, false, NULL, NULL, NULL }}},
       {{{ KEY_LANG2, false, false, NULL, NULL, NULL },{ KEY_LANG2, false, false, NULL, NULL, NULL },{ KEY_LANG2, false, false, NULL, NULL, NULL }}},
       {{{ KEY_BACKSPACE, false, false, NULL, NULL, NULL },{ KEY_BACKSPACE, false, false, NULL, NULL, NULL },{ KEYPAD_0, false, false, NULL, NULL, NULL }}}
    };
strKeyMapping thumbMapingRightHold[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_ENTER, false, false, NULL, NULL, NULL },{ KEY_ENTER, false, false, NULL, NULL, NULL },{ KEY_ENTER, false, false, NULL, NULL, NULL }}},
       {{{ KEY_LANG2, false, false, NULL, NULL, NULL },{ KEY_LANG2, false, false, NULL, NULL, NULL },{ KEY_LANG2, false, false, NULL, NULL, NULL }}},
       {{{ KEY_BACKSPACE, false, false, NULL, NULL, NULL },{ KEY_BACKSPACE, false, false, NULL, NULL, NULL },{ KEYPAD_0, false, false, NULL, NULL, NULL }}}
    };
#endif // KEYMAP_H
