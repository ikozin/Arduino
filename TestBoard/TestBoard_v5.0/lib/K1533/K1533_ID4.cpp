#include "K1533_ID4.h"

const static TDevicePin PROGMEM pin_map_1533_id4_1[] =
{
  // Входы      1   2   &   &                 Выходы      0   1   2   3
  { .Input = { 13,  3, 14, 15, 0, 0, 0, 0 }, .Output = {  9, 10, 11, 12, 0, 0, 0, 0 }},
};

const static TDevicePin PROGMEM pin_map_1533_id4_2[] =
{
  // Входы      1   2   &   &                 Выходы      0   1   2   3
  { .Input = { 13,  3,  1,  2, 0, 0, 0, 0 }, .Output = { 7 ,  6,  5,  4, 0, 0, 0, 0 }},
};

const static TDeviceVal PROGMEM values_1533_id4_1[] =
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

const static TDeviceVal PROGMEM values_1533_id4_2[] =
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

const __FlashStringHelper * K1533ID4::menu(void) {
  return F("ИД4 (2 Дешифратора)");
}

const char K1533ID4_Description[] PROGMEM = 
"KP1533ИД4\r\n"
"2 Дешифратора\r\n"
"DIP16\r\n"
"\t         16 - +5V        \r\n"
"\t          8 - GND        \r\n"
"\t      --------------     \r\n"
"\t 14 -o &  | DC |  0 o- 9 \r\n"
"\t 15 -o S0 |    |  1 o-10 \r\n"
"\t     |----|    |  2 o-11 \r\n"
"\t 13 -| 1  |    |  3 o-12 \r\n"
"\t  3 -| 2  |    |----|    \r\n"
"\t     |----|    |  0 o- 7 \r\n"
"\t  1 -| &  |    |  1 o- 6 \r\n"
"\t  2 -o S1 |    |  2 o- 5 \r\n"
"\t     |    |    |  3 o- 4 \r\n"
"\t      --------------     \r\n"
;

void K1533ID4::info(void) {
  Serial.println((__FlashStringHelper *)K1533ID4_Description);
}

K1533ID4_SubDev sub_1533_id4_dev1(pin_map_1533_id4_1, values_1533_id4_1, sizeof(values_1533_id4_1)/sizeof(values_1533_id4_1[0]));
K1533ID4_SubDev sub_1533_id4_dev2(pin_map_1533_id4_2, values_1533_id4_2, sizeof(values_1533_id4_2)/sizeof(values_1533_id4_2[0]));
TDevice * composite_1533_id4[] { &sub_1533_id4_dev1, &sub_1533_id4_dev2 };

K1533ID4::K1533ID4(): TDeviceComposite(composite_1533_id4, sizeof(composite_1533_id4)/sizeof(composite_1533_id4[0])) {
}
