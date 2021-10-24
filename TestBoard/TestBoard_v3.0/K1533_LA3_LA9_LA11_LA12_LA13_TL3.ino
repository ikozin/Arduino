#ifdef K1533_LA3_LA9_LA11_LA12_LA13_TL3

#include "K1533_LA3_LA9_LA11_LA12_LA13_TL3.h"

TDevicePin pin_map_1533_la3_la9_la11_la12_la13_tl3[4] =
{
  { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  4,  5,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 12, 13,  0,  0,  0,  0,  0,  0 }, .Output = { 11,  0,  0,  0,  0,  0,  0,  0 }},
};

TDeviceVal values_1533_la3_la9_la11_la12_la13_tl3[4] =
{
  { .value = (uint16_t)0, .result = (uint16_t)1 },
  { .value = (uint16_t)1, .result = (uint16_t)1 },
  { .value = (uint16_t)2, .result = (uint16_t)1 },
  { .value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LA3LA9LA11LA12LA13TL3::K1533LA3LA9LA11LA12LA13TL3() {
  _devices = pin_map_1533_la3_la9_la11_la12_la13_tl3;
  _values = values_1533_la3_la9_la11_la12_la13_tl3;
  _devices_count = sizeof(pin_map_1533_la3_la9_la11_la12_la13_tl3)/sizeof(pin_map_1533_la3_la9_la11_la12_la13_tl3[0]);
  _values_count = sizeof(values_1533_la3_la9_la11_la12_la13_tl3)/sizeof(values_1533_la3_la9_la11_la12_la13_tl3[0]);
}

void K1533LA3LA9LA11LA12LA13TL3::info(void) {
  Serial.println(F("КР1533ЛА3"));
  Serial.println(F("КР1533ЛА9"));
  Serial.println(F("КР1533ЛА11 - открытый коллектор"));
  Serial.println(F("КР1533ЛА12 - повышеннаая нагрузка"));
  Serial.println(F("КР1533ЛА13 - открытый коллектор,"));
  Serial.println(F("             повышеннаая нагрузка"));
  Serial.println(F("КР1533ТЛ3  - триггер Шмитта"));
  Serial.println(F("4 элемента 2И-НЕ   "));
  Serial.println(F("DIP14              "));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  1 -| &   |     "));
  Serial.println(F("\t     |     o- 3  "));
  Serial.println(F("\t  2 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  4 -| &   |     "));
  Serial.println(F("\t     |     o- 6  "));
  Serial.println(F("\t  5 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  9 -| &   |     "));
  Serial.println(F("\t     |     o- 8  "));
  Serial.println(F("\t  10-|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  12-| &   |     "));
  Serial.println(F("\t     |     o- 11 "));
  Serial.println(F("\t  13-|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}

#endif
