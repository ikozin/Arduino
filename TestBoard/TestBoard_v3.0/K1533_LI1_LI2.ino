#ifdef K1533_LI1_LI2

#include "K1533_LI1_LI2.h"

Input16Out16DevPin pin_map_1533_li1_li2[4] =
{
  { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  4,  5,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 12, 13,  0,  0,  0,  0,  0,  0 }, .Output = { 11,  0,  0,  0,  0,  0,  0,  0 }},
};

Input16Out16DevVal values_1533_li1_li2[4] =
{
  { .value = (uint16_t)0, .result = (uint16_t)0 },
  { .value = (uint16_t)1, .result = (uint16_t)0 },
  { .value = (uint16_t)2, .result = (uint16_t)0 },
  { .value = (uint16_t)3, .result = (uint16_t)1 },
};

K1533LI1LI2::K1533LI1LI2(){
  _devices = pin_map_1533_li1_li2;
  _values = values_1533_li1_li2;
  _devices_count = sizeof(pin_map_1533_li1_li2)/sizeof(pin_map_1533_li1_li2[0]);
  _values_count = sizeof(values_1533_li1_li2)/sizeof(values_1533_li1_li2[0]);
}

void K1533LI1LI2::info(void) {
  Serial.println(F("КР1533ЛИ1"));
  Serial.println(F("КР1533ЛИ2  - открытый коллектор"));
  Serial.println(F("4 элемента 2И"));
  Serial.println(F("DIP14"));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  1 -| &   |     "));
  Serial.println(F("\t     |     |- 3  "));
  Serial.println(F("\t  2 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  4 -| &   |     "));
  Serial.println(F("\t     |     |- 6  "));
  Serial.println(F("\t  5 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  9 -| &   |     "));
  Serial.println(F("\t     |     |- 8  "));
  Serial.println(F("\t  10-|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  12-| &   |     "));
  Serial.println(F("\t     |     |- 11 "));
  Serial.println(F("\t  13-|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}

#endif
