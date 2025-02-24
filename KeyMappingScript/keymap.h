#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdbool.h>

typedef unsigned char KeyboardKeycode;
typedef char* String;

typedef struct {
    KeyboardKeycode Keycode;
    bool isShifted;
    bool isAMacro;
    bool isText;
    String Text;
    KeyboardKeycode MacroKey1;
    KeyboardKeycode MacroKey2;
    KeyboardKeycode MacroKey3;
} strKeyCode;

typedef struct {
    strKeyCode LayerMap[3];
} strKeyMapping;

extern const strKeyMapping keymaps[3];

const strKeyMapping LeftPress[3][6] = {
    {
       {{{ KEY_ESC, 0, true, false, "Password", KEY_A, KEY_A, KEY_A },{ KEY_TAB, 0, true, false, "Password", KEY_A, KEY_A, KEY_A },{ KEY_TILDE, 0, true, false, "Password", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Q, 0, true, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_1, 0, true, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F1, 0, true, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_W, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_2, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F2, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_E, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_3, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F3, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_R, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_4, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F4, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_T, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_5, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F5, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_SHIFT, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_CAPS_LOCK, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LEFT_SHIFT, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_A, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_A, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F6, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_S, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_S, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F7, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_D, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_D, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F8, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_F, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F9, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_G, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_G, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F10, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_CTRL, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Z, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_Z, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F11, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_X, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_X, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_F12, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_C, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_C, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_C, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_V, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_V, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_V, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_B, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_B, 0, false, false, "NULL", KEY_A, KEY_A, KEY_A },{ KEY_B, 0, false, false, "NULL", KEY_F6, KEY_F6, KEY_F6 }}}
    }
};
const strKeyMapping LeftHold[3][6] = {
    {
       {{{ KEY_ESC, 0, false, false, "Password", NULL, NULL, NULL },{ KEY_TAB, 0, false, false, "Password", NULL, NULL, NULL },{ KEY_TILDE, 0, false, false, "Password", NULL, NULL, NULL }}},
       {{{ KEY_Q, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_1, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F1, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_W, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_2, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F2, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_E, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_3, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F3, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_R, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_4, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F4, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_T, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_5, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F5, 0, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_LEFT_SHIFT, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_CAPS_LOCK, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_SHIFT, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_A, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_A, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F6, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_S, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_S, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F7, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_D, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_D, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F8, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_F, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F9, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_G, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_G, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F10, 0, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_LEFT_CTRL, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_CTRL, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_CTRL, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_Z, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_Z, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F11, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_X, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_X, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_F12, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_C, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_C, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_C, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_V, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_V, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_V, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_B, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_B, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_B, 0, false, false, "NULL", NULL, NULL, NULL }}}
    }
};
const strKeyMapping RightPress[3][6] = {
    {
       {{{ KEY_Y, 0, false, false, "Password", NULL, NULL, NULL },{ KEY_6, 0, false, false, "Password", NULL, NULL, NULL },{ KEY_6, 0, false, false, "Password", NULL, NULL, NULL }}},
       {{{ KEY_U, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_7, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_7, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_I, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_8, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_8, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_O, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_9, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_9, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_P, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_SUBTRACT, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_BACKSPACE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_DELETE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_BACKSPACE, 0, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_H, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_H, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_H, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_J, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_J, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_4, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_K, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_UP_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_5, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_L, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_BRACE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_6, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_SEMICOLON, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_RIGHT_BRACE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_ADD, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_HOME, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_HOME, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_DIVIDE, 0, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_N, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_N, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_5, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_M, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_1, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_COMMA, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_DOWN_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_2, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_PERIOD, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_RIGHT_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_3, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_QUOTE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_SLASH, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_EQUAL, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_END, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_END, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_DIVIDE, 0, false, false, "NULL", NULL, NULL, NULL }}}
    }
};
const strKeyMapping RightHold[3][6] = {
    {
       {{{ KEY_Y, 0, false, false, "Password", NULL, NULL, NULL },{ KEY_6, 0, false, false, "Password", NULL, NULL, NULL },{ KEY_6, 0, false, false, "Password", NULL, NULL, NULL }}},
       {{{ KEY_U, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_7, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_7, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_I, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_8, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_8, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_O, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_9, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_9, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_P, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_0, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_SUBTRACT, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_BACKSPACE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_DELETE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_BACKSPACE, 0, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_H, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_H, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_H, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_J, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_J, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_4, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_K, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_UP_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_5, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_L, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_BRACE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_6, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_SEMICOLON, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_RIGHT_BRACE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_ADD, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_HOME, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_HOME, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_DIVIDE, 0, false, false, "NULL", NULL, NULL, NULL }}}
    },
    {
       {{{ KEY_N, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_N, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_5, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_M, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_LEFT_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_1, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_COMMA, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_DOWN_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_2, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_PERIOD, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_RIGHT_ARROW, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_3, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_QUOTE, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_SLASH, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_EQUAL, 0, false, false, "NULL", NULL, NULL, NULL }}},
       {{{ KEY_END, 0, false, false, "NULL", NULL, NULL, NULL },{ KEY_END, 0, false, false, "NULL", NULL, NULL, NULL },{ KEYPAD_DIVIDE, 0, false, false, "NULL", NULL, NULL, NULL }}}
    }
};
};

#endif // KEYMAP_H
