#include QMK_KEYBOARD_H

// =========================================================================================================
// БЛОК 1: ПОЛЬЗОВАТЕЛЬСКИЕ МАКРОСЫ И КАСТОМНЫЕ КЛАВИШИ
// =========================================================================================================

// Макросы для управления слоями:
// TG (Toggle) - переключает слой навсегда (как Caps Lock). Нажал - включилось, нажал еще раз - выключилось.
// MO (Momentary) - включает слой ТОЛЬКО пока клавиша удерживается (как Shift).
#define SLTG TG(_SUPER) // Переключить слой _SUPER
#define SLMO MO(_SUPER) // Удерживать для слоя _SUPER
#define PLTG TG(_PUNCT) // Переключить слой _PUNCT
#define PLMO MO(_PUNCT) // Удерживать для слоя _PUNCT
#define MLTG TG(_MEDIA) // Переключить слой _MEDIA
#define MLMO MO(_MEDIA) // Удерживать для слоя _MEDIA
#define GLTG TG(_GAME)  // Переключить слой _GAME
#define BTO  TO(_BASE)   // TO полностью отключает все другие слои и переводит на _BASE

// Макросы для "Shift + клавиша" (позволяет выводить символы верхнего регистра нажатием одной кнопки):
#define KC_STAB LSFT(KC_TAB)  // Shift + Tab
#define KC_CLN  LSFT(KC_SCLN) // Двоеточие ( : )
#define KC_UOT  LSFT(KC_QUOT) // Двойная кавычка ( " )
#define KC_LBRS LSFT(KC_LBRC) // Левая фигурная скобка ( { )
#define KC_RBRS LSFT(KC_RBRC) // Правая фигурная скобка ( } )
#define KC_LARW LSFT(KC_COMM) // Угловая скобка влево ( < )
#define KC_RARW LSFT(KC_DOT)  // Угловая скобка вправо ( > )
#define KC_LAR  LSFT(KC_9)    // Левая круглая скобка ( ( )
#define KC_RAR  LSFT(KC_0)    // Правая круглая скобка ( ) )

// =========================================================================================================
// БЛОК 2: ПЕРЕЧИСЛЕНИЯ (ENUMS) - НАЗВАНИЯ СЛОЕВ И КОМБО
// =========================================================================================================

// Индексы слоев. Порядок важен: чем ниже в списке, тем выше приоритет слоя.
enum layers {
    _BASE = 0, // Базовый слой (QWERTY)
    _SUPER,    // Слой с F-клавишами, навигацией и системными кнопками
    _PUNCT,    // Слой со знаками препинания (скобки, кавычки)
    _MEDIA,    // Слой для управления музыкой и громкостью
    _GAME,     // Игровой слой (смещенный нижний ряд, отключение лишнего)
};

// Идентификаторы для комбо-нажатий (аккордов)
enum combos {
    COMBO_SUPER_LR,
    COMBO_SUPER_LR_MOD,
    COMBO_SUPER_LR_MOD_ALT,
    COMBO_PUNCT_LR,
    COMBO_PUNCT_LR_MOD,
    COMBO_MEDIA_LR_MOD,
    COMBO_GAME_LR,
    COMBO_CLEAN_LR,
    COMBO_CAPS,
    COMBO_LENGTH // Обязательный элемент в конце для подсчета количества комбо
};

// =========================================================================================================
// БЛОК 3: НАСТРОЙКА КОМБО-НАЖАТИЙ (ОДНОВРЕМЕННОЕ НАЖАТИЕ НЕСКОЛЬКИХ КЛАВИШ)
// =========================================================================================================

uint16_t COMBO_LEN = COMBO_LENGTH;

