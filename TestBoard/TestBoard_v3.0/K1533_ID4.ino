#ifdef K1533_ID4
#include "Input8Out8Device.h"

#define B_00_00   0
#define B_00_01   1
#define B_00_10   2
#define B_00_11   3
#define B_01_00   4
#define B_01_01   5
#define B_01_10   6
#define B_01_11   7
#define B_10_00   8
#define B_10_01   9
#define B_10_10   10
#define B_10_11   11
#define B_11_00   12
#define B_11_01   13
#define B_11_10   14
#define B_11_11   15

#define B_1110    14
#define B_1101    13
#define B_1011    11
#define B_0111    7
#define B_1111    15

Input8Out8DevPin pin_map_1533_id4[2] =
{
  // Входы      1   2   &   &                 Выходы      0   1   2   3
  { .Input = { 24, 35, 23, 22, 0, 0, 0, 0 }, .Output = { 28, 27, 26, 25, 0, 0, 0, 0 }},
  { .Input = { 37, 36, 23, 22, 0, 0, 0, 0 }, .Output = { 31, 32, 33, 34, 0, 0, 0, 0 }},
};

Input8Out8DevVal values_1533_id4[16] =
{  
  { { .value = B_00_00 }, { .result = B_1110 } },
  { { .value = B_00_01 }, { .result = B_1101 } },
  { { .value = B_00_10 }, { .result = B_1011 } },
  { { .value = B_00_11 }, { .result = B_0111 } },
  { { .value = B_01_00 }, { .result = B_1111 } },
  { { .value = B_01_01 }, { .result = B_1111 } },
  { { .value = B_01_10 }, { .result = B_1111 } },
  { { .value = B_01_11 }, { .result = B_1111 } },
  { { .value = B_10_00 }, { .result = B_1111 } },
  { { .value = B_10_01 }, { .result = B_1111 } },
  { { .value = B_10_10 }, { .result = B_1111 } },
  { { .value = B_10_11 }, { .result = B_1111 } },
  { { .value = B_11_00 }, { .result = B_1111 } },
  { { .value = B_11_01 }, { .result = B_1111 } },
  { { .value = B_11_10 }, { .result = B_1111 } },
  { { .value = B_11_11 }, { .result = B_1111 } },
};

void info_1533_id4(void) {
  Serial.println(F("КР1533ИД4                              "));
  Serial.println(F("Два дешифратора                        "));
  Serial.println(F("DIP16                                  "));
  Serial.println(F("                 16 - +5V              "));
  Serial.println(F("                  8 - GND              "));
  Serial.println(F("              --------------           "));
  Serial.println(F("    (23) 14 -o &  | DC |  0 o- 9  (28) "));
  Serial.println(F("    (22) 15 -o S0 |    |  1 o-10  (27) "));
  Serial.println(F("             |----|    |  2 o-11  (26) "));
  Serial.println(F("    (24) 13 -| 1  |    |  3 o-12  (25) "));
  Serial.println(F("    (35)  3 -| 2  |    |----|          "));
  Serial.println(F("             |----|    |  0 o- 7  (31) "));
  Serial.println(F("    (37)  1 -o &  |    |  1 o- 6  (32) "));
  Serial.println(F("    (36)  2 -o S1 |    |  2 o- 5  (33) "));
  Serial.println(F("             |    |    |  3 o- 4  (34) "));
  Serial.println(F("              --------------           "));
  Serial.println();
}

void test_1533_id4() {
  info_1533_id4();
  init_Input8Out8Dev(pin_map_1533_id4, 2);
  int result = check_Input8Out8Dev(pin_map_1533_id4, 2, values_1533_id4, 16);
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
