#include "K1533_KP2.h"

const static TDevicePin pin_map_1533_kp2[] =
{
  // Входы     D0  D1  D2  D3   S   1   2
  { .Input = {  6,  5,  4,  3,  1, 14,  2,  0 }, .Output = {  7,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 10, 11, 12, 13, 15, 14,  2,  0 }, .Output = {  9,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal values_1533_kp2[] =
{	
  { .value = (uint16_t)B_00_0_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_0001, .result = (uint16_t)1 },
  { .value = (uint16_t)B_00_0_0010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_0011, .result = (uint16_t)1 },
  { .value = (uint16_t)B_00_0_0100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_0101, .result = (uint16_t)1 },
  { .value = (uint16_t)B_00_0_0110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_0111, .result = (uint16_t)1 },
  { .value = (uint16_t)B_00_0_1000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_1001, .result = (uint16_t)1 },
  { .value = (uint16_t)B_00_0_1010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_1011, .result = (uint16_t)1 },
  { .value = (uint16_t)B_00_0_1100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_1101, .result = (uint16_t)1 },
  { .value = (uint16_t)B_00_0_1110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_0_1111, .result = (uint16_t)1 },

  { .value = (uint16_t)B_01_0_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_0001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_0010, .result = (uint16_t)1 },
  { .value = (uint16_t)B_01_0_0011, .result = (uint16_t)1 },
  { .value = (uint16_t)B_01_0_0100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_0101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_0110, .result = (uint16_t)1 },
  { .value = (uint16_t)B_01_0_0111, .result = (uint16_t)1 },
  { .value = (uint16_t)B_01_0_1000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_1001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_1010, .result = (uint16_t)1 },
  { .value = (uint16_t)B_01_0_1011, .result = (uint16_t)1 },
  { .value = (uint16_t)B_01_0_1100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_1101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_0_1110, .result = (uint16_t)1 },
  { .value = (uint16_t)B_01_0_1111, .result = (uint16_t)1 },

  { .value = (uint16_t)B_10_0_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_0001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_0010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_0011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_0100, .result = (uint16_t)1 },
  { .value = (uint16_t)B_10_0_0101, .result = (uint16_t)1 },
  { .value = (uint16_t)B_10_0_0110, .result = (uint16_t)1 },
  { .value = (uint16_t)B_10_0_0111, .result = (uint16_t)1 },
  { .value = (uint16_t)B_10_0_1000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_1001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_1010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_1011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_0_1100, .result = (uint16_t)1 },
  { .value = (uint16_t)B_10_0_1101, .result = (uint16_t)1 },
  { .value = (uint16_t)B_10_0_1110, .result = (uint16_t)1 },
  { .value = (uint16_t)B_10_0_1111, .result = (uint16_t)1 },

  { .value = (uint16_t)B_11_0_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_0001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_0010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_0011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_0100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_0101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_0110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_0111, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_0_1000, .result = (uint16_t)1 },
  { .value = (uint16_t)B_11_0_1001, .result = (uint16_t)1 },
  { .value = (uint16_t)B_11_0_1010, .result = (uint16_t)1 },
  { .value = (uint16_t)B_11_0_1011, .result = (uint16_t)1 },
  { .value = (uint16_t)B_11_0_1100, .result = (uint16_t)1 },
  { .value = (uint16_t)B_11_0_1101, .result = (uint16_t)1 },
  { .value = (uint16_t)B_11_0_1110, .result = (uint16_t)1 },
  { .value = (uint16_t)B_11_0_1111, .result = (uint16_t)1 },

  { .value = (uint16_t)B_00_1_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_0001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_0010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_0011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_0100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_0101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_0110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_0111, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_00_1_1111, .result = (uint16_t)0 },

  { .value = (uint16_t)B_01_1_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_0001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_0010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_0011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_0100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_0101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_0110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_0111, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_01_1_1111, .result = (uint16_t)0 },

  { .value = (uint16_t)B_10_1_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_0001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_0010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_0011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_0100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_0101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_0110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_0111, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_10_1_1111, .result = (uint16_t)0 },

  { .value = (uint16_t)B_11_1_0000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_0001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_0010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_0011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_0100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_0101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_0110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_0111, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1000, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1001, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1010, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1011, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1100, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1101, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1110, .result = (uint16_t)0 },
  { .value = (uint16_t)B_11_1_1111, .result = (uint16_t)0 },
};

K1533KP2::K1533KP2(void) {
  _devices = pin_map_1533_kp2;
  _values = values_1533_kp2;  
  _devices_count = sizeof(pin_map_1533_kp2)/sizeof(pin_map_1533_kp2[0]);
  _values_count = sizeof(values_1533_kp2)/sizeof(values_1533_kp2[0]);
}

const __FlashStringHelper * K1533KP2::menu(void) {
  return F("KП2 (2 Мультиплексора)");
}

void K1533KP2::info(void) {
  Serial.println(F("KP1533KП2"));
  Serial.println(F("2 Мультиплексора"));
  Serial.println(F("DIP16"));
  Serial.println(F("\t      16 - +5V       "));
  Serial.println(F("\t       8 - GND       "));
  Serial.println(F("\t      ---------      "));
  Serial.println(F("\t  6 -| D0 | MS |- 7  "));
  Serial.println(F("\t  5 -| D1 |    |     "));
  Serial.println(F("\t  4 -| D2 |    |     "));
  Serial.println(F("\t  3 -| D3 |    |     "));
  Serial.println(F("\t     |----|    |     "));
  Serial.println(F("\t  1 -o S  |    |     "));
  Serial.println(F("\t     |---------|     "));
  Serial.println(F("\t 10 -| D0 | MS |- 9  "));
  Serial.println(F("\t 11 -| D1 |    |     "));
  Serial.println(F("\t 12 -| D2 |    |     "));
  Serial.println(F("\t 13 -| D3 |    |     "));
  Serial.println(F("\t     |----|    |     "));
  Serial.println(F("\t 15 -o S  |    |     "));
  Serial.println(F("\t     |----|    |     "));
  Serial.println(F("\t 14 -| 1  |    |     "));
  Serial.println(F("\t  2 -| 2  |    |     "));
  Serial.println(F("\t      ---------      "));
  Serial.println();
}