// Массивы клавиш, которые нужно нажать одновременно. Обязательно заканчиваются на COMBO_END.
const uint16_t PROGMEM tg_super_layer_combo[]     = {KC_LSFT, KC_DEL, COMBO_END}; // LShift + Del
const uint16_t PROGMEM mo_super_layer_combo[]     = {KC_SPC, KC_LALT, COMBO_END}; // Пробел + LAlt
const uint16_t PROGMEM mo_super_layer_combo_alt[] = {KC_BSPC, KC_TAB, COMBO_END}; // Backspace + Tab
const uint16_t PROGMEM tg_punct_layer_combo[]     = {KC_SPC, KC_BSPC, COMBO_END}; // Пробел + Backspace
const uint16_t PROGMEM mo_punct_layer_combo[]     = {KC_LCTL, KC_LGUI, COMBO_END}; // LCtrl + LWin
const uint16_t PROGMEM mo_media_layer_combo[]     = {KC_ENT, KC_STAB, COMBO_END};  // Enter + Shift+Tab
const uint16_t PROGMEM tg_game_layer_combo[]      = {KC_LSFT, KC_SPC, KC_BSPC, KC_DEL, COMBO_END}; // Активация игрового мода
const uint16_t PROGMEM to_base_layer_combo[]      = {KC_LSFT, KC_SPC, KC_LCTL, KC_ENT, KC_BSPC, KC_DEL, COMBO_END}; // Полный сброс на _BASE
const uint16_t PROGMEM caps_combo[]               = {KC_LCTL, KC_ENT, COMBO_END}; // LCtrl + Enter

// Привязка комбинаций клавиш к конкретным действиям/макросам
combo_t key_combos[] = {
    [COMBO_SUPER_LR]         = COMBO(tg_super_layer_combo, SLTG),       // Включить/выключить слой SUPER
    [COMBO_SUPER_LR_MOD]     = COMBO(mo_super_layer_combo, SLMO),       // Удерживать слой SUPER
    [COMBO_SUPER_LR_MOD_ALT] = COMBO(mo_super_layer_combo_alt, SLMO),   // Удерживать слой SUPER (альтернатива)
    [COMBO_PUNCT_LR]         = COMBO(tg_punct_layer_combo, PLTG),       // Включить/выключить слой PUNCT
    [COMBO_PUNCT_LR_MOD]     = COMBO(mo_punct_layer_combo, PLMO),       // Удерживать слой PUNCT
    [COMBO_GAME_LR]          = COMBO(tg_game_layer_combo, GLTG),        // Включить/выключить ИГРОВОЙ слой
    [COMBO_CLEAN_LR]         = COMBO(to_base_layer_combo, BTO),         // Экстренный возврат на БАЗОВЫЙ слой
    [COMBO_MEDIA_LR_MOD]     = COMBO(mo_media_layer_combo, MLMO),       // Удерживать слой MEDIA
    [COMBO_CAPS]             = COMBO(caps_combo, KC_CAPS),              // Включить Caps Lock
};       

