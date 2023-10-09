#include "K1533_LN1_LN2_LN3_LN5_LN8.h"

const static TDevicePin PROGMEM pin_map_1533_ln1_ln2_ln3_ln5_ln8[] =
{
  { .Input = {  1,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  2,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  3,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  4,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  5,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  6,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = {  9,  0,  0,  0,  0,  0,  0,  0 }, .Output = {  8,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 11,  0,  0,  0,  0,  0,  0,  0 }, .Output = { 10,  0,  0,  0,  0,  0,  0,  0 }},
  { .Input = { 13,  0,  0,  0,  0,  0,  0,  0 }, .Output = { 12,  0,  0,  0,  0,  0,  0,  0 }},
};

const static TDeviceVal PROGMEM values_1533_ln1_ln2_ln3_ln5_ln8[] =
{
  { .value = (uint16_t)0, .result = (uint16_t)1 },
  { .value = (uint16_t)1, .result = (uint16_t)0 },
};

K1533LN1LN2LN3LN5LN8::K1533LN1LN2LN3LN5LN8(void) {
  _devices = pin_map_1533_ln1_ln2_ln3_ln5_ln8;
  _values = values_1533_ln1_ln2_ln3_ln5_ln8;  
  _devices_count = sizeof(pin_map_1533_ln1_ln2_ln3_ln5_ln8)/sizeof(pin_map_1533_ln1_ln2_ln3_ln5_ln8[0]);
  _values_count = sizeof(values_1533_ln1_ln2_ln3_ln5_ln8)/sizeof(values_1533_ln1_ln2_ln3_ln5_ln8[0]);
}

const __FlashStringHelper * K1533LN1LN2LN3LN5LN8::menu(void) {
  return F("ЛH1 ЛH2 ЛH3 ЛH5 ЛH8 (6 элементов HE)");
}

const char K1533LN1LN2LN3LN5LN8_Description[] PROGMEM = 
"KP1533ЛH1\r\n"
"KP1533ЛH2  - открытый коллектор\r\n"
"KP1533ЛH3  - открытый коллектор\r\n"
"KP1533ЛH5  - открытый коллектор\r\n"
"KP1533ЛH8  - повышеннаая нагрузка\r\n"
"KP1533TЛ2  - триггер Шмитта\r\n"
"6 элементов HE\r\n"
"DIP14\r\n"
"\t    14 - +5V     \r\n"
"\t     7 - GND     \r\n"
"\t      -----      \r\n"
"\t     | 1   |     \r\n"
"\t  1 -|     o- 2  \r\n"
"\t     |     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t     | 1   |     \r\n"
"\t  3 -|     o- 4  \r\n"
"\t     |     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t     | 1   |     \r\n"
"\t  5 -|     o- 6  \r\n"
"\t     |     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t     | 1   |     \r\n"
"\t  9 -|     o- 8  \r\n"
"\t     |     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t     | 1   |     \r\n"
"\t 11 -|     o- 10 \r\n"
"\t     |     |     \r\n"
"\t      -----      \r\n"
"\t      -----      \r\n"
"\t     | 1   |     \r\n"
"\t 13 -|     o- 12 \r\n"
"\t     |     |     \r\n"
"\t      -----      \r\n"
;

void K1533LN1LN2LN3LN5LN8::info(void) {
  Serial.println((__FlashStringHelper *)K1533LN1LN2LN3LN5LN8_Description);
}
