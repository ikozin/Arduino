#include <Arduino.h>
#include <GyverIO.h>

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

uint8_t table[128];


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

void loop() {
    Serial.println("loop");
    for (int i = 0; i < 64; i++) {
        key value;
        value.matrix.value = table[i];
        SetAddr_MT8826(value.matrix.value);
        SetKey_MT8826(true);
        
        Serial.print(i);
        Serial.print(" = row:");
        Serial.print(value.matrix.row);
        Serial.print(", col:");
        Serial.print(value.matrix.col);
        Serial.println();
    }
    delay(10000);
}

