/** @file
  Helper functions for USB Keyboard Driver.

Copyright (c) 2004 - 2008, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "KeyBoard.h"

//
// Default English keyboard layout
// Format:<efi key>, <unicode without shift>, <unicode with shift>, <Modifier>, <AffectedAttribute>
//
// According to Universal Serial Bus HID Usage Tables document ver 1.12,
// a Boot Keyboard should support the keycode range from 0x0 to 0x65 and 0xE0 to 0xE7.
// 0x0 to 0x3 are reserved for typical keyboard status or keyboard errors, so they are excluded.
//
UINT8 KeyboardLayoutTable[NUMBER_OF_VALID_USB_KEYCODE][5] = {
  {EfiKeyC1,         'a',      'A',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x04
  {EfiKeyB5,         'b',      'B',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x05
  {EfiKeyB3,         'c',      'C',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x06
  {EfiKeyC3,         'd',      'D',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x07
  {EfiKeyD3,         'e',      'E',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x08
  {EfiKeyC4,         'f',      'F',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x09
  {EfiKeyC5,         'g',      'G',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x0A
  {EfiKeyC6,         'h',      'H',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x0B
  {EfiKeyD8,         'i',      'I',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x0C
  {EfiKeyC7,         'j',      'J',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x0D
  {EfiKeyC8,         'k',      'K',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x0E
  {EfiKeyC9,         'l',      'L',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x0F
  {EfiKeyB7,         'm',      'M',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x10
  {EfiKeyB6,         'n',      'N',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x11
  {EfiKeyD9,         'o',      'O',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x12
  {EfiKeyD10,        'p',      'P',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x13
  {EfiKeyD1,         'q',      'Q',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x14
  {EfiKeyD4,         'r',      'R',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x15
  {EfiKeyC2,         's',      'S',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x16
  {EfiKeyD5,         't',      'T',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x17
  {EfiKeyD7,         'u',      'U',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x18
  {EfiKeyB4,         'v',      'V',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x19
  {EfiKeyD2,         'w',      'W',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x1A
  {EfiKeyB2,         'x',      'X',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x1B
  {EfiKeyD6,         'y',      'Y',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x1C
  {EfiKeyB1,         'z',      'Z',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},   // 0x1D
  {EfiKeyE1,         '1',      '!',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x1E
  {EfiKeyE2,         '2',      '@',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x1F
  {EfiKeyE3,         '3',      '#',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x20
  {EfiKeyE4,         '4',      '$',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x21
  {EfiKeyE5,         '5',      '%',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x22
  {EfiKeyE6,         '6',      '^',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x23
  {EfiKeyE7,         '7',      '&',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x24
  {EfiKeyE8,         '8',      '*',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x25
  {EfiKeyE9,         '9',      '(',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x26
  {EfiKeyE10,        '0',      ')',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x27
  {EfiKeyEnter,      0x0d,     0x0d,  EFI_NULL_MODIFIER,   0},                                // 0x28   Enter
  {EfiKeyEsc,        0x1b,     0x1b,  EFI_NULL_MODIFIER,   0},                                // 0x29   Esc
  {EfiKeyBackSpace,  0x08,     0x08,  EFI_NULL_MODIFIER,   0},                                // 0x2A   Backspace
  {EfiKeyTab,        0x09,     0x09,  EFI_NULL_MODIFIER,   0},                                // 0x2B   Tab
  {EfiKeySpaceBar,   ' ',      ' ',   EFI_NULL_MODIFIER,   0},                                // 0x2C   Spacebar
  {EfiKeyE11,        '-',      '_',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x2D
  {EfiKeyE12,        '=',      '+',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x2E
  {EfiKeyD11,        '[',      '{',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x2F
  {EfiKeyD12,        ']',      '}',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x30
  {EfiKeyD13,        '\\',     '|',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x31
  {EfiKeyC12,        '\\',     '|',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x32  Keyboard Non-US # and ~
  {EfiKeyC10,        ';',      ':',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x33
  {EfiKeyC11,        '\'',     '"',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x34
  {EfiKeyE0,         '`',      '~',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x35  Keyboard Grave Accent and Tlide
  {EfiKeyB8,         ',',      '<',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x36
  {EfiKeyB9,         '.',      '>',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x37
  {EfiKeyB10,        '/',      '?',   EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},   // 0x38
  {EfiKeyCapsLock,   0x00,     0x00,  EFI_CAPS_LOCK_MODIFIER,            0},                  // 0x39   CapsLock
  {EfiKeyF1,         0x00,     0x00,  EFI_FUNCTION_KEY_ONE_MODIFIER,     0},                  // 0x3A
  {EfiKeyF2,         0x00,     0x00,  EFI_FUNCTION_KEY_TWO_MODIFIER,     0},                  // 0x3B
  {EfiKeyF3,         0x00,     0x00,  EFI_FUNCTION_KEY_THREE_MODIFIER,   0},                  // 0x3C
  {EfiKeyF4,         0x00,     0x00,  EFI_FUNCTION_KEY_FOUR_MODIFIER,    0},                  // 0x3D
  {EfiKeyF5,         0x00,     0x00,  EFI_FUNCTION_KEY_FIVE_MODIFIER,    0},                  // 0x3E
  {EfiKeyF6,         0x00,     0x00,  EFI_FUNCTION_KEY_SIX_MODIFIER,     0},                  // 0x3F
  {EfiKeyF7,         0x00,     0x00,  EFI_FUNCTION_KEY_SEVEN_MODIFIER,   0},                  // 0x40
  {EfiKeyF8,         0x00,     0x00,  EFI_FUNCTION_KEY_EIGHT_MODIFIER,   0},                  // 0x41
  {EfiKeyF9,         0x00,     0x00,  EFI_FUNCTION_KEY_NINE_MODIFIER,    0},                  // 0x42
  {EfiKeyF10,        0x00,     0x00,  EFI_FUNCTION_KEY_TEN_MODIFIER,     0},                  // 0x43
  {EfiKeyF11,        0x00,     0x00,  EFI_FUNCTION_KEY_ELEVEN_MODIFIER,  0},                  // 0x44   F11
  {EfiKeyF12,        0x00,     0x00,  EFI_FUNCTION_KEY_TWELVE_MODIFIER,  0},                  // 0x45   F12
  {EfiKeyPrint,      0x00,     0x00,  EFI_PRINT_MODIFIER,                0},                  // 0x46   PrintScreen
  {EfiKeySLck,       0x00,     0x00,  EFI_SCROLL_LOCK_MODIFIER,          0},                  // 0x47   Scroll Lock
  {EfiKeyPause,      0x00,     0x00,  EFI_PAUSE_MODIFIER,                0},                  // 0x48   Pause
  {EfiKeyIns,        0x00,     0x00,  EFI_INSERT_MODIFIER,               0},                  // 0x49
  {EfiKeyHome,       0x00,     0x00,  EFI_HOME_MODIFIER,                 0},                  // 0x4A
  {EfiKeyPgUp,       0x00,     0x00,  EFI_PAGE_UP_MODIFIER,              0},                  // 0x4B
  {EfiKeyDel,        0x00,     0x00,  EFI_DELETE_MODIFIER,               0},                  // 0x4C
  {EfiKeyEnd,        0x00,     0x00,  EFI_END_MODIFIER,                  0},                  // 0x4D
  {EfiKeyPgDn,       0x00,     0x00,  EFI_PAGE_DOWN_MODIFIER,            0},                  // 0x4E
  {EfiKeyRightArrow, 0x00,     0x00,  EFI_RIGHT_ARROW_MODIFIER,          0},                  // 0x4F
  {EfiKeyLeftArrow,  0x00,     0x00,  EFI_LEFT_ARROW_MODIFIER,           0},                  // 0x50
  {EfiKeyDownArrow,  0x00,     0x00,  EFI_DOWN_ARROW_MODIFIER,           0},                  // 0x51
  {EfiKeyUpArrow,    0x00,     0x00,  EFI_UP_ARROW_MODIFIER,             0},                  // 0x52
  {EfiKeyNLck,       0x00,     0x00,  EFI_NUM_LOCK_MODIFIER,             0},                  // 0x53   NumLock
  {EfiKeySlash,      '/',      '/',   EFI_NULL_MODIFIER,                 0},                  // 0x54
  {EfiKeyAsterisk,   '*',      '*',   EFI_NULL_MODIFIER,                 0},                  // 0x55
  {EfiKeyMinus,      '-',      '-',   EFI_NULL_MODIFIER,                 0},                  // 0x56
  {EfiKeyPlus,       '+',      '+',   EFI_NULL_MODIFIER,                 0},                  // 0x57
  {EfiKeyEnter,      0x0d,     0x0d,  EFI_NULL_MODIFIER,                 0},                  // 0x58
  {EfiKeyOne,        '1',      '1',   EFI_END_MODIFIER,         EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x59
  {EfiKeyTwo,        '2',      '2',   EFI_DOWN_ARROW_MODIFIER,  EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x5A
  {EfiKeyThree,      '3',      '3',   EFI_PAGE_DOWN_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x5B
  {EfiKeyFour,       '4',      '4',   EFI_LEFT_ARROW_MODIFIER,  EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x5C
  {EfiKeyFive,       '5',      '5',   EFI_NULL_MODIFIER,        EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x5D
  {EfiKeySix,        '6',      '6',   EFI_RIGHT_ARROW_MODIFIER, EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x5E
  {EfiKeySeven,      '7',      '7',   EFI_HOME_MODIFIER,        EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x5F
  {EfiKeyEight,      '8',      '8',   EFI_UP_ARROW_MODIFIER,    EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x60
  {EfiKeyNine,       '9',      '9',   EFI_PAGE_UP_MODIFIER,     EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x61
  {EfiKeyZero,       '0',      '0',   EFI_INSERT_MODIFIER,      EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x62
  {EfiKeyPeriod,     '.',      '.',   EFI_DELETE_MODIFIER,      EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},   // 0x63
  {EfiKeyB0,         '\\',     '|',   EFI_NULL_MODIFIER,        EFI_AFFECTED_BY_STANDARD_SHIFT}, // 0x64 Keyboard Non-US \ and |
  {EfiKeyA4,         0x00,     0x00,  EFI_MENU_MODIFIER,        0},                              // 0x65 Keyboard Application

  {EfiKeyLCtrl,      0,        0,     EFI_LEFT_CONTROL_MODIFIER,    0},  // 0xe0
  {EfiKeyLShift,     0,        0,     EFI_LEFT_SHIFT_MODIFIER,      0},  // 0xe1
  {EfiKeyLAlt,       0,        0,     EFI_LEFT_ALT_MODIFIER,        0},  // 0xe2
  {EfiKeyA0,         0,        0,     EFI_LEFT_LOGO_MODIFIER,       0},  // 0xe3
  {EfiKeyRCtrl,      0,        0,     EFI_RIGHT_CONTROL_MODIFIER,   0},  // 0xe4
  {EfiKeyRShift,     0,        0,     EFI_RIGHT_SHIFT_MODIFIER,     0},  // 0xe5
  {EfiKeyA2,         0,        0,     EFI_RIGHT_ALT_MODIFIER,       0},  // 0xe6
  {EfiKeyA3,         0,        0,     EFI_RIGHT_LOGO_MODIFIER,      0},  // 0xe7
};

//
// EFI_KEY to USB Keycode convertion table
// EFI_KEY is defined in UEFI spec.
// USB Keycode is defined in USB HID Firmware spec.
//
UINT8 EfiKeyToUsbKeyCodeConvertionTable[] = {
  0xe0,  //  EfiKeyLCtrl
  0xe3,  //  EfiKeyA0
  0xe2,  //  EfiKeyLAlt
  0x2c,  //  EfiKeySpaceBar
  0xe6,  //  EfiKeyA2
  0xe7,  //  EfiKeyA3
  0x65,  //  EfiKeyA4
  0xe4,  //  EfiKeyRCtrl
  0x50,  //  EfiKeyLeftArrow
  0x51,  //  EfiKeyDownArrow
  0x4F,  //  EfiKeyRightArrow
  0x62,  //  EfiKeyZero
  0x63,  //  EfiKeyPeriod
  0x28,  //  EfiKeyEnter
  0xe1,  //  EfiKeyLShift
  0x64,  //  EfiKeyB0
  0x1D,  //  EfiKeyB1
  0x1B,  //  EfiKeyB2
  0x06,  //  EfiKeyB3
  0x19,  //  EfiKeyB4
  0x05,  //  EfiKeyB5
  0x11,  //  EfiKeyB6
  0x10,  //  EfiKeyB7
  0x36,  //  EfiKeyB8
  0x37,  //  EfiKeyB9
  0x38,  //  EfiKeyB10
  0xe5,  //  EfiKeyRShift
  0x52,  //  EfiKeyUpArrow
  0x59,  //  EfiKeyOne
  0x5A,  //  EfiKeyTwo
  0x5B,  //  EfiKeyThree
  0x39,  //  EfiKeyCapsLock
  0x04,  //  EfiKeyC1
  0x16,  //  EfiKeyC2
  0x07,  //  EfiKeyC3
  0x09,  //  EfiKeyC4
  0x0A,  //  EfiKeyC5
  0x0B,  //  EfiKeyC6
  0x0D,  //  EfiKeyC7
  0x0E,  //  EfiKeyC8
  0x0F,  //  EfiKeyC9
  0x33,  //  EfiKeyC10
  0x34,  //  EfiKeyC11
  0x32,  //  EfiKeyC12
  0x5C,  //  EfiKeyFour
  0x5D,  //  EfiKeyFive
  0x5E,  //  EfiKeySix
  0x57,  //  EfiKeyPlus
  0x2B,  //  EfiKeyTab
  0x14,  //  EfiKeyD1
  0x1A,  //  EfiKeyD2
  0x08,  //  EfiKeyD3
  0x15,  //  EfiKeyD4
  0x17,  //  EfiKeyD5
  0x1C,  //  EfiKeyD6
  0x18,  //  EfiKeyD7
  0x0C,  //  EfiKeyD8
  0x12,  //  EfiKeyD9
  0x13,  //  EfiKeyD10
  0x2F,  //  EfiKeyD11
  0x30,  //  EfiKeyD12
  0x31,  //  EfiKeyD13
  0x4C,  //  EfiKeyDel
  0x4D,  //  EfiKeyEnd
  0x4E,  //  EfiKeyPgDn
  0x5F,  //  EfiKeySeven
  0x60,  //  EfiKeyEight
  0x61,  //  EfiKeyNine
  0x35,  //  EfiKeyE0
  0x1E,  //  EfiKeyE1
  0x1F,  //  EfiKeyE2
  0x20,  //  EfiKeyE3
  0x21,  //  EfiKeyE4
  0x22,  //  EfiKeyE5
  0x23,  //  EfiKeyE6
  0x24,  //  EfiKeyE7
  0x25,  //  EfiKeyE8
  0x26,  //  EfiKeyE9
  0x27,  //  EfiKeyE10
  0x2D,  //  EfiKeyE11
  0x2E,  //  EfiKeyE12
  0x2A,  //  EfiKeyBackSpace
  0x49,  //  EfiKeyIns
  0x4A,  //  EfiKeyHome
  0x4B,  //  EfiKeyPgUp
  0x53,  //  EfiKeyNLck
  0x54,  //  EfiKeySlash
  0x55,  //  EfiKeyAsterisk
  0x56,  //  EfiKeyMinus
  0x29,  //  EfiKeyEsc
  0x3A,  //  EfiKeyF1
  0x3B,  //  EfiKeyF2
  0x3C,  //  EfiKeyF3
  0x3D,  //  EfiKeyF4
  0x3E,  //  EfiKeyF5
  0x3F,  //  EfiKeyF6
  0x40,  //  EfiKeyF7
  0x41,  //  EfiKeyF8
  0x42,  //  EfiKeyF9
  0x43,  //  EfiKeyF10
  0x44,  //  EfiKeyF11
  0x45,  //  EfiKeyF12
  0x46,  //  EfiKeyPrint
  0x47,  //  EfiKeySLck
  0x48   //  EfiKeyPause
};

//
// Keyboard modifier value to EFI Scan Code convertion table
// EFI Scan Code and the modifier values are defined in UEFI spec.
//
UINT8 ModifierValueToEfiScanCodeConvertionTable[] = {
  SCAN_NULL,       // EFI_NULL_MODIFIER
  SCAN_NULL,       // EFI_LEFT_CONTROL_MODIFIER
  SCAN_NULL,       // EFI_RIGHT_CONTROL_MODIFIER
  SCAN_NULL,       // EFI_LEFT_ALT_MODIFIER
  SCAN_NULL,       // EFI_RIGHT_ALT_MODIFIER
  SCAN_NULL,       // EFI_ALT_GR_MODIFIER
  SCAN_INSERT,     // EFI_INSERT_MODIFIER
  SCAN_DELETE,     // EFI_DELETE_MODIFIER
  SCAN_PAGE_DOWN,  // EFI_PAGE_DOWN_MODIFIER
  SCAN_PAGE_UP,    // EFI_PAGE_UP_MODIFIER
  SCAN_HOME,       // EFI_HOME_MODIFIER
  SCAN_END,        // EFI_END_MODIFIER
  SCAN_NULL,       // EFI_LEFT_SHIFT_MODIFIER
  SCAN_NULL,       // EFI_RIGHT_SHIFT_MODIFIER
  SCAN_NULL,       // EFI_CAPS_LOCK_MODIFIER
  SCAN_NULL,       // EFI_NUM_LOCK_MODIFIER
  SCAN_LEFT,       // EFI_LEFT_ARROW_MODIFIER
  SCAN_RIGHT,      // EFI_RIGHT_ARROW_MODIFIER
  SCAN_DOWN,       // EFI_DOWN_ARROW_MODIFIER
  SCAN_UP,         // EFI_UP_ARROW_MODIFIER
  SCAN_NULL,       // EFI_NS_KEY_MODIFIER
  SCAN_NULL,       // EFI_NS_KEY_DEPENDENCY_MODIFIER
  SCAN_F1,         // EFI_FUNCTION_KEY_ONE_MODIFIER
  SCAN_F2,         // EFI_FUNCTION_KEY_TWO_MODIFIER
  SCAN_F3,         // EFI_FUNCTION_KEY_THREE_MODIFIER
  SCAN_F4,         // EFI_FUNCTION_KEY_FOUR_MODIFIER
  SCAN_F5,         // EFI_FUNCTION_KEY_FIVE_MODIFIER
  SCAN_F6,         // EFI_FUNCTION_KEY_SIX_MODIFIER
  SCAN_F7,         // EFI_FUNCTION_KEY_SEVEN_MODIFIER
  SCAN_F8,         // EFI_FUNCTION_KEY_EIGHT_MODIFIER
  SCAN_F9,         // EFI_FUNCTION_KEY_NINE_MODIFIER
  SCAN_F10,        // EFI_FUNCTION_KEY_TEN_MODIFIER
  SCAN_F11,        // EFI_FUNCTION_KEY_ELEVEN_MODIFIER
  SCAN_F12,        // EFI_FUNCTION_KEY_TWELVE_MODIFIER
};

EFI_GUID  mKeyboardLayoutEventGuid = EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID;

/**
  Initialize Key Convertion Table by using default keyboard layout.

  @param  UsbKeyboardDevice    The USB_KB_DEV instance.

**/
VOID
EFIAPI
LoadDefaultKeyboardLayout (
  IN OUT USB_KB_DEV                 *UsbKeyboardDevice
  )
{
  UINTN               Index;
  EFI_KEY_DESCRIPTOR  *KeyDescriptor;

  //
  // Construct KeyConvertionTable by default keyboard layout
  //
  KeyDescriptor = &UsbKeyboardDevice->KeyConvertionTable[0];

  for (Index = 0; Index < (NUMBER_OF_VALID_USB_KEYCODE); Index++) {
    KeyDescriptor->Key                 = (EFI_KEY) KeyboardLayoutTable[Index][0];
    KeyDescriptor->Unicode             = KeyboardLayoutTable[Index][1];
    KeyDescriptor->ShiftedUnicode      = KeyboardLayoutTable[Index][2];
    KeyDescriptor->AltGrUnicode        = 0;
    KeyDescriptor->ShiftedAltGrUnicode = 0;
    KeyDescriptor->Modifier            = KeyboardLayoutTable[Index][3];
    KeyDescriptor->AffectedAttribute   = KeyboardLayoutTable[Index][4];

    KeyDescriptor++;
  }
}

