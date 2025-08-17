#include "K155_RE3.h"

const static TDevicePin PROGMEM pin_map_155_re3[] =
{
  // Входы      V  16   8   4   2   1                 8   7   6   5   4   3   2   1
  { .Input = { 15, 14, 13, 12, 11, 10 }, .Output = {  9,  7,  6,  5,  4,  3,  2,  1 }},
};

const static TDeviceVal PROGMEM values_155_re3[] =
{  
  //
  { .value = (uint16_t) 0, .result = (uint16_t)0 },
  { .value = (uint16_t) 1, .result = (uint16_t)0 },
  { .value = (uint16_t) 2, .result = (uint16_t)0 },
  { .value = (uint16_t) 3, .result = (uint16_t)0 },
  { .value = (uint16_t) 4, .result = (uint16_t)0 },
  { .value = (uint16_t) 5, .result = (uint16_t)0 },
  { .value = (uint16_t) 6, .result = (uint16_t)0 },
  { .value = (uint16_t) 7, .result = (uint16_t)0 },
  { .value = (uint16_t) 8, .result = (uint16_t)0 },
  { .value = (uint16_t) 9, .result = (uint16_t)0 },
  { .value = (uint16_t)10, .result = (uint16_t)0 },
  { .value = (uint16_t)11, .result = (uint16_t)0 },
  { .value = (uint16_t)12, .result = (uint16_t)0 },
  { .value = (uint16_t)13, .result = (uint16_t)0 },
  { .value = (uint16_t)14, .result = (uint16_t)0 },
  { .value = (uint16_t)15, .result = (uint16_t)0 },
  { .value = (uint16_t)16, .result = (uint16_t)0 },
  { .value = (uint16_t)17, .result = (uint16_t)0 },
  { .value = (uint16_t)18, .result = (uint16_t)0 },
  { .value = (uint16_t)19, .result = (uint16_t)0 },
  { .value = (uint16_t)20, .result = (uint16_t)0 },
  { .value = (uint16_t)21, .result = (uint16_t)0 },
  { .value = (uint16_t)22, .result = (uint16_t)0 },
  { .value = (uint16_t)23, .result = (uint16_t)0 },
  { .value = (uint16_t)24, .result = (uint16_t)0 },
  { .value = (uint16_t)25, .result = (uint16_t)0 },
  { .value = (uint16_t)26, .result = (uint16_t)0 },
  { .value = (uint16_t)27, .result = (uint16_t)0 },
  { .value = (uint16_t)28, .result = (uint16_t)0 },
  { .value = (uint16_t)29, .result = (uint16_t)0 },
  { .value = (uint16_t)30, .result = (uint16_t)0 },
  { .value = (uint16_t)31, .result = (uint16_t)0 },
};

K155RE3::K155RE3(void) {
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
"\t      -------------      \r\n"
"\t 10 -|  1 | RG | 1 |-  1 \r\n"
"\t 11 -|  2 |    | 2 |-  2 \r\n"
"\t 12 -|  4 |    | 3 |-  3 \r\n"
"\t 13 -|  8 |    | 4 |-  4 \r\n"
"\t 14 -| 16 |    | 5 |-  5 \r\n"
"\t     |    |    | 6 |-  6 \r\n"
"\t     |    |    | 7 |-  7 \r\n"
"\t 15 -o V  |    | 8 |-  9 \r\n"
"\t      -------------      \r\n"
    );
};


const __FlashStringHelper * K155RE3::title(void) {
  return F("К155РЕ3\r\nПЗУ 256b(32x8)\r\nDIP16\r\n");
}
