#include "K565_RU7.h"

const static TDevicePin pin_map_565_ru7[] =
{
  // Входы     A0  A1  A2  A3  A4  A5  A6  A7  A8  DI RAS CAS  WE                   DO
  { .Input = {  5,  7,  6, 12, 11, 10, 13,  9,  1,  2,  4, 15,  3,  0}, .Output = { 14,  0 }},
};

K565RU7::K565RU7(void) {
  _devices = pin_map_565_ru7;
  _values = NULL;  
  _devices_count = 1;
  _values_count = 0;
}

const __FlashStringHelper * K565RU7::menu(void) {
  return F("PУ7 (OЗУ 256Kx1)");
}

void K565RU7::info(void) {
  Serial.println(F("K565PУ7"));
  Serial.println(F("OЗУ 256Kx1"));
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
  Serial.println(F("\t  1 -| A8  |     |     |     "));
  Serial.println(F("\t     |-----|     |     |     "));
  Serial.println(F("\t  4 -o RAS |     |     |     "));
  Serial.println(F("\t 15 -o CAS |     |     |     "));
  Serial.println(F("\t  3 -o WE  |     |     |     "));
  Serial.println(F("\t      -----------------      "));
  Serial.println();
}

int K565RU7::test_device(const TDevicePin *device, const TDeviceVal *data) {
  int errorCount = 0;
  info();
  init();
  debug_println("----------");
  noInterrupts();
  // for (size_t i = 0; i < _devices_count; i++) {
  //   for (size_t n = 0; n < _values_count; n++) {
  //     debug_printf("\r\nDevice[%d], Test[%d]\r\n", i, n);
  //     errorCount += test_device(&_devices[i], &_values[n]);
  //   }
  // }
  interrupts();
  debug_println("----------");
  done();
  return errorCount;
}
