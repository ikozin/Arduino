#include "K1533_IE5.h"

const static TDevicePin PROGMEM pin_map_1533_ie5[] = {
    // Входы     C1  C2   &   R                     Выходы      1   2   4   8
    { .Input = { 14,  1,  2,  3,  0,  0,  0,  0 }, .Output = { 12,  9,  8, 11,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_ie5[] = {  
    //                      R  & C2 C1                         8  4  2  1
    { .value = (uint16_t)B__1__1__0__0, .result = (uint16_t)B__0__0__0__0 },

    { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__1__0__1, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__1__0__0__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__1__0__0__1, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__1__0__0__0, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__1__0__1, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__0 },

    //                      R  & C2 C1                         8  4  2  1
    { .value = (uint16_t)B__1__1__0__0, .result = (uint16_t)B__0__0__0__0 },

    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__1__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__0__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__0__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__1__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__1__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__1__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__0__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__0__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__1__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__0__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__0__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__1__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__1__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__1__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__0 },
};


K1533IE5::K1533IE5(void) {
    _devices = pin_map_1533_ie5;
    _values = values_1533_ie5;  
    _devices_count = sizeof(pin_map_1533_ie5)/sizeof(pin_map_1533_ie5[0]);
    _values_count = sizeof(values_1533_ie5)/sizeof(values_1533_ie5[0]);
}

const __FlashStringHelper * K1533IE5::menu(void) {
    return F("ИE5 (Счетчик)");
}

const __FlashStringHelper * K1533IE5::description(void) {
    return F(
"KP1533ИE5\r\n"
"Счетчик двоичный\r\n"
"DIP14\r\n"
"\t       5 - +5V         \r\n"
"\t      10 - GND         \r\n"
"\t      ------------     \r\n"
"\t 14 -\\ C1 |CT2| 1 |- 12\r\n"
"\t  1 -\\ C2 |   | 2 |-  9\r\n"
"\t     |----|   | 4 |-  8\r\n"
"\t  2 -| &  |   | 8 |- 11\r\n"
"\t  3 -| R  |   |   |    \r\n"
"\t      ------------     \r\n"
    );
}

const __FlashStringHelper * K1533IE5::title(void) {
    return F("KP1533ИE5\r\nСчетчик двоичный\r\nDIP14\r\n");
}
