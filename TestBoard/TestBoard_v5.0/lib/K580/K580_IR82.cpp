#include "K580_IR82.h"

const static TDevicePin pin_map_580_ir82[] =
{
  // Входы     D1  D2  D3  D4  D5  D6  D7  D8   E   C
  { .Input = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 11,  0 }, .Output = { 19, 18, 17, 16, 15, 14, 13, 12,  0 }},
};

const static TDeviceVal values_580_ir82[] =
{ 
  { .value = (uint16_t)B_1_1_00000000, .result = (uint16_t)B11111111 },

  { .value = (uint16_t)B_1_0_00000000, .result = (uint16_t)B00000000 },
  { .value = (uint16_t)B_0_0_00000000, .result = (uint16_t)B00000000 },
  
  { .value = (uint16_t)B_1_0_11111111, .result = (uint16_t)B11111111 },
  { .value = (uint16_t)B_0_0_11111111, .result = (uint16_t)B11111111 },

  { .value = (uint16_t)B_1_0_01010101, .result = (uint16_t)B01010101 },
  { .value = (uint16_t)B_0_0_01010101, .result = (uint16_t)B01010101 },
  
  { .value = (uint16_t)B_1_0_10101010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_10101010, .result = (uint16_t)B10101010 },
  
  { .value = (uint16_t)B_1_0_00110011, .result = (uint16_t)B00110011 },
  { .value = (uint16_t)B_0_0_00110011, .result = (uint16_t)B00110011 },
  
  { .value = (uint16_t)B_1_0_11001100, .result = (uint16_t)B11001100 },
  { .value = (uint16_t)B_0_0_11001100, .result = (uint16_t)B11001100 },
  
  { .value = (uint16_t)B_1_0_00001111, .result = (uint16_t)B00001111 },
  { .value = (uint16_t)B_0_0_00001111, .result = (uint16_t)B00001111 },
  
  { .value = (uint16_t)B_1_0_11110000, .result = (uint16_t)B11110000 },
  { .value = (uint16_t)B_0_0_11110000, .result = (uint16_t)B11110000 },

  { .value = (uint16_t)B_1_0_00000001, .result = (uint16_t)B00000001 },
  { .value = (uint16_t)B_0_0_00000001, .result = (uint16_t)B00000001 },

  { .value = (uint16_t)B_1_0_00000010, .result = (uint16_t)B00000010 },
  { .value = (uint16_t)B_0_0_00000010, .result = (uint16_t)B00000010 },
  
  { .value = (uint16_t)B_1_0_00000100, .result = (uint16_t)B00000100 },
  { .value = (uint16_t)B_0_0_00000100, .result = (uint16_t)B00000100 },
  
  { .value = (uint16_t)B_1_0_00001000, .result = (uint16_t)B00001000 },
  { .value = (uint16_t)B_0_0_00001000, .result = (uint16_t)B00001000 },
  
  { .value = (uint16_t)B_1_0_00010000, .result = (uint16_t)B00010000 },
  { .value = (uint16_t)B_0_0_00010000, .result = (uint16_t)B00010000 },
  
  { .value = (uint16_t)B_1_0_00100000, .result = (uint16_t)B00100000 },
  { .value = (uint16_t)B_0_0_00100000, .result = (uint16_t)B00100000 },
  
  { .value = (uint16_t)B_1_0_01000000, .result = (uint16_t)B01000000 },
  { .value = (uint16_t)B_0_0_01000000, .result = (uint16_t)B01000000 },

  { .value = (uint16_t)B_1_0_10000000, .result = (uint16_t)B10000000 },
  { .value = (uint16_t)B_0_0_10000000, .result = (uint16_t)B10000000 },

};

K580IR82::K580IR82(void) {
  _devices = pin_map_580_ir82;
  _values = values_580_ir82;  
  _devices_count = sizeof(pin_map_580_ir82)/sizeof(pin_map_580_ir82[0]);
  _values_count = sizeof(values_580_ir82)/sizeof(values_580_ir82[0]);
}

const __FlashStringHelper * K580IR82::menu(void) {
  return F("ИP82 (Регистр)");
}

void K580IR82::info(void) {
  Serial.println(F("KP580ИP82"));
  Serial.println(F("Регистр"));
  Serial.println(F("DIP20"));
  Serial.println(F("\t         20 - +5V        "));
  Serial.println(F("\t         10 - GND        "));
  Serial.println(F("\t      -------------      "));
  Serial.println(F("\t  1 -| D1 | RG | 1 |- 19 "));
  Serial.println(F("\t  2 -| D2 |    | 2 |- 18 "));
  Serial.println(F("\t  3 -| D3 |    | 3 |- 17 "));
  Serial.println(F("\t  4 -| D4 |    | 4 |- 16 "));
  Serial.println(F("\t  5 -| D5 |    | 5 |- 15 "));
  Serial.println(F("\t  6 -| D6 |    | 6 |- 14 "));
  Serial.println(F("\t  7 -| D7 |    | 7 |- 13 "));
  Serial.println(F("\t  8 -| D8 |    | 8 |- 12 "));
  Serial.println(F("\t     |----|    |   |     "));
  Serial.println(F("\t 11 -| C  |    |   |     "));
  Serial.println(F("\t  9 -o E  |    |   |     "));
  Serial.println(F("\t      -------------      "));
  Serial.println();
}
