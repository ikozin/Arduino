#include "K1533_LA8.h"

const static TDevicePin pin_map_1533_la8[] =
{
  {.Input = {  2,  3,  0,  0,  0,  0,  0,  0 }, .Output = {  1,  0,  0,  0,  0,  0,  0,  0 }},
  {.Input = {  5,  6,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  {.Input = {  8,  9,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  {.Input = { 11, 11,  0,  0,  0,  0,  0,  0 }, .Output = { 13,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal values_1533_la8[] =
{
  {.value = (uint16_t)0, .result = (uint16_t)1 },
  {.value = (uint16_t)1, .result = (uint16_t)1 },
  {.value = (uint16_t)2, .result = (uint16_t)1 },
  {.value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LA8::K1533LA8(void) {
  _devices = pin_map_1533_la8;
  _values = values_1533_la8;
  _devices_count = sizeof(pin_map_1533_la8)/sizeof(pin_map_1533_la8[0]);
  _values_count = sizeof(values_1533_la8)/sizeof(values_1533_la8[0]);
}

const __FlashStringHelper * K1533LA8::menu(void) {
  return F("ЛA8 (4 элемента 2И-HE)");
}

void K1533LA8::info(void) {
  Serial.println(F("KP1533ЛA8 - открытый коллектор"));
  Serial.println(F("4 элемента 2И-HE   "));
  Serial.println(F("DIP14              "));
  Serial.println(F("\t    14 - +5V     "));
  Serial.println(F("\t     7 - GND     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  2 -| &   |     "));
  Serial.println(F("\t     |     o- 1  "));
  Serial.println(F("\t  3 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  5 -| &   |     "));
  Serial.println(F("\t     |     o- 4  "));
  Serial.println(F("\t  6 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  8 -| &   |     "));
  Serial.println(F("\t     |     o- 10 "));
  Serial.println(F("\t  9 -|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t      -----      "));
  Serial.println(F("\t  11-| &   |     "));
  Serial.println(F("\t     |     o- 13 "));
  Serial.println(F("\t  12-|     |     "));
  Serial.println(F("\t      -----      "));
  Serial.println();
}
