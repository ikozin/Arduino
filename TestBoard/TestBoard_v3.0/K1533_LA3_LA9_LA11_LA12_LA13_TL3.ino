#ifdef K1533_LA3_LA9_LA11_LA12_LA13_TL3
#include "Input8Out1Device.h"

Input8Out1DevPin pin_map_1533_la3_la9_la11_la12_la13_tl3[4] =
{
  { {37, 36, 0, 0, 0, 0, 0, 0 }, 35},
  { {34, 33, 0, 0, 0, 0, 0, 0 }, 32},
  { {26, 25, 0, 0, 0, 0, 0, 0 }, 27},
  { {23, 22, 0, 0, 0, 0, 0, 0 }, 24},
};

Input8Out1DevVal values_1533_la3_la9_la11_la12_la13_tl3[4] =
{
  { { .value = 0 }, .Result = 1 },
  { { .value = 1 }, .Result = 1 },
  { { .value = 2 }, .Result = 1 },
  { { .value = 3 }, .Result = 0 },
};

void info_1533_la3_la9_la11_la12_la13_tl3(void) {
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

void test_1533_la3_la9_la11_la12_la13_tl3(void) {
  info_1533_la3_la9_la11_la12_la13_tl3();
  init_Input8Out1Dev(pin_map_1533_la3_la9_la11_la12_la13_tl3, 4);
  int result = check_Input8Out1Dev(pin_map_1533_la3_la9_la11_la12_la13_tl3, 4, values_1533_la3_la9_la11_la12_la13_tl3, 4);
  if (result == 0) {
    Serial.println(F("\nТЕСТ ПРОЙДЕН"));
  }
  else {
    Serial.println(F("\n!!! ОШИБКА !!!"));
    Serial.print(F("Кол-во ошибок = "));
    Serial.println(result);
  }
  done_Input8Out1Dev();
}

#endif