/**
  Uses USB I/O to check whether the device is a USB keyboard device.

  @param  UsbIo    Pointer to a USB I/O protocol instance.

  @retval TRUE     Device is a USB keyboard device.
  @retval FALSE    Device is a not USB keyboard device.

**/
BOOLEAN
EFIAPI
IsUSBKeyboard (
  IN  EFI_USB_IO_PROTOCOL       *UsbIo
  )
{
  EFI_STATUS                    Status;
  EFI_USB_INTERFACE_DESCRIPTOR  InterfaceDescriptor;

  //
  // Get the default interface descriptor
  //
  Status = UsbIo->UsbGetInterfaceDescriptor (
                    UsbIo,
                    &InterfaceDescriptor
                    );

  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  if (InterfaceDescriptor.InterfaceClass == CLASS_HID &&
      InterfaceDescriptor.InterfaceSubClass == SUBCLASS_BOOT &&
      InterfaceDescriptor.InterfaceProtocol == PROTOCOL_KEYBOARD
      ) {
    return TRUE;
  }

  return FALSE;
}

/**
  Get current keyboard layout from HII database.

  @return Pointer to HII Keyboard Layout.
          NULL means failure occurred while trying to get keyboard layout.

**/
EFI_HII_KEYBOARD_LAYOUT *
EFIAPI
GetCurrentKeyboardLayout (
  VOID
  )
{
  EFI_STATUS                Status;
  EFI_HII_DATABASE_PROTOCOL *HiiDatabase;
  EFI_HII_KEYBOARD_LAYOUT   *KeyboardLayout;
  UINT16                    Length;

  //
  // Locate HII Database Protocol
  //
  Status = gBS->LocateProtocol (
                  &gEfiHiiDatabaseProtocolGuid,
                  NULL,
                  (VOID **) &HiiDatabase
                  );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  //
  // Get current keyboard layout from HII database
  //
  Length = 0;
  KeyboardLayout = NULL;
  Status = HiiDatabase->GetKeyboardLayout (
                          HiiDatabase,
                          NULL,
                          &Length,
                          KeyboardLayout
                          );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    KeyboardLayout = AllocatePool (Length);
    ASSERT (KeyboardLayout != NULL);

    Status = HiiDatabase->GetKeyboardLayout (
                            HiiDatabase,
                            NULL,
                            &Length,
                            KeyboardLayout
                            );
    if (EFI_ERROR (Status)) {
      gBS->FreePool (KeyboardLayout);
      KeyboardLayout = NULL;
    }
  }

  return KeyboardLayout;
}

