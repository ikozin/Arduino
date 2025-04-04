#include "K580_VA86.h"

const static TDevicePin PROGMEM pin_map_580_va86_a[] =
{
  // Входы     A1  A2  A3  A4  A5  A6  A7  A8   E   T         Выходы     B1  B2  B3  B4  B5  B6  B7  B8
  { .Input = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 11,  0 }, .Output = { 19, 18, 17, 16, 15, 14, 13, 12,  0 }},
};

const static TDevicePin PROGMEM pin_map_580_va86_b[] =
{
  // Входы     B1  B2  B3  B4  B5  B6  B7  B8   E   T         Выходы     A1  A2  A3  A4  A5  A6  A7  A8
  { .Input = { 19, 18, 17, 16, 15, 14, 13, 12,  9, 11,  0 }, .Output = {  1,  2,  3,  4,  5,  6,  7,  8,  0 }},
};

const static TDeviceVal PROGMEM values_580_va86_a[17] =
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

const static TDeviceVal PROGMEM values_580_va86_b[17] =
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

const __FlashStringHelper * K580VA86::description(void) {
    return F(
"KP580BA86\r\n"
"Буфер\r\n"
"DIP20\r\n"
"\t         20 - +5V         \r\n"
"\t         10 - GND         \r\n"
"\t      --------------      \r\n"
"\t  1 -| A1 | <> | B1 |- 19 \r\n"
"\t  2 -| A2 |    | B2 |- 18 \r\n"
"\t  3 -| A3 |    | B3 |- 17 \r\n"
"\t  4 -| A4 |    | B4 |- 16 \r\n"
"\t  5 -| A5 |    | B5 |- 15 \r\n"
"\t  6 -| A6 |    | B6 |- 14 \r\n"
"\t  5 -| A7 |    | B7 |- 13 \r\n"
"\t  6 -| A8 |    | B8 |- 12 \r\n"
"\t     |----|    |    |     \r\n"
"\t 11 -| T  |    |    |     \r\n"
"\t  9 -o E  |    |    |     \r\n"
"\t      --------------      \r\n"
    );
}

const __FlashStringHelper * K580VA86::title(void) {
  return F("KP580BA86\r\nБуфер\r\nDIP20\r\n");
}

K580VA86_SubDev sub_580_va86_dev1(pin_map_580_va86_a, values_580_va86_a, 17);
K580VA86_SubDev sub_580_va86_dev2(pin_map_580_va86_b, values_580_va86_b, 17);
TDevice * composite_580_va86[] { &sub_580_va86_dev1, &sub_580_va86_dev2 };

K580VA86::K580VA86(void): TDeviceComposite(composite_580_va86, sizeof(composite_580_va86)/sizeof(composite_580_va86[0])) {
}
