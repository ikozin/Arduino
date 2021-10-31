#ifdef K1533_LA4_LA10_LA24

#include "K1533_LA4_LA10_LA24.h"

TDevicePin pin_map_1533_la4_la10_la24[] =
{
  { .Input = {  1,  2, 13,  0,  0,  0,  0,  0 }, .Output = { 12,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  3,  4,  5,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10, 11,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
};

TDeviceVal values_1533_la4_la10_la24[] =
{
  { .value = (uint16_t) 0, .result = (uint16_t)1 },
  { .value = (uint16_t) 1, .result = (uint16_t)1 },
  { .value = (uint16_t) 2, .result = (uint16_t)1 },
  { .value = (uint16_t) 3, .result = (uint16_t)1 },
  { .value = (uint16_t) 4, .result = (uint16_t)1 },
  { .value = (uint16_t) 5, .result = (uint16_t)1 },
  { .value = (uint16_t) 6, .result = (uint16_t)1 },
  { .value = (uint16_t) 7, .result = (uint16_t)0 },
};

K1533LA4LA10LA24::K1533LA4LA10LA24() {
  _devices = pin_map_1533_la4_la10_la24;
  _values = values_1533_la4_la10_la24;
  _devices_count = sizeof(pin_map_1533_la4_la10_la24)/sizeof(pin_map_1533_la4_la10_la24[0]);
  _values_count = sizeof(values_1533_la4_la10_la24)/sizeof(values_1533_la4_la10_la24[0]);
}

void K1533LA4LA10LA24::info(void) {
  Serial.println(F("КР1533ЛА4"));
  Serial.println(F("КР1533ЛА10  - открытый коллектор"));
  Serial.println(F("КР1533ЛА24  - повышеннаая нагрузка"));
  Serial.println(F("3 элемента 3И-НЕ   "));
  Serial.println(F("DIP14              "));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  1 -| &   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  2 -|     o- 12  "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t 13 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  3 -| &   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  4 -|     o- 6   "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  5 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  9 -| &   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t 10 -|     o- 8   "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t 11 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}

#endif
