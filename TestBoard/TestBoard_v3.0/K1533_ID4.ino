#ifdef K1533_ID4

#include "K1533_ID4.h"

#define B_00_00   0
#define B_00_01   1
#define B_00_10   2
#define B_00_11   3
#define B_01_00   4
#define B_01_01   5
#define B_01_10   6
#define B_01_11   7
#define B_10_00   8
#define B_10_01   9
#define B_10_10   10
#define B_10_11   11
#define B_11_00   12
#define B_11_01   13
#define B_11_10   14
#define B_11_11   15

#define B_1110    14
#define B_1101    13
#define B_1011    11
#define B_0111    7
#define B_1111    15

Input16Out16DevPin pin_map_1533_id4_1[1] =
{
  // Входы      1   2   &   &                 Выходы      0   1   2   3
  { .Input = { 24, 35, 23, 22, 0, 0, 0, 0 }, .Output = { 28, 27, 26, 25, 0, 0, 0, 0 }},
};

Input16Out16DevPin pin_map_1533_id4_2[1] =
{
  // Входы      1   2   &   &                 Выходы      0   1   2   3
  { .Input = { 24, 35, 37, 36, 0, 0, 0, 0 }, .Output = { 31, 32, 33, 34, 0, 0, 0, 0 }},
};

Input16Out16DevVal values_1533_id4_1[16] =
{  
  { .value = (uint16_t)B_00_00, .result = (uint16_t)B_1110 },
  { .value = (uint16_t)B_00_01, .result = (uint16_t)B_1101 },
  { .value = (uint16_t)B_00_10, .result = (uint16_t)B_1011 },
  { .value = (uint16_t)B_00_11, .result = (uint16_t)B_0111 },
  { .value = (uint16_t)B_01_00, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_01_01, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_01_10, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_01_11, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_10_00, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_10_01, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_10_10, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_10_11, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_00, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_01, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_10, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_11, .result = (uint16_t)B_1111 },
};

Input16Out16DevVal values_1533_id4_2[16] =
{  
  { .value = (uint16_t)B_00_00, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_00_01, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_00_10, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_00_11, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_01_00, .result = (uint16_t)B_1110 },
  { .value = (uint16_t)B_01_01, .result = (uint16_t)B_1101 },
  { .value = (uint16_t)B_01_10, .result = (uint16_t)B_1011 },
  { .value = (uint16_t)B_01_11, .result = (uint16_t)B_0111 },
  { .value = (uint16_t)B_10_00, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_10_01, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_10_10, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_10_11, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_00, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_01, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_10, .result = (uint16_t)B_1111 },
  { .value = (uint16_t)B_11_11, .result = (uint16_t)B_1111 },
};

void K1533ID4::info(void) {
  Serial.println(F("КР1533ИД4"));
  Serial.println(F("2 Дешифратора"));
  Serial.println(F("DIP16"));
  Serial.println(F("\t         16 - +5V              "));
  Serial.println(F("\t          8 - GND              "));
  Serial.println(F("\t      --------------           "));
  Serial.println(F("\t 14 -o &  | DC |  0 o- 9  (28) "));
  Serial.println(F("\t 15 -o S0 |    |  1 o-10  (27) "));
  Serial.println(F("\t     |----|    |  2 o-11  (26) "));
  Serial.println(F("\t 13 -| 1  |    |  3 o-12  (25) "));
  Serial.println(F("\t  3 -| 2  |    |----|          "));
  Serial.println(F("\t     |----|    |  0 o- 7  (31) "));
  Serial.println(F("\t  1 -| &  |    |  1 o- 6  (32) "));
  Serial.println(F("\t  2 -o S1 |    |  2 o- 5  (33) "));
  Serial.println(F("\t     |    |    |  3 o- 4  (34) "));
  Serial.println(F("\t      --------------           "));
  Serial.println();
}

K1533ID4_SubDev::K1533ID4_SubDev(Input16Out16DevPin *device, size_t device_count, Input16Out16DevVal *value, size_t value_count) {
  _devices = device;
  _values = value;
  _devices_count = device_count;
  _values_count = value_count;
}

K1533ID4::K1533ID4() {
  _devices_count = 0;
  _values_count = 0;    
}


int K1533ID4::test(void) {
  int result = 0;
  K1533ID4_SubDev dev1(pin_map_1533_id4_1, 1, values_1533_id4_1, 16);
  K1533ID4_SubDev dev2(pin_map_1533_id4_2, 1, values_1533_id4_2, 16);

  info();
  dev1.init();
  dev2.init();
  result += dev1.check_devices();
  result += dev2.check_devices();
  dev1.done();
  dev2.done();
  
  if (result == 0) {
    debug_println(F("\r\nТЕСТ ПРОЙДЕН"));
  }
  else {
    sprintf(text, "\r\nОШИБКА!\r\nКол-во ошибок = %d\r\n", result);
    debug_println(result);
  }
  return result;
}


#endif
