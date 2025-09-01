#include "K1533_LA4_LA10_LA24.h"

const static TDevicePin PROGMEM pin_map_1533_la4_la10_la24[] = {
    { .Input = {  1,  2, 13,  0,  0,  0,  0,  0 }, .Output = { 12,  0,  0,  0,  0,  0,  0,  0 }},
    { .Input = {  3,  4,  5,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
    { .Input = {  9, 10, 11,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_la4_la10_la24[] = {
    { .value = (uint16_t) 0, .result = (uint16_t)1 },
    { .value = (uint16_t) 1, .result = (uint16_t)1 },
    { .value = (uint16_t) 2, .result = (uint16_t)1 },
    { .value = (uint16_t) 3, .result = (uint16_t)1 },
    { .value = (uint16_t) 4, .result = (uint16_t)1 },
    { .value = (uint16_t) 5, .result = (uint16_t)1 },
    { .value = (uint16_t) 6, .result = (uint16_t)1 },
    { .value = (uint16_t) 7, .result = (uint16_t)0 },
};

K1533LA4LA10LA24::K1533LA4LA10LA24(void) {
    _devices = pin_map_1533_la4_la10_la24;
    _values = values_1533_la4_la10_la24;
    _devices_count = sizeof(pin_map_1533_la4_la10_la24)/sizeof(pin_map_1533_la4_la10_la24[0]);
    _values_count = sizeof(values_1533_la4_la10_la24)/sizeof(values_1533_la4_la10_la24[0]);
}

const __FlashStringHelper * K1533LA4LA10LA24::menu(void) {
    return F("ЛA4,10,24 (3И-HE)");
}

const __FlashStringHelper * K1533LA4LA10LA24::description(void) {
    return F(
"KP1533ЛA4\r\n"
"KP1533ЛA10 - открытый коллектор\r\n"
"KP1533ЛA24 - повышеннаая нагрузка\r\n"
"3 элемента 3И-HE\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  1 -| &   |     \r\n"
"\t     |     |     \r\n"
"\t  2 -|     o- 12 \r\n"
"\t     |     |     \r\n"
"\t 13 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  3 -| &   |     \r\n"
"\t     |     |     \r\n"
"\t  4 -|     o- 6  \r\n"
"\t     |     |     \r\n"
"\t  5 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  9 -| &   |     \r\n"
"\t     |     |     \r\n"
"\t 10 -|     o- 8  \r\n"
"\t     |     |     \r\n"
"\t 11 -|     |     \r\n"
"\t      -----      \r\n"
    );
}

const __FlashStringHelper * K1533LA4LA10LA24::title(void) {
    return F("KP1533ЛA4 ЛA10 ЛA24\r\n3 элемента 3И-HE\r\nDIP14\r\n");
}
