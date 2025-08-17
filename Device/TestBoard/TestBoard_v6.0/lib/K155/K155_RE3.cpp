#include "K155_RE3.h"

const static TDevicePin PROGMEM pin_map_155_re3[] =
{
    // Входы      1   2   4   8  16   V                     1   2   3   4   5   6   7   8
    { .Input = { 10, 11, 12, 13, 14, 15,  0 }, .Output = {  1,  2,  3,  4,  5,  6,  7,  9,  0 }},
};

const static TDeviceVal PROGMEM values_155_re3[] =
{  
    //
    { .value = (uint16_t) 0x00, .result = (uint16_t)0 },
};

K155RE3::K155RE3(void): Dip16_ROM(5, 8) {
    _devices = pin_map_155_re3;
    _values = values_155_re3;  
    _devices_count = sizeof(pin_map_155_re3)/sizeof(pin_map_155_re3[0]);
    _values_count = sizeof(values_155_re3)/sizeof(values_155_re3[0]);
}

const __FlashStringHelper * K155RE3::menu(void) {
    return F("PЕ3 (ПЗУ 32x8)");
}

const __FlashStringHelper * K155RE3::description(void) {
    return F(
"К155РЕ3\r\n"
"ПЗУ емкостью 256 бит (32x8)\r\n"
"DIP16\r\n"
"\t         16 - +5V        \r\n"
"\t          8 - GND        \r\n"
"\t      --------------      \r\n"
"\t 10 -|  1 | ROM | 1 |-  1 \r\n"
"\t 11 -|  2 |     | 2 |-  2 \r\n"
"\t 12 -|  4 |     | 3 |-  3 \r\n"
"\t 13 -|  8 |     | 4 |-  4 \r\n"
"\t 14 -| 16 |     | 5 |-  5 \r\n"
"\t     |    |     | 6 |-  6 \r\n"
"\t     |    |     | 7 |-  7 \r\n"
"\t 15 -o V  |     | 8 |-  9 \r\n"
"\t      --------------      \r\n"
    );
};

const __FlashStringHelper * K155RE3::title(void) {
    return F("К155РЕ3\r\nПЗУ 256b(32x8)\r\nDIP16\r\n");
}
