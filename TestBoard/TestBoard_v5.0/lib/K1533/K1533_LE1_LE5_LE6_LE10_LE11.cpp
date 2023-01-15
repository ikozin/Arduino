#include "K1533_LE1_LE5_LE6_LE10_LE11.h"

const static TDevicePin pin_map_1533_le1_le5_le6_le10_le11[] =
{
  { .Input = {  2,  3,  0,  0,  0,  0,  0,  0 }, .Output = {  1,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  5,  6,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  8,  9,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 11, 12,  0,  0,  0,  0,  0,  0 }, .Output = { 13,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal values_1533_le1_le5_le6_le10_le11[] =
{
  { .value = (uint16_t)0, .result = (uint16_t)1 },
  { .value = (uint16_t)1, .result = (uint16_t)0 },
  { .value = (uint16_t)2, .result = (uint16_t)0 },
  { .value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LE1LE5LE6LE10LE11::K1533LE1LE5LE6LE10LE11(void) {
  _devices = pin_map_1533_le1_le5_le6_le10_le11;
  _values = values_1533_le1_le5_le6_le10_le11;
  _devices_count = sizeof(pin_map_1533_le1_le5_le6_le10_le11)/sizeof(pin_map_1533_le1_le5_le6_le10_le11[0]);
  _values_count = sizeof(values_1533_le1_le5_le6_le10_le11)/sizeof(values_1533_le1_le5_le6_le10_le11[0]);
}

const __FlashStringHelper * K1533LE1LE5LE6LE10LE11::menu(void) {
  return F("ЛE1 ЛE5 ЛE6 ЛE10 ЛE11 (4 элемента 2ИЛИ-HE)");
}

void K1533LE1LE5LE6LE10LE11::info(void) {
  Serial.println(F("KP1533ЛE1"));
  Serial.println(F("KP1533ЛE5  - повышеннаая нагрузка"));
  Serial.println(F("KP1533ЛE6  - повышеннаая нагрузка"));
  Serial.println(F("KP1533ЛE10 - повышеннаая нагрузка"));
  Serial.println(F("KP1533ЛE11 - повышеннаая нагрузка"));
  Serial.println(F("             открытый коллектор"));  
  Serial.println(F("4 элемента 2ИЛИ-HE"));
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
