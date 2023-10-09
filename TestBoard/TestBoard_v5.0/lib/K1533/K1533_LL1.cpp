#include "K1533_LL1.h"

const static TDevicePin PROGMEM pin_map_1533_ll1[] =
{
  { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  4,  5,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 12, 13,  0,  0,  0,  0,  0,  0 }, .Output = { 11,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_ll1[] =
{
  { .value = (uint16_t)0, .result = (uint16_t)0 },
  { .value = (uint16_t)1, .result = (uint16_t)1 },
  { .value = (uint16_t)2, .result = (uint16_t)1 },
  { .value = (uint16_t)3, .result = (uint16_t)1 },
};

K1533LL1::K1533LL1(void){
  _devices = pin_map_1533_ll1;
  _values = values_1533_ll1;
  _devices_count = sizeof(pin_map_1533_ll1)/sizeof(pin_map_1533_ll1[0]);
  _values_count = sizeof(values_1533_ll1)/sizeof(values_1533_ll1[0]);
}

const __FlashStringHelper * K1533LL1::menu(void) {
  return F("ЛЛ1 (4 элемента 2ИЛИ)");
}

const char K1533LL1_Description[] PROGMEM = 
"KP1533ЛЛ1\r\n"
"4 элемента 2ИЛИ\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  1 -| 1   |     \r\n"
"\t     |     |- 3  \r\n"
"\t  2 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  4 -| 1   |     \r\n"
"\t     |     |- 6  \r\n"
"\t  5 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  9 -| 1   |     \r\n"
"\t     |     |- 8  \r\n"
"\t  10-|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  12-| 1   |     \r\n"
"\t     |     |- 11 \r\n"
"\t  13-|     |     \r\n"
"\t      -----      \r\n"
;

void K1533LL1::info(void) {
  Serial.println((__FlashStringHelper *)K1533LL1_Description);
}