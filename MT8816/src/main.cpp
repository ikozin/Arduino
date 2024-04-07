#include <Arduino.h>
#include <GyverIO.h>
#include "PS2KeyMapping.h"
#include "PS2KeyRaw.h"
PS2KeyRaw keyboard;

#ifndef ARDUINO_AVR_ATmega328P_BB8
#error ATmega328P BB 8Mhz.json
#endif

#define DEBUG_CONSOLE

void (* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0
uint8_t processKeyCode(uint8_t code);

#ifdef DEBUG_CONSOLE
char text[128];

#define DEBUG_PRINT_HEX(k) { sprintf(text, "0x%02X", k); Serial.println(text);}

#endif

#define NO_KEY  (0xFF)

constexpr const uint8_t reverse_row(uint8_t row) {
    return 7 - row;
};

typedef struct _key_ {
    uint8_t scancode;
    union {
        struct {
            uint8_t row : 4;
            uint8_t col : 3;
        };
        uint8_t value;
    } matrix;
} key;

const key keymapTest[] PROGMEM = {
    { 0, {reverse_row(0), 0}},
    { 1, {reverse_row(0), 1}},
    { 2, {reverse_row(0), 2}},
    { 3, {reverse_row(0), 3}},
    { 4, {reverse_row(0), 4}},
    { 5, {reverse_row(0), 5}},
    { 6, {reverse_row(0), 6}},
    { 7, {reverse_row(0), 7}},

    { 8, {reverse_row(1), 0}},
    { 9, {reverse_row(1), 1}},
    {10, {reverse_row(1), 2}},
    {11, {reverse_row(1), 3}},
    {12, {reverse_row(1), 4}},
    {13, {reverse_row(1), 5}},
    {14, {reverse_row(1), 6}},
    {15, {reverse_row(1), 7}},

    {16, {reverse_row(2), 0}},
    {17, {reverse_row(2), 1}},
    {18, {reverse_row(2), 2}},
    {19, {reverse_row(2), 3}},
    {20, {reverse_row(2), 4}},
    {21, {reverse_row(2), 5}},
    {22, {reverse_row(2), 6}},
    {23, {reverse_row(2), 7}},

    {24, {reverse_row(3), 0}},
    {25, {reverse_row(3), 1}},
    {26, {reverse_row(3), 2}},
    {27, {reverse_row(3), 3}},
    {28, {reverse_row(3), 4}},
    {29, {reverse_row(3), 5}},
    {30, {reverse_row(3), 6}},
    {31, {reverse_row(3), 7}},

    {32, {reverse_row(4), 0}},
    {33, {reverse_row(4), 1}},
    {34, {reverse_row(4), 2}},
    {35, {reverse_row(4), 3}},
    {36, {reverse_row(4), 4}},
    {37, {reverse_row(4), 5}},
    {38, {reverse_row(4), 6}},
    {39, {reverse_row(4), 7}},

    {40, {reverse_row(5), 0}},
    {41, {reverse_row(5), 1}},
    {42, {reverse_row(5), 2}},
    {43, {reverse_row(5), 3}},
    {44, {reverse_row(5), 4}},
    {45, {reverse_row(5), 5}},
    {46, {reverse_row(5), 6}},
    {47, {reverse_row(5), 7}},

    {48, {reverse_row(6), 0}},
    {49, {reverse_row(6), 1}},
    {50, {reverse_row(6), 2}},
    {51, {reverse_row(6), 3}},
    {52, {reverse_row(6), 4}},
    {53, {reverse_row(6), 5}},
    {54, {reverse_row(6), 6}},
    {55, {reverse_row(6), 7}},

    {56, {reverse_row(7), 0}},
    {57, {reverse_row(7), 1}},
    {58, {reverse_row(7), 2}},
    {59, {reverse_row(7), 3}},
    {60, {reverse_row(7), 4}},
    {61, {reverse_row(7), 5}},
    {62, {reverse_row(7), 6}},
    {63, {reverse_row(7), 7}},
};

const key keymapOrion128[] PROGMEM = {
    {  0x01, {reverse_row(0), 0}}, //F9
    {  0x03, {reverse_row(0), 0}}, //F5
    {  0x04, {reverse_row(0), 0}}, //F3
    {  0x05, {reverse_row(0), 0}}, //F1
    {  0x06, {reverse_row(0), 0}}, //F2
    {  0x07, {reverse_row(0), 0}}, //F12
    {  0x09, {reverse_row(0), 0}}, //F10
    {  0x0A, {reverse_row(0), 0}}, //F8
    {  0x0B, {reverse_row(0), 0}}, //F6
    {  0x0C, {reverse_row(0), 0}}, //F4
    {  0x0D, {reverse_row(0), 0}}, //TAB
    {  0x0E, {reverse_row(0), 0}}, //`
    {  0x11, {reverse_row(0), 0}}, //ALT
    {  0x12, {reverse_row(0), 0}}, //SHIFT L
    {  0x14, {reverse_row(0), 0}}, //CTRL L
    {  0x15, {reverse_row(0), 0}}, //q
    {  0x16, {reverse_row(0), 0}}, //1
    {  0x1A, {reverse_row(0), 0}}, //z
    {  0x1B, {reverse_row(0), 0}}, //s
    {  0x1C, {reverse_row(0), 0}}, //a
    {  0x1D, {reverse_row(0), 0}}, //w
    {  0x1E, {reverse_row(0), 0}}, //2
    {  0x1F, {reverse_row(0), 0}}, //WIN
    {  0x21, {reverse_row(0), 0}}, //c
    {  0x22, {reverse_row(0), 0}}, //x
    {  0x23, {reverse_row(0), 0}}, //d
    {  0x24, {reverse_row(0), 0}}, //e
    {  0x25, {reverse_row(0), 0}}, //4
    {  0x26, {reverse_row(0), 0}}, //3
    {  0x27, {reverse_row(0), 0}}, //WIN
    {  0x29, {reverse_row(0), 0}}, //SPACE
    {  0x2A, {reverse_row(0), 0}}, //v
    {  0x2B, {reverse_row(0), 0}}, //f
    {  0x2C, {reverse_row(0), 0}}, //t
    {  0x2D, {reverse_row(0), 0}}, //r
    {  0x2E, {reverse_row(0), 0}}, //5
    {  0x2F, {reverse_row(0), 0}}, //CTRL R
    {  0x31, {reverse_row(0), 0}}, //n
    {  0x32, {reverse_row(0), 0}}, //b
    {  0x33, {reverse_row(0), 0}}, //h
    {  0x34, {reverse_row(0), 0}}, //g
    {  0x35, {reverse_row(0), 0}}, //y
    {  0x36, {reverse_row(0), 0}}, //6
    {  0x37, {reverse_row(0), 0}}, //POWER
    {  0x3A, {reverse_row(0), 0}}, //m
    {  0x3B, {reverse_row(0), 0}}, //j
    {  0x3C, {reverse_row(0), 0}}, //u
    {  0x3D, {reverse_row(0), 0}}, //7
    {  0x3E, {reverse_row(0), 0}}, //8
    {  0x3F, {reverse_row(0), 0}}, //SLEEP
    {  0x41, {reverse_row(0), 0}}, //,
    {  0x42, {reverse_row(0), 0}}, //k
    {  0x43, {reverse_row(0), 0}}, //i
    {  0x44, {reverse_row(0), 0}}, //o
    {  0x45, {reverse_row(0), 0}}, //0
    {  0x46, {reverse_row(0), 0}}, //9
    {  0x49, {reverse_row(0), 0}}, //.
    {  0x4A, {reverse_row(0), 0}}, ///
    {  0x4B, {reverse_row(0), 0}}, //l
    {  0x4C, {reverse_row(0), 0}}, //;
    {  0x4D, {reverse_row(0), 0}}, //p
    {  0x4E, {reverse_row(0), 0}}, //-
    {  0x52, {reverse_row(0), 0}}, //'
    {  0x54, {reverse_row(0), 0}}, //[
    {  0x55, {reverse_row(0), 0}}, //+
    {  0x58, {reverse_row(0), 0}}, //CAPS
    {  0x59, {reverse_row(0), 0}}, //SHIFT R
    {  0x5A, {reverse_row(0), 0}}, //ENTER
    {  0x5B, {reverse_row(0), 0}}, //]
    {  0x5D, {reverse_row(0), 0}}, //"\\"
    {  0x5E, {reverse_row(0), 0}}, //WAKEUP
    {  0x66, {reverse_row(0), 0}}, //ЗБ
    {  0x69, {reverse_row(0), 0}}, //END
    {  0x6B, {reverse_row(0), 0}}, //LEFT
    {  0x6C, {reverse_row(0), 0}}, //HOME
    {  0x70, {reverse_row(0), 0}}, //INS
    {  0x71, {reverse_row(0), 0}}, //DEL
    {  0x72, {reverse_row(0), 0}}, //DOWN
    {  0x73, {reverse_row(0), 0}}, //CENTER
    {  0x74, {reverse_row(0), 0}}, //RIGHT
    {  0x75, {reverse_row(0), 0}}, //UP
    {  0x76, {reverse_row(0), 0}}, //ESC
    {  0x77, {reverse_row(0), 0}}, //NUM
    {  0x78, {reverse_row(0), 0}}, //F11
    {  0x79, {reverse_row(0), 0}}, //+
    {  0x7A, {reverse_row(0), 0}}, //PG DOWN
    {  0x7B, {reverse_row(0), 0}}, //-
    {  0x7C, {reverse_row(0), 0}}, //*
    {  0x7D, {reverse_row(0), 0}}, //PG UP
    {  0x7E, {reverse_row(0), 0}}, //SCROLL
    {  0x83, {reverse_row(0), 0}}, //F7
    {  0xFF, {reverse_row(0), 0}}, //BREAK

};

uint8_t table[256];


// ОРИОН-128
#define RESET_ORION     (PD3)   // PD3
#define SHIFT_ORION     (PC0)   // PC0
#define CRTL_ORION      (PC1)   // PC1
#define LANG_ORION      (PC2)   // PC2

// MT8816
#define RESET_MT8816    (PD4)   // PD4
#define DATA_MT8816     (PD5)   // PD5
#define STROBE_MT8816   (PD6)   // PD6
#define CS_MT8816       (PD7)   // PD7

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
    // gio::write(AX0_MT8816, bitRead(addr,0));    // PB0
    // gio::write(AX1_MT8816, bitRead(addr,1));    // PB1
    // gio::write(AX2_MT8816, bitRead(addr,2));    // PB2
    // gio::write(AX3_MT8816, bitRead(addr,3));    // PB3
    // gio::write(AY0_MT8816, bitRead(addr,4));    // PB4
    // gio::write(AY1_MT8816, bitRead(addr,5));    // PB5
    // gio::write(AY2_MT8816, bitRead(addr,6));    // PB6
    PORTB = addr;
}

