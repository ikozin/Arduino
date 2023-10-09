#include "K1533_LE1_LE5_LE6_LE10_LE11.h"

const static TDevicePin PROGMEM pin_map_1533_le1_le5_le6_le10_le11[] =
{
  { .Input = {  2,  3,  0,  0,  0,  0,  0,  0 }, .Output = {  1,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  5,  6,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  8,  9,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 11, 12,  0,  0,  0,  0,  0,  0 }, .Output = { 13,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_le1_le5_le6_le10_le11[] =
{
  { .value = (uint16_t)0, .result = (uint16_t)1 },
  { .value = (uint16_t)1, .result = (uint16_t)0 },
  { .value = (uint16_t)2, .result = (uint16_t)0 },
  { .value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LE1LE5LE6LE10LE11::K1533LE1LE5LE6LE10LE11(void) {
  _devices = pin_map_1533_le1_le5_le6_le10_le11;
  _values = values_1533_le1_le5_le6_le10_le11;
  _devices_count = sizeof(pin_map_1533_le1_le5_le6_le10_le11)/sizeof(pin_map_1533_le1_le5_le6_le10_le11[0]);
  _values_count = sizeof(values_1533_le1_le5_le6_le10_le11)/sizeof(values_1533_le1_le5_le6_le10_le11[0]);
}

const __FlashStringHelper * K1533LE1LE5LE6LE10LE11::menu(void) {
  return F("ЛE1 ЛE5 ЛE6 ЛE10 ЛE11 (4 элемента 2ИЛИ-HE)");
}

const char K1533LE1LE5LE6LE10LE11_Description[] PROGMEM = 
"KP1533ЛE1\r\n"
"KP1533ЛE5  - повышеннаая нагрузка\r\n"
"KP1533ЛE6  - повышеннаая нагрузка\r\n"
"KP1533ЛE10 - повышеннаая нагрузка\r\n"
"KP1533ЛE11 - повышеннаая нагрузка\r\n"
"             открытый коллектор\r\n"
"4 элемента 2ИЛИ-HE\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  2 -| 1   |     \r\n"
"\t     |     o- 1  \r\n"
"\t  3 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  5 -| 1   |     \r\n"
"\t     |     o- 4  \r\n"
"\t  6 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  8 -| 1   |     \r\n"
"\t     |     o- 10 \r\n"
"\t  9 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  11-| 1   |     \r\n"
"\t     |     o- 13 \r\n"
"\t  12-|     |     \r\n"
"\t      -----      \r\n"
;

void K1533LE1LE5LE6LE10LE11::info(void) {
  Serial.println((__FlashStringHelper *)K1533LE1LE5LE6LE10LE11_Description);
}
