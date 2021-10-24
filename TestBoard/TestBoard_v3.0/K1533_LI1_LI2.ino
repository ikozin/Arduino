#ifdef K1533_LI1_LI2

#include "K1533_LI1_LI2.h"

Input8Out8DevPin pin_map_1533_li1_li2[4] =
{
  { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  4,  5,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 12, 13,  0,  0,  0,  0,  0,  0 }, .Output = { 11,  0,  0,  0,  0,  0,  0,  0 }},
};

Input8Out8DevVal values_1533_li1_li2[4] =
{
  { { .value = 0 }, { .result = 0 } },
  { { .value = 1 }, { .result = 0 } },
  { { .value = 2 }, { .result = 0 } },
  { { .value = 3 }, { .result = 1 } },
};

K1533LI1LI2::K1533LI1LI2(){
  _devices = pin_map_1533_li1_li2;
  _values = values_1533_li1_li2;
  _devices_count = sizeof(pin_map_1533_li1_li2)/sizeof(pin_map_1533_li1_li2[0]);
  _values_count = sizeof(values_1533_li1_li2)/sizeof(values_1533_li1_li2[0]);
}

void K1533LI1LI2::info(void) {
  Serial.println(F("КР1533ЛИ1                            "));
  Serial.println(F("КР1533ЛИ2  - открытый коллектор      "));
  Serial.println(F("4 элемента 2И                        "));
  Serial.println(F("DIP14                                "));
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (37)   1 -| &   |               "));
  Serial.println(F("               |     |- 3   (35)     "));
  Serial.println(F("     (36)   2 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (34)   4 -| &   |               "));
  Serial.println(F("               |     |- 6   (32)     "));
  Serial.println(F("     (33)   5 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (26)   9 -| &   |               "));
  Serial.println(F("               |     |- 8   (27)     "));
  Serial.println(F("     (25)   10-|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (23)   12-| &   |               "));
  Serial.println(F("               |     |- 11  (24)     "));
  Serial.println(F("     (22)   13-|     |               "));
  Serial.println(F("                -----                "));
  Serial.println();
}

#endif
