#include "K1533_LE4.h"

const static TDevicePin PROGMEM pin_map_1533_le4[] = {
    { .Input = {  1,  2, 13,  0,  0,  0,  0,  0 }, .Output = { 12,  0,  0,  0,  0,  0,  0,  0 }},
    { .Input = {  3,  4,  5,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
    { .Input = {  9, 10, 11,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_le4[] = {
    { .value = (uint16_t) 0, .result = (uint16_t) 1 },
    { .value = (uint16_t) 1, .result = (uint16_t) 0 },
    { .value = (uint16_t) 2, .result = (uint16_t) 0 },
    { .value = (uint16_t) 3, .result = (uint16_t) 0 },
    { .value = (uint16_t) 4, .result = (uint16_t) 0 },
    { .value = (uint16_t) 5, .result = (uint16_t) 0 },
    { .value = (uint16_t) 6, .result = (uint16_t) 0 },
    { .value = (uint16_t) 7, .result = (uint16_t) 0 },
};

K1533LE4::K1533LE4(void) {
    _devices = pin_map_1533_le4;
    _values = values_1533_le4;
    _devices_count = sizeof(pin_map_1533_le4)/sizeof(pin_map_1533_le4[0]);
    _values_count = sizeof(values_1533_le4)/sizeof(values_1533_le4[0]);
}

const __FlashStringHelper * K1533LE4::menu(void) {
    return F("ЛE4 (3ИЛИ-HE)");
}

const __FlashStringHelper * K1533LE4::description(void) {
    return F(
"KP1533ЛE4\r\n"
"3 элемента 3ИЛИ-HE\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  1 -| 1   |     \r\n"
"\t     |     |     \r\n"
"\t  2 -|     o- 12 \r\n"
"\t     |     |     \r\n"
"\t 13 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  3 -| 1   |     \r\n"
"\t     |     |     \r\n"
"\t  4 -|     o- 6  \r\n"
"\t     |     |     \r\n"
"\t  5 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  9 -| 1   |     \r\n"
"\t     |     |     \r\n"
"\t 10 -|     o- 8  \r\n"
"\t     |     |     \r\n"
"\t 11 -|     |     \r\n"
"\t      -----      \r\n"
    );
}

const __FlashStringHelper * K1533LE4::title(void) {
    return F("KP1533ЛE4\r\n3 элемента 3ИЛИ-HE\r\nDIP14\r\n");
}
