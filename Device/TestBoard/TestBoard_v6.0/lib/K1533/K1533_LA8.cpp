#include "K1533_LA8.h"

const static TDevicePin PROGMEM pin_map_1533_la8[] = {
    {.Input = {  2,  3,  0,  0,  0,  0,  0,  0 }, .Output = {  1,  0,  0,  0,  0,  0,  0,  0 }},
    {.Input = {  5,  6,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
    {.Input = {  8,  9,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
    {.Input = { 11, 11,  0,  0,  0,  0,  0,  0 }, .Output = { 13,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_la8[] = {
    {.value = (uint16_t)0, .result = (uint16_t)1 },
    {.value = (uint16_t)1, .result = (uint16_t)1 },
    {.value = (uint16_t)2, .result = (uint16_t)1 },
    {.value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LA8::K1533LA8(void) {
    _devices = pin_map_1533_la8;
    _values = values_1533_la8;
    _devices_count = sizeof(pin_map_1533_la8)/sizeof(pin_map_1533_la8[0]);
    _values_count = sizeof(values_1533_la8)/sizeof(values_1533_la8[0]);
}

const __FlashStringHelper * K1533LA8::menu(void) {
    return F("ЛA8 (2И-HE)");
}

const __FlashStringHelper * K1533LA8::description(void) {
    return F(
"KP1533ЛA8 - открытый коллектор\r\n"
"4 элемента 2И-HE\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  2 -| &   |     \r\n"
"\t     |     o- 1  \r\n"
"\t  3 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  5 -| &   |     \r\n"
"\t     |     o- 4  \r\n"
"\t  6 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  8 -| &   |     \r\n"
"\t     |     o- 10 \r\n"
"\t  9 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  11-| &   |     \r\n"
"\t     |     o- 13 \r\n"
"\t  12-|     |     \r\n"
"\t      -----      \r\n"
    );
}

const __FlashStringHelper * K1533LA8::title(void) {
    return F("KP1533ЛA8\r\n4 элемента 2И-HE\r\nDIP14\r\n");
}
