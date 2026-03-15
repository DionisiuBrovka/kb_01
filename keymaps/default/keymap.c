#include QMK_KEYBOARD_H

// TODO
// - GAMEBAR KEY
// - START RECORD GB KEY
// - STOP RECORD GB KEY
// - PUNCTUATIONS
// - MEDIA KEYS

// ---------------------------------------------------------------------------------------------------------

#define SLTG TG(_SUPER)
#define SLMO MO(_SUPER)
#define PLMO MO(_PUNCT)
#define GLTG TG(_GAME)
#define BTO TO(_BASE)

// ---------------------------------------------------------------------------------------------------------

enum layers {
    _BASE = 0,
    _SUPER,
    _PUNCT,
    _GAME,
};

enum custom_keycodes {
    KC_STAB = LSFT(KC_TAB),
    KC_ECUT  = LCTL(KC_X),
    KC_ECPY = LCTL(KC_C),
    KC_EPST  = LCTL(KC_V),
    KC_CLN = LSFT(KC_SCLN),
    KC_UOT = LSFT(KC_QUOT),
    KC_LBRS = LSFT(KC_LBRC),
    KC_RBRS = LSFT(KC_RBRC)
};

enum combos {
    COMBO_SUPER_LR,
    COMBO_SUPER_LR_MOD,
    COMBO_PUNCT_LR_MOD,
    COMBO_GAME_LR,
    COMBO_CLEAN_LR,
    COMBO_LENGTH
};

// ---------------------------------------------------------------------------------------------------------

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM tg_super_layer_combo[] = {KC_LSFT, KC_DEL, COMBO_END};
const uint16_t PROGMEM mo_super_layer_combo[] = {KC_SPC, KC_LALT, COMBO_END};
const uint16_t PROGMEM mo_punct_layer_combo[] =  {KC_LCTL, KC_LGUI, COMBO_END};
const uint16_t PROGMEM tg_game_layer_combo[] =  {KC_LSFT, KC_SPC, KC_BSPC, KC_DEL, COMBO_END};
const uint16_t PROGMEM to_base_layer_combo[] =  {KC_LSFT, KC_SPC, KC_LCTL, KC_ENT, KC_BSPC, KC_DEL, COMBO_END};

combo_t key_combos[] = {
    [COMBO_SUPER_LR] = COMBO(tg_super_layer_combo, SLTG),
    [COMBO_SUPER_LR_MOD] = COMBO(mo_super_layer_combo, SLMO), 
    [COMBO_GAME_LR] = COMBO(tg_game_layer_combo, GLTG),
    [COMBO_PUNCT_LR_MOD] = COMBO(mo_punct_layer_combo, PLMO),
    [COMBO_CLEAN_LR] = COMBO(to_base_layer_combo, BTO),
};

// ---------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    [_BASE] = LAYOUT(
        KC_GRV  ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_LBRC,
        KC_ESC  ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_RBRC,
        KC_EQL  ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
        KC_MINS ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_NUBS,
                                         KC_LALT,KC_LGUI,KC_STAB,KC_TAB,
                                 KC_LSFT,KC_SPC ,KC_LCTL,KC_ENT ,KC_BSPC,KC_DEL
    ),    

    [_SUPER] = LAYOUT(
         KC_SLEP,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_MSTP,KC_MPLY,KC_NO  ,KC_PSCR,KC_SCRL,KC_PAUS,KC_INS ,KC_WHOM,KC_F12 , 
         KC_NO  ,KC_NO  ,KC_MPRV,KC_VOLD,KC_VOLU,KC_MNXT,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,KC_WBAK,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_SPC ,KC_LCTL,KC_LALT,KC_MUTE,KC_HOME,KC_PGDN,KC_PGUP,KC_END ,KC_WFWD,KC_NO  ,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),

    [_PUNCT] = LAYOUT(
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_LBRC,KC_RBRC,KC_LBRS,KC_RBRS,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_COMM,KC_DOT ,KC_SCLN,KC_CLN ,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_QUOT,KC_UOT ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),

    [_GAME] = LAYOUT(
         KC_ESC ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_CAPS,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),
};

// ---------------------------------------------------------------------------------------------------------

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); 
    rgblight_setrgb(2, 2, 2);   
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        
        case _SUPER:
            rgblight_setrgb(255, 25, 25); 
            break;

        
        case _GAME:
            rgblight_setrgb(25, 255, 25); 
            break;

        case _PUNCT:
            rgblight_setrgb(255, 25, 255); 
            break;

            
        default:
            rgblight_setrgb(2, 2, 2); 
            break;
    }
    
    return state;
}