/**
  Find Key Descriptor in Key Convertion Table given its USB keycode.

  @param  UsbKeyboardDevice   The USB_KB_DEV instance.
  @param  KeyCode             USB Keycode.

  @return The Key Descriptor in Key Convertion Table.
          NULL means not found.

**/
EFI_KEY_DESCRIPTOR *
EFIAPI
GetKeyDescriptor (
  IN USB_KB_DEV        *UsbKeyboardDevice,
  IN UINT8             KeyCode
  )
{
  UINT8  Index;

  //
  // Make sure KeyCode is in the range of [0x4, 0x65] or [0xe0, 0xe7]
  //
  if ((!USBKBD_VALID_KEYCODE (KeyCode)) || ((KeyCode > 0x65) && (KeyCode < 0xe0)) || (KeyCode > 0xe7)) {
    return NULL;
  }

  //
  // Calculate the index of Key Descriptor in Key Convertion Table
  //
  if (KeyCode <= 0x65) {
    Index = (UINT8) (KeyCode - 4);
  } else {
    Index = (UINT8) (KeyCode - 0xe0 + NUMBER_OF_VALID_NON_MODIFIER_USB_KEYCODE);
  }

  return &UsbKeyboardDevice->KeyConvertionTable[Index];
}

/**
  Find Non-Spacing key for given Key descriptor.

  @param  UsbKeyboardDevice    The USB_KB_DEV instance.
  @param  KeyDescriptor        Key descriptor.

  @return The Non-Spacing key corresponding to KeyDescriptor
          NULL means not found.

**/
USB_NS_KEY *
EFIAPI
FindUsbNsKey (
  IN USB_KB_DEV          *UsbKeyboardDevice,
  IN EFI_KEY_DESCRIPTOR  *KeyDescriptor
  )
{
  LIST_ENTRY      *Link;
  LIST_ENTRY      *NsKeyList;
  USB_NS_KEY      *UsbNsKey;
  
  NsKeyList = &UsbKeyboardDevice->NsKeyList;
  Link = GetFirstNode (NsKeyList);
  while (!IsNull (NsKeyList, Link)) {
    UsbNsKey = USB_NS_KEY_FORM_FROM_LINK (Link);

    if (UsbNsKey->NsKey[0].Key == KeyDescriptor->Key) {
      return UsbNsKey;
    }

    Link = GetNextNode (NsKeyList, Link);
  }

  return NULL;
}

/**
  Find physical key definition for a given key descriptor.

  For a specified non-spacing key, there are a list of physical
  keys following it. This function traverses the list of
  physical keys and tries to find the physical key matching
  the KeyDescriptor.

  @param  UsbNsKey          The non-spacing key information.
  @param  KeyDescriptor     The key descriptor.

  @return The physical key definition.
          If no physical key is found, parameter KeyDescriptor is returned.

**/
EFI_KEY_DESCRIPTOR *
EFIAPI
FindPhysicalKey (
  IN USB_NS_KEY          *UsbNsKey,
  IN EFI_KEY_DESCRIPTOR  *KeyDescriptor
  )
{
  UINTN               Index;
  EFI_KEY_DESCRIPTOR  *PhysicalKey;

  PhysicalKey = &UsbNsKey->NsKey[1];
  for (Index = 0; Index < UsbNsKey->KeyCount; Index++) {
    if (KeyDescriptor->Key == PhysicalKey->Key) {
      return PhysicalKey;
    }

    PhysicalKey++;
  }

  //
  // No children definition matched, return original key
  //
  return KeyDescriptor;
}

