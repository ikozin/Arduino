#ifdef K1533_LE1_LE5_LE6_LE10_LE11

#include "K1533_LE1_LE5_LE6_LE10_LE11.h"

TDevicePin pin_map_1533_le1_le5_le6_le10_le11[] =
{
  { .Input = {  2,  3,  0,  0,  0,  0,  0,  0 }, .Output = {  1,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  5,  6,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  8,  9,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 11, 12,  0,  0,  0,  0,  0,  0 }, .Output = { 13,  0,  0,  0,  0,  0,  0,  0 }},
};

TDeviceVal values_1533_le1_le5_le6_le10_le11[] =
{
  { .value = (uint16_t)0, .result = (uint16_t)1 },
  { .value = (uint16_t)1, .result = (uint16_t)0 },
  { .value = (uint16_t)2, .result = (uint16_t)0 },
  { .value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LE1LE5LE6LE10LE11::K1533LE1LE5LE6LE10LE11() {
  _devices = pin_map_1533_le1_le5_le6_le10_le11;
  _values = values_1533_le1_le5_le6_le10_le11;
  _devices_count = sizeof(pin_map_1533_le1_le5_le6_le10_le11)/sizeof(pin_map_1533_le1_le5_le6_le10_le11[0]);
  _values_count = sizeof(values_1533_le1_le5_le6_le10_le11)/sizeof(values_1533_le1_le5_le6_le10_le11[0]);
}

void K1533LE1LE5LE6LE10LE11::info(void) {
  Serial.println(F("КР1533ЛЕ1"));
  Serial.println(F("КР1533ЛЕ5  - повышеннаая нагрузка"));
  Serial.println(F("КР1533ЛЕ6  - повышеннаая нагрузка"));
  Serial.println(F("КР1533ЛЕ10 - повышеннаая нагрузка"));
  Serial.println(F("КР1533ЛЕ11 - повышеннаая нагрузка"));
  Serial.println(F("             открытый коллектор"));  
  Serial.println(F("4 элемента 2ИЛИ-НЕ"));
  Serial.println(F("DIP14"));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  2 -| 1   |     "));
  Serial.println(F("\t     |     o- 1  "));
  Serial.println(F("\t  3 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  5 -| 1   |     "));
  Serial.println(F("\t     |     o- 4  "));
  Serial.println(F("\t  6 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  8 -| 1   |     "));
  Serial.println(F("\t     |     o- 10 "));
  Serial.println(F("\t  9 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  11-| 1   |     "));
  Serial.println(F("\t     |     o- 13 "));
  Serial.println(F("\t  12-|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}

#endif
