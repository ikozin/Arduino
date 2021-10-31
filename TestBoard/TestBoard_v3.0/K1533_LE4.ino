#ifdef K1533_LE4

#include "K1533_LE4.h"

TDevicePin pin_map_1533_le4[] =
{
  { .Input = {  1,  2, 13,  0,  0,  0,  0,  0 }, .Output = { 12,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  3,  4,  5,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10, 11,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
};

TDeviceVal values_1533_le4[] =
{
  { .value = (uint16_t) 0, .result = (uint16_t) 1 },
  { .value = (uint16_t) 1, .result = (uint16_t) 0 },
  { .value = (uint16_t) 2, .result = (uint16_t) 0 },
  { .value = (uint16_t) 3, .result = (uint16_t) 0 },
  { .value = (uint16_t) 4, .result = (uint16_t) 0 },
  { .value = (uint16_t) 5, .result = (uint16_t) 0 },
  { .value = (uint16_t) 6, .result = (uint16_t) 0 },
  { .value = (uint16_t) 7, .result = (uint16_t) 0 },
};

K1533LE4::K1533LE4() {
  _devices = pin_map_1533_le4;
  _values = values_1533_le4;
  _devices_count = sizeof(pin_map_1533_le4)/sizeof(pin_map_1533_le4[0]);
  _values_count = sizeof(values_1533_le4)/sizeof(values_1533_le4[0]);
}

void K1533LE4::info(void) {
  Serial.println(F("КР1533ЛЕ4"));
  Serial.println(F("3 элемента 3ИЛИ-НЕ "));
  Serial.println(F("DIP14              "));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  1 -| 1   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  2 -|     o- 12  "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t 13 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  3 -| 1   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  4 -|     o- 6   "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t  5 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  9 -| 1   |     "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t 10 -|     o- 8   "));
  Serial.println(F("\t     |     |     "));
  Serial.println(F("\t 11 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}

#endif