/**
  The notification function for EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID.

  This function is registered to event of EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID
  group type, which will be triggered by EFI_HII_DATABASE_PROTOCOL.SetKeyboardLayout().
  It tries to get curent keyboard layout from HII database.

  @param  Event        Event being signaled.
  @param  Context      Points to USB_KB_DEV instance.

**/
VOID
EFIAPI
SetKeyboardLayoutEvent (
  IN EFI_EVENT              Event,
  IN VOID                   *Context
  )
{
  USB_KB_DEV                *UsbKeyboardDevice;
  EFI_HII_KEYBOARD_LAYOUT   *KeyboardLayout;
  EFI_KEY_DESCRIPTOR        TempKey;
  EFI_KEY_DESCRIPTOR        *KeyDescriptor;
  EFI_KEY_DESCRIPTOR        *TableEntry;
  EFI_KEY_DESCRIPTOR        *NsKey;
  USB_NS_KEY                *UsbNsKey;
  UINTN                     Index;
  UINTN                     Index2;
  UINTN                     KeyCount;
  UINT8                     KeyCode;

  UsbKeyboardDevice = (USB_KB_DEV *) Context;

  //
  // Try to get current keyboard layout from HII database
  //
  KeyboardLayout = GetCurrentKeyboardLayout ();
  if (KeyboardLayout == NULL) {
    return;
  }

  //
  // Re-allocate resource for KeyConvertionTable
  //
  ReleaseKeyboardLayoutResources (UsbKeyboardDevice);
  UsbKeyboardDevice->KeyConvertionTable = AllocateZeroPool ((NUMBER_OF_VALID_USB_KEYCODE) * sizeof (EFI_KEY_DESCRIPTOR));
  ASSERT (UsbKeyboardDevice->KeyConvertionTable != NULL);

  //
  // Traverse the list of key descriptors following the header of EFI_HII_KEYBOARD_LAYOUT
  //
  KeyDescriptor = (EFI_KEY_DESCRIPTOR *) (((UINT8 *) KeyboardLayout) + sizeof (EFI_HII_KEYBOARD_LAYOUT));
  for (Index = 0; Index < KeyboardLayout->DescriptorCount; Index++) {
    //
    // Copy from HII keyboard layout package binary for alignment
    //
    CopyMem (&TempKey, KeyDescriptor, sizeof (EFI_KEY_DESCRIPTOR));

    //
    // Fill the key into KeyConvertionTable, whose index is calculated from USB keycode.
    //
    KeyCode = EfiKeyToUsbKeyCodeConvertionTable [(UINT8) (TempKey.Key)];
    TableEntry = GetKeyDescriptor (UsbKeyboardDevice, KeyCode);
    CopyMem (TableEntry, KeyDescriptor, sizeof (EFI_KEY_DESCRIPTOR));

    //
    // For non-spacing key, create the list with a non-spacing key followed by physical keys.
    //
    if (TempKey.Modifier == EFI_NS_KEY_MODIFIER) {
      UsbNsKey = AllocatePool (sizeof (USB_NS_KEY));
      ASSERT (UsbNsKey != NULL);

      //
      // Search for sequential children physical key definitions
      //
      KeyCount = 0;
      NsKey = KeyDescriptor + 1;
      for (Index2 = Index + 1; Index2 < KeyboardLayout->DescriptorCount; Index2++) {
        CopyMem (&TempKey, NsKey, sizeof (EFI_KEY_DESCRIPTOR));
        if (TempKey.Modifier & EFI_NS_KEY_DEPENDENCY_MODIFIER) {
          KeyCount++;
        } else {
          break;
        }
        NsKey++;
      }

      UsbNsKey->Signature = USB_NS_KEY_SIGNATURE;
      UsbNsKey->KeyCount = KeyCount;
      UsbNsKey->NsKey = AllocateCopyPool (
                          (KeyCount + 1) * sizeof (EFI_KEY_DESCRIPTOR),
                          KeyDescriptor
                          );
      InsertTailList (&UsbKeyboardDevice->NsKeyList, &UsbNsKey->Link);

      //
      // Skip over the child physical keys
      //
      Index += KeyCount;
      KeyDescriptor += KeyCount;
    }

    KeyDescriptor++;
  }

  //
  // There are two EfiKeyEnter, duplicate its key descriptor
  //
  TableEntry = GetKeyDescriptor (UsbKeyboardDevice, 0x58);
  KeyDescriptor = GetKeyDescriptor (UsbKeyboardDevice, 0x28);
  CopyMem (TableEntry, KeyDescriptor, sizeof (EFI_KEY_DESCRIPTOR));

  FreePool (KeyboardLayout);
}

/**
  Destroy resources for keyboard layout.

  @param  UsbKeyboardDevice    The USB_KB_DEV instance.

**/
VOID
EFIAPI
ReleaseKeyboardLayoutResources (
  IN OUT USB_KB_DEV              *UsbKeyboardDevice
  )
{
  USB_NS_KEY      *UsbNsKey;
  LIST_ENTRY      *Link;

  if (UsbKeyboardDevice->KeyConvertionTable != NULL) {
    FreePool (UsbKeyboardDevice->KeyConvertionTable);
  }
  UsbKeyboardDevice->KeyConvertionTable = NULL;

  while (!IsListEmpty (&UsbKeyboardDevice->NsKeyList)) {
    Link = GetFirstNode (&UsbKeyboardDevice->NsKeyList);
    UsbNsKey = USB_NS_KEY_FORM_FROM_LINK (Link);
    RemoveEntryList (&UsbNsKey->Link);

    FreePool (UsbNsKey->NsKey);
    FreePool (UsbNsKey);
  }
}

/**
  Initialize USB keyboard layout.

  This function initializes Key Convertion Table for the USB keyboard device.
  It first tries to retrieve layout from HII database. If failed and default
  layout is enabled, then it just uses the default layout.

  @param  UsbKeyboardDevice      The USB_KB_DEV instance.

  @retval EFI_SUCCESS            Initialization succeeded.
  @retval EFI_NOT_READY          Keyboard layout cannot be retrieve from HII
                                 database, and default layout is disabled.
  @retval Other                  Fail to register event to EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID group.

**/
EFI_STATUS
EFIAPI
InitKeyboardLayout (
  OUT USB_KB_DEV   *UsbKeyboardDevice
  )
{
  EFI_HII_KEYBOARD_LAYOUT   *KeyboardLayout;
  EFI_STATUS                Status;

  UsbKeyboardDevice->KeyConvertionTable = AllocateZeroPool ((NUMBER_OF_VALID_USB_KEYCODE) * sizeof (EFI_KEY_DESCRIPTOR));
  ASSERT (UsbKeyboardDevice->KeyConvertionTable != NULL);

  InitializeListHead (&UsbKeyboardDevice->NsKeyList);
  UsbKeyboardDevice->CurrentNsKey = NULL;
  UsbKeyboardDevice->KeyboardLayoutEvent = NULL;

  //
  // Register event to EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID group,
  // which will be triggered by EFI_HII_DATABASE_PROTOCOL.SetKeyboardLayout().
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  SetKeyboardLayoutEvent,
                  UsbKeyboardDevice,
                  &mKeyboardLayoutEventGuid,
                  &UsbKeyboardDevice->KeyboardLayoutEvent
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  KeyboardLayout = GetCurrentKeyboardLayout ();
  if (KeyboardLayout != NULL) {
    //
    // If current keyboard layout is successfully retrieved from HII database,
    // force to initialize the keyboard layout.
    //
    gBS->SignalEvent (UsbKeyboardDevice->KeyboardLayoutEvent);
  } else {
    if (FeaturePcdGet (PcdDisableDefaultKeyboardLayoutInUsbKbDriver)) {
      //
      // If no keyboard layout can be retrieved from HII database, and default layout
      // is disabled, then return EFI_NOT_READY.
      //
      return EFI_NOT_READY;
    }
    //
    // If no keyboard layout can be retrieved from HII database, and default layout
    // is enabled, then load the default keyboard layout.
    //
    LoadDefaultKeyboardLayout (UsbKeyboardDevice);
  }
  
  return EFI_SUCCESS;
}


/**
  Initialize USB keyboard device and all private data structures.

  @param  UsbKeyboardDevice  The USB_KB_DEV instance.

  @retval EFI_SUCCESS        Initialization is successful.
  @retval EFI_DEVICE_ERROR   Keyboard initialization failed.

**/
EFI_STATUS
EFIAPI
InitUSBKeyboard (
  IN OUT USB_KB_DEV   *UsbKeyboardDevice
  )
{
  UINT8               ConfigValue;
  UINT8               Protocol;
  UINT8               ReportId;
  UINT8               Duration;
  EFI_STATUS          Status;
  UINT32              TransferResult;

  REPORT_STATUS_CODE_WITH_DEVICE_PATH (
    EFI_PROGRESS_CODE,
    PcdGet32 (PcdStatusCodeValueKeyboardSelfTest),
    UsbKeyboardDevice->DevicePath
    );

  InitUSBKeyBuffer (&(UsbKeyboardDevice->KeyboardBuffer));

  //
  // Uses default configuration to configure the USB keyboard device.
  //
  ConfigValue = 0x01;
  Status = UsbSetConfiguration (
             UsbKeyboardDevice->UsbIo,
             (UINT16) ConfigValue,
             &TransferResult
             );
  if (EFI_ERROR (Status)) {
    //
    // If configuration could not be set here, it means
    // the keyboard interface has some errors and could
    // not be initialized
    //
    REPORT_STATUS_CODE_WITH_DEVICE_PATH (
      EFI_ERROR_CODE | EFI_ERROR_MINOR,
      PcdGet32 (PcdStatusCodeValueKeyboardInterfaceError),
      UsbKeyboardDevice->DevicePath
      );

    return EFI_DEVICE_ERROR;
  }

  UsbGetProtocolRequest (
    UsbKeyboardDevice->UsbIo,
    UsbKeyboardDevice->InterfaceDescriptor.InterfaceNumber,
    &Protocol
    );
  //
  // Set boot protocol for the USB Keyboard.
  // This driver only supports boot protocol.
  // The device that does not support boot protocol is not supported.
  //
  if (Protocol != BOOT_PROTOCOL) {
    UsbSetProtocolRequest (
      UsbKeyboardDevice->UsbIo,
      UsbKeyboardDevice->InterfaceDescriptor.InterfaceNumber,
      BOOT_PROTOCOL
      );
  }

  //
  // ReportId is zero, which means the idle rate applies to all input reports.
  //
  ReportId = 0;
  //
  // Duration is zero, which means the duration is infinite.
  // so the endpoint will inhibit reporting forever,
  // and only reporting when a change is detected in the report data.
  //
  Duration = 0;
  UsbSetIdleRequest (
    UsbKeyboardDevice->UsbIo,
    UsbKeyboardDevice->InterfaceDescriptor.InterfaceNumber,
    ReportId,
    Duration
    );

  UsbKeyboardDevice->CtrlOn     = FALSE;
  UsbKeyboardDevice->AltOn      = FALSE;
  UsbKeyboardDevice->ShiftOn    = FALSE;
  UsbKeyboardDevice->NumLockOn  = FALSE;
  UsbKeyboardDevice->CapsOn     = FALSE;
  UsbKeyboardDevice->ScrollOn   = FALSE;
  
  UsbKeyboardDevice->LeftCtrlOn   = FALSE;
  UsbKeyboardDevice->LeftAltOn    = FALSE;
  UsbKeyboardDevice->LeftShiftOn  = FALSE;
  UsbKeyboardDevice->LeftLogoOn   = FALSE;
  UsbKeyboardDevice->RightCtrlOn  = FALSE;
  UsbKeyboardDevice->RightAltOn   = FALSE;
  UsbKeyboardDevice->RightShiftOn = FALSE;
  UsbKeyboardDevice->RightLogoOn  = FALSE;
  UsbKeyboardDevice->MenuKeyOn    = FALSE;
  UsbKeyboardDevice->SysReqOn     = FALSE;

  UsbKeyboardDevice->AltGrOn      = FALSE;

  UsbKeyboardDevice->CurrentNsKey = NULL;

  //
  // Sync the initial state of lights on keyboard.
  //
  SetKeyLED (UsbKeyboardDevice);

  ZeroMem (UsbKeyboardDevice->LastKeyCodeArray, sizeof (UINT8) * 8);

  //
  // Set a timer for repeat keys' generation.
  //
  if (UsbKeyboardDevice->RepeatTimer != NULL) {
    gBS->CloseEvent (UsbKeyboardDevice->RepeatTimer);
    UsbKeyboardDevice->RepeatTimer = NULL;
  }

  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  USBKeyboardRepeatHandler,
                  UsbKeyboardDevice,
                  &UsbKeyboardDevice->RepeatTimer
                  );

  if (UsbKeyboardDevice->DelayedRecoveryEvent != NULL) {
    gBS->CloseEvent (UsbKeyboardDevice->DelayedRecoveryEvent);
    UsbKeyboardDevice->DelayedRecoveryEvent = NULL;
  }

  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  USBKeyboardRecoveryHandler,
                  UsbKeyboardDevice,
                  &UsbKeyboardDevice->DelayedRecoveryEvent
                  );

  return EFI_SUCCESS;
}


