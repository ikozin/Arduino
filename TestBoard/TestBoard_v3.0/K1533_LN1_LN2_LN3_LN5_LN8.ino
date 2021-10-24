#ifdef K1533_LN1_LN2_LN3_LN5_LN8

#include "K1533_LN1_LN2_LN3_LN5_LN8.h"

Input8Out8DevPin pin_map_1533_ln1_ln2_ln3_ln5_ln8[6] =
{
  { .Input = {  1,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  2,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  3,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  5,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 11,  0,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 13,  0,  0,  0,  0,  0,  0,  0 }, .Output = { 12,  0,  0,  0,  0,  0,  0,  0 }},
};

Input8Out8DevVal values_1533_ln1_ln2_ln3_ln5_ln8[4] =
{
  { { .value = 0 }, { .result = 1 } },
  { { .value = 1 }, { .result = 0 } },
};

K1533LN1LN2LN3LN5LN8::K1533LN1LN2LN3LN5LN8() {
  _devices = pin_map_1533_ln1_ln2_ln3_ln5_ln8;
  _values = values_1533_ln1_ln2_ln3_ln5_ln8;  
  _devices_count = sizeof(pin_map_1533_ln1_ln2_ln3_ln5_ln8)/sizeof(pin_map_1533_ln1_ln2_ln3_ln5_ln8[0]);
  _values_count = sizeof(values_1533_ln1_ln2_ln3_ln5_ln8)/sizeof(values_1533_ln1_ln2_ln3_ln5_ln8[0]);
}

void K1533LN1LN2LN3LN5LN8::info(void) {
  Serial.println(F("КР1533ЛН1                            "));
  Serial.println(F("КР1533ЛН2  - открытый коллектор      "));
  Serial.println(F("КР1533ЛН3  - открытый коллектор      "));
  Serial.println(F("КР1533ЛН5  - открытый коллектор      "));
  Serial.println(F("КР1533ЛН8  - повышеннаая нагрузка    "));
  Serial.println(F("КР1533ТЛ2  - триггер Шмитта          "));
  Serial.println(F("6 элементов НЕ                        "));
  Serial.println(F("DIP14                                "));
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("     (37)   1 -|     o- 2   (36)     "));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("     (35)   3 -|     o- 4   (34)     "));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("     (33)   5 -|     o- 6   (32)     "));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("     (26)   9 -|     o- 8   (27)     "));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("     (24)  11 -|     o- 10  (25)     "));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("     (22)  13 -|     o- 12  (23)     "));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println();
}

#endif
