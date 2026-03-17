/* ==========================================================================
 * QMK Firmware — Custom Keyboard Keymap
 *
 * Features:
 *   - 5 layers: BASE (QWERTY), SUPER (F-keys / navigation), PUNCT (brackets
 *     and punctuation via Windows Alt-codes), MEDIA (volume / playback),
 *     GAME (shifted modifiers for gaming).
 *   - Layer switching through key combos (chords).
 *   - Per-layer RGB underglow indication.
 * ========================================================================== */

#include QMK_KEYBOARD_H

/* --------------------------------------------------------------------------
 * Layer-switching shorthand macros
 * -------------------------------------------------------------------------- */
#define SLTG TG(_SUPER)  // Toggle the _SUPER layer on / off
#define SLMO MO(_SUPER)  // Momentary activation of _SUPER while held
#define PLTG TG(_PUNCT)  // Toggle the _PUNCT layer on / off
#define PLMO MO(_PUNCT)  // Momentary activation of _PUNCT while held
#define MLTG TG(_MEDIA)  // Toggle the _MEDIA layer on / off
#define MLMO MO(_MEDIA)  // Momentary activation of _MEDIA while held
#define GLTG TG(_GAME)   // Toggle the _GAME layer on / off
#define BTO  TO(_BASE)   // Force-switch to _BASE, deactivating every other layer

/* --------------------------------------------------------------------------
 * Shifted-key shorthand macros
 * Each macro sends a single keypress that normally requires Shift.
 * -------------------------------------------------------------------------- */
#define KC_STAB LSFT(KC_TAB)   // Shift + Tab
#define KC_CLN  LSFT(KC_SCLN)  // Colon          ( : )
#define KC_UOT  LSFT(KC_QUOT)  // Double quote    ( " )
#define KC_LBRS LSFT(KC_LBRC)  // Left brace      ( { )
#define KC_RBRS LSFT(KC_RBRC)  // Right brace     ( } )
#define KC_LARW LSFT(KC_COMM)  // Left angle bracket  ( < )
#define KC_RARW LSFT(KC_DOT)   // Right angle bracket ( > )
#define KC_LAR  LSFT(KC_9)     // Left parenthesis    ( ( )
#define KC_RAR  LSFT(KC_0)     // Right parenthesis   ( ) )

/* --------------------------------------------------------------------------
 * Layer definitions
 * -------------------------------------------------------------------------- */
enum layers {
    _BASE = 0,  // Default QWERTY typing layer
    _SUPER,     // F-keys, arrow / page navigation, system controls
    _PUNCT,     // Punctuation & brackets (output via Alt-codes)
    _MEDIA,     // Media playback and volume controls
    _GAME,      // Gaming-oriented layout with repositioned modifiers
};

/* --------------------------------------------------------------------------
 * Combo identifiers
 * Each entry corresponds to a chord (simultaneous key press) that triggers
 * a specific action.  COMBO_LENGTH must be the last element — QMK uses it
 * to determine the total number of registered combos.
 * -------------------------------------------------------------------------- */
enum combos {
    COMBO_SUPER_LR,         // Toggle _SUPER
    COMBO_SUPER_LR_MOD,     // Momentary _SUPER (primary)
    COMBO_SUPER_LR_MOD_ALT, // Momentary _SUPER (alternative chord)
    COMBO_PUNCT_LR,         // Toggle _PUNCT
    COMBO_PUNCT_LR_MOD,     // Momentary _PUNCT
    COMBO_MEDIA_LR_MOD,     // Momentary _MEDIA
    COMBO_GAME_LR,          // Toggle _GAME
    COMBO_CLEAN_LR,         // Emergency reset to _BASE
    COMBO_CAPS,             // Caps Lock
    COMBO_LENGTH            // ← keeps combo count in sync automatically
};

/* --------------------------------------------------------------------------
 * Custom keycodes — punctuation characters sent as Windows Alt-codes
 *
 * On Windows, holding Left Alt and typing a decimal number on the numpad
 * inserts the corresponding ASCII character.  These custom keycodes
 * automate that sequence so the characters are input regardless of the
 * currently active OS keyboard layout.
 * -------------------------------------------------------------------------- */
