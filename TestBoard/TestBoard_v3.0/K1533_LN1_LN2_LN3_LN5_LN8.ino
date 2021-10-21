#ifdef K1533_LN1_LN2_LN3_LN5_LN8
#include "Input8Out8Device.h"

Input8Out8DevPin pin_map_1533_ln1_ln2_ln3_ln5_ln8[6] =
{
  { .Input = { 37, 0, 0, 0, 0, 0, 0, 0 }, .Output = { 36, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 35, 0, 0, 0, 0, 0, 0, 0 }, .Output = { 34, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 33, 0, 0, 0, 0, 0, 0, 0 }, .Output = { 32, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 26, 0, 0, 0, 0, 0, 0, 0 }, .Output = { 27, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 24, 0, 0, 0, 0, 0, 0, 0 }, .Output = { 25, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 22, 0, 0, 0, 0, 0, 0, 0 }, .Output = { 23, 0, 0, 0, 0, 0, 0, 0 }},
};

Input8Out8DevVal values_1533_ln1_ln2_ln3_ln5_ln8[4] =
{
  { { .value = 0 }, { .result = 1 } },
  { { .value = 1 }, { .result = 0 } },
};

void info_1533_ln1_ln2_ln3_ln5_ln8(void) {
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

bool test_1533_ln1_ln2_ln3_ln5_ln8() {
  info_1533_ln1_ln2_ln3_ln5_ln8();
  init_Input8Out8Dev(pin_map_1533_ln1_ln2_ln3_ln5_ln8, 6);
  int result = check_Input8Out8Dev(pin_map_1533_ln1_ln2_ln3_ln5_ln8, 6, values_1533_ln1_ln2_ln3_ln5_ln8, 2);
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
