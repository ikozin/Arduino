#ifdef K1533_AP6

#include "K1533_AP6.h"

TDevicePin pin_map_1533_ap6_a[] =
{
  // Входы     A1  A2  A3  A4  A5  A6  A7  A8   E   T         Выходы     B1  B2  B3  B4  B5  B6  B7  B8
  { .Input = {  2,  3,  4,  5,  6,  7,  8,  9, 19,  1,  0 }, .Output = { 18, 17, 16, 15, 14, 13, 12, 11,  0 }},
};

TDevicePin pin_map_1533_ap6_b[] =
{
  // Входы     B1  B2  B3  B4  B5  B6  B7  B8   E   T         Выходы     A1  A2  A3  A4  A5  A6  A7  A8
  { .Input = { 18, 17, 16, 15, 14, 13, 12, 11, 19,  1,  0 }, .Output = {  2,  3,  4,  5,  6,  7,  8,  9,  0 }},
};

TDeviceVal values_1533_ap6_a[17] =
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

TDeviceVal values_1533_ap6_b[17] =
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

void K1533AP6::info(void) {
  Serial.println(F("КР1533АП6"));
  Serial.println(F("Буфер"));
  Serial.println(F("DIP20"));
  Serial.println(F("\t         20 - +5V         "));
  Serial.println(F("\t         10 - GND         "));
  Serial.println(F("\t      --------------      "));
  Serial.println(F("\t  2 -| A1 | <> | B1 |- 18 "));
  Serial.println(F("\t  3 -| A2 |    | B2 |- 17 "));
  Serial.println(F("\t  4 -| A3 |    | B3 |- 16 "));
  Serial.println(F("\t  5 -| A4 |    | B4 |- 15 "));
  Serial.println(F("\t  6 -| A5 |    | B5 |- 14 "));
  Serial.println(F("\t  7 -| A6 |    | B6 |- 13 "));
  Serial.println(F("\t  8 -| A7 |    | B7 |- 12 "));
  Serial.println(F("\t  9 -| A8 |    | B8 |- 11 "));
  Serial.println(F("\t     |----|    |    |     "));
  Serial.println(F("\t  1 -| T  |    |    |     "));
  Serial.println(F("\t 19 -o E  |    |    |     "));
  Serial.println(F("\t      --------------      "));
  Serial.println();
}

K1533AP6_SubDev sub_1533_ap6_dev1(pin_map_1533_ap6_a, values_1533_ap6_a, 17);
K1533AP6_SubDev sub_1533_ap6_dev2(pin_map_1533_ap6_b, values_1533_ap6_b, 17);
TDevice * composite_1533_ap6[] { &sub_1533_ap6_dev1, &sub_1533_ap6_dev2 };
K1533AP6::K1533AP6(): TDeviceComposite(composite_1533_ap6, sizeof(composite_1533_ap6)/sizeof(composite_1533_ap6[0])) {}

#endif