enum custom_keycodes {
    DOT_A = SAFE_RANGE,  // .  (period)        — Alt+46
    COMM_A,              // ,  (comma)         — Alt+44
    EXC_A,               // !  (exclamation)   — Alt+33
    QUES_A,              // ?  (question mark) — Alt+63
    COL_A,               // :  (colon)         — Alt+58
    SEM_A,               // ;  (semicolon)     — Alt+59
    APO_A,               // '  (apostrophe)    — Alt+39
    HYP_A,               // -  (hyphen)        — Alt+45
    QUO_A,               // "  (double quote)  — Alt+34
    SQUO_A,              // '  (single quote)  — Alt+39
    LPRN_A,              // (  (left paren)    — Alt+40
    RPRN_A,              // )  (right paren)   — Alt+41
    LBRC_A,              // [  (left bracket)  — Alt+91
    RBRC_A,              // ]  (right bracket) — Alt+93
    LCBR_A,              // {  (left brace)    — Alt+123
    RCBR_A,              // }  (right brace)   — Alt+125
    LABK_A,              // <  (less-than)     — Alt+60
    RABK_A,              // >  (greater-than)  — Alt+62
};

/* --------------------------------------------------------------------------
 * send_alt_code — helper that performs a Windows Alt-code input sequence.
 *
 * Holds Left Alt, taps each numpad digit in `digits[]`, then releases Alt.
 * @param digits  Array of numpad keycodes (KC_P0 … KC_P9).
 * @param len     Number of digits in the array.
 * -------------------------------------------------------------------------- */
void send_alt_code(uint16_t *digits, uint8_t len) {
    register_code(KC_LALT);
    for (uint8_t i = 0; i < len; i++) {
        tap_code(digits[i]);
    }
    unregister_code(KC_LALT);
}

/* --------------------------------------------------------------------------
 * process_record_user — per-keypress callback.
 *
 * Intercepts custom keycodes on key-down events and emits the matching
 * Alt-code sequence.  All other keycodes pass through to default handling.
 * -------------------------------------------------------------------------- */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* Only act on key press, ignore release */
    if (!record->event.pressed) return true;

    switch (keycode) {

        /* --- Basic punctuation ------------------------------------------ */

        case DOT_A: {                           // .  Alt+46
            uint16_t d[] = {KC_P4, KC_P6};
            send_alt_code(d, 2);
            return false;
        }

        case COMM_A: {                          // ,  Alt+44
            uint16_t d[] = {KC_P4, KC_P4};
            send_alt_code(d, 2);
            return false;
        }

        case EXC_A: {                           // !  Alt+33
            uint16_t d[] = {KC_P3, KC_P3};
            send_alt_code(d, 2);
            return false;
        }

        case QUES_A: {                          // ?  Alt+63
            uint16_t d[] = {KC_P6, KC_P3};
            send_alt_code(d, 2);
            return false;
        }

        case COL_A: {                           // :  Alt+58
            uint16_t d[] = {KC_P5, KC_P8};
            send_alt_code(d, 2);
            return false;
        }

        case SEM_A: {                           // ;  Alt+59
            uint16_t d[] = {KC_P5, KC_P9};
            send_alt_code(d, 2);
            return false;
        }

        case APO_A: {                           // '  Alt+39
            uint16_t d[] = {KC_P3, KC_P9};
            send_alt_code(d, 2);
            return false;
        }

        case HYP_A: {                           // -  Alt+45
            uint16_t d[] = {KC_P4, KC_P5};
            send_alt_code(d, 2);
            return false;
        }

        /* --- Quotation marks -------------------------------------------- */

        case QUO_A: {                           // "  Alt+34
            uint16_t d[] = {KC_P3, KC_P4};
            send_alt_code(d, 2);
            return false;
        }

        case SQUO_A: {                          // '  Alt+39 (single quote / apostrophe)
            uint16_t d[] = {KC_P3, KC_P9};
            send_alt_code(d, 2);
            return false;
        }

        /* --- Parentheses ------------------------------------------------ */

        case LPRN_A: {                          // (  Alt+40
            uint16_t d[] = {KC_P4, KC_P0};
            send_alt_code(d, 2);
            return false;
        }

        case RPRN_A: {                          // )  Alt+41
            uint16_t d[] = {KC_P4, KC_P1};
            send_alt_code(d, 2);
            return false;
        }

        /* --- Square brackets -------------------------------------------- */

        case LBRC_A: {                          // [  Alt+91
            uint16_t d[] = {KC_P9, KC_P1};
            send_alt_code(d, 2);
            return false;
        }

        case RBRC_A: {                          // ]  Alt+93
            uint16_t d[] = {KC_P9, KC_P3};
            send_alt_code(d, 2);
            return false;
        }

        /* --- Curly braces ----------------------------------------------- */

        case LCBR_A: {                          // {  Alt+123
            uint16_t d[] = {KC_P1, KC_P2, KC_P3};
            send_alt_code(d, 3);
            return false;
        }

        case RCBR_A: {                          // }  Alt+125
            uint16_t d[] = {KC_P1, KC_P2, KC_P5};
            send_alt_code(d, 3);
            return false;
        }

        /* --- Angle brackets --------------------------------------------- */

        case LABK_A: {                          // <  Alt+60
            uint16_t d[] = {KC_P6, KC_P0};
            send_alt_code(d, 2);
            return false;
        }

        case RABK_A: {                          // >  Alt+62
            uint16_t d[] = {KC_P6, KC_P2};
            send_alt_code(d, 2);
            return false;
        }
    }

    return true;  // Let QMK handle every other keycode normally
}

