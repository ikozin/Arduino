#include "K580_VA86.h"

const static TDevicePin pin_map_580_va86_a[] =
{
  // Входы     A1  A2  A3  A4  A5  A6  A7  A8   E   T         Выходы     B1  B2  B3  B4  B5  B6  B7  B8
  { .Input = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 11,  0 }, .Output = { 19, 18, 17, 16, 15, 14, 13, 12,  0 }},
};

const static TDevicePin pin_map_580_va86_b[] =
{
  // Входы     B1  B2  B3  B4  B5  B6  B7  B8   E   T         Выходы     A1  A2  A3  A4  A5  A6  A7  A8
  { .Input = { 19, 18, 17, 16, 15, 14, 13, 12,  9, 11,  0 }, .Output = {  1,  2,  3,  4,  5,  6,  7,  8,  0 }},
};

const static TDeviceVal values_580_va86_a[17] =
{  
  { .value = (uint16_t)B_1_1_00000000, .result = (uint16_t)B11111111 },
  { .value = (uint16_t)B_1_0_00000000, .result = (uint16_t)B00000000 },
  { .value = (uint16_t)B_1_0_11111111, .result = (uint16_t)B11111111 },
  { .value = (uint16_t)B_1_0_01010101, .result = (uint16_t)B01010101 },
  { .value = (uint16_t)B_1_0_10101010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_1_0_00110011, .result = (uint16_t)B00110011 },
  { .value = (uint16_t)B_1_0_11001100, .result = (uint16_t)B11001100 },
  { .value = (uint16_t)B_1_0_00001111, .result = (uint16_t)B00001111 },
  { .value = (uint16_t)B_1_0_11110000, .result = (uint16_t)B11110000 },

  { .value = (uint16_t)B_1_0_00000001, .result = (uint16_t)B00000001 },
  { .value = (uint16_t)B_1_0_00000010, .result = (uint16_t)B00000010 },
  { .value = (uint16_t)B_1_0_00000100, .result = (uint16_t)B00000100 },
  { .value = (uint16_t)B_1_0_00001000, .result = (uint16_t)B00001000 },
  { .value = (uint16_t)B_1_0_00010000, .result = (uint16_t)B00010000 },
  { .value = (uint16_t)B_1_0_00100000, .result = (uint16_t)B00100000 },
  { .value = (uint16_t)B_1_0_01000000, .result = (uint16_t)B01000000 },
  { .value = (uint16_t)B_1_0_10000000, .result = (uint16_t)B10000000 },
  
};

const static TDeviceVal values_580_va86_b[17] =
{  
  { .value = (uint16_t)B_0_1_00000000, .result = (uint16_t)B11111111 },
  { .value = (uint16_t)B_0_0_00000000, .result = (uint16_t)B00000000 },
  { .value = (uint16_t)B_0_0_11111111, .result = (uint16_t)B11111111 },
  { .value = (uint16_t)B_0_0_01010101, .result = (uint16_t)B01010101 },
  { .value = (uint16_t)B_0_0_10101010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_00110011, .result = (uint16_t)B00110011 },
  { .value = (uint16_t)B_0_0_11001100, .result = (uint16_t)B11001100 },
  { .value = (uint16_t)B_0_0_00001111, .result = (uint16_t)B00001111 },
  { .value = (uint16_t)B_0_0_11110000, .result = (uint16_t)B11110000 },

  { .value = (uint16_t)B_0_0_00000001, .result = (uint16_t)B00000001 },
  { .value = (uint16_t)B_0_0_00000010, .result = (uint16_t)B00000010 },
  { .value = (uint16_t)B_0_0_00000100, .result = (uint16_t)B00000100 },
  { .value = (uint16_t)B_0_0_00001000, .result = (uint16_t)B00001000 },
  { .value = (uint16_t)B_0_0_00010000, .result = (uint16_t)B00010000 },
  { .value = (uint16_t)B_0_0_00100000, .result = (uint16_t)B00100000 },
  { .value = (uint16_t)B_0_0_01000000, .result = (uint16_t)B01000000 },
  { .value = (uint16_t)B_0_0_10000000, .result = (uint16_t)B10000000 },
};

const __FlashStringHelper * K580VA86::menu(void) {
  return F("BA86 (Буфер)");
}

void K580VA86::info(void) {
  Serial.println(F("KP580BA86"));
  Serial.println(F("Буфер"));
  Serial.println(F("DIP20"));
  Serial.println(F("\t         20 - +5V         "));
  Serial.println(F("\t         10 - GND         "));
  Serial.println(F("\t      --------------      "));
  Serial.println(F("\t  1 -| A1 | <> | B1 |- 19 "));
  Serial.println(F("\t  2 -| A2 |    | B2 |- 18 "));
  Serial.println(F("\t  3 -| A3 |    | B3 |- 17 "));
  Serial.println(F("\t  4 -| A4 |    | B4 |- 16 "));
  Serial.println(F("\t  5 -| A5 |    | B5 |- 15 "));
  Serial.println(F("\t  6 -| A6 |    | B6 |- 14 "));
  Serial.println(F("\t  5 -| A7 |    | B7 |- 13 "));
  Serial.println(F("\t  6 -| A8 |    | B8 |- 12 "));
  Serial.println(F("\t     |----|    |    |     "));
  Serial.println(F("\t 11 -| T  |    |    |     "));
  Serial.println(F("\t  9 -o E  |    |    |     "));
  Serial.println(F("\t      --------------      "));
  Serial.println();
}

K580VA86_SubDev sub_580_va86_dev1(pin_map_580_va86_a, values_580_va86_a, 17);
K580VA86_SubDev sub_580_va86_dev2(pin_map_580_va86_b, values_580_va86_b, 17);
TDevice * composite_580_va86[] { &sub_580_va86_dev1, &sub_580_va86_dev2 };

K580VA86::K580VA86(void): TDeviceComposite(composite_580_va86, sizeof(composite_580_va86)/sizeof(composite_580_va86[0])) {
}
