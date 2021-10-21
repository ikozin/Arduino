#ifdef K1533_LA3_LI1_LI2
#include "Input8Out8Device.h"

Input8Out8DevPin pin_map_1533_li1_li2[4] =
{
  { .Input = { 37, 36, 0, 0, 0, 0, 0, 0 }, .Output = { 35, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 34, 33, 0, 0, 0, 0, 0, 0 }, .Output = { 32, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 26, 25, 0, 0, 0, 0, 0, 0 }, .Output = { 27, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 23, 22, 0, 0, 0, 0, 0, 0 }, .Output = { 24, 0, 0, 0, 0, 0, 0, 0 }},
};

Input8Out8DevVal values_1533_li1_li2[4] =
{
  { { .value = 0 }, { .result = 0 } },
  { { .value = 1 }, { .result = 0 } },
  { { .value = 2 }, { .result = 0 } },
  { { .value = 3 }, { .result = 1 } },
};

void info_1533_li1_li2(void) {
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

void test_1533_li1_li2(void) {
  info_1533_li1_li2();
  init_Input8Out8Dev(pin_map_1533_li1_li2, 4);
  int result = check_Input8Out8Dev(pin_map_1533_li1_li2, 4, values_1533_li1_li2, 4);
  if (result == 0) {
    Serial.println(F("\nТЕСТ ПРОЙДЕН"));
  }
  else {
    Serial.println(F("\n!!! ОШИБКА !!!"));
    Serial.print(F("Кол-во ошибок = "));
    Serial.println(result);
  }
  done_Input8Out8Dev();
}
#endif
