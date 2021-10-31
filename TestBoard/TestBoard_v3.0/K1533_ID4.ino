#ifdef K1533_ID4

#include "K1533_ID4.h"

TDevicePin pin_map_1533_id4_1[] =
{
  // Входы      1   2   &   &                 Выходы      0   1   2   3
  { .Input = { 13,  3, 14, 15, 0, 0, 0, 0 }, .Output = {  9, 10, 11, 12, 0, 0, 0, 0 }},
};

TDevicePin pin_map_1533_id4_2[] =
{
  // Входы      1   2   &   &                 Выходы      0   1   2   3
  { .Input = { 13,  3,  1,  2, 0, 0, 0, 0 }, .Output = { 7 ,  6,  5,  4, 0, 0, 0, 0 }},
};

TDeviceVal values_1533_id4_1[] =
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

TDeviceVal values_1533_id4_2[] =
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

K1533ID4_SubDev sub_1533_id4_dev1(pin_map_1533_id4_1, values_1533_id4_1, sizeof(values_1533_id4_1)/sizeof(values_1533_id4_1[0]));
K1533ID4_SubDev sub_1533_id4_dev2(pin_map_1533_id4_2, values_1533_id4_2, sizeof(values_1533_id4_2)/sizeof(values_1533_id4_2[0]));
TDevice * composite_1533_id4[] { &sub_1533_id4_dev1, &sub_1533_id4_dev2 };
K1533ID4::K1533ID4(): TDeviceComposite(composite_1533_id4, sizeof(composite_1533_id4)/sizeof(composite_1533_id4[0])) {}


#endif