/**
  Handler function for USB keyboard's asynchronous interrupt transfer.

  This function is the handler function for USB keyboard's asynchronous interrupt transfer
  to manage the keyboard. It parses the USB keyboard input report, and inserts data to
  keyboard buffer according to state of modifer keys and normal keys. Timer for repeat key
  is also set accordingly.

  @param  Data             A pointer to a buffer that is filled with key data which is
                           retrieved via asynchronous interrupt transfer.
  @param  DataLength       Indicates the size of the data buffer.
  @param  Context          Pointing to USB_KB_DEV instance.
  @param  Result           Indicates the result of the asynchronous interrupt transfer.

  @retval EFI_SUCCESS      Asynchronous interrupt transfer is handled successfully.
  @retval EFI_DEVICE_ERROR Hardware error occurs.

**/
EFI_STATUS
EFIAPI
KeyboardHandler (
  IN  VOID          *Data,
  IN  UINTN         DataLength,
  IN  VOID          *Context,
  IN  UINT32        Result
  )
{
  USB_KB_DEV          *UsbKeyboardDevice;
  EFI_USB_IO_PROTOCOL *UsbIo;
  UINT8               *CurKeyCodeBuffer;
  UINT8               *OldKeyCodeBuffer;
  UINT8               CurModifierMap;
  UINT8               OldModifierMap;
  UINT8               Mask;
  UINT8               Index;
  UINT8               Index2;
  BOOLEAN             Down;
  BOOLEAN             KeyRelease;
  BOOLEAN             KeyPress;
  UINT8               SavedTail;
  USB_KEY             UsbKey;
  UINT8               NewRepeatKey;
  UINT32              UsbStatus;
  EFI_KEY_DESCRIPTOR  *KeyDescriptor;

  ASSERT (Context != NULL);

  NewRepeatKey      = 0;
  UsbKeyboardDevice = (USB_KB_DEV *) Context;
  UsbIo             = UsbKeyboardDevice->UsbIo;

  //
  // Analyzes Result and performs corresponding action.
  //
  if (Result != EFI_USB_NOERROR) {
    //
    // Some errors happen during the process
    //
    REPORT_STATUS_CODE_WITH_DEVICE_PATH (
      EFI_ERROR_CODE | EFI_ERROR_MINOR,
      PcdGet32 (PcdStatusCodeValueKeyboardInputError),
      UsbKeyboardDevice->DevicePath
      );

    //
    // Stop the repeat key generation if any
    //
    UsbKeyboardDevice->RepeatKey = 0;

    gBS->SetTimer (
          UsbKeyboardDevice->RepeatTimer,
          TimerCancel,
          USBKBD_REPEAT_RATE
          );

    if ((Result & EFI_USB_ERR_STALL) == EFI_USB_ERR_STALL) {
      UsbClearEndpointHalt (
        UsbIo,
        UsbKeyboardDevice->IntEndpointDescriptor.EndpointAddress,
        &UsbStatus
        );
    }

    //
    // Delete & Submit this interrupt again
    // Handler of DelayedRecoveryEvent triggered by timer will re-submit the interrupt. 
    //
    UsbIo->UsbAsyncInterruptTransfer (
             UsbIo,
             UsbKeyboardDevice->IntEndpointDescriptor.EndpointAddress,
             FALSE,
             0,
             0,
             NULL,
             NULL
             );
    //
    // EFI_USB_INTERRUPT_DELAY is defined in USB standard for error handling.
    //
    gBS->SetTimer (
           UsbKeyboardDevice->DelayedRecoveryEvent,
           TimerRelative,
           EFI_USB_INTERRUPT_DELAY
           );

    return EFI_DEVICE_ERROR;
  }

  //
  // If no error and no data, just return EFI_SUCCESS.
  //
  if (DataLength == 0 || Data == NULL) {
    return EFI_SUCCESS;
  }

  //
  // Following code checks current keyboard input report against old key code buffer.
  // According to USB HID Firmware Specification, the report consists of 8 bytes.
  // Byte 0 is map of Modifier keys.
  // Byte 1 is reserved.
  // Bytes 2 to 7 are keycodes.
  //
  CurKeyCodeBuffer  = (UINT8 *) Data;
  OldKeyCodeBuffer  = UsbKeyboardDevice->LastKeyCodeArray;

  //
  // Checks for new key stroke.
  //
  for (Index = 0; Index < 8; Index++) {
    if (OldKeyCodeBuffer[Index] != CurKeyCodeBuffer[Index]) {
      break;
    }
  }

  //
  // If no new key, return EFI_SUCCESS immediately.
  //
  if (Index == 8) {
    return EFI_SUCCESS;
  }

  //
  // Parse the modifier key, which is the first byte of keyboard input report.
  //
  CurModifierMap  = CurKeyCodeBuffer[0];
  OldModifierMap  = OldKeyCodeBuffer[0];

  //
  // Handle modifier key's pressing or releasing situation.
  // According to USB HID Firmware spec, Byte 0 uses folloing map of Modifier keys:
  // Bit0: Left Control,  Keycode: 0xe0
  // Bit1: Left Shift,    Keycode: 0xe1
  // Bit2: Left Alt,      Keycode: 0xe2
  // Bit3: Left GUI,      Keycode: 0xe3
  // Bit4: Right Control, Keycode: 0xe4
  // Bit5: Right Shift,   Keycode: 0xe5
  // Bit6: Right Alt,     Keycode: 0xe6
  // Bit7: Right GUI,     Keycode: 0xe7
  //
  for (Index = 0; Index < 8; Index++) {
    Mask = (UINT8) (1 << Index);
    if ((CurModifierMap & Mask) != (OldModifierMap & Mask)) {
      //
      // If current modifier key is up, then CurModifierMap & Mask = 0;
      // otherwise it is a non-zero value.
      // Insert the changed modifier key into key buffer.
      //
      Down = (BOOLEAN) ((CurModifierMap & Mask) != 0);
      InsertKeyCode (&(UsbKeyboardDevice->KeyboardBuffer), (UINT8) (0xe0 + Index), Down);
    }
  }

  //
  // Handle normal key's releasing situation
  // Bytes 2 to 7 are for normal keycodes
  //
  KeyRelease = FALSE;
  for (Index = 2; Index < 8; Index++) {

    if (!USBKBD_VALID_KEYCODE (OldKeyCodeBuffer[Index])) {
      continue;
    }
    //
    // For any key in old keycode buffer, if it is not in current keycode buffer,
    // then it is released. Otherwise, it is not released.
    //
    KeyRelease = TRUE;
    for (Index2 = 2; Index2 < 8; Index2++) {

      if (!USBKBD_VALID_KEYCODE (CurKeyCodeBuffer[Index2])) {
        continue;
      }

      if (OldKeyCodeBuffer[Index] == CurKeyCodeBuffer[Index2]) {
        KeyRelease = FALSE;
        break;
      }
    }

    if (KeyRelease) {
      InsertKeyCode (
        &(UsbKeyboardDevice->KeyboardBuffer),
        OldKeyCodeBuffer[Index],
        FALSE
        );
      //
      // The original repeat key is released.
      //
      if (OldKeyCodeBuffer[Index] == UsbKeyboardDevice->RepeatKey) {
        UsbKeyboardDevice->RepeatKey = 0;
      }
    }
  }

  //
  // If original repeat key is released, cancel the repeat timer
  //
  if (UsbKeyboardDevice->RepeatKey == 0) {
    gBS->SetTimer (
           UsbKeyboardDevice->RepeatTimer,
           TimerCancel,
           USBKBD_REPEAT_RATE
           );
  }

  //
  // Handle normal key's pressing situation
  //
  KeyPress = FALSE;
  for (Index = 2; Index < 8; Index++) {

    if (!USBKBD_VALID_KEYCODE (CurKeyCodeBuffer[Index])) {
      continue;
    }
    //
    // For any key in current keycode buffer, if it is not in old keycode buffer,
    // then it is pressed. Otherwise, it is not pressed.
    //
    KeyPress = TRUE;
    for (Index2 = 2; Index2 < 8; Index2++) {

      if (!USBKBD_VALID_KEYCODE (OldKeyCodeBuffer[Index2])) {
        continue;
      }

      if (CurKeyCodeBuffer[Index] == OldKeyCodeBuffer[Index2]) {
        KeyPress = FALSE;
        break;
      }
    }

    if (KeyPress) {
      InsertKeyCode (&(UsbKeyboardDevice->KeyboardBuffer), CurKeyCodeBuffer[Index], TRUE);

      //
      // Handle repeat key
      //
      KeyDescriptor = GetKeyDescriptor (UsbKeyboardDevice, CurKeyCodeBuffer[Index]);
      if (KeyDescriptor->Modifier == EFI_NUM_LOCK_MODIFIER || KeyDescriptor->Modifier == EFI_CAPS_LOCK_MODIFIER) {
        //
        // For NumLock or CapsLock pressed, there is no need to handle repeat key for them.
        //
        UsbKeyboardDevice->RepeatKey = 0;
      } else {
        //
        // Prepare new repeat key, and clear the original one.
        //
        NewRepeatKey = CurKeyCodeBuffer[Index];
        UsbKeyboardDevice->RepeatKey = 0;
      }
    }
  }

  //
  // Update LastKeycodeArray buffer in the UsbKeyboardDevice data structure.
  //
  for (Index = 0; Index < 8; Index++) {
    UsbKeyboardDevice->LastKeyCodeArray[Index] = CurKeyCodeBuffer[Index];
  }

  //
  // Pre-process KeyboardBuffer to check if Ctrl + Alt + Del is pressed.
  //
  SavedTail = UsbKeyboardDevice->KeyboardBuffer.BufferTail;
  Index     = UsbKeyboardDevice->KeyboardBuffer.BufferHead;
  while (Index != SavedTail) {
    RemoveKeyCode (&(UsbKeyboardDevice->KeyboardBuffer), &UsbKey);

    KeyDescriptor = GetKeyDescriptor (UsbKeyboardDevice, UsbKey.KeyCode);

    switch (KeyDescriptor->Modifier) {

    case EFI_LEFT_CONTROL_MODIFIER:
    case EFI_RIGHT_CONTROL_MODIFIER:
      if (UsbKey.Down) {
        UsbKeyboardDevice->CtrlOn = TRUE;
      } else {
        UsbKeyboardDevice->CtrlOn = FALSE;
      }
      break;

    case EFI_LEFT_ALT_MODIFIER:
    case EFI_RIGHT_ALT_MODIFIER:
      if (UsbKey.Down) {
        UsbKeyboardDevice->AltOn = TRUE;
      } else {
        UsbKeyboardDevice->AltOn = FALSE;
      }
      break;

    case EFI_ALT_GR_MODIFIER:
      if (UsbKey.Down) {
        UsbKeyboardDevice->AltGrOn = TRUE;
      } else {
        UsbKeyboardDevice->AltGrOn = FALSE;
      }
      break;

    //
    // For Del Key, check if Ctrl + Alt + Del occurs for reset.
    //
    case EFI_DELETE_MODIFIER:
      if (UsbKey.Down) {
        if ((UsbKeyboardDevice->CtrlOn) && (UsbKeyboardDevice->AltOn)) {
          gRT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);
        }
      }
      break;

    default:
      break;
    }

    //
    // Insert the key back to the buffer,
    // so the key sequence will not be destroyed.
    //
    InsertKeyCode (
      &(UsbKeyboardDevice->KeyboardBuffer),
      UsbKey.KeyCode,
      UsbKey.Down
      );
    Index = UsbKeyboardDevice->KeyboardBuffer.BufferHead;

  }
  //
  // If there is new key pressed, update the RepeatKey value, and set the
  // timer to repeate delay timer
  //
  if (NewRepeatKey != 0) {
    //
    // Sets trigger time to "Repeat Delay Time",
    // to trigger the repeat timer when the key is hold long
    // enough time.
    //
    gBS->SetTimer (
           UsbKeyboardDevice->RepeatTimer,
           TimerRelative,
           USBKBD_REPEAT_DELAY
           );
    UsbKeyboardDevice->RepeatKey = NewRepeatKey;
  }

  return EFI_SUCCESS;
}


