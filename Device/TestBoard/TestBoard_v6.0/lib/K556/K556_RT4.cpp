#include "K556_RT4.h"

const static TDevicePin PROGMEM pin_map_556_rt4[] = {
    // Входы     A0  A1  A2  A3  A4  A5  A6  A7   W  CE                     1   2   3   4
    { .Input = { 15,  7,  6,  5,  4,  3,  2,  1, 13, 14, 0 }, .Output = {  12, 11, 10,  9,  0 }},
};

const static TDeviceVal PROGMEM values_556_rt4[] = {  
    //
    { .value = (uint16_t) 0x00, .result = (uint16_t)0 },
};

K556RT4::K556RT4(void): Dip16_ROM(8, 4) {
    _devices = pin_map_556_rt4;
    _values = values_556_rt4;  
    _devices_count = sizeof(pin_map_556_rt4)/sizeof(pin_map_556_rt4[0]);
    _values_count = sizeof(values_556_rt4)/sizeof(values_556_rt4[0]);
}

const __FlashStringHelper * K556RT4::menu(void) {
    return F("РТ4 (ПЗУ 256x4)");
}

const __FlashStringHelper * K556RT4::description(void) {
    return F(
"К556РТ4\r\n"
"ПЗУ емкостью 1024 бит (256x4)\r\n"
"DIP16\r\n"
"\t         16 - +5V        \r\n"
"\t          8 - GND        \r\n"
"\t      --------------      \r\n"
"\t 15 -| A0 | R0M | 1 |- 12 \r\n"
"\t  7 -| A1 |     | 2 |- 11 \r\n"
"\t  6 -| A2 |     | 3 |- 10 \r\n"
"\t  5 -| A3 |     | 4 |-  9 \r\n"
"\t  4 -| A4 |     |   |     \r\n"
"\t  3 -| A5 |     |   |     \r\n"
"\t  2 -| A6 |     |   |     \r\n"
"\t  1 -| A7 |     |   |     \r\n"
"\t     |    |     |   |     \r\n"
"\t 13 -o W  |     |   |     \r\n"
"\t 14 -o CE |     |   |     \r\n"
"\t      --------------      \r\n"
    );
};

const __FlashStringHelper * K556RT4::title(void) {
    return F("К556РТ4\r\nПЗУ 1024b(256x4)\r\nDIP16\r\n");
}
