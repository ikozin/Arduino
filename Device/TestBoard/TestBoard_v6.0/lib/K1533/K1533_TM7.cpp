#include "K1533_TM7.h"

const static TDevicePin PROGMEM pin_map_1533_tm7[] = {
    // Входы     D1  D2   C         Выходы      1       2
    { .Input = {  2,  3, 13,  0 }, .Output = { 16,  1, 15, 14,  0 }},

    // Входы     D3  D4   C         Выходы      3       4
    { .Input = {  6,  7,  4,  0 }, .Output = { 10, 11,  9,  8,  0 }},
};

const static TDeviceVal PROGMEM values_1533_tm7[] = {
    //                      C 2 1
    { .value = (uint16_t)B_1_0_0, .result = (uint16_t)B_1_0_1_0 },
    { .value = (uint16_t)B_0_0_0, .result = (uint16_t)B_1_0_1_0 },

    { .value = (uint16_t)B_1_0_1, .result = (uint16_t)B_1_0_0_1 },
    { .value = (uint16_t)B_0_0_1, .result = (uint16_t)B_1_0_0_1 },

    { .value = (uint16_t)B_1_1_0, .result = (uint16_t)B_0_1_1_0 },
    { .value = (uint16_t)B_0_1_0, .result = (uint16_t)B_0_1_1_0 },

    { .value = (uint16_t)B_1_1_1, .result = (uint16_t)B_0_1_0_1 },
    { .value = (uint16_t)B_0_1_1, .result = (uint16_t)B_0_1_0_1 },
};

K1533TM7::K1533TM7() {
    _devices = pin_map_1533_tm7;
    _values = values_1533_tm7;  
    _devices_count = sizeof(pin_map_1533_tm7)/sizeof(pin_map_1533_tm7[0]);
    _values_count = sizeof(values_1533_tm7)/sizeof(values_1533_tm7[0]);
}

const __FlashStringHelper * K1533TM7::menu(void) {
    return F("TM7 (Регистр)");
}

const __FlashStringHelper * K1533TM7::description(void) {
    return F(
"KP1533TM7\r\n"
"Регистр\r\n"
"DIP16\r\n"
"\t         5 - +5V         \r\n"
"\t        12 - GND         \r\n"
"\t      -------------      \r\n"
"\t  2 -| D1 | RG | 1 |- 16 \r\n"
"\t  3 -| D2 |    |   o- 1  \r\n"
"\t     |    |    | 2 |- 15 \r\n"
"\t 13 -| C  |    |   o- 14 \r\n"
"\t      -------------      \r\n"
"\t      -------------      \r\n"
"\t  6 -| D3 | RG | 3 |- 10 \r\n"
"\t  7 -| D4 |    |   o- 11 \r\n"
"\t     |    |    | 4 |- 9  \r\n"
"\t  4 -| C  |    |   o- 8  \r\n"
"\t      -------------      \r\n"
    );
}

const __FlashStringHelper * K1533TM7::title(void) {
    return F("KP1533TM7\r\nРегистр\r\nDIP16\r\n");
}
