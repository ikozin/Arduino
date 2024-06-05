#include <Arduino.h>
#include <GyverIO.h>
#include <PS2KeyAdvanced.h>
#include "KeyDef.h"


PS2KeyAdvanced keyboard;

#ifndef ARDUINO_AVR_ATmega328P_BB8
#error ATmega328P BB 8Mhz.json
#endif


//////////////////////////////////////////////////////
//
//   Q   W   E   R   T   Y   U   I   O   P   [   ]
//   Й   Ц   У   К   Е   Н   Г   Ш   Щ   З   Х   Ъ
//
//     A   S   D   F   G   H   J   K   L   ;   '
//     Ф   Ы   В   А   П   Р   О   Л   Д   Ж   Э
//
//       Z   X   C   V   B   N   M   ,   .
//       Я   Ч   С   М   И   Т   Ь   Б   Ю
//
//////////////////////////////////////////////////////

//#define DEBUG_CONSOLE

void (* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0
uint16_t processKeyCode(uint16_t code);

#ifdef DEBUG_CONSOLE
char text[128];
#define DEBUG_PRINT_HEX(k) { sprintf(text, "0x%04X ", k); Serial.print(text); Serial.flush(); }
#else
#define DEBUG_PRINT_HEX(k)
#endif

#define NO_KEY  ((uint8_t)0xFF)

typedef union _matrix_ {
    struct {
        uint8_t row : 4;
        uint8_t col : 3;
        uint8_t shift : 1;
    };
    uint8_t value;
} matrix_t;

typedef struct _key_ {
    uint8_t scancode;
    matrix_t matrix;
} key_t;

const key_t keymapOrion128_Main[] PROGMEM = {
{  0x11, KEY_Home },                // HOME
{  0x15, KEY_Left },                // LEFT
{  0x16, KEY_Right },               // RIGHT
{  0x17, KEY_Up },                  // UP
{  0x18, KEY_Down },                // DOWN
{  0x1A, KEY_Back },                // DEL
{  0x1B, KEY_AP2 },                 // ESC
{  0x1C, KEY_Back },                // BACKSPACE
{  0x1D, KEY_Tab },                 // TAB
{  0x1E, KEY_ENTER },               // ENTER
{  0x1F, KEY_Space },               // SPACE
{  0x20, KEY_0 },                   // KP0
{  0x21, KEY_1 },                   // KP1
{  0x22, KEY_2 },                   // KP2
{  0x23, KEY_3 },                   // KP3
{  0x24, KEY_4 },                   // KP4
{  0x25, KEY_5 },                   // KP5
{  0x26, KEY_6 },                   // KP6
{  0x27, KEY_7 },                   // KP7
{  0x28, KEY_8 },                   // KP8
{  0x29, KEY_9 },                   // KP9
{  0x2A, KEY_Dot },                 // KP_DOT
{  0x2B, KEY_ENTER },               // KP_ENTER
{  0x2C, KEY_Plus },                // KP_PLUS
{  0x2D, KEY_Minus },               // KP_MINUS
{  0x2E, KEY_Aster },               // KP_TIMES
{  0x2F, KEY_Slash },               // KP_DIV
{  0x30, KEY_0 },                   // 0 )
{  0x31, KEY_1 },                   // 1 !
{  0x32, KEY_2 },                   // 2 @
{  0x33, KEY_3 },                   // 3 #
{  0x34, KEY_4 },                   // 4 $
{  0x35, KEY_5 },                   // 5 %
{  0x36, KEY_6 },                   // 6 ^
{  0x37, KEY_7 },                   // 7 &
{  0x38, KEY_8 },                   // 8 *
{  0x39, KEY_9 },                   // 9 (
{  0x3A, KEY_Quote },               // ' "
{  0x3B, KEY_Comma },               // , <
{  0x3C, KEY_Minus },               // - _
{  0x3D, KEY_Dot },                 // . >
{  0x3E, KEY_Slash },               // / ?
{  0x41, KEY_A },                   // A
{  0x42, KEY_B },                   // B
{  0x43, KEY_C },                   // C
{  0x44, KEY_D },                   // D
{  0x45, KEY_E },                   // E
{  0x46, KEY_F },                   // F
{  0x47, KEY_G },                   // G
{  0x48, KEY_H },                   // H
{  0x49, KEY_I },                   // I
{  0x4A, KEY_J },                   // J
{  0x4B, KEY_K },                   // K
{  0x4C, KEY_L },                   // L
{  0x4D, KEY_M },                   // M
{  0x4E, KEY_N },                   // N
{  0x4F, KEY_O },                   // O 
{  0x50, KEY_P },                   // P
{  0x51, KEY_Q },                   // Q
{  0x52, KEY_R },                   // R
{  0x53, KEY_S },                   // S
{  0x54, KEY_T },                   // T
{  0x55, KEY_U },                   // U
{  0x56, KEY_V },                   // V
{  0x57, KEY_W },                   // W
{  0x58, KEY_X },                   // X
{  0x59, KEY_Y },                   // Y
{  0x5A, KEY_Z },                   // Z
{  0x5B, KEY_SeCol },               // ; :
{  0x5C, KEY_Slash },               // "\\"
{  0x5D, KEY_SqBrL },               // [ {
{  0x5E, KEY_SqBrR },               // ] }
{  0x5F, KEY_Equal },               // = +
{  0x61, KEY_F1 },                  // F1
{  0x62, KEY_F2 },                  // F2
{  0x63, KEY_F3 },                  // F3
{  0x64, KEY_F4 },                  // F4
{  0x65, KEY_F5 },                  // F5
};

const key_t keymapOrion128_Shift[] PROGMEM = {
{  0x30, KEY_OpenL },               // 0 )
{  0x31, KEY_Excla },               // 1 !
{  0x32, KEY_At },                  // 2 @
{  0x33, KEY_Octot },               // 3 #
{  0x34, KEY_Dolla },               // 4 $
{  0x35, KEY_Perce },               // 5 %
{  0x36, KEY_Circ },                // 6 ^
{  0x37, KEY_Amper },               // 7 &
{  0x38, KEY_Aster},                // 8 *
{  0x39, KEY_ClosR },               // 9 (
{  0x3A, KEY_Quote },               // ' "
{  0x3B, KEY_Less },                // , <
{  0x3C, KEY_UnLin },               // - _
{  0x3D, KEY_Great },               // . >
{  0x3E, KEY_Quest },               // / ?
{  0x5B, KEY_Colon },               // ; :
{  0x5C, KEY_BaSl },                // "\\"
{  0x5F, KEY_Plus },                // = +
};

const key_t keymapOrion128_RU[] PROGMEM = {
{  0x32, KEY_2 },                   // 2 @
{  0x36, KEY_6 },                   // 6 ^
{  0x41, KEY_A },                   // A - Ф
{  0x42, KEY_B },                   // B - И
{  0x43, KEY_C },                   // C - С
{  0x44, KEY_D },                   // D - В
{  0x45, KEY_E },                   // E - У
{  0x46, KEY_F },                   // F - А
{  0x47, KEY_G },                   // G - П
{  0x48, KEY_H },                   // H - Р
{  0x49, KEY_I },                   // I - Ш
{  0x4A, KEY_J },                   // J - О
{  0x4B, KEY_K },                   // K - Л
{  0x4C, KEY_L },                   // L - Д
{  0x4D, KEY_M },                   // M - Ь
{  0x4E, KEY_N },                   // N - Т
{  0x4F, KEY_O },                   // O - Щ
{  0x50, KEY_P },                   // P - З
{  0x51, KEY_Q },                   // Q - Й
{  0x52, KEY_R },                   // R - К
{  0x53, KEY_S },                   // S - Ы
{  0x54, KEY_T },                   // T - Е
{  0x55, KEY_U },                   // U - Г
{  0x56, KEY_V },                   // V - М
{  0x57, KEY_W },                   // W - Ц
{  0x58, KEY_X },                   // X - Ч
{  0x59, KEY_Y },                   // Y - Н
{  0x5A, KEY_Z },                   // Z - Я
{  0x5C, KEY_Slash },               // "\\"
{  0x5D, KEY_SqBrL },               // [ {
{  0x5E, KEY_SqBrR },               // ] }
};

uint8_t table_main[128];
uint8_t table_shift[128];
uint8_t table_ru[128];



// ОРИОН-128
#define SHIFT_ORION     (A0)   // PC0
#define CRTL_ORION      (A1)   // PC1
#define LANG_ORION      (A2)   // PC2
#define RESET_ORION     (A3)   // PC3

// MT8816
#define RESET_MT8816    (4)   // PD4
#define DATA_MT8816     (5)   // PD5
#define STROBE_MT8816   (6)   // PD6
#define CS_MT8816       (7)   // PD7

// #define AX0_MT8816      (PB0)   // PB0
// #define AX1_MT8816      (PB1)   // PB1
// #define AX2_MT8816      (PB2)   // PB2
// #define AX3_MT8816      (PB3)   // PB3
// #define AY0_MT8816      (PB4)   // PB4
// #define AY1_MT8816      (PB5)   // PB5
// #define AY2_MT8816      (PB6)   // PB6

void Reset_MT8826() {
    gio::high(CS_MT8816);           //выбор чипа
    gio::high(RESET_MT8816);
    gio::low(RESET_MT8816);         //сброс
    gio::low(CS_MT8816);
}

void SetKey_MT8826(boolean data){
    gio::high(CS_MT8816);           //выбор чипа
    gio::high(STROBE_MT8816);       //строб on
    gio::write(DATA_MT8816, data);  //данные
    gio::low(STROBE_MT8816);        //строб off    
    gio::low(CS_MT8816);   
}

void SetAddr_MT8826(uint8_t addr) {
    PORTB = addr & 0x7F;
}

void setTable(uint8_t * table, size_t tableSize, const key_t* map, size_t mapSize) {
    memset(table, NO_KEY, tableSize);
    const uint8_t *addr = reinterpret_cast<const uint8_t *>(map);
    for(uint8_t i = 0; i < mapSize; i++) {    
        uint8_t index = pgm_read_byte(addr++);  // map[i].scancode;
        uint8_t value = pgm_read_byte(addr++);  // map[i].matrix.value;
        table[index] = value; 
    }
}

void setup() {
    setTable(table_main, sizeof(table_main) / sizeof(table_main[0]),  keymapOrion128_Main, sizeof(keymapOrion128_Main) / sizeof(keymapOrion128_Main[0]));
    setTable(table_shift, sizeof(table_shift) / sizeof(table_shift[0]),  keymapOrion128_Shift, sizeof(keymapOrion128_Shift) / sizeof(keymapOrion128_Shift[0]));
    setTable(table_ru, sizeof(table_ru) / sizeof(table_ru[0]),  keymapOrion128_RU, sizeof(keymapOrion128_RU) / sizeof(keymapOrion128_RU[0]));
    
    keyboard.begin(3, 2);
    keyboard.resetKey();
#ifdef DEBUG_CONSOLE
    Serial.begin(57600);
    while (!Serial); // wait for serial port to connect. Needed for native USB
    Serial.println("Start");
#endif
    // ОРИОН-128
    gio::high(RESET_ORION);
    gio::high(SHIFT_ORION);
    gio::high(CRTL_ORION);
    gio::high(LANG_ORION);

    gio::mode(RESET_ORION, OUTPUT);
    gio::mode(SHIFT_ORION, OUTPUT);
    gio::mode(CRTL_ORION, OUTPUT);
    gio::mode(LANG_ORION, OUTPUT);

    // MT8816
    gio::mode(RESET_MT8816, OUTPUT);
    gio::mode(DATA_MT8816, OUTPUT);
    gio::mode(STROBE_MT8816, OUTPUT);
    gio::mode(CS_MT8816, OUTPUT);

    gio::low(RESET_MT8816);
    gio::low(DATA_MT8816);
    gio::low(STROBE_MT8816);
    gio::low(CS_MT8816);

    // https://docs.arduino.cc/retired/hacking/software/PortManipulation/
    // https://arduino.ru/Tutorial/Upravlenie_portami_cherez_registry
    // PORTB maps to Arduino digital pins 8 to 13 The two high bits (6 & 7) map to the crystal pins and are not usable
    // DDRB - The Port B Data Direction Register - read/write
    // PORTB - The Port B Data Register - read/write
    // PINB - The Port B Input Pins Register - read only
    DDRB = B11111111;               // Set output mode port B 

    SetAddr_MT8826(0);    
    Reset_MT8826();
}

#ifdef DEBUG_CONSOLE
void decode(uint8_t key) {
    if (key == 0x11) Serial.print("HOME");
    if (key == 0x15) Serial.print("LEFT");
    if (key == 0x16) Serial.print("RIGHT");
    if (key == 0x17) Serial.print("UP");
    if (key == 0x18) Serial.print("DOWN");
    if (key == 0x19) Serial.print("INS");
    if (key == 0x1A) Serial.print("DEL");
    if (key == 0x1B) Serial.print("ESC");
    if (key == 0x1C) Serial.print("BACKSPACE");
    if (key == 0x1D) Serial.print("TAB");
    if (key == 0x1E) Serial.print("ENTER");
    if (key == 0x1F) Serial.print("SPACE");
    if (key == 0x20) Serial.print("KP0");
    if (key == 0x21) Serial.print("KP1");
    if (key == 0x22) Serial.print("KP2");
    if (key == 0x23) Serial.print("KP3");
    if (key == 0x24) Serial.print("KP4");
    if (key == 0x25) Serial.print("KP5");
    if (key == 0x26) Serial.print("KP6");
    if (key == 0x27) Serial.print("KP7");
    if (key == 0x28) Serial.print("KP8");
    if (key == 0x29) Serial.print("KP9");
    if (key == 0x2A) Serial.print("KP_DOT");
    if (key == 0x2B) Serial.print("KP_ENTER");
    if (key == 0x2C) Serial.print("KP_PLUS");
    if (key == 0x2D) Serial.print("KP_MINUS");
    if (key == 0x2E) Serial.print("KP_TIMES");
    if (key == 0x2F) Serial.print("KP_DIV");
    if (key == 0x30) Serial.print("0");
    if (key == 0x31) Serial.print("1");
    if (key == 0x32) Serial.print("2");
    if (key == 0x33) Serial.print("3");
    if (key == 0x34) Serial.print("4");
    if (key == 0x35) Serial.print("5");
    if (key == 0x36) Serial.print("6");
    if (key == 0x37) Serial.print("7");
    if (key == 0x38) Serial.print("8");
    if (key == 0x39) Serial.print("9");
    if (key == 0x3A) Serial.print("'");
    if (key == 0x3B) Serial.print(",");
    if (key == 0x3C) Serial.print("-");
    if (key == 0x3D) Serial.print(".");
    if (key == 0x3E) Serial.print("/");
    if (key == 0x40) Serial.print("`");
    if (key == 0x41) Serial.print("A");
    if (key == 0x42) Serial.print("B");
    if (key == 0x43) Serial.print("C");
    if (key == 0x44) Serial.print("D");
    if (key == 0x45) Serial.print("E");
    if (key == 0x46) Serial.print("F");
    if (key == 0x47) Serial.print("G");
    if (key == 0x48) Serial.print("H");
    if (key == 0x49) Serial.print("I");
    if (key == 0x4A) Serial.print("J");
    if (key == 0x4B) Serial.print("K");
    if (key == 0x4C) Serial.print("L");
    if (key == 0x4D) Serial.print("M");
    if (key == 0x4E) Serial.print("N");
    if (key == 0x4F) Serial.print("O");
    if (key == 0x50) Serial.print("P");
    if (key == 0x51) Serial.print("Q");
    if (key == 0x52) Serial.print("R");
    if (key == 0x53) Serial.print("S");
    if (key == 0x54) Serial.print("T");
    if (key == 0x55) Serial.print("U");
    if (key == 0x56) Serial.print("V");
    if (key == 0x57) Serial.print("W");
    if (key == 0x58) Serial.print("X");
    if (key == 0x59) Serial.print("Y");
    if (key == 0x5A) Serial.print("Z");
    if (key == 0x5B) Serial.print(";");
    if (key == 0x5C) Serial.print("\\");
    if (key == 0x5D) Serial.print("[");
    if (key == 0x5E) Serial.print("]");
    if (key == 0x5F) Serial.print("=");
    if (key == 0x61) Serial.print("F1");
    if (key == 0x62) Serial.print("F2");
    if (key == 0x63) Serial.print("F3");
    if (key == 0x64) Serial.print("F4");
    if (key == 0x65) Serial.print("F5");
    Serial.println();
}
#endif

uint16_t getScanCode() {
    while (!keyboard.available()) {
        delayMicroseconds(100);
    }
    return keyboard.read();
}

// E2 E0 XX E0 F0 XX E2
uint16_t processKeyCodeApp() {
    uint16_t code;
    // code = getScanCode();   // 0xE2
    // DEBUG_PRINT_HEX(code);
    code = getScanCode();   // code
    DEBUG_PRINT_HEX(code);
    code = getScanCode();   // code
    DEBUG_PRINT_HEX(code);
    code = getScanCode();   // 0xE2
    DEBUG_PRINT_HEX(code);
    return 0;
}

uint16_t processKeyCode(uint16_t code) {
    // extended code key (start from 0xE0)
    DEBUG_PRINT_HEX(code);
    switch (code & 0xFF) {
        case 0xE2:
            code = processKeyCodeApp();
            break;
        default:
            break;
    }
    return code;
}

matrix_t current_key = { .value = 0 };

void loop() {
    uint16_t code = getScanCode();
    if (code == PS2_KEY_ACK) return;

    uint8_t index = (uint8_t)code;

    // Обрабатываем сброс
    if (index == PS2_KEY_F12) {
        gio::low(RESET_ORION);
        delay(100);
        gio::high(RESET_ORION);
        delay(500);
        resetFunc();
        return;
    }
    
    // Обрабатываем переключения языка
    if (index == PS2_KEY_CAPS) {
        gio::toggle(LANG_ORION);
        return;
    }

    matrix_t value = { .value = table_main[index] };
    if ((code & PS2_SHIFT) == PS2_SHIFT) {
        if (table_shift[index] != NO_KEY) {
            value.value = table_shift[index];
        }
    }

    if (value.value == NO_KEY) return;

    // При отпускании любой клавиши на PS/2, отпускаем на эмуляторе (shift, ctrl)
    if ((code & PS2_BREAK) == PS2_BREAK) {
        SetKey_MT8826(false);
        gio::high(SHIFT_ORION);
        // Если Ctrl отпущен, то тоже отпускаем 
        if ((code & PS2_CTRL) == 0) {
            gio::high(CRTL_ORION);
        }
        current_key.value = 0;
        return;
    }
    // При одновременном нажатии клавиш на PS/2, проверяем теущую нажатую и если клавиша другая, отпуcкаем текущую на эмуляторе  
    if (current_key.value != value.value) {
        SetKey_MT8826(false);
    }

    // При необходимости для новой клавиши нажимаем Ctrl
    if ((code & PS2_CTRL) == PS2_CTRL) {
        gio::low(CRTL_ORION);
    }
    // При необходимости для новой клавиши нажимаем Shift
    if (value.shift) {
        gio::low(SHIFT_ORION);
    }
    
    // Нажимаем новую клавишу
    SetAddr_MT8826(value.value);
    SetKey_MT8826(true);
    // Сохраняем нажатую
    current_key = value;

#ifdef DEBUG_CONSOLE    
    index = processKeyCode(code);
    decode(index);
    Serial.print(" row: ");  Serial.print(7 - value.row);
    Serial.print(" col: ");  Serial.print(value.col);
    Serial.print(" shift: ");  Serial.print(value.shift);
    Serial.println();
#endif
    // matrix_t value;
    // for (int i = 0; i < 64; i++) {
    //     value.value = table[i];
    //     if (value.value == NO_KEY) continue;
    //     if (value.shift) gio::low(SHIFT_ORION);
    //     SetAddr_MT8826(value.value & 0x7F);
    //     SetKey_MT8826(true);
    //     delay(800);
    //     SetKey_MT8826(false);
    //     if (value.shift) gio::high(SHIFT_ORION);
    //     delay(400);
    // }
}
