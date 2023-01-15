#include "K1533_LA1_LA6_LA7_LA22.h"

const static TDevicePin pin_map_1533_la1_la6_la7_la22[] =
{
  { .Input = {  1,  2,  4,  5,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10, 12, 13,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal values_1533_la1_la6_la7_la22[] =
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
  return F("ЛA1 ЛA6 ЛA7 ЛA22 (2 элемента 4И-HE)");
}

void K1533LA1LA6LA7LA22::info(void) {
  Serial.println(F("KP1533ЛA1"));
  Serial.println(F("KP1533ЛA6  - повышеннаая нагрузка"));
  Serial.println(F("KP1533ЛA7  - открытый коллектор"));
  Serial.println(F("KP1533ЛA22 - повышеннаая нагрузка"));
  Serial.println(F("2 элемента 4И-HE   "));
  Serial.println(F("DIP14              "));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  1 -| &   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  2 -|     |     "));
  Serial.println(F("\t     |     o- 6  "));
  Serial.println(F("\t  4 -|     |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  5 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  9 -| &   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  10-|     |     "));
  Serial.println(F("\t     |     o- 8  "));
  Serial.println(F("\t  12-|     |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  13-|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}
