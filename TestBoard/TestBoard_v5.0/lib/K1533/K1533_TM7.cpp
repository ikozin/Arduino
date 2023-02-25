#include "K1533_TM7.h"

const static TDevicePin pin_map_1533_tm7[] =
{
  // Входы     D1  D2   C         Выходы      1       2
  { .Input = {  2,  3, 13,  0 }, .Output = { 16,  1, 15, 14,  0 }},

  // Входы     D3  D4   C         Выходы      3       4
  { .Input = {  6,  7,  4,  0 }, .Output = { 10, 11,  9,  8,  0 }},
};

const static TDeviceVal values_1533_tm7[] =
{//                      C 2 1
  { .value = (uint16_t)B_1_0_0, .result = (uint16_t)B_1_0_1_0 },
  { .value = (uint16_t)B_0_0_0, .result = (uint16_t)B_1_0_1_0 },

  { .value = (uint16_t)B_1_0_1, .result = (uint16_t)B_1_0_0_1 },
  { .value = (uint16_t)B_0_0_1, .result = (uint16_t)B_1_0_0_1 },

  { .value = (uint16_t)B_1_1_0, .result = (uint16_t)B_0_1_1_0 },
  { .value = (uint16_t)B_0_1_0, .result = (uint16_t)B_0_1_1_0 },

  { .value = (uint16_t)B_1_1_1, .result = (uint16_t)B_0_1_0_1 },
  { .value = (uint16_t)B_0_1_1, .result = (uint16_t)B_0_1_0_1 },
};

K1533TM7::K1533TM7() {
  _devices = pin_map_1533_tm7;
  _values = values_1533_tm7;  
  _devices_count = sizeof(pin_map_1533_tm7)/sizeof(pin_map_1533_tm7[0]);
  _values_count = sizeof(values_1533_tm7)/sizeof(values_1533_tm7[0]);
}

const __FlashStringHelper * K1533TM7::menu(void) {
  return F("TM7 (2 Регистра)");
}

void K1533TM7::info(void) {
  Serial.println(F("KP1533TM7                  "));
  Serial.println(F("Регистр                    "));
  Serial.println(F("DIP16                      "));
  Serial.println(F("\t         5 - +5V         "));
  Serial.println(F("\t        12 - GND         "));
  Serial.println(F("\t      -------------      "));
  Serial.println(F("\t  2 -| D1 | RG | 1 |- 16 "));
  Serial.println(F("\t  3 -| D2 |    |   o- 1  "));
  Serial.println(F("\t     |    |    | 2 |- 15 "));
  Serial.println(F("\t 13 -| C  |    |   o- 14 "));
  Serial.println(F("\t      -------------      "));
  Serial.println(F("\t      -------------      "));
  Serial.println(F("\t  6 -| D3 | RG | 3 |- 10 "));
  Serial.println(F("\t  7 -| D4 |    |   o- 11 "));
  Serial.println(F("\t     |    |    | 4 |- 9  "));
  Serial.println(F("\t  4 -| C  |    |   o- 8  "));
  Serial.println(F("\t      -------------      "));
  Serial.println();
}