/**
  Retrieves a USB keycode after parsing the raw data in keyboard buffer.

  This function parses keyboard buffer. It updates state of modifier key for
  USB_KB_DEV instancem, and returns keycode for output.

  @param  UsbKeyboardDevice    The USB_KB_DEV instance.
  @param  KeyCode              Pointer to the USB keycode for output.

  @retval EFI_SUCCESS          Keycode successfully parsed.
  @retval EFI_NOT_READY        Keyboard buffer is not ready for a valid keycode

**/
EFI_STATUS
EFIAPI
USBParseKey (
  IN OUT  USB_KB_DEV  *UsbKeyboardDevice,
     OUT  UINT8       *KeyCode
  )
{
  USB_KEY             UsbKey;
  EFI_KEY_DESCRIPTOR  *KeyDescriptor;

  *KeyCode = 0;

  while (!IsUSBKeyboardBufferEmpty (&UsbKeyboardDevice->KeyboardBuffer)) {
    //
    // Pops one raw data off.
    //
    RemoveKeyCode (&(UsbKeyboardDevice->KeyboardBuffer), &UsbKey);

    KeyDescriptor = GetKeyDescriptor (UsbKeyboardDevice, UsbKey.KeyCode);
    if (!UsbKey.Down) {
      //
      // Key is released.
      //
      switch (KeyDescriptor->Modifier) {

      //
      // Ctrl release
      //
      case EFI_LEFT_CONTROL_MODIFIER:
        UsbKeyboardDevice->LeftCtrlOn = FALSE;
        UsbKeyboardDevice->CtrlOn = FALSE;
        break;
      case EFI_RIGHT_CONTROL_MODIFIER:
        UsbKeyboardDevice->RightCtrlOn = FALSE;
        UsbKeyboardDevice->CtrlOn = FALSE;
        break;

      //
      // Shift release
      //
      case EFI_LEFT_SHIFT_MODIFIER:
        UsbKeyboardDevice->LeftShiftOn = FALSE;
        UsbKeyboardDevice->ShiftOn = FALSE;
        break;
      case EFI_RIGHT_SHIFT_MODIFIER:
        UsbKeyboardDevice->RightShiftOn = FALSE;
        UsbKeyboardDevice->ShiftOn = FALSE;
        break;

      //
      // Alt release
      //
      case EFI_LEFT_ALT_MODIFIER:
        UsbKeyboardDevice->LeftAltOn = FALSE;
        UsbKeyboardDevice->AltOn = FALSE;
        break;
      case EFI_RIGHT_ALT_MODIFIER:
        UsbKeyboardDevice->RightAltOn = FALSE;
        UsbKeyboardDevice->AltOn = FALSE;
        break;

      //
      // Left Logo release
      //
      case EFI_LEFT_LOGO_MODIFIER:
        UsbKeyboardDevice->LeftLogoOn = FALSE;
        break;

      //
      // Right Logo release
      //
      case EFI_RIGHT_LOGO_MODIFIER:
        UsbKeyboardDevice->RightLogoOn = FALSE;
        break;

      //
      // Menu key release
      //
      case EFI_MENU_MODIFIER:
        UsbKeyboardDevice->MenuKeyOn = FALSE;
        break;

      //
      // SysReq release
      //
      case EFI_PRINT_MODIFIER:
      case EFI_SYS_REQUEST_MODIFIER:
        UsbKeyboardDevice->SysReqOn = FALSE;
        break;

      //
      // AltGr release
      //
      case EFI_ALT_GR_MODIFIER:
        UsbKeyboardDevice->AltGrOn = FALSE;
        break;

      default:
        break;
      }

      continue;
    }

    //
    // Analyzes key pressing situation
    //
    switch (KeyDescriptor->Modifier) {

    //
    // Ctrl press
    //
    case EFI_LEFT_CONTROL_MODIFIER:
      UsbKeyboardDevice->LeftCtrlOn = TRUE;
      UsbKeyboardDevice->CtrlOn = TRUE;
      continue;
      break;
    case EFI_RIGHT_CONTROL_MODIFIER:
      UsbKeyboardDevice->RightCtrlOn = TRUE;
      UsbKeyboardDevice->CtrlOn = TRUE;
      continue;
      break;

    //
    // Shift press
    //
    case EFI_LEFT_SHIFT_MODIFIER:
      UsbKeyboardDevice->LeftShiftOn = TRUE;
      UsbKeyboardDevice->ShiftOn = TRUE;
      continue;
      break;
    case EFI_RIGHT_SHIFT_MODIFIER:
      UsbKeyboardDevice->RightShiftOn = TRUE;
      UsbKeyboardDevice->ShiftOn = TRUE;
      continue;
      break;

    //
    // Alt press
    //
    case EFI_LEFT_ALT_MODIFIER:
      UsbKeyboardDevice->LeftAltOn = TRUE;
      UsbKeyboardDevice->AltOn = TRUE;
      continue;
      break;
    case EFI_RIGHT_ALT_MODIFIER:
      UsbKeyboardDevice->RightAltOn = TRUE;
      UsbKeyboardDevice->AltOn = TRUE;
      continue;
      break;

    //
    // Left Logo press
    //
    case EFI_LEFT_LOGO_MODIFIER:
      UsbKeyboardDevice->LeftLogoOn = TRUE;
      break;

    //
    // Right Logo press
    //
    case EFI_RIGHT_LOGO_MODIFIER:
      UsbKeyboardDevice->RightLogoOn = TRUE;
      break;

    //
    // Menu key press
    //
    case EFI_MENU_MODIFIER:
      UsbKeyboardDevice->MenuKeyOn = TRUE;
      break;

    //
    // SysReq press
    //
    case EFI_PRINT_MODIFIER:
    case EFI_SYS_REQUEST_MODIFIER:
      UsbKeyboardDevice->SysReqOn = TRUE;
      continue;
      break;

    //
    // AltGr press
    //
    case EFI_ALT_GR_MODIFIER:
      UsbKeyboardDevice->AltGrOn = TRUE;
      break;

    case EFI_NUM_LOCK_MODIFIER:
      //
      // Toggle NumLock
      //
      UsbKeyboardDevice->NumLockOn = (BOOLEAN) (!(UsbKeyboardDevice->NumLockOn));
      SetKeyLED (UsbKeyboardDevice);
      continue;
      break;

    case EFI_CAPS_LOCK_MODIFIER:
      //
      // Toggle CapsLock
      //
      UsbKeyboardDevice->CapsOn = (BOOLEAN) (!(UsbKeyboardDevice->CapsOn));
      SetKeyLED (UsbKeyboardDevice);
      continue;
      break;

    case EFI_SCROLL_LOCK_MODIFIER:
      //
      // Toggle ScrollLock
      //
      UsbKeyboardDevice->ScrollOn = (BOOLEAN) (!(UsbKeyboardDevice->ScrollOn));
      SetKeyLED (UsbKeyboardDevice);
      continue;
      break;

    //
    // F11, F12, PrintScreen, Pause/Break
    // could not be retrieved via SimpleTextInEx protocol
    //
    case EFI_FUNCTION_KEY_ELEVEN_MODIFIER:
    case EFI_FUNCTION_KEY_TWELVE_MODIFIER:
    case EFI_PAUSE_MODIFIER:
    case EFI_BREAK_MODIFIER:
      //
      // Fall through
      //
      continue;
      break;

    default:
      break;
    }

    //
    // When encountering Ctrl + Alt + Del, then warm reset.
    //
    if (KeyDescriptor->Modifier == EFI_DELETE_MODIFIER) {
      if ((UsbKeyboardDevice->CtrlOn) && (UsbKeyboardDevice->AltOn)) {
        gRT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);
      }
    }

    *KeyCode = UsbKey.KeyCode;
    return EFI_SUCCESS;
  }

  return EFI_NOT_READY;
}


