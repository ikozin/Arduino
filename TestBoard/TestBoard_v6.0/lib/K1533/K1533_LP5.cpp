#include "K1533_LP5.h"

const static TDevicePin PROGMEM pin_map_1533_lp5[] =
{
  { .Input = {  1,  2,  0,  0,  0,  0,  0,  0 }, .Output = {  3,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  4,  5,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9, 10,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 12, 13,  0,  0,  0,  0,  0,  0 }, .Output = { 11,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_lp5[] =
{
  { .value = (uint16_t)0, .result = (uint16_t)0 },
  { .value = (uint16_t)1, .result = (uint16_t)1 },
  { .value = (uint16_t)2, .result = (uint16_t)1 },
  { .value = (uint16_t)3, .result = (uint16_t)0 },
};

K1533LP5::K1533LP5(void){
  _devices = pin_map_1533_lp5;
  _values = values_1533_lp5;
  _devices_count = sizeof(pin_map_1533_lp5)/sizeof(pin_map_1533_lp5[0]);
  _values_count = sizeof(values_1533_lp5)/sizeof(values_1533_lp5[0]);
}

const __FlashStringHelper * K1533LP5::menu(void) {
  return F("ЛП5 (2ИЛИ)");
}

const __FlashStringHelper * K1533LP5::description(void) {
    return F(
"KP1533ЛП5\r\n"
"4 элемента 2ИЛИ по модулю 2\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t  1 -| =1  |     \r\n"
"\t     |     |- 3  \r\n"
"\t  2 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  4 -| =1  |     \r\n"
"\t     |     |- 6  \r\n"
"\t  5 -|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  9 -| =1  |     \r\n"
"\t     |     |- 8  \r\n"
"\t  10-|     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t  12-| =1  |     \r\n"
"\t     |     |- 11 \r\n"
"\t  13-|     |     \r\n"
"\t      -----      \r\n"
    );
}

const __FlashStringHelper * K1533LP5::title(void) {
  return F("KP1533ЛП5\r\n4 элемента 2ИЛИ по модулю 2\r\nDIP14\r\n");
}