/* ==========================================================================
 * Combo (chord) configuration
 * ========================================================================== */

uint16_t COMBO_LEN = COMBO_LENGTH;

/*
 * Each array lists the keys that must be pressed simultaneously to fire
 * the combo.  Every array MUST end with COMBO_END.
 */
const uint16_t PROGMEM tg_super_layer_combo[]     = {KC_LSFT, KC_DEL, COMBO_END};                              // LShift + Del
const uint16_t PROGMEM mo_super_layer_combo[]     = {KC_SPC, KC_LALT, COMBO_END};                              // Space + LAlt
const uint16_t PROGMEM mo_super_layer_combo_alt[] = {KC_BSPC, KC_TAB, COMBO_END};                              // Backspace + Tab
const uint16_t PROGMEM tg_punct_layer_combo[]     = {KC_SPC, KC_BSPC, COMBO_END};                              // Space + Backspace
const uint16_t PROGMEM mo_punct_layer_combo[]     = {KC_LCTL, KC_LGUI, COMBO_END};                             // LCtrl + LWin
const uint16_t PROGMEM mo_media_layer_combo[]     = {KC_ENT, KC_STAB, COMBO_END};                              // Enter + Shift+Tab
const uint16_t PROGMEM tg_game_layer_combo[]      = {KC_LSFT, KC_SPC, KC_BSPC, KC_DEL, COMBO_END};            // 4-key chord → game mode
const uint16_t PROGMEM to_base_layer_combo[]      = {KC_LSFT, KC_SPC, KC_LCTL, KC_ENT, KC_BSPC, KC_DEL, COMBO_END}; // 6-key emergency reset
const uint16_t PROGMEM caps_combo[]               = {KC_LCTL, KC_ENT, COMBO_END};                              // LCtrl + Enter

/* Map each combo identifier to its trigger keys and resulting action */
combo_t key_combos[] = {
    [COMBO_SUPER_LR]         = COMBO(tg_super_layer_combo,     SLTG),    // Toggle _SUPER layer
    [COMBO_SUPER_LR_MOD]     = COMBO(mo_super_layer_combo,     SLMO),    // Hold for _SUPER (primary)
    [COMBO_SUPER_LR_MOD_ALT] = COMBO(mo_super_layer_combo_alt, SLMO),    // Hold for _SUPER (alt chord)
    [COMBO_PUNCT_LR]         = COMBO(tg_punct_layer_combo,     PLTG),    // Toggle _PUNCT layer
    [COMBO_PUNCT_LR_MOD]     = COMBO(mo_punct_layer_combo,     PLMO),    // Hold for _PUNCT
    [COMBO_GAME_LR]          = COMBO(tg_game_layer_combo,      GLTG),    // Toggle _GAME layer
    [COMBO_CLEAN_LR]         = COMBO(to_base_layer_combo,      BTO),     // Emergency return to _BASE
    [COMBO_MEDIA_LR_MOD]     = COMBO(mo_media_layer_combo,     MLMO),    // Hold for _MEDIA
    [COMBO_CAPS]             = COMBO(caps_combo,               KC_CAPS), // Caps Lock
};