/**
  Converts USB Keycode ranging from 0x4 to 0x65 to EFI_INPUT_KEY.

  @param  UsbKeyboardDevice     The USB_KB_DEV instance.
  @param  KeyCode               Indicates the key code that will be interpreted.
  @param  Key                   A pointer to a buffer that is filled in with
                                the keystroke information for the key that
                                was pressed.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER KeyCode is not in the range of 0x4 to 0x65.
  @retval EFI_INVALID_PARAMETER Translated EFI_INPUT_KEY has zero for both ScanCode and UnicodeChar.
  @retval EFI_NOT_READY         KeyCode represents a dead key with EFI_NS_KEY_MODIFIER

**/
EFI_STATUS
EFIAPI
UsbKeyCodeToEfiInputKey (
  IN  USB_KB_DEV      *UsbKeyboardDevice,
  IN  UINT8           KeyCode,
  OUT EFI_INPUT_KEY   *Key
  )
{
  EFI_KEY_DESCRIPTOR  *KeyDescriptor;

  //
  // KeyCode must in the range of 0x4 to 0x65
  //
  if (!USBKBD_VALID_KEYCODE (KeyCode)) {
    return EFI_INVALID_PARAMETER;
  }
  if ((KeyCode - 4) >= NUMBER_OF_VALID_NON_MODIFIER_USB_KEYCODE) {
    return EFI_INVALID_PARAMETER;
  }

  KeyDescriptor = GetKeyDescriptor (UsbKeyboardDevice, KeyCode);

  if (KeyDescriptor->Modifier == EFI_NS_KEY_MODIFIER) {
    //
    // If this is a dead key with EFI_NS_KEY_MODIFIER, then record it and return.
    //
    UsbKeyboardDevice->CurrentNsKey = FindUsbNsKey (UsbKeyboardDevice, KeyDescriptor);
    return EFI_NOT_READY;
  }

  if (UsbKeyboardDevice->CurrentNsKey != NULL) {
    //
    // If this keystroke follows a non-spacing key, then find the descriptor for corresponding
    // physical key.
    //
    KeyDescriptor = FindPhysicalKey (UsbKeyboardDevice->CurrentNsKey, KeyDescriptor);
    UsbKeyboardDevice->CurrentNsKey = NULL;
  }

  Key->ScanCode = ModifierValueToEfiScanCodeConvertionTable[KeyDescriptor->Modifier];
  Key->UnicodeChar = KeyDescriptor->Unicode;

  if ((KeyDescriptor->AffectedAttribute & EFI_AFFECTED_BY_STANDARD_SHIFT)!= 0) {
    if (UsbKeyboardDevice->ShiftOn) {
      Key->UnicodeChar = KeyDescriptor->ShiftedUnicode;

      //
      // Need not return associated shift state if a class of printable characters that
      // are normally adjusted by shift modifiers. e.g. Shift Key + 'f' key = 'F'
      //
      if ((KeyDescriptor->AffectedAttribute & EFI_AFFECTED_BY_CAPS_LOCK) != 0) {
        UsbKeyboardDevice->LeftShiftOn = FALSE;
        UsbKeyboardDevice->RightShiftOn = FALSE;
      }

      if (UsbKeyboardDevice->AltGrOn) {
        Key->UnicodeChar = KeyDescriptor->ShiftedAltGrUnicode;
      }
    } else {
      //
      // Shift off
      //
      Key->UnicodeChar = KeyDescriptor->Unicode;

      if (UsbKeyboardDevice->AltGrOn) {
        Key->UnicodeChar = KeyDescriptor->AltGrUnicode;
      }
    }
  }

  if ((KeyDescriptor->AffectedAttribute & EFI_AFFECTED_BY_CAPS_LOCK) != 0) {
    if (UsbKeyboardDevice->CapsOn) {
      if (Key->UnicodeChar == KeyDescriptor->Unicode) {
        Key->UnicodeChar = KeyDescriptor->ShiftedUnicode;
      } else if (Key->UnicodeChar == KeyDescriptor->ShiftedUnicode) {
        Key->UnicodeChar = KeyDescriptor->Unicode;
      }
    }
  }

  //
  // Translate the CTRL-Alpha characters to their corresponding control value
  // (ctrl-a = 0x0001 through ctrl-Z = 0x001A)
  //
  if (UsbKeyboardDevice->CtrlOn) {
    if (Key->UnicodeChar >= 'a' && Key->UnicodeChar <= 'z') {
      Key->UnicodeChar = (UINT8) (Key->UnicodeChar - 'a' + 1);
    } else if (Key->UnicodeChar >= 'A' && Key->UnicodeChar <= 'Z') {
      Key->UnicodeChar = (UINT8) (Key->UnicodeChar - 'A' + 1);
    }
  }

  if (KeyDescriptor->AffectedAttribute & EFI_AFFECTED_BY_NUM_LOCK) {
    //
    // For key affected by NumLock, if NumLock is on and Shift is not pressed, then it means
    // normal key, instead of original control key. So the ScanCode should be cleaned.
    // Otherwise, it means control key, so preserve the EFI Scan Code and clear the unicode keycode.
    //
    if ((UsbKeyboardDevice->NumLockOn) && (!(UsbKeyboardDevice->ShiftOn))) {
      Key->ScanCode = SCAN_NULL;
    } else {
      Key->UnicodeChar = 0x00;
    }
  }

  //
  // Translate Unicode 0x1B (ESC) to EFI Scan Code
  //
  if (Key->UnicodeChar == 0x1B && Key->ScanCode == SCAN_NULL) {
    Key->ScanCode = SCAN_ESC;
    Key->UnicodeChar = 0x00;
  }

  //
  // Not valid for key without both unicode key code and EFI Scan Code.
  //
  if (Key->UnicodeChar == 0 && Key->ScanCode == SCAN_NULL) {
    return EFI_NOT_READY;
  }


  //
  // Save Shift/Toggle state
  //
  if (UsbKeyboardDevice->LeftCtrlOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_LEFT_CONTROL_PRESSED;
  }
  if (UsbKeyboardDevice->RightCtrlOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_RIGHT_CONTROL_PRESSED;
  }
  if (UsbKeyboardDevice->LeftAltOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_LEFT_ALT_PRESSED;
  }
  if (UsbKeyboardDevice->RightAltOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_RIGHT_ALT_PRESSED;
  }
  if (UsbKeyboardDevice->LeftShiftOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_LEFT_SHIFT_PRESSED;
  }
  if (UsbKeyboardDevice->RightShiftOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_RIGHT_SHIFT_PRESSED;
  }
  if (UsbKeyboardDevice->LeftLogoOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_LEFT_LOGO_PRESSED;
  }
  if (UsbKeyboardDevice->RightLogoOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_RIGHT_LOGO_PRESSED;
  }
  if (UsbKeyboardDevice->MenuKeyOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_MENU_KEY_PRESSED;
  }
  if (UsbKeyboardDevice->SysReqOn) {
    UsbKeyboardDevice->KeyState.KeyShiftState |= EFI_SYS_REQ_PRESSED;
  }

  if (UsbKeyboardDevice->ScrollOn) {
    UsbKeyboardDevice->KeyState.KeyToggleState |= EFI_SCROLL_LOCK_ACTIVE;
  }
  if (UsbKeyboardDevice->NumLockOn) {
    UsbKeyboardDevice->KeyState.KeyToggleState |= EFI_NUM_LOCK_ACTIVE;
  }
  if (UsbKeyboardDevice->CapsOn) {
    UsbKeyboardDevice->KeyState.KeyToggleState |= EFI_CAPS_LOCK_ACTIVE;
  }

  return EFI_SUCCESS;

}


