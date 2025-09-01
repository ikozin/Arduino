#include "K1533_IE19.h"

const static TDevicePin PROGMEM pin_map_1533_ie19_1[] = {
    // Входы      C   R                             Выходы      1   2   4   8
    { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  4,  5,  6,  0,  0,  0,  0 }},
    { .Input = { 13, 12,  0,  0,  0,  0,  0,  0 }, .Output = { 11, 10,  9,  8,  0,  0,  0,  0 }},
};

const static TDevicePin PROGMEM pin_map_1533_ie19_2[] = {
    // Входы      C   R                             Выходы      1   2   4   8
    { .Input = { 13, 12,  0,  0,  0,  0,  0,  0 }, .Output = { 11, 10,  9,  8,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_ie19[] = {  
    //                            R  C                         8  4  2  1
    { .value = (uint16_t)B__0__0__1__1, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__1__1, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__1__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__1__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__1__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__0__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__1__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__0__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__1__0__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__1__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__1__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__1__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__1__1__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__0__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__0__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__0__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__0__0__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__1__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__0__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__1__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__0__1__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__0__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__1__0__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__0__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__1__0__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__1__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__1__1__0 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__1__1 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__1__1__1__1 },
    { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__0 },
    { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__0 },
};

const __FlashStringHelper * K1533IE19::menu(void) {
    return F("ИE19 (Счетчик)");
}

const __FlashStringHelper * K1533IE19::description(void) {
    return F(
"KP1533ИE19\r\n"
"Счетчик двоичный\r\n"
"DIP14\r\n"
"\t       14 - +5V       \r\n"
"\t        7 - GND       \r\n"
"\t      -----------     \r\n"
"\t  1 -\\ C |CT2| 1 |-  3\r\n"
"\t     |   |   | 2 |-  4\r\n"
"\t     |---|   | 4 |-  5\r\n"
"\t  2 -| R |   | 8 |-  6\r\n"
"\t      -----------     \r\n"
"\t      -----------     \r\n"
"\t 13 -\\ C |CT2| 1 |- 11\r\n"
"\t     |   |   | 2 |- 10\r\n"
"\t     |---|   | 4 |-  9\r\n"
"\t 12 -| R |   | 8 |-  8\r\n"
"\t      -----------     \r\n"
    );
}

const __FlashStringHelper * K1533IE19::title(void) {
    return F("KP1533ИE19\r\nСчетчик двоичный\r\nDIP14\r\n");
}

K1533IE19_SubDev sub_1533_ie19_dev1(pin_map_1533_ie19_1, values_1533_ie19, sizeof(values_1533_ie19)/sizeof(values_1533_ie19[0]));
K1533IE19_SubDev sub_1533_ie19_dev2(pin_map_1533_ie19_2, values_1533_ie19, sizeof(values_1533_ie19)/sizeof(values_1533_ie19[0]));
TDevice * composite_1533_ie19[] { &sub_1533_ie19_dev1, &sub_1533_ie19_dev2 };

K1533IE19::K1533IE19(): TDeviceComposite(composite_1533_ie19, sizeof(composite_1533_ie19)/sizeof(composite_1533_ie19[0])) {
}