/* ==========================================================================
 * Keymaps
 * ========================================================================== */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* ------------------------------------------------------------------
     * Layer 0: _BASE — Standard QWERTY with number row
     * ------------------------------------------------------------------
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  [  │
     * │ Esc │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  ]  │
     * │  =  │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │
     * │  -  │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │  \  │
     * │     │     │     │     │LAlt │LGui │S+Tab│ Tab │     │     │     │     │
     * │     │     │LSft │Space│LCtrl│Enter│BSpc │ Del │     │     │     │     │
     * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_BASE] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_LBRC,
        KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_RBRC,
        KC_EQL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_MINS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_NUBS,
                                            KC_LALT, KC_LGUI, KC_STAB, KC_TAB ,
                                   KC_LSFT, KC_SPC , KC_LCTL, KC_ENT , KC_BSPC, KC_DEL
    ),

    /* ------------------------------------------------------------------
     * Layer 1: _SUPER — Navigation, F-keys and system controls
     *
     *  • Top row   : Sleep, F1–F11
     *  • 2nd row   : Power, PrtSc, ScrLk, Pause, Insert, F12
     *  • Home row  : Browser Back, Home/End, PgUp/PgDn, Arrow keys,
     *                Browser Home
     *  • Bottom row: Modifier mirrors for one-handed combos
     *  • Thumb keys: transparent (inherit from _BASE)
     * ------------------------------------------------------------------ */
    [_SUPER] = LAYOUT(
        KC_SLEP, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
        KC_PWR , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_PSCR, KC_SCRL, KC_PAUS, KC_INS , KC_NO  , KC_F12 ,
        KC_WBAK, KC_NO  , KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_NO  , KC_WHOM,
        KC_NO  , KC_NO  , KC_LALT, KC_LCTL, KC_LSFT, KC_LGUI, KC_TAB , KC_LSFT, KC_LCTL, KC_LALT, KC_NO  , KC_NO  ,
                                            _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______
    ),

    /* ------------------------------------------------------------------
     * Layer 2: _PUNCT — Punctuation and brackets (via Alt-codes)
     *
     * All characters are emitted through Windows Alt-code sequences so
     * they produce the correct symbol regardless of the OS input language.
     *
     *  • 2nd row : [ ]  { }
     *  • Home row: ! ?  ' "  , .  ; :
     *  • Bot row : ( )  < >
     *
     * KC_NO = key disabled on this layer.
     * ------------------------------------------------------------------ */
    [_PUNCT] = LAYOUT(
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , LBRC_A , RBRC_A , LCBR_A , RCBR_A , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , EXC_A  , QUES_A , SQUO_A , QUO_A  , COMM_A , DOT_A  , SEM_A  , COL_A  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , LPRN_A , RPRN_A , LABK_A , RABK_A , KC_NO  , KC_NO  ,
                                            _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______
    ),

    /* ------------------------------------------------------------------
     * Layer 3: _MEDIA — Multimedia playback and volume
     *
     *  • Mute, Stop, Play/Pause
     *  • Previous / Next track
     *  • Volume Down / Volume Up
     * ------------------------------------------------------------------ */
    [_MEDIA] = LAYOUT(
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_MUTE, KC_NO  , KC_NO  , KC_MSTP, KC_MPLY, KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_MPRV, KC_MNXT, KC_NO  , KC_NO  , KC_VOLD, KC_VOLU, KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______
    ),

    /* ------------------------------------------------------------------
     * Layer 4: _GAME — Gaming layout
     *
     * Based on _BASE with adjustments for comfortable gaming:
     *  • Esc moved to top-left (was Grave on _BASE)
     *  • Tab moved to the second row far-left
     *  • CapsLock replaces = on the home-row far-left
     *  • LAlt replaces - on the bottom-row far-left (easier crouch/walk)
     *  • Thumb cluster remains transparent (inherited from _BASE)
     * ------------------------------------------------------------------ */
    [_GAME] = LAYOUT(
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_LBRC,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_RBRC,
        KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LALT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_NUBS,
                                            _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______
    ),
};

/* ==========================================================================
 * RGB underglow — per-layer colour indication
 * ========================================================================== */

/**
 * keyboard_post_init_user — runs once after the keyboard finishes its
 * hardware initialisation.
 *
 * Enables RGB lighting without writing to EEPROM (avoids unnecessary
 * wear) and sets the default colour to a very dim white.
 */
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();  // Turn on LEDs; skip EEPROM write
    rgblight_setrgb(2, 2, 2);   // Dim white — subtle "keyboard is on" indicator
}

/**
 * layer_state_set_user — called by QMK every time the active layer changes.
 *
 * Sets the RGB underglow colour to visually indicate which layer is
 * currently active:
 *   _SUPER : Red         (255, 25, 25)
 *   _GAME  : Green       ( 25,255, 25)
 *   _PUNCT : Magenta     (255, 25,255)
 *   _MEDIA : Cyan        ( 25,255,255)
 *   _BASE  : Dim white   (  2,  2,  2)
 */
layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {

        case _SUPER:
            rgblight_setrgb(255, 25, 25);   // Red
            break;

        case _GAME:
            rgblight_setrgb(25, 255, 25);   // Green
            break;

        case _PUNCT:
            rgblight_setrgb(255, 25, 255);  // Magenta
            break;

        case _MEDIA:
            rgblight_setrgb(25, 255, 255);  // Cyan
            break;

        default: /* _BASE or any unexpected state */
            rgblight_setrgb(2, 2, 2);       // Dim white
            break;
    }

    return state;  // Must return the state for QMK's internal layer processing
}