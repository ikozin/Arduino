#include "K1533_LA1_LA6_LA7_LA22.h"

const static TDevicePin PROGMEM pin_map_1533_la1_la6_la7_la22[] =
{
  { .Input = {  1,  2,  4,  5,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10, 12, 13,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_la1_la6_la7_la22[] =
{
  { .value = (uint16_t) 0, .result = (uint16_t)1 },
  { .value = (uint16_t) 1, .result = (uint16_t)1 },
  { .value = (uint16_t) 2, .result = (uint16_t)1 },
  { .value = (uint16_t) 3, .result = (uint16_t)1 },
  { .value = (uint16_t) 4, .result = (uint16_t)1 },
  { .value = (uint16_t) 5, .result = (uint16_t)1 },
  { .value = (uint16_t) 6, .result = (uint16_t)1 },
  { .value = (uint16_t) 7, .result = (uint16_t)1 },
  { .value = (uint16_t) 8, .result = (uint16_t)1 },
  { .value = (uint16_t) 9, .result = (uint16_t)1 },
  { .value = (uint16_t)10, .result = (uint16_t)1 },
  { .value = (uint16_t)11, .result = (uint16_t)1 },
  { .value = (uint16_t)12, .result = (uint16_t)1 },
  { .value = (uint16_t)13, .result = (uint16_t)1 },
  { .value = (uint16_t)14, .result = (uint16_t)1 },
  { .value = (uint16_t)15, .result = (uint16_t)0 },
};

K1533LA1LA6LA7LA22::K1533LA1LA6LA7LA22(void) {
  _devices = pin_map_1533_la1_la6_la7_la22;
  _values = values_1533_la1_la6_la7_la22;
  _devices_count = sizeof(pin_map_1533_la1_la6_la7_la22)/sizeof(pin_map_1533_la1_la6_la7_la22[0]);
  _values_count = sizeof(values_1533_la1_la6_la7_la22)/sizeof(values_1533_la1_la6_la7_la22[0]);
}

const __FlashStringHelper * K1533LA1LA6LA7LA22::menu(void) {
  return F("ЛA1,6,7,22 (4И-HE)");
}

const __FlashStringHelper * K1533LA1LA6LA7LA22::description(void) {
    return F(
"KP1533ЛA1\r\n"
"KP1533ЛA6  - повышеннаая нагрузка\r\n"
"KP1533ЛA7  - открытый коллектор\r\n"
"KP1533ЛA22 - повышеннаая нагрузка\r\n"
"2 элемента 4И-HE\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  1 -| &   |     \r\n"
"\t     |     |     \r\n"
"\t  2 -|     |     \r\n"
"\t     |     o- 6  \r\n"
"\t  4 -|     |     \r\n"
"\t     |     |     \r\n"
"\t  5 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  9 -| &   |     \r\n"
"\t     |     |     \r\n"
"\t  10-|     |     \r\n"
"\t     |     o- 8  \r\n"
"\t  12-|     |     \r\n"
"\t     |     |     \r\n"
"\t  13-|     |     \r\n"
"\t      -----      \r\n"
    );
}

const __FlashStringHelper * K1533LA1LA6LA7LA22::title(void) {
  return F("KP1533ЛA1 ЛA6 ЛA7\r\nKP1533ЛA22\r\n2 элемента 4И-HE\r\nDIP14\r\n");
}
