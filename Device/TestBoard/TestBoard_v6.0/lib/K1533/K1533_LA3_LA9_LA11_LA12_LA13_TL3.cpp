#include "K1533_LA3_LA9_LA11_LA12_LA13_TL3.h"

const static TDevicePin PROGMEM pin_map_1533_la3_la9_la11_la12_la13_tl3[] = {
    { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  0,  0,  0,  0,  0,  0,  0 }},
    { .Input = {  4,  5,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
    { .Input = {  9, 10,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
    { .Input = { 12, 13,  0,  0,  0,  0,  0,  0 }, .Output = { 11,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_la3_la9_la11_la12_la13_tl3[] = {
    { .value = (uint16_t)0, .result = (uint16_t)1 },
    { .value = (uint16_t)1, .result = (uint16_t)1 },
    { .value = (uint16_t)2, .result = (uint16_t)1 },
    { .value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LA3LA9LA11LA12LA13TL3::K1533LA3LA9LA11LA12LA13TL3(void) {
    _devices = pin_map_1533_la3_la9_la11_la12_la13_tl3;
    _values = values_1533_la3_la9_la11_la12_la13_tl3;
    _devices_count = sizeof(pin_map_1533_la3_la9_la11_la12_la13_tl3)/sizeof(pin_map_1533_la3_la9_la11_la12_la13_tl3[0]);
    _values_count = sizeof(values_1533_la3_la9_la11_la12_la13_tl3)/sizeof(values_1533_la3_la9_la11_la12_la13_tl3[0]);
}

const __FlashStringHelper * K1533LA3LA9LA11LA12LA13TL3::menu(void) {
    return F("ЛA3,9,11,12,13,TЛ3 (2И-HE)");
}

const __FlashStringHelper * K1533LA3LA9LA11LA12LA13TL3::description(void) {
    return F(
"KP1533ЛA3\r\n"
"KP1533ЛA9\r\n"
"KP1533ЛA11 - открытый коллектор\r\n"
"KP1533ЛA12 - повышеннаая нагрузка\r\n"
"KP1533ЛA13 - открытый коллектор,\r\n"
"             повышеннаая нагрузка\r\n"
"KP1533TЛ3  - триггер Шмитта\r\n"
"4 элемента 2И-HE\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  1 -| &   |     \r\n"
"\t     |     o- 3  \r\n"
"\t  2 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  4 -| &   |     \r\n"
"\t     |     o- 6  \r\n"
"\t  5 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  9 -| &   |     \r\n"
"\t     |     o- 8  \r\n"
"\t  10-|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  12-| &   |     \r\n"
"\t     |     o- 11 \r\n"
"\t  13-|     |     \r\n"
"\t      -----      \r\n"
    );
}

const __FlashStringHelper * K1533LA3LA9LA11LA12LA13TL3::title(void) {
    return F("ЛA3 ЛA9 ЛA11\r\nЛA12 ЛA13 TЛ3\r\n4 элемента 2И-HE\r\nDIP14\r\n");
}
