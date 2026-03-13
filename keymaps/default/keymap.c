#include QMK_KEYBOARD_H

// ---------------------------------------------------------------------------------------------------------

enum layers {
    _BASE = 0,
    _SUPER,
};

enum custom_keycodes {
    KC_STAB = LSFT(KC_TAB),
};

enum combos {
    COMBO_SUPER_LR,
    COMBO_LENGTH
};

// ---------------------------------------------------------------------------------------------------------

#define SLTG TG(_SUPER)

// ---------------------------------------------------------------------------------------------------------

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM tg_super_layer_combo[] = {KC_LSFT, KC_DEL, COMBO_END};

combo_t key_combos[] = {
    [COMBO_SUPER_LR] = COMBO(tg_super_layer_combo, SLTG),
};

// ---------------------------------------------------------------------------------------------------------


void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); 
    rgblight_setrgb(0, 0, 0);  
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        
        case _SUPER:
            rgblight_setrgb(255, 25, 0); 
            break;

            
        default:
            rgblight_setrgb(0, 0, 0); 
            break;
    }
    
    return state;
}

// ---------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    [_BASE] = LAYOUT(
        KC_GRV  ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_LBRC,
        KC_ESC  ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_RBRC,
        KC_EQL  ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
        KC_MINS ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_NUBS,
                                         KC_LGUI,KC_LALT,KC_TAB ,KC_STAB,
                                 KC_LSFT,KC_SPC ,KC_LCTL,KC_ENT ,KC_BSPC,KC_DEL
    ),    

    [_SUPER] = LAYOUT(
         KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),
};