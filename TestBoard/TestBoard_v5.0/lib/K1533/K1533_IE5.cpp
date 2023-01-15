#include "K1533_IE5.h"

const static TDevicePin pin_map_1533_ie5[] =
{
  // Входы     C1  C2   &   R                     Выходы      1   2   4   8
  { .Input = { 14,  1,  2,  3,  0,  0,  0,  0 }, .Output = { 12,  9,  8, 11,  0,  0,  0,  0 }},
};

const static TDeviceVal values_1533_ie5[] =
{  
  //                      R  & C2 C1                         8  4  2  1
  { .value = (uint16_t)B__1__1__0__0, .result = (uint16_t)B__0__0__0__0 },

  { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__1__0__1, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__1 },
  { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__1 },
  { .value = (uint16_t)B__1__0__0__0, .result = (uint16_t)B__0__0__0__1 },
  { .value = (uint16_t)B__1__0__0__1, .result = (uint16_t)B__0__0__0__1 },
  { .value = (uint16_t)B__1__0__0__0, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__1__0__1, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__1__0__0, .result = (uint16_t)B__0__0__0__1 },
  { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__1 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__1 },
  { .value = (uint16_t)B__0__0__0__1, .result = (uint16_t)B__0__0__0__1 },

  //                      R  & C2 C1                         8  4  2  1
  { .value = (uint16_t)B__1__1__0__0, .result = (uint16_t)B__0__0__0__0 },
  
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__0__0__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__0__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__0__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__0__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__1__0__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__0__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__1__0__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__1__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__1__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__0__1__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__0__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__0__0__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__0__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__0__0__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__0__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__0__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__0__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__0__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__1__0__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__0__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__1__0__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__1__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__1__1__1__0 },
  { .value = (uint16_t)B__0__0__1__0, .result = (uint16_t)B__1__1__1__0 },
  { .value = (uint16_t)B__0__0__0__0, .result = (uint16_t)B__0__0__0__0 },
};


K1533IE5::K1533IE5(void) {
  _devices = pin_map_1533_ie5;
  _values = values_1533_ie5;  
  _devices_count = sizeof(pin_map_1533_ie5)/sizeof(pin_map_1533_ie5[0]);
  _values_count = sizeof(values_1533_ie5)/sizeof(values_1533_ie5[0]);
}

const __FlashStringHelper * K1533IE5::menu(void) {
  return F("Счетчик двоичный");
}

void K1533IE5::info(void) {
  Serial.println(F("KP1533ИE5                "));
  Serial.println(F("Счетчик двоичный         "));
  Serial.println(F("DIP14                    "));
  Serial.println(F("\t       5 - +5V         "));
  Serial.println(F("\t      10 - GND         "));
  Serial.println(F("\t      ------------     "));
  Serial.println(F("\t 14 -\\ C1 |CT2| 1 |- 12"));
  Serial.println(F("\t  1 -\\ C2 |   | 2 |-  9"));
  Serial.println(F("\t     |----|   | 4 |-  8"));
  Serial.println(F("\t  2 -| &  |   | 8 |- 11"));
  Serial.println(F("\t  3 -| R  |   |   |    "));
  Serial.println(F("\t      ------------     "));
  Serial.println();
}