// =========================================================================================================
// БЛОК 4: РАСКЛАДКИ (KEYMAPS)
// =========================================================================================================
// Заметка: _______ (или KC_TRNS) означает "прозрачную" клавишу. 
// При её нажатии будет срабатывать та клавиша, которая находится на этом же месте на слое ниже.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* СЛОЙ 0: _BASE (Основной QWERTY + цифры)
     * ,-----------------------------------------------------------------------------------.
     * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  [  |
     * | Esc |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  ]  |
     * |  =  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |
     * |  -  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  \  |
     * |                 | LAlt| LWin|S+Tab| Tab |
     * |      LShift     |Space|LCtrl|Enter|BSpc | Del |
     * `-----------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT(
        KC_GRV  ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_LBRC,
        KC_ESC  ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_RBRC,
        KC_EQL  ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
        KC_MINS ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_NUBS,
                                         KC_LALT,KC_LGUI,KC_STAB,KC_TAB,
                                 KC_LSFT,KC_SPC ,KC_LCTL,KC_ENT ,KC_BSPC,KC_DEL
    ),    

    /* СЛОЙ 1: _SUPER (Навигация, F-клавиши, управление ПК)
     * Включает стрелочки, Home/End, системные (Sleep, Power) и функциональный ряд F1-F12.
     */
    [_SUPER] = LAYOUT(
         KC_SLEP,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,
         KC_PWR ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_PSCR,KC_SCRL,KC_PAUS,KC_INS ,KC_NO  ,KC_F12 , 
         KC_WBAK,KC_NO  ,KC_HOME,KC_PGDN,KC_PGUP,KC_END ,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,KC_NO  ,KC_WHOM,
         KC_NO  ,KC_NO  ,KC_LALT,KC_LCTL,KC_LSFT,KC_LGUI,KC_TAB ,KC_LSFT,KC_LCTL,KC_LALT,KC_NO  ,KC_NO  ,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),

    /* СЛОЙ 2: _PUNCT (Знаки препинания)
     * Выделенный слой для скобок (), {}, [], кавычек и двоеточий. Очень удобно для программирования.
     * KC_NO означает, что кнопка на этом слое полностью отключена.
     */
    [_PUNCT] = LAYOUT(
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_LBRC,KC_RBRC,KC_LBRS,KC_RBRS,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_COMM,KC_DOT ,KC_SCLN,KC_CLN ,KC_LAR ,KC_RAR ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_QUOT,KC_UOT ,KC_LARW,KC_RARW,KC_NO  ,KC_NO  ,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),

    /* СЛОЙ 3: _MEDIA (Управление мультимедиа)
     * Громкость (VOLD/VOLU), Пауза/Плей (MPLY), Треки (MPRV/MNXT), Мут (MUTE).
     */
    [_MEDIA] = LAYOUT(
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_MUTE,KC_NO  ,KC_NO  ,KC_MSTP,KC_MPLY,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_MPRV,KC_MNXT,KC_NO  ,KC_NO  ,KC_VOLD,KC_VOLU,KC_NO  ,KC_NO  ,KC_NO  ,
         KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),

    /* СЛОЙ 4: _GAME (Игровой слой)
     * Похож на _BASE, но некоторые клавиши-модификаторы изменены. 
     * Например, на месте нижнего Shift теперь LAlt, а на месте '=' стоит CapsLock.
     */
    [_GAME] = LAYOUT(
         KC_ESC ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_LBRC,
         KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_RBRC,
         KC_CAPS,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
         KC_LALT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_NUBS,
                                         _______,_______,_______,_______,
                                 _______,_______,_______,_______,_______,_______
    ),
};

// =========================================================================================================
// БЛОК 5: ЛОГИКА ПОДСВЕТКИ (RGB) ПРИ ПЕРЕКЛЮЧЕНИИ СЛОЕВ
// =========================================================================================================

// Функция выполняется один раз при запуске клавиатуры
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Включаем RGB, не сохраняя состояние в память (чтобы не убивать EEPROM)
    rgblight_setrgb(2, 2, 2);   // Базовый цвет по умолчанию - очень тусклый белый/серый (R:2, G:2, B:2)
}

// Функция выполняется каждый раз при смене слоя
layer_state_t layer_state_set_user(layer_state_t state) {
    
    // Смотрим, какой слой сейчас является самым "верхним" (активным)
    switch (get_highest_layer(state)) {
        
        case _SUPER:
            rgblight_setrgb(255, 25, 25); // Красная подсветка для слоя SUPER
            break;

        case _GAME:
            rgblight_setrgb(25, 255, 25); // Зеленая подсветка для ИГРОВОГО слоя
            break;

        case _PUNCT:
            rgblight_setrgb(255, 25, 255); // Пурпурная (Розовая) подсветка для слоя с ПУНКТУАЦИЕЙ
            break;

        case _MEDIA:
            rgblight_setrgb(25, 255, 255); // Голубая (Cyan) подсветка для слоя MEDIA
            break;
     
        default:
            // Слой по умолчанию (_BASE)
            rgblight_setrgb(2, 2, 2); // Тусклый серый/белый
            break;
    }
    
    return state; // Обязательный возврат состояния слоя для внутренних процессов QMK
}