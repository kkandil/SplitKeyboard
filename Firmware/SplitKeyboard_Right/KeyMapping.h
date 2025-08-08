#ifndef KEYMAP_H
#define KEYMAP_H

#include "HID-Project.h"

// #include "SplitKeyboard_Cfg.h"

#define KEYBORD_ROWS_COUNT 3
#define KEYBORD_COLS_COUNT 6

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
 

// #if GAMIN_MODE_ENABLE == false
strKeyMapping keyMapingLeftPress_Normal[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
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
       {{{ KEY_D, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_BRACE, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F8, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_F, false, false, KEY_A, KEY_A, KEY_A },{ KEY_RIGHT_BRACE, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F9, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_G, false, false, KEY_A, KEY_A, KEY_A },{ KEY_OPER, false, true, KEY_LEFT_SHIFT, KEY_HOME, KEY_RESERVED },{ KEY_F10, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_WINDOWS, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_ALT, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_LEFT_ALT, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Z, false, false, KEY_A, KEY_A, KEY_A },{ KEY_PAGE_UP, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F11, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_X, false, false, KEY_A, KEY_A, KEY_A },{ KEY_PAGE_DOWN, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_F12, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_C, false, false, KEY_A, KEY_A, KEY_A },{ KEY_9, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_TILDE, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_V, false, false, KEY_A, KEY_A, KEY_A },{ KEY_0, true, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_OPER, false, true, KEY_LEFT_ALT, KEY_LEFT_ARROW, KEY_F6 }}},
       {{{ KEY_B, false, false, KEY_A, KEY_A, KEY_A },{ KEY_OPER, false, true, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ARROW },{ KEY_OPER, false, true, KEY_LEFT_ALT, KEY_RIGHT_ARROW, KEY_F6 }}}
    }
};
 

// #if GAMIN_MODE_ENABLE == false
strKeyMapping thumbMapingLeftPress_Normal[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LEFT_CTRL, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_LEFT_CTRL, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_LANG1, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LANG1, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_LANG1, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_SPACE, false, false, KEY_A, KEY_A, KEY_A },{ KEY_SPACE, false, false, KEY_LANG3, KEY_LANG3, KEY_LANG3 },{ KEY_SPACE, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    };
 
strKeyMapping keyMapingLeftPress_Gaming[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
       {{{ KEY_ESC, false, false, KEY_A, KEY_A, KEY_A },{ KEY_ESC, false, false, KEY_A, KEY_A, KEY_A },{ KEY_TAB, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Q, false, false, KEY_A, KEY_A, KEY_A },{ KEY_1, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F1, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_W, false, false, KEY_A, KEY_A, KEY_A },{ KEY_2, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F2, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_E, false, false, KEY_A, KEY_A, KEY_A },{ KEY_3, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F3, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_R, false, false, KEY_A, KEY_A, KEY_A },{ KEY_4, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F4, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_T, false, false, KEY_A, KEY_A, KEY_A },{ KEY_5, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F5, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_LEFT_SHIFT, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_SHIFT, false, false, KEY_A, KEY_A, KEY_A },{ KEY_CAPS_LOCK, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_A, false, false, KEY_A, KEY_A, KEY_A },{ KEY_A, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F6, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_S, false, false, KEY_A, KEY_A, KEY_A },{ KEY_S, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F7, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_D, false, false, KEY_A, KEY_A, KEY_A },{ KEY_D, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F8, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_F, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F9, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_G, false, false, KEY_A, KEY_A, KEY_A },{ KEY_G, false, false, KEY_LEFT_SHIFT, KEY_HOME, KEY_RESERVED },{ KEY_F10, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    },
    {
       {{{ KEY_SPACE, false, false, KEY_A, KEY_A, KEY_A },{ KEY_SPACE, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_ALT, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_Z, false, false, KEY_A, KEY_A, KEY_A },{ KEY_Z, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F11, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_X, false, false, KEY_A, KEY_A, KEY_A },{ KEY_X, false, false, KEY_A, KEY_A, KEY_A },{ KEY_F12, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_C, false, false, KEY_A, KEY_A, KEY_A },{ KEY_C, false, false, KEY_A, KEY_A, KEY_A },{ KEY_TILDE, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_V, false, false, KEY_A, KEY_A, KEY_A },{ KEY_V, false, false, KEY_A, KEY_A, KEY_A },{ KEY_V, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_B, false, false, KEY_A, KEY_A, KEY_A },{ KEY_B, false, false, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ARROW },{ KEY_B, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    }
};
strKeyMapping thumbMapingLeftPress_Gaming[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LANG1, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LANG1, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_LEFT_CTRL, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_CTRL, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LANG1, false, false, KEY_F6, KEY_F6, KEY_F6 }}},
       {{{ KEY_LEFT_ALT, false, false, KEY_A, KEY_A, KEY_A },{ KEY_LEFT_ALT, false, false, KEY_A, KEY_A, KEY_A },{ KEY_SPACE, false, false, KEY_F6, KEY_F6, KEY_F6 }}}
    };
// #endif
#endif // KEYMAP_H
