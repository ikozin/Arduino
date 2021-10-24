#ifdef K1533_TM2

#include "K1533_TM2.h"

#define B_0_0_0_0   B0000
#define B_0_0_0_1   B0001
#define B_0_0_1_0   B0010
#define B_0_0_1_1   B0011
#define B_0_1_0_0   B0100
#define B_0_1_0_1   B0101
#define B_0_1_1_0   B0110
#define B_0_1_1_1   B0111
#define B_1_0_0_0   B1000
#define B_1_0_0_1   B1001
#define B_1_0_1_0   B1010
#define B_1_0_1_1   B1011
#define B_1_1_0_0   B1100
#define B_1_1_0_1   B1101
#define B_1_1_1_0   B1110
#define B_1_1_1_1   B1111

Input8Out8DevPin pin_map_1533_tm2[2] =
{
  // Входы      R   S   D   C                     Выходы      0   1
  { .Input = {  1,  4,  2,  3,  0,  0,  0,  0 }, .Output = {  5,  6,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 13, 10, 12, 11,  0,  0,  0,  0 }, .Output = {  9,  8,  0,  0,  0,  0,  0,  0 }},
};

Input8Out8DevVal values_1533_tm2[20] =
{  
  //             C D S R
  { { .value = B_0_0_0_1 }, { .result = 1 } },
  { { .value = B_1_0_0_1 }, { .result = 1 } },
  { { .value = B_0_1_0_1 }, { .result = 1 } },
  { { .value = B_1_1_0_1 }, { .result = 1 } },
  //             C D S R
  { { .value = B_0_0_1_0 }, { .result = 2 } },
  { { .value = B_1_0_1_0 }, { .result = 2 } },
  { { .value = B_0_1_1_0 }, { .result = 2 } },
  { { .value = B_1_1_1_0 }, { .result = 2 } },
  //             C D S R
  { { .value = B_0_0_1_1 }, { .result = 2 } },
  { { .value = B_1_0_1_1 }, { .result = 2 } },
  { { .value = B_0_1_1_1 }, { .result = 2 } },
  { { .value = B_1_1_1_1 }, { .result = 1 } },
  { { .value = B_0_0_1_1 }, { .result = 1 } },
  { { .value = B_1_0_1_1 }, { .result = 2 } },
  { { .value = B_0_1_1_1 }, { .result = 2 } },
  { { .value = B_1_1_1_1 }, { .result = 1 } },
  { { .value = B_0_0_1_1 }, { .result = 1 } },
  { { .value = B_1_0_1_1 }, { .result = 2 } },
  { { .value = B_0_1_1_1 }, { .result = 2 } },
  { { .value = B_1_1_1_1 }, { .result = 1 } },
};


K1533TM2::K1533TM2() {
  _devices = pin_map_1533_tm2;
  _values = values_1533_tm2;  
  _devices_count = sizeof(pin_map_1533_tm2)/sizeof(pin_map_1533_tm2[0]);
  _values_count = sizeof(values_1533_tm2)/sizeof(values_1533_tm2[0]);
}

void K1533TM2::info(void) {
  Serial.println(F("КР1533ТМ2                             "));
  Serial.println(F("2 D-триггера                          "));
  Serial.println(F("DIP14                                 "));
  Serial.println(F("               14 - +5V               "));
  Serial.println(F("                7 - GND               "));
  Serial.println(F("                --------              "));
  Serial.println(F("    (37)    1 -o R | TT |- 5  (33)    "));
  Serial.println(F("               |---|    |             "));
  Serial.println(F("    (36)    2 -| D |    |             "));
  Serial.println(F("    (35)    3 -/ С |    |             "));
  Serial.println(F("               |---|    |             "));
  Serial.println(F("    (34)    4 -o S |    o- 6  (32)    "));
  Serial.println(F("                --------              "));
  Serial.println(F("                --------              "));
  Serial.println(F("    (22)   13 -o R | TT |- 9  (26)    "));
  Serial.println(F("               |---|    |             "));
  Serial.println(F("    (23)   12 -| D |    |             "));
  Serial.println(F("    (24)   11 -/ С |    |             "));
  Serial.println(F("               |---|    |             "));
  Serial.println(F("    (25)   10 -o S |    o- 8  (27)    "));
  Serial.println(F("                --------              "));
  Serial.println();
}

#endif
