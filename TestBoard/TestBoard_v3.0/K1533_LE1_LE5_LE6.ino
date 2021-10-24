#ifdef K1533_LE1_LE5_LE6

#include "K1533_LE1_LE5_LE6.h"

Input8Out8DevPin pin_map_1533_le1_le5_le6[4] =
{
  { .Input = {  2,  3,  0,  0,  0,  0,  0,  0 }, .Output = {  1,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  5,  6,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  8,  9,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 11, 12,  0,  0,  0,  0,  0,  0 }, .Output = { 13,  0,  0,  0,  0,  0,  0,  0 }},
};

Input8Out8DevVal values_1533_le1_le5_le6[4] =
{
  { { .value = 0 }, { .result = 1 } },
  { { .value = 1 }, { .result = 0 } },
  { { .value = 2 }, { .result = 0 } },
  { { .value = 3 }, { .result = 0 } },
};

K1533LE1LE5LE6::K1533LE1LE5LE6() {
  _devices = pin_map_1533_le1_le5_le6;
  _values = values_1533_le1_le5_le6;
  _devices_count = sizeof(pin_map_1533_le1_le5_le6)/sizeof(pin_map_1533_le1_le5_le6[0]);
  _values_count = sizeof(values_1533_le1_le5_le6)/sizeof(values_1533_le1_le5_le6[0]);
}

void K1533LE1LE5LE6::info(void) {
  Serial.println(F("КР1533ЛЕ1                         "));
  Serial.println(F("КР1533ЛЕ5  - повышеннаая нагрузка "));
  Serial.println(F("КР1533ЛЕ6  - повышеннаая нагрузка "));
  Serial.println(F("4 элемента 2ИЛИ-НЕ                "));
  Serial.println(F("DIP14                             "));
  Serial.println(F("              14 - +5V            "));
  Serial.println(F("               7 - GND            "));
  Serial.println(F("                -----             "));
  Serial.println(F("            2 -| 1   |            "));
  Serial.println(F("               |     o- 1         "));
  Serial.println(F("            3 -|     |            "));
  Serial.println(F("                -----             "));
  Serial.println(F("                -----             "));
  Serial.println(F("            5 -| 1   |            "));
  Serial.println(F("               |     o- 4         "));
  Serial.println(F("            6 -|     |            "));
  Serial.println(F("                -----             "));
  Serial.println(F("                -----             "));
  Serial.println(F("            8 -| 1   |            "));
  Serial.println(F("               |     o- 10        "));
  Serial.println(F("            9 -|     |            "));
  Serial.println(F("                -----             "));
  Serial.println(F("                -----             "));
  Serial.println(F("            11-| 1   |            "));
  Serial.println(F("               |     o- 13        "));
  Serial.println(F("            12-|     |            "));
  Serial.println(F("                -----             "));
  Serial.println();
}

#endif
