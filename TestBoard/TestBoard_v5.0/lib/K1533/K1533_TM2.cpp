#include "K1533_TM2.h"

const static TDevicePin pin_map_1533_tm2[] =
{
  // Входы      R   S   D   C                     Выходы      0   1
  { .Input = {  1,  4,  2,  3,  0,  0,  0,  0 }, .Output = {  5,  6,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 13, 10, 12, 11,  0,  0,  0,  0 }, .Output = {  9,  8,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal values_1533_tm2[] =
{  
  //                     C D S R
  { .value = (uint16_t)B_0_0_0_1, .result = (uint16_t)1 },
  { .value = (uint16_t)B_1_0_0_1, .result = (uint16_t)1 },
  { .value = (uint16_t)B_0_1_0_1, .result = (uint16_t)1 },
  { .value = (uint16_t)B_1_1_0_1, .result = (uint16_t)1 },
  //                     C D S R
  { .value = (uint16_t)B_0_0_1_0, .result = (uint16_t)2 },
  { .value = (uint16_t)B_1_0_1_0, .result = (uint16_t)2 },
  { .value = (uint16_t)B_0_1_1_0, .result = (uint16_t)2 },
  { .value = (uint16_t)B_1_1_1_0, .result = (uint16_t)2 },
  //                     C D S R
  { .value = (uint16_t)B_0_0_1_1, .result = (uint16_t)2 },
  { .value = (uint16_t)B_1_0_1_1, .result = (uint16_t)2 },
  { .value = (uint16_t)B_0_1_1_1, .result = (uint16_t)2 },
  { .value = (uint16_t)B_1_1_1_1, .result = (uint16_t)1 },
  { .value = (uint16_t)B_0_0_1_1, .result = (uint16_t)1 },
  { .value = (uint16_t)B_1_0_1_1, .result = (uint16_t)2 },
  { .value = (uint16_t)B_0_1_1_1, .result = (uint16_t)2 },
  { .value = (uint16_t)B_1_1_1_1, .result = (uint16_t)1 },
  { .value = (uint16_t)B_0_0_1_1, .result = (uint16_t)1 },
  { .value = (uint16_t)B_1_0_1_1, .result = (uint16_t)2 },
  { .value = (uint16_t)B_0_1_1_1, .result = (uint16_t)2 },
  { .value = (uint16_t)B_1_1_1_1, .result = (uint16_t)1 },
};


K1533TM2::K1533TM2(void) {
  _devices = pin_map_1533_tm2;
  _values = values_1533_tm2;  
  _devices_count = sizeof(pin_map_1533_tm2)/sizeof(pin_map_1533_tm2[0]);
  _values_count = sizeof(values_1533_tm2)/sizeof(values_1533_tm2[0]);
}

const __FlashStringHelper * K1533TM2::menu(void) {
  return F("TM2 (2 D-Триггера)");
}

void K1533TM2::info(void) {
  Serial.println(F("KP1533TM2             "));
  Serial.println(F("2 D-триггера          "));
  Serial.println(F("DIP14                 "));
  Serial.println(F("\t      14 - +5V      "));
  Serial.println(F("\t       7 - GND      "));
  Serial.println(F("\t      --------      "));
  Serial.println(F("\t  1 -o R | TT |- 5  "));
  Serial.println(F("\t     |---|    |     "));
  Serial.println(F("\t  2 -| D |    |     "));
  Serial.println(F("\t  3 -/ C |    |     "));
  Serial.println(F("\t     |---|    |     "));
  Serial.println(F("\t  4 -o S |    o- 6  "));
  Serial.println(F("\t      --------      "));
  Serial.println(F("\t      --------      "));
  Serial.println(F("\t 13 -o R | TT |- 9  "));
  Serial.println(F("\t     |---|    |     "));
  Serial.println(F("\t 12 -| D |    |     "));
  Serial.println(F("\t 11 -/ C |    |     "));
  Serial.println(F("\t     |---|    |     "));
  Serial.println(F("\t 10 -o S |    o- 8  "));
  Serial.println(F("\t      --------      "));
  Serial.println();
}
