/*
 * Defines keyboard scancodes.
 * Mirrors the values in SDL_scancode.h, please refer to SDL documentation.
 */

#ifndef REVYV_SCANCODES_H
#define REVYV_SCANCODES_H

typedef enum {
    REVYV_SCANCODE_UNKNOWN = 0,

    REVYV_SCANCODE_A = 4,
    REVYV_SCANCODE_B = 5,
    REVYV_SCANCODE_C = 6,
    REVYV_SCANCODE_D = 7,
    REVYV_SCANCODE_E = 8,
    REVYV_SCANCODE_F = 9,
    REVYV_SCANCODE_G = 10,
    REVYV_SCANCODE_H = 11,
    REVYV_SCANCODE_I = 12,
    REVYV_SCANCODE_J = 13,
    REVYV_SCANCODE_K = 14,
    REVYV_SCANCODE_L = 15,
    REVYV_SCANCODE_M = 16,
    REVYV_SCANCODE_N = 17,
    REVYV_SCANCODE_O = 18,
    REVYV_SCANCODE_P = 19,
    REVYV_SCANCODE_Q = 20,
    REVYV_SCANCODE_R = 21,
    REVYV_SCANCODE_S = 22,
    REVYV_SCANCODE_T = 23,
    REVYV_SCANCODE_U = 24,
    REVYV_SCANCODE_V = 25,
    REVYV_SCANCODE_W = 26,
    REVYV_SCANCODE_X = 27,
    REVYV_SCANCODE_Y = 28,
    REVYV_SCANCODE_Z = 29,

    REVYV_SCANCODE_1 = 30,
    REVYV_SCANCODE_2 = 31,
    REVYV_SCANCODE_3 = 32,
    REVYV_SCANCODE_4 = 33,
    REVYV_SCANCODE_5 = 34,
    REVYV_SCANCODE_6 = 35,
    REVYV_SCANCODE_7 = 36,
    REVYV_SCANCODE_8 = 37,
    REVYV_SCANCODE_9 = 38,
    REVYV_SCANCODE_0 = 39,

    REVYV_SCANCODE_RETURN = 40,
    REVYV_SCANCODE_ESCAPE = 41,
    REVYV_SCANCODE_BACKSPACE = 42,
    REVYV_SCANCODE_TAB = 43,
    REVYV_SCANCODE_SPACE = 44,

    REVYV_SCANCODE_MINUS = 45,
    REVYV_SCANCODE_EQUALS = 46,
    REVYV_SCANCODE_LEFTBRACKET = 47,
    REVYV_SCANCODE_RIGHTBRACKET = 48,

    /* Located at the lower left of the return key on ISO keyboards and at the right end
     * of the QWERTY row on ANSI keyboards. Produces REVERSE SOLIDUS (backslash) and
     * VERTICAL LINE in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac
     * layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN and POUND SIGN
     * in a Swiss German layout, NUMBER SIGN and APOSTROPHE in a German layout, GRAVE
     * ACCENT and POUND SIGN in a French Mac layout, and ASTERISK and MICRO SIGN in a
     * French Windows layout.
     */
    REVYV_SCANCODE_BACKSLASH = 49,

    /* ISO USB keyboards actually use this code instead of 49 for the same key, but all
     * OSes I've seen treat the two codes identically. So, as an implementor, unless
     * your keyboard generates both of those codes and your OS treats them differently,
     * you should generate REVYV_SCANCODE_BACKSLASH instead of this code. As a user, you
     * should not rely on this code because ASL will never generate it with most (all?) keyboards.
     */
    REVYV_SCANCODE_NONUSHASH = 50,

    REVYV_SCANCODE_SEMICOLON = 51,
    REVYV_SCANCODE_APOSTROPHE = 52,

    /* Located in the top left corner (on both ANSI and ISO keyboards). Produces GRAVE ACCENT and
     * TILDE in a US Windows layout and in US and UK Mac layouts on ANSI keyboards, GRAVE ACCENT
     * and NOT SIGN in a UK Windows layout, SECTION SIGN and PLUS-MINUS SIGN in US and UK Mac
     * layouts on ISO keyboards, SECTION SIGN and DEGREE SIGN in a Swiss German layout (Mac:
     * only on ISO keyboards), CIRCUMFLEX ACCENT and DEGREE SIGN in a German layout (Mac: only on
     * ISO keyboards), SUPERSCRIPT TWO and TILDE in a French Windows layout, COMMERCIAL AT and
     * NUMBER SIGN in a French Mac layout on ISO keyboards, and LESS-THAN SIGN and GREATER-THAN
     * SIGN in a Swiss German, German, or French Mac layout on ANSI keyboards.
     */
    REVYV_SCANCODE_GRAVE = 53,

    REVYV_SCANCODE_COMMA = 54,
    REVYV_SCANCODE_PERIOD = 55,
    REVYV_SCANCODE_SLASH = 56,

    REVYV_SCANCODE_CAPSLOCK = 57,

    REVYV_SCANCODE_F1 = 58,
    REVYV_SCANCODE_F2 = 59,
    REVYV_SCANCODE_F3 = 60,
    REVYV_SCANCODE_F4 = 61,
    REVYV_SCANCODE_F5 = 62,
    REVYV_SCANCODE_F6 = 63,
    REVYV_SCANCODE_F7 = 64,
    REVYV_SCANCODE_F8 = 65,
    REVYV_SCANCODE_F9 = 66,
    REVYV_SCANCODE_F10 = 67,
    REVYV_SCANCODE_F11 = 68,
    REVYV_SCANCODE_F12 = 69,

    REVYV_SCANCODE_PRINTSCREEN = 70,
    REVYV_SCANCODE_SCROLLLOCK = 71,
    REVYV_SCANCODE_PAUSE = 72,

    // Insert on PC, help on some Mac keyboards (but does send code 73, not 117)
    REVYV_SCANCODE_INSERT = 73,

    REVYV_SCANCODE_HOME = 74,
    REVYV_SCANCODE_PAGEUP = 75,
    REVYV_SCANCODE_DELETE = 76,
    REVYV_SCANCODE_END = 77,
    REVYV_SCANCODE_PAGEDOWN = 78,
    REVYV_SCANCODE_RIGHT = 79,
    REVYV_SCANCODE_LEFT = 80,
    REVYV_SCANCODE_DOWN = 81,
    REVYV_SCANCODE_UP = 82,

    // Num lock on PC, clear on Mac keyboards
    REVYV_SCANCODE_NUMLOCKCLEAR = 83,

    REVYV_SCANCODE_KP_DIVIDE = 84,
    REVYV_SCANCODE_KP_MULTIPLY = 85,
    REVYV_SCANCODE_KP_MINUS = 86,
    REVYV_SCANCODE_KP_PLUS = 87,
    REVYV_SCANCODE_KP_ENTER = 88,
    REVYV_SCANCODE_KP_1 = 89,
    REVYV_SCANCODE_KP_2 = 90,
    REVYV_SCANCODE_KP_3 = 91,
    REVYV_SCANCODE_KP_4 = 92,
    REVYV_SCANCODE_KP_5 = 93,
    REVYV_SCANCODE_KP_6 = 94,
    REVYV_SCANCODE_KP_7 = 95,
    REVYV_SCANCODE_KP_8 = 96,
    REVYV_SCANCODE_KP_9 = 97,
    REVYV_SCANCODE_KP_0 = 98,
    REVYV_SCANCODE_KP_PERIOD = 99,

    /* This is the additional key that ISO keyboards have over ANSI ones,
     * located between left shift and Y. Produces GRAVE ACCENT and TILDE in a
     * US or UK Mac layout, REVERSE SOLIDUS (backslash) and VERTICAL LINE in a
     * US or UK Windows layout, and LESS-THAN SIGN and GREATER-THAN SIGN
     * in a Swiss German, German, or French layout. */
    REVYV_SCANCODE_NONUSBACKSLASH = 100,

    // Windows contextual menu, compose
    REVYV_SCANCODE_APPLICATION = 101,

    /* The USB document says this is a status flag, not a physical
     * key - but some Mac keyboards do have a power key. */
    REVYV_SCANCODE_POWER = 102,

    REVYV_SCANCODE_KP_EQUALS = 103,
    REVYV_SCANCODE_F13 = 104,
    REVYV_SCANCODE_F14 = 105,
    REVYV_SCANCODE_F15 = 106,
    REVYV_SCANCODE_F16 = 107,
    REVYV_SCANCODE_F17 = 108,
    REVYV_SCANCODE_F18 = 109,
    REVYV_SCANCODE_F19 = 110,
    REVYV_SCANCODE_F20 = 111,
    REVYV_SCANCODE_F21 = 112,
    REVYV_SCANCODE_F22 = 113,
    REVYV_SCANCODE_F23 = 114,
    REVYV_SCANCODE_F24 = 115,
    REVYV_SCANCODE_EXECUTE = 116,
    REVYV_SCANCODE_HELP = 117,
    REVYV_SCANCODE_MENU = 118,
    REVYV_SCANCODE_SELECT = 119,
    REVYV_SCANCODE_STOP = 120,

    /* Redo */
    REVYV_SCANCODE_AGAIN = 121,

    REVYV_SCANCODE_UNDO = 122,
    REVYV_SCANCODE_CUT = 123,
    REVYV_SCANCODE_COPY = 124,
    REVYV_SCANCODE_PASTE = 125,
    REVYV_SCANCODE_FIND = 126,
    REVYV_SCANCODE_MUTE = 127,
    REVYV_SCANCODE_VOLUMEUP = 128,
    REVYV_SCANCODE_VOLUMEDOWN = 129,

    /* Not sure whether there's a reason to enable these: */
    // REVYV_SCANCODE_LOCKINGCAPSLOCK = 130,
    // REVYV_SCANCODE_LOCKINGNUMLOCK = 131,
    // REVYV_SCANCODE_LOCKINGSCROLLLOCK = 132,

    REVYV_SCANCODE_KP_COMMA = 133,

    REVYV_SCANCODE_KP_EQUALSAS400 = 134,

    // Used on Asian keyboards, see footnotes in USB doc
    REVYV_SCANCODE_INTERNATIONAL1 = 135,

    REVYV_SCANCODE_INTERNATIONAL2 = 136,

    // Yen
    REVYV_SCANCODE_INTERNATIONAL3 = 137,

    REVYV_SCANCODE_INTERNATIONAL4 = 138,
    REVYV_SCANCODE_INTERNATIONAL5 = 139,
    REVYV_SCANCODE_INTERNATIONAL6 = 140,
    REVYV_SCANCODE_INTERNATIONAL7 = 141,
    REVYV_SCANCODE_INTERNATIONAL8 = 142,
    REVYV_SCANCODE_INTERNATIONAL9 = 143,

    // Hangul/English toggle
    REVYV_SCANCODE_LANG1 = 144,

    // Hanja conversion
    REVYV_SCANCODE_LANG2 = 145,

    // Katakana
    REVYV_SCANCODE_LANG3 = 146,

    // Hiragana
    REVYV_SCANCODE_LANG4 = 147,

    // Zenkaku/Hankaku
    REVYV_SCANCODE_LANG5 = 148,

    // Reserved
    REVYV_SCANCODE_LANG6 = 149,

    // Reserved
    REVYV_SCANCODE_LANG7 = 150,

    // Reserved
    REVYV_SCANCODE_LANG8 = 151,

    // Reserved
    REVYV_SCANCODE_LANG9 = 152,

    // Erase-Eaze
    REVYV_SCANCODE_ALTERASE = 153,

    REVYV_SCANCODE_SYSREQ = 154,
    REVYV_SCANCODE_CANCEL = 155,
    REVYV_SCANCODE_CLEAR = 156,
    REVYV_SCANCODE_PRIOR = 157,
    REVYV_SCANCODE_RETURN2 = 158,
    REVYV_SCANCODE_SEPARATOR = 159,
    REVYV_SCANCODE_OUT = 160,
    REVYV_SCANCODE_OPER = 161,
    REVYV_SCANCODE_CLEARAGAIN = 162,
    REVYV_SCANCODE_CRSEL = 163,
    REVYV_SCANCODE_EXSEL = 164,

    REVYV_SCANCODE_KP_00 = 176,
    REVYV_SCANCODE_KP_000 = 177,
    REVYV_SCANCODE_THOUSANDSSEPARATOR = 178,
    REVYV_SCANCODE_DECIMALSEPARATOR = 179,
    REVYV_SCANCODE_CURRENCYUNIT = 180,
    REVYV_SCANCODE_CURRENCYSUBUNIT = 181,
    REVYV_SCANCODE_KP_LEFTPAREN = 182,
    REVYV_SCANCODE_KP_RIGHTPAREN = 183,
    REVYV_SCANCODE_KP_LEFTBRACE = 184,
    REVYV_SCANCODE_KP_RIGHTBRACE = 185,
    REVYV_SCANCODE_KP_TAB = 186,
    REVYV_SCANCODE_KP_BACKSPACE = 187,
    REVYV_SCANCODE_KP_A = 188,
    REVYV_SCANCODE_KP_B = 189,
    REVYV_SCANCODE_KP_C = 190,
    REVYV_SCANCODE_KP_D = 191,
    REVYV_SCANCODE_KP_E = 192,
    REVYV_SCANCODE_KP_F = 193,
    REVYV_SCANCODE_KP_XOR = 194,
    REVYV_SCANCODE_KP_POWER = 195,
    REVYV_SCANCODE_KP_PERCENT = 196,
    REVYV_SCANCODE_KP_LESS = 197,
    REVYV_SCANCODE_KP_GREATER = 198,
    REVYV_SCANCODE_KP_AMPERSAND = 199,
    REVYV_SCANCODE_KP_DBLAMPERSAND = 200,
    REVYV_SCANCODE_KP_VERTICALBAR = 201,
    REVYV_SCANCODE_KP_DBLVERTICALBAR = 202,
    REVYV_SCANCODE_KP_COLON = 203,
    REVYV_SCANCODE_KP_HASH = 204,
    REVYV_SCANCODE_KP_SPACE = 205,
    REVYV_SCANCODE_KP_AT = 206,
    REVYV_SCANCODE_KP_EXCLAM = 207,
    REVYV_SCANCODE_KP_MEMSTORE = 208,
    REVYV_SCANCODE_KP_MEMRECALL = 209,
    REVYV_SCANCODE_KP_MEMCLEAR = 210,
    REVYV_SCANCODE_KP_MEMADD = 211,
    REVYV_SCANCODE_KP_MEMSUBTRACT = 212,
    REVYV_SCANCODE_KP_MEMMULTIPLY = 213,
    REVYV_SCANCODE_KP_MEMDIVIDE = 214,
    REVYV_SCANCODE_KP_PLUSMINUS = 215,
    REVYV_SCANCODE_KP_CLEAR = 216,
    REVYV_SCANCODE_KP_CLEARENTRY = 217,
    REVYV_SCANCODE_KP_BINARY = 218,
    REVYV_SCANCODE_KP_OCTAL = 219,
    REVYV_SCANCODE_KP_DECIMAL = 220,
    REVYV_SCANCODE_KP_HEXADECIMAL = 221,

    REVYV_SCANCODE_LCTRL = 224,
    REVYV_SCANCODE_LSHIFT = 225,

    // Alt, Option
    REVYV_SCANCODE_LALT = 226,

    // Windows, Command (Apple), Meta
    REVYV_SCANCODE_LGUI = 227,

    REVYV_SCANCODE_RCTRL = 228,
    REVYV_SCANCODE_RSHIFT = 229,

    // Alt-Gr, Option
    REVYV_SCANCODE_RALT = 230,

    // Windows, Command (Apple), Meta
    REVYV_SCANCODE_RGUI = 231,

    /* I'm not sure if this is really not covered by any of the above,
     * but since there's a special KMOD_MODE for it, I'm adding it here. */
    REVYV_SCANCODE_MODE = 257,

    REVYV_SCANCODE_AUDIONEXT = 258,
    REVYV_SCANCODE_AUDIOPREV = 259,
    REVYV_SCANCODE_AUDIOSTOP = 260,
    REVYV_SCANCODE_AUDIOPLAY = 261,
    REVYV_SCANCODE_AUDIOMUTE = 262,
    REVYV_SCANCODE_MEDIASELECT = 263,
    REVYV_SCANCODE_WWW = 264,
    REVYV_SCANCODE_MAIL = 265,
    REVYV_SCANCODE_CALCULATOR = 266,
    REVYV_SCANCODE_COMPUTER = 267,
    REVYV_SCANCODE_AC_SEARCH = 268,
    REVYV_SCANCODE_AC_HOME = 269,
    REVYV_SCANCODE_AC_BACK = 270,
    REVYV_SCANCODE_AC_FORWARD = 271,
    REVYV_SCANCODE_AC_STOP = 272,
    REVYV_SCANCODE_AC_REFRESH = 273,
    REVYV_SCANCODE_AC_BOOKMARKS = 274,

    REVYV_SCANCODE_BRIGHTNESSDOWN = 275,
    REVYV_SCANCODE_BRIGHTNESSUP = 276,

    // Display mirroring/dual display switch, video mode switch
    REVYV_SCANCODE_DISPLAYSWITCH = 277,

    REVYV_SCANCODE_KBDILLUMTOGGLE = 278,
    REVYV_SCANCODE_KBDILLUMDOWN = 279,
    REVYV_SCANCODE_KBDILLUMUP = 280,
    REVYV_SCANCODE_EJECT = 281,
    REVYV_SCANCODE_SLEEP = 282,

    REVYV_SCANCODE_APP1 = 283,
    REVYV_SCANCODE_APP2 = 284,

    /* Walther keys */

    /* Add any other keys here. */

    // Not a key, just marks the number of scancodes for array bounds
    REVYV_NUM_SCANCODES = 512
} RevyvScancode;

#endif