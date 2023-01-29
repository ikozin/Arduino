#include "K565_RU5.h"

const static TDevicePin pin_map_565_ru5[] =
{
  // Входы     A0  A1  A2  A3  A4  A5  A6  A7  DI RAS CAS  WE                   DO
  { .Input = {  5,  7,  6, 12, 11, 10, 13,  9,  2,  4, 15,  3,  0}, .Output = { 14,  0 }},
};

K565RU5::K565RU5(void) {
  _devices = pin_map_565_ru5;
  _rows = 256;
  _cols = 256;

  _values = NULL;  
  _devices_count = 1;
  _values_count = 0;
}

const __FlashStringHelper * K565RU5::menu(void) {
  return F("PУ5 (OЗУ 64Kx1)");
}

void K565RU5::info(void) {
  Serial.println(F("K565PУ5"));
  Serial.println(F("OЗУ 64Kx1"));
  Serial.println(F("DIP16"));
  Serial.println(F("\t            8 - +5V          "));
  Serial.println(F("\t           16 - GND          "));
  Serial.println(F("\t      -----------------      "));
  Serial.println(F("\t  2 -| DI  | RAM | DO  |- 14 "));
  Serial.println(F("\t     |-----|     |     |     "));
  Serial.println(F("\t  5 -| A0  |     |     |     "));
  Serial.println(F("\t  7 -| A1  |     |     |     "));
  Serial.println(F("\t  6 -| A2  |     |     |     "));
  Serial.println(F("\t 12 -| A3  |     |     |     "));
  Serial.println(F("\t 11 -| A4  |     |     |     "));
  Serial.println(F("\t 10 -| A5  |     |     |     "));
  Serial.println(F("\t 13 -| A6  |     |     |     "));
  Serial.println(F("\t  9 -| A7  |     |     |     "));
  Serial.println(F("\t     |-----|     |     |     "));
  Serial.println(F("\t  4 -o RAS |     |     |     "));
  Serial.println(F("\t 15 -o CAS |     |     |     "));
  Serial.println(F("\t  3 -o WE  |     |     |     "));
  Serial.println(F("\t      -----------------      "));
  Serial.println();
}
