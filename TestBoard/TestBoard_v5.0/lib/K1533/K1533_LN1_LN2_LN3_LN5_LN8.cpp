#include "K1533_LN1_LN2_LN3_LN5_LN8.h"

const static TDevicePin pin_map_1533_ln1_ln2_ln3_ln5_ln8[] =
{
  { .Input = {  1,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  2,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  3,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  5,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 11,  0,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 13,  0,  0,  0,  0,  0,  0,  0 }, .Output = { 12,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal values_1533_ln1_ln2_ln3_ln5_ln8[] =
{
  { .value = (uint16_t)0, .result = (uint16_t)1 },
  { .value = (uint16_t)1, .result = (uint16_t)0 },
};

K1533LN1LN2LN3LN5LN8::K1533LN1LN2LN3LN5LN8(void) {
  _devices = pin_map_1533_ln1_ln2_ln3_ln5_ln8;
  _values = values_1533_ln1_ln2_ln3_ln5_ln8;  
  _devices_count = sizeof(pin_map_1533_ln1_ln2_ln3_ln5_ln8)/sizeof(pin_map_1533_ln1_ln2_ln3_ln5_ln8[0]);
  _values_count = sizeof(values_1533_ln1_ln2_ln3_ln5_ln8)/sizeof(values_1533_ln1_ln2_ln3_ln5_ln8[0]);
}

const __FlashStringHelper * K1533LN1LN2LN3LN5LN8::menu(void) {
  return F("ЛH1 ЛH2 ЛH3 ЛH5 ЛH8 (6 элементов HE)");
}

void K1533LN1LN2LN3LN5LN8::info(void) {
  Serial.println(F("KP1533ЛH1"));
  Serial.println(F("KP1533ЛH2  - открытый коллектор"));
  Serial.println(F("KP1533ЛH3  - открытый коллектор"));
  Serial.println(F("KP1533ЛH5  - открытый коллектор"));
  Serial.println(F("KP1533ЛH8  - повышеннаая нагрузка"));
  Serial.println(F("KP1533TЛ2  - триггер Шмитта"));
  Serial.println(F("6 элементов HE"));
  Serial.println(F("DIP14"));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t     | 1   |     "));
  Serial.println(F("\t  1 -|     o- 2  "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t     | 1   |     "));
  Serial.println(F("\t  3 -|     o- 4  "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t     | 1   |     "));
  Serial.println(F("\t  5 -|     o- 6  "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t     | 1   |     "));
  Serial.println(F("\t  9 -|     o- 8  "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t     | 1   |     "));
  Serial.println(F("\t 11 -|     o- 10 "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t     | 1   |     "));
  Serial.println(F("\t 13 -|     o- 12 "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}