/**
  Resets USB keyboard buffer.

  @param  KeyboardBuffer     Points to the USB keyboard buffer.

**/
VOID
EFIAPI
InitUSBKeyBuffer (
  OUT  USB_KB_BUFFER   *KeyboardBuffer
  )
{
  ZeroMem (KeyboardBuffer, sizeof (USB_KB_BUFFER));

  KeyboardBuffer->BufferHead = KeyboardBuffer->BufferTail;
}


/**
  Check whether USB keyboard buffer is empty.

  @param  KeyboardBuffer     USB keyboard buffer

  @retval TRUE               Keyboard buffer is empty.
  @retval FALSE              Keyboard buffer is not empty.

**/
BOOLEAN
EFIAPI
IsUSBKeyboardBufferEmpty (
  IN  USB_KB_BUFFER   *KeyboardBuffer
  )
{
  //
  // Meet FIFO empty condition
  //
  return (BOOLEAN) (KeyboardBuffer->BufferHead == KeyboardBuffer->BufferTail);
}


/**
  Check whether USB keyboard buffer is full.

  @param  KeyboardBuffer     USB keyboard buffer

  @retval TRUE               Keyboard buffer is full.
  @retval FALSE              Keyboard buffer is not full.

**/
BOOLEAN
EFIAPI
IsUSBKeyboardBufferFull (
  IN  USB_KB_BUFFER   *KeyboardBuffer
  )
{
  return (BOOLEAN)(((KeyboardBuffer->BufferTail + 1) % (MAX_KEY_ALLOWED + 1)) == KeyboardBuffer->BufferHead);
}


/**
  Inserts a keycode into keyboard buffer.

  @param  KeyboardBuffer     Points to the USB keyboard buffer.
  @param  Key                Keycode to insert.
  @param  Down               TRUE means key is pressed.
                             FALSE means key is released.

**/
VOID
EFIAPI
InsertKeyCode (
  IN OUT  USB_KB_BUFFER *KeyboardBuffer,
  IN      UINT8         Key,
  IN      BOOLEAN       Down
  )
{
  USB_KEY UsbKey;

  //
  // If keyboard buffer is full, throw the
  // first key out of the keyboard buffer.
  //
  if (IsUSBKeyboardBufferFull (KeyboardBuffer)) {
    RemoveKeyCode (KeyboardBuffer, &UsbKey);
  }

  KeyboardBuffer->Buffer[KeyboardBuffer->BufferTail].KeyCode = Key;
  KeyboardBuffer->Buffer[KeyboardBuffer->BufferTail].Down    = Down;

  //
  // Adjust the tail pointer of the FIFO keyboard buffer.
  //
  KeyboardBuffer->BufferTail = (UINT8) ((KeyboardBuffer->BufferTail + 1) % (MAX_KEY_ALLOWED + 1));
}


/**
  Remove a keycode from keyboard buffer and return it.

  @param  KeyboardBuffer     Points to the USB keyboard buffer.
  @param  UsbKey             Points to the buffer that contains keycode for output.

  @retval EFI_SUCCESS        Keycode successfully removed from keyboard buffer.
  @retval EFI_DEVICE_ERROR   Keyboard buffer is empty.

**/
EFI_STATUS
EFIAPI
RemoveKeyCode (
  IN OUT  USB_KB_BUFFER *KeyboardBuffer,
     OUT  USB_KEY       *UsbKey
  )
{
  if (IsUSBKeyboardBufferEmpty (KeyboardBuffer)) {
    return EFI_DEVICE_ERROR;
  }

  UsbKey->KeyCode = KeyboardBuffer->Buffer[KeyboardBuffer->BufferHead].KeyCode;
  UsbKey->Down    = KeyboardBuffer->Buffer[KeyboardBuffer->BufferHead].Down;

  //
  // Adjust the head pointer of the FIFO keyboard buffer.
  //
  KeyboardBuffer->BufferHead = (UINT8) ((KeyboardBuffer->BufferHead + 1) % (MAX_KEY_ALLOWED + 1));

  return EFI_SUCCESS;
}


/**
  Sets USB keyboard LED state.

  @param  UsbKeyboardDevice  The USB_KB_DEV instance.

**/
VOID
EFIAPI
SetKeyLED (
  IN  USB_KB_DEV    *UsbKeyboardDevice
  )
{
  LED_MAP Led;
  UINT8   ReportId;

  //
  // Set each field in Led map.
  //
  Led.NumLock    = (UINT8) ((UsbKeyboardDevice->NumLockOn) ? 1 : 0);
  Led.CapsLock   = (UINT8) ((UsbKeyboardDevice->CapsOn) ? 1 : 0);
  Led.ScrollLock = (UINT8) ((UsbKeyboardDevice->ScrollOn) ? 1 : 0);
  Led.Resrvd     = 0;

  ReportId       = 0;
  //
  // Call Set_Report Request to lighten the LED.
  //
  UsbSetReportRequest (
    UsbKeyboardDevice->UsbIo,
    UsbKeyboardDevice->InterfaceDescriptor.InterfaceNumber,
    ReportId,
    HID_OUTPUT_REPORT,
    1,
    (UINT8 *) &Led
    );
}


/**
  Handler for Repeat Key event.

  This function is the handler for Repeat Key event triggered
  by timer.
  After a repeatable key is pressed, the event would be triggered
  with interval of USBKBD_REPEAT_DELAY. Once the event is triggered,
  following trigger will come with interval of USBKBD_REPEAT_RATE.

  @param  Event              The Repeat Key event.
  @param  Context            Points to the USB_KB_DEV instance.

**/
VOID
EFIAPI
USBKeyboardRepeatHandler (
  IN    EFI_EVENT    Event,
  IN    VOID         *Context
  )
{
  USB_KB_DEV  *UsbKeyboardDevice;

  UsbKeyboardDevice = (USB_KB_DEV *) Context;

  //
  // Do nothing when there is no repeat key.
  //
  if (UsbKeyboardDevice->RepeatKey != 0) {
    //
    // Inserts the repeat key into keyboard buffer,
    //
    InsertKeyCode (
      &(UsbKeyboardDevice->KeyboardBuffer),
      UsbKeyboardDevice->RepeatKey,
      TRUE
      );

    //
    // Set repeat rate for next repeat key generation.
    //
    gBS->SetTimer (
           UsbKeyboardDevice->RepeatTimer,
           TimerRelative,
           USBKBD_REPEAT_RATE
           );
  }
}


/**
  Handler for Delayed Recovery event.

  This function is the handler for Delayed Recovery event triggered
  by timer.
  After a device error occurs, the event would be triggered
  with interval of EFI_USB_INTERRUPT_DELAY. EFI_USB_INTERRUPT_DELAY
  is defined in USB standard for error handling.

  @param  Event              The Delayed Recovery event.
  @param  Context            Points to the USB_KB_DEV instance.

**/
VOID
EFIAPI
USBKeyboardRecoveryHandler (
  IN    EFI_EVENT    Event,
  IN    VOID         *Context
  )
{

  USB_KB_DEV          *UsbKeyboardDevice;
  EFI_USB_IO_PROTOCOL *UsbIo;
  UINT8               PacketSize;

  UsbKeyboardDevice = (USB_KB_DEV *) Context;

  UsbIo             = UsbKeyboardDevice->UsbIo;

  PacketSize        = (UINT8) (UsbKeyboardDevice->IntEndpointDescriptor.MaxPacketSize);

  //
  // Re-submit Asynchronous Interrupt Transfer for recovery.
  //
  UsbIo->UsbAsyncInterruptTransfer (
           UsbIo,
           UsbKeyboardDevice->IntEndpointDescriptor.EndpointAddress,
           TRUE,
           UsbKeyboardDevice->IntEndpointDescriptor.Interval,
           PacketSize,
           KeyboardHandler,
           UsbKeyboardDevice
           );
}
