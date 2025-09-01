#include "K565_RU7.h"

///////////////////////////////////////////////////////////////////
// https://forum.defence-force.org/viewtopic.php?t=1699&start=45 //
///////////////////////////////////////////////////////////////////

const static TDevicePin PROGMEM pin_map_565_ru7[] = {
  // Входы     A0  A1  A2  A3  A4  A5  A6  A7  A8  DI RAS CAS  WE                   DO
  { .Input = {  5,  7,  6, 12, 11, 10, 13,  9,  1,  2,  4, 15,  3,  0}, .Output = { 14,  0 }},
};

K565RU7::K565RU7(void) {
    _devices = pin_map_565_ru7;
    _rows = 512;
    _cols = 512;

    _values = NULL;  
    _devices_count = 1;
    _values_count = 0;
}

const __FlashStringHelper * K565RU7::menu(void) {
    return F("PУ7 (OЗУ 256Kx1)");
}

const __FlashStringHelper * K565RU7::description(void) {
    return F(
"K565PУ7\r\n"
"OЗУ 256Kx1\r\n"
"DIP16\r\n"
"\t            8 - +5V          \r\n"
"\t           16 - GND          \r\n"
"\t      -----------------      \r\n"
"\t  2 -| DI  | RAM | DO  |- 14 \r\n"
"\t     |-----|     |     |     \r\n"
"\t  5 -| A0  |     |     |     \r\n"
"\t  7 -| A1  |     |     |     \r\n"
"\t  6 -| A2  |     |     |     \r\n"
"\t 12 -| A3  |     |     |     \r\n"
"\t 11 -| A4  |     |     |     \r\n"
"\t 10 -| A5  |     |     |     \r\n"
"\t 13 -| A6  |     |     |     \r\n"
"\t  9 -| A7  |     |     |     \r\n"
"\t  1 -| A8  |     |     |     \r\n"
"\t     |-----|     |     |     \r\n"
"\t  4 -o RAS |     |     |     \r\n"
"\t 15 -o CAS |     |     |     \r\n"
"\t  3 -o WE  |     |     |     \r\n"
"\t      -----------------      \r\n"
    );
}

const __FlashStringHelper * K565RU7::title(void) {
    return F("K565PУ7\r\nOЗУ 256Kx1\r\nDIP16\r\n");
}