void setTable(const key* map, size_t size) {
    memset(table, NO_KEY, sizeof(table));
    const uint8_t *addr = reinterpret_cast<const uint8_t *>(map);
    for(uint8_t i = 0; i < size; i++) {    
        uint8_t index = pgm_read_byte(addr++);  // map[i].scancode;
        uint8_t value = pgm_read_byte(addr++);  // map[i].matrix.value;
        table[index] = value; 
    }
}

void setup() {
    setTable(keymapTest, sizeof(keymapTest) / sizeof(keymapTest[0]));

    interrupts();
    keyboard.begin();
    Serial.begin(57600);
    while (!Serial); // wait for serial port to connect. Needed for native USB
    Serial.println("Start");

    // ОРИОН-128
    gio::mode(RESET_ORION, OUTPUT);
    gio::mode(SHIFT_ORION, OUTPUT);
    gio::mode(CRTL_ORION, OUTPUT);
    gio::mode(LANG_ORION, OUTPUT);

    gio::high(RESET_ORION);
    gio::high(SHIFT_ORION);
    gio::high(CRTL_ORION);
    gio::high(LANG_ORION);

    // MT8816
    gio::mode(RESET_MT8816, OUTPUT);
    gio::mode(DATA_MT8816, OUTPUT);
    gio::mode(STROBE_MT8816, OUTPUT);
    gio::mode(CS_MT8816, OUTPUT);

    gio::low(RESET_MT8816);
    gio::low(DATA_MT8816);
    gio::low(STROBE_MT8816);
    gio::low(CS_MT8816);

    // gio::mode(AX0_MT8816, OUTPUT);  // PB0
    // gio::mode(AX1_MT8816, OUTPUT);  // PB1
    // gio::mode(AX2_MT8816, OUTPUT);  // PB2
    // gio::mode(AX3_MT8816, OUTPUT);  // PB3
    // gio::mode(AY0_MT8816, OUTPUT);  // PB4
    // gio::mode(AY1_MT8816, OUTPUT);  // PB5
    // gio::mode(AY2_MT8816, OUTPUT);  // PB6

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

void decode(uint8_t key) {
    
    if (key == 0x01) Serial.println("F9");
    if (key == 0x03) Serial.println("F5");
    if (key == 0x04) Serial.println("F3");
    if (key == 0x05) Serial.println("F1");
    if (key == 0x06) Serial.println("F2");
    if (key == 0x07) Serial.println("F12");
    if (key == 0x09) Serial.println("F10");
    if (key == 0x0A) Serial.println("F8");
    if (key == 0x0B) Serial.println("F6");
    if (key == 0x0C) Serial.println("F4");
    if (key == 0x0D) Serial.println("TAB");
    if (key == 0x0E) Serial.println("`");
    if (key == 0x11) Serial.println("ALT");
    if (key == 0x12) Serial.println("SHIFT L");
    if (key == 0x14) Serial.println("CTRL L");
    if (key == 0x15) Serial.println("q");
    if (key == 0x16) Serial.println("1");
    if (key == 0x1A) Serial.println("z");
    if (key == 0x1B) Serial.println("s");
    if (key == 0x1C) Serial.println("a");
    if (key == 0x1D) Serial.println("w");
    if (key == 0x1E) Serial.println("2");
    if (key == 0x1F) Serial.println("WIN");
    if (key == 0x21) Serial.println("c");
    if (key == 0x22) Serial.println("x");
    if (key == 0x23) Serial.println("d");
    if (key == 0x24) Serial.println("e");
    if (key == 0x25) Serial.println("4");
    if (key == 0x26) Serial.println("3");
    if (key == 0x27) Serial.println("WIN");
    if (key == 0x29) Serial.println("SPACE");
    if (key == 0x2A) Serial.println("v");
    if (key == 0x2B) Serial.println("f");
    if (key == 0x2C) Serial.println("t");
    if (key == 0x2D) Serial.println("r");
    if (key == 0x2E) Serial.println("5");
    if (key == 0x2F) Serial.println("CTRL R");
    if (key == 0x31) Serial.println("n");
    if (key == 0x32) Serial.println("b");
    if (key == 0x33) Serial.println("h");
    if (key == 0x34) Serial.println("g");
    if (key == 0x35) Serial.println("y");
    if (key == 0x36) Serial.println("6");
    if (key == 0x37) Serial.println("POWER");
    if (key == 0x3A) Serial.println("m");
    if (key == 0x3B) Serial.println("j");
    if (key == 0x3C) Serial.println("u");
    if (key == 0x3D) Serial.println("7");
    if (key == 0x3E) Serial.println("8");
    if (key == 0x3F) Serial.println("SLEEP");
    if (key == 0x41) Serial.println(",");
    if (key == 0x42) Serial.println("k");
    if (key == 0x43) Serial.println("i");
    if (key == 0x44) Serial.println("o");
    if (key == 0x45) Serial.println("0");
    if (key == 0x46) Serial.println("9");
    if (key == 0x49) Serial.println(".");
    if (key == 0x4A) Serial.println("/");
    if (key == 0x4B) Serial.println("l");
    if (key == 0x4C) Serial.println(";");
    if (key == 0x4D) Serial.println("p");
    if (key == 0x4E) Serial.println("-");
    if (key == 0x52) Serial.println("'");
    if (key == 0x54) Serial.println("[");
    if (key == 0x55) Serial.println("+");
    if (key == 0x58) Serial.println("CAPS");
    if (key == 0x59) Serial.println("SHIFT R");
    if (key == 0x5A) Serial.println("ENTER");
    if (key == 0x5B) Serial.println("]");
    if (key == 0x5D) Serial.println("\\");
    if (key == 0x5E) Serial.println("WAKEUP");
    if (key == 0x66) Serial.println("ЗБ");
    if (key == 0x69) Serial.println("END");
    if (key == 0x6B) Serial.println("LEFT");
    if (key == 0x6C) Serial.println("HOME");
    if (key == 0x70) Serial.println("INS");
    if (key == 0x71) Serial.println("DEL");
    if (key == 0x72) Serial.println("DOWN");
    if (key == 0x73) Serial.println("CENTER");
    if (key == 0x74) Serial.println("RIGHT");
    if (key == 0x75) Serial.println("UP");
    if (key == 0x76) Serial.println("ESC");
    if (key == 0x77) Serial.println("NUM");
    if (key == 0x78) Serial.println("F11");
    if (key == 0x79) Serial.println("+");
    if (key == 0x7A) Serial.println("PG DOWN");
    if (key == 0x7B) Serial.println("-");
    if (key == 0x7C) Serial.println("*");
    if (key == 0x7D) Serial.println("PG UP");
    if (key == 0x7E) Serial.println("SCROLL");
    if (key == 0x83) Serial.println("F7");

    if (key == 0xFF) {
        Serial.println("BREAK");
        resetFunc();   //Serial.println("BREAK");
    }
}

// E2 E0 XX E0 F0 XX E2
uint8_t processKeyCodeApp() {
    uint8_t code;
    while (!(code = keyboard.read()));  // 0xE0
    while (!(code = keyboard.read()));  // code
    while (!(code = keyboard.read()));  // 0xE0
    while (!(code = keyboard.read()));  // 0xF0
    while (!(code = keyboard.read()));  // code
    while (!(code = keyboard.read()));  // 0xE2
    return 0;
}

// WIN  - E0 1F E0 F0 1F 
// UP   - E0 12 E0 75 - E0 F0 75 E0 F0 12
// DOWN - E0 12 E0 72 - E0 F0 72 E0 F0 12
// LEFT - E0 12 E0 6B - E0 F0 6B E0 F0 12
// RIGHT- E0 12 E0 74 - E0 F0 74 E0 F0 12
uint8_t processKeyCodeExt() {                   // 0xE0
    uint8_t code;
    while (!(code = keyboard.read()));
    if (code == 0XF0) {                         // 0xF0
        while (!(code = keyboard.read()));      // code
        return 0;
    }    
    if (code == 0x12) {                         // 0x12
        while (!(code = keyboard.read()));
        code = processKeyCode(code);
        return code;
    }
    return processKeyCode(code);
}

// E1 14 77 E1 F0 14 F0 77
uint8_t processKeyCodeBreak() {         // 0xE1
    uint8_t code;
    while (!(code = keyboard.read()));  // 0x14
    while (!(code = keyboard.read()));  // 0x77
    while (!(code = keyboard.read()));  // 0xE1
    while (!(code = keyboard.read()));  // 0xF0
    while (!(code = keyboard.read()));  // 0x14
    while (!(code = keyboard.read()));  // 0xF0
    while (!(code = keyboard.read()));  // 0x77
    return 0xFF;    
}

uint8_t processKeyCode(uint8_t code) {
    // extended code key (start from 0xE0)

    switch (code) {
        case 0xE0:
            code = processKeyCodeExt();
            break;
        case 0xE1:
            code = processKeyCodeBreak();
            break;
        case 0xE2:
            code = processKeyCodeApp();
            break;
        default:
            break;
    }
    return code;
}

void loop() {
    // Serial.println("loop");
    // for (int i = 0; i < 64; i++) {
    //     key value;
    //     value.matrix.value = table[i];
    //     SetAddr_MT8826(value.matrix.value);
    //     SetKey_MT8826(true);
        
    //     Serial.print(i);
    //     Serial.print(" = row:");
    //     Serial.print(value.matrix.row);
    //     Serial.print(", col:");
    //     Serial.print(value.matrix.col);
    //     Serial.println();
    // }
    // delay(10000);

    // uint8_t code;
    // while (!(code = keyboard.read()));
    // DEBUG_PRINT_HEX(code);

    uint8_t code;
    while ((code = keyboard.read())) {
        if (code == 0xF0) {
            while (!(code = keyboard.read()));
            processKeyCode(code);
            return;
        }
        code = processKeyCode(code);
        decode(code);

        uint8_t key = (code < (sizeof(mapping) / sizeof(mapping[0]))) ? mapping[code] : NO_KEY;
        if (key != NO_KEY) {

        }
    }
}

