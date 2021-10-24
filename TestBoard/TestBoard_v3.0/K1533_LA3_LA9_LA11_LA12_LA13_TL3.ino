#ifdef K1533_LA3_LA9_LA11_LA12_LA13_TL3

#include "K1533_LA3_LA9_LA11_LA12_LA13_TL3.h"

Input8Out8DevPin pin_map_1533_la3_la9_la11_la12_la13_tl3[4] =
{
  { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  4,  5,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 12, 13,  0,  0,  0,  0,  0,  0 }, .Output = { 11,  0,  0,  0,  0,  0,  0,  0 }},
};

Input8Out8DevVal values_1533_la3_la9_la11_la12_la13_tl3[4] =
{
  { { .value = 0 }, { .result = 1 } },
  { { .value = 1 }, { .result = 1 } },
  { { .value = 2 }, { .result = 1 } },
  { { .value = 3 }, { .result = 0 } },
};

K1533LA3LA9LA11LA12LA13TL3::K1533LA3LA9LA11LA12LA13TL3() {
  _devices = pin_map_1533_la3_la9_la11_la12_la13_tl3;
  _values = values_1533_la3_la9_la11_la12_la13_tl3;
  _devices_count = sizeof(pin_map_1533_la3_la9_la11_la12_la13_tl3)/sizeof(pin_map_1533_la3_la9_la11_la12_la13_tl3[0]);
  _values_count = sizeof(values_1533_la3_la9_la11_la12_la13_tl3)/sizeof(values_1533_la3_la9_la11_la12_la13_tl3[0]);
}

void K1533LA3LA9LA11LA12LA13TL3::info(void) {
  Serial.println(F("КР1533ЛА3                            "));
  Serial.println(F("КР1533ЛА9                            "));
  Serial.println(F("КР1533ЛА11 - открытый коллектор      "));
  Serial.println(F("КР1533ЛА12 - повышеннаая нагрузка    "));
  Serial.println(F("КР1533ЛА13 - открытый коллектор,     "));
  Serial.println(F("             повышеннаая нагрузка    "));
  Serial.println(F("КР1533ТЛ3  - триггер Шмитта          "));
  Serial.println(F("4 элемента 2И-НЕ                     "));
  Serial.println(F("DIP14                                "));
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (37)   1 -| &   |               "));
  Serial.println(F("               |     o- 3   (35)     "));
  Serial.println(F("     (36)   2 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (34)   4 -| &   |               "));
  Serial.println(F("               |     o- 6   (32)     "));
  Serial.println(F("     (33)   5 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (26)   9 -| &   |               "));
  Serial.println(F("               |     o- 8   (27)     "));
  Serial.println(F("     (25)   10-|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("     (23)   12-| &   |               "));
  Serial.println(F("               |     o- 11  (24)     "));
  Serial.println(F("     (22)   13-|     |               "));
  Serial.println(F("                -----                "));
  Serial.println();
}

#endif
