#ifndef KEYMAP_H
#define KEYMAP_H

#include "HID-Project.h"

#include "SplitKeyboard_Cfg.h"
typedef enum{
KeyType_Normal,
KeyType_Macro,
KeyType_String,
KeyType_Consumer
}enKeyType;

typedef struct {
    KeyboardKeycode Keycode;
    bool isShifted;
    enKeyType keyType;
    KeyboardKeycode MacroKey1;
    KeyboardKeycode MacroKey2;
    KeyboardKeycode MacroKey3;
    String txt;
} strKeyCode;

typedef struct {
    strKeyCode LayerMap[KEYBOARD_LAYERS_COUNT];
} strKeyMapping;

strKeyMapping keyMapingLeftPress[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
      {{{ KEY_VOLUME_MUTE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_VOLUME_MUTE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_VOLUME_MUTE, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_ESC, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_ESC, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_ESC, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_PAGE_UP, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG9, false, KeyType_String, KEY_A, KEY_A, KEY_A, "" }, { KEY_PAGE_UP, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_PAGE_DOWN, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_3, false, KeyType_String, KEY_A, KEY_A, KEY_A, "2wad@Mywork1" }, { KEY_PAGE_DOWN, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_CAPS_LOCK, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_CAPS_LOCK, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_CAPS_LOCK, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
    },
    {
      {{{ KEY_TAB, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_TAB, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_TAB, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_Q, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_1, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F1, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_W, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_2, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F2, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_E, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_3, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F3, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_R, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_4, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F4, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_T, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_5, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F5, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
    },
    {
      {{{ KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_A, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_A, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F6, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_S, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_S, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F7, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_D, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_BRACE, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F8, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_F, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RIGHT_BRACE, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F9, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_G, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_SHIFT, KEY_HOME, KEY_RESERVED, "" }, { KEY_F10, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
    },
    {
      {{{ KEY_LEFT_ALT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_ALT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_ALT, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_Z, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_Z, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F11, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_X, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_X, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F12, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_C, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_9, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_TILDE, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_V, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_0, true, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_ALT, KEY_LEFT_ARROW, KEY_F6, "" }}},
      {{{ KEY_B, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ARROW, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_ALT, KEY_RIGHT_ARROW, KEY_F6, "" }}},
    },
};
strKeyMapping keyMapingRightPress[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
      {{{ KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_PRINTSCREEN, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_PRINTSCREEN, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG5, false, KeyType_Normal, KEY_LEFT_ALT, KEY_LEFT_ARROW, KEY_RESERVED, "" }}},
      {{{ KEY_DELETE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_DELETE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_DELETE, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_INSERT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG8, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_INSERT, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ Key_CALC, false, KeyType_Consumer, KEY_A, KEY_A, KEY_A, "" }, { Key_CALC, false, KeyType_Consumer, KEY_A, KEY_A, KEY_A, "" }, { Key_CALC, false, KeyType_Consumer, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
    },
    {
      {{{ KEY_Y, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_6, true, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_Y, false, KeyType_Normal, KEY_LEFT_ALT, KEY_LEFT_ARROW, KEY_RESERVED, "" }}},
      {{{ KEY_U, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_7, true, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_7, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_I, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_8, true, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_8, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_O, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_EQUAL, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_9, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_P, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_MINUS, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_SUBTRACT, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
    },
    {
      {{{ KEY_H, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSLASH, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSLASH, false, KeyType_Normal, KEY_LEFT_ALT, KEY_RIGHT_ARROW, KEY_RESERVED, "" }}},
      {{{ KEY_J, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSLASH, true, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_4, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_K, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_UP_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_5, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_L, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LEFT_BRACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_6, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_SEMICOLON, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_RIGHT_BRACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_ADD, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_QUOTE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_SLASH, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_SLASH, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
    },
    {
      {{{ KEY_N, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_N, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_EQUAL, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_M, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LEFT_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_1, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_COMMA, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_DOWN_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_PERIOD, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_RIGHT_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_3, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_HOME, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_HOME, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_8, true, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_END, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_END, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_END, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
    },
};
strKeyMapping thumbMapingLeftPress[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LEFT_WINDOWS, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_WINDOWS, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_WINDOWS, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
       {{{ KEY_LEFT_CTRL, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_CTRL, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_CTRL, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
       {{{ KEY_LANG1, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG1, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG1, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
       {{{ KEY_SPACE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_SPACE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_SPACE, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
};
strKeyMapping thumbMapingRightPress[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_ENTER, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_ENTER, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_ENTER, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
       {{{ KEY_LANG2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LANG2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LANG2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
       {{{ KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_0, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
       {{{ KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_PERIOD, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
};

strKeyMapping keyMapingLeftPress_Gaming[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
      {{{ KEY_MUTE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_MUTE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_MUTE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_6, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_6, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_6, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_7, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_7, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_7, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_8, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_8, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_8, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_9, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_9, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_9, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
    },
    {
      {{{ KEY_ESC, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_ESC, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_ESC, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_Q, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_1, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_Q, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_W, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_2, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "WoodWall" }}},
      {{{ KEY_E, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_3, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "StoneWall" }}},
      {{{ KEY_R, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_4, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Tower" }}},
      {{{ KEY_T, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_5, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Keep" }}},
    },
    {
      {{{ KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_A, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_A, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "House" }}},
      {{{ KEY_S, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_S, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "MinCamp" }}},
      {{{ KEY_D, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_D, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "LumbCamp" }}},
      {{{ KEY_F, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_F, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Mill" }}},
      {{{ KEY_G, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_G, false, KeyType_Normal, KEY_LEFT_SHIFT, KEY_HOME, KEY_RESERVED, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Farm" }}},
    },
    {
      {{{ KEY_DELETE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_DELETE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_DELETE, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_Z, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_Z, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "ArchRange" }}},
      {{{ KEY_X, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_X, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Stable" }}},
      {{{ KEY_C, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_C, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Barak" }}},
      {{{ KEY_V, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_V, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Seig" }}},
      {{{ KEY_B, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_B, false, KeyType_Normal, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ARROW, "" }, { KEY_RESERVED, false, KeyType_String, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "Market" }}},
    },
};
strKeyMapping keyMapingRightPress_Gaming[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {
    {
      {{{ KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
      {{{ KEY_LANG5, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG5, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG5, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_I, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_I, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_I, "" }}},
      {{{ KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_K, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_K, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_K, "" }}},
      {{{ KEY_LANG7, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG7, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG7, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
      {{{ KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_RESERVED, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
    },
    {
      {{{ KEY_Y, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_Y, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_Y, "" }}},
      {{{ KEY_U, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_U, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_U, "" }}},
      {{{ KEY_I, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_8, true, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_8, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_O, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_EQUAL, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_9, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_P, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_MINUS, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_SUBTRACT, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
    },
    {
      {{{ KEY_H, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_H, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_H, "" }}},
      {{{ KEY_J, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_J, "" }, { KEY_OPER, false, KeyType_Macro, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_J, "" }}},
      {{{ KEY_K, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_UP_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_5, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_L, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LEFT_BRACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_6, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_SEMICOLON, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_RIGHT_BRACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_ADD, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_QUOTE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_SLASH, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_SLASH, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
    },
    {
      {{{ KEY_N, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_N, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_EQUAL, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_M, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LEFT_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_1, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_COMMA, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_DOWN_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_PERIOD, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_RIGHT_ARROW, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_3, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_HOME, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_HOME, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_8, true, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
      {{{ KEY_END, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_END, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_END, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
    },
};
strKeyMapping thumbMapingLeftPress_Gaming[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_LANG2, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG2, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG2, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
       {{{ KEY_LANG1, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG1, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LANG1, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
       {{{ KEY_LEFT_CTRL, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_CTRL, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_CTRL, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
       {{{ KEY_LEFT_ALT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_ALT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_ALT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }}},
};
strKeyMapping thumbMapingRightPress_Gaming[KEYBORD_ROWS_COUNT] = {
       {{{ KEY_ENTER, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_ENTER, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_ENTER, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
       {{{ KEY_LANG2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LANG2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_LANG2, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
       {{{ KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEY_BACKSPACE, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }, { KEYPAD_0, false, KeyType_Normal, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, "" }}},
       {{{ KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_LEFT_SHIFT, false, KeyType_Normal, KEY_A, KEY_A, KEY_A, "" }, { KEY_PERIOD, false, KeyType_Normal, KEY_F6, KEY_F6, KEY_F6, "" }}},
};

#endif
