#include "K1533_IR33.h"

const static TDevicePin PROGMEM pin_map_1533_ir33[] =
{
  // Входы     D1  D2  D3  D4  D5  D6  D7  D8   E   C
  { .Input = {  2,  3,  4,  5,  6,  7,  8,  9,  1, 11,  0 }, .Output = { 19, 18, 17, 16, 15, 14, 13, 12,  0 }},
};

const static TDeviceVal PROGMEM values_1533_ir33[] =
{ 
  { .value = (uint16_t)B_1_1_00000000, .result = (uint16_t)B11111111 },

  { .value = (uint16_t)B_1_0_00000000, .result = (uint16_t)B00000000 },
  { .value = (uint16_t)B_0_0_00000000, .result = (uint16_t)B00000000 },
  
  { .value = (uint16_t)B_1_0_11111111, .result = (uint16_t)B11111111 },
  { .value = (uint16_t)B_0_0_11111111, .result = (uint16_t)B11111111 },

  { .value = (uint16_t)B_1_0_01010101, .result = (uint16_t)B01010101 },
  { .value = (uint16_t)B_0_0_01010101, .result = (uint16_t)B01010101 },
  
  { .value = (uint16_t)B_1_0_10101010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_10101010, .result = (uint16_t)B10101010 },
  
  { .value = (uint16_t)B_1_0_00110011, .result = (uint16_t)B00110011 },
  { .value = (uint16_t)B_0_0_00110011, .result = (uint16_t)B00110011 },
  
  { .value = (uint16_t)B_1_0_11001100, .result = (uint16_t)B11001100 },
  { .value = (uint16_t)B_0_0_11001100, .result = (uint16_t)B11001100 },
  
  { .value = (uint16_t)B_1_0_00001111, .result = (uint16_t)B00001111 },
  { .value = (uint16_t)B_0_0_00001111, .result = (uint16_t)B00001111 },
  
  { .value = (uint16_t)B_1_0_11110000, .result = (uint16_t)B11110000 },
  { .value = (uint16_t)B_0_0_11110000, .result = (uint16_t)B11110000 },

  { .value = (uint16_t)B_1_0_00000001, .result = (uint16_t)B00000001 },
  { .value = (uint16_t)B_0_0_00000001, .result = (uint16_t)B00000001 },

  { .value = (uint16_t)B_1_0_00000010, .result = (uint16_t)B00000010 },
  { .value = (uint16_t)B_0_0_00000010, .result = (uint16_t)B00000010 },
  
  { .value = (uint16_t)B_1_0_00000100, .result = (uint16_t)B00000100 },
  { .value = (uint16_t)B_0_0_00000100, .result = (uint16_t)B00000100 },
  
  { .value = (uint16_t)B_1_0_00001000, .result = (uint16_t)B00001000 },
  { .value = (uint16_t)B_0_0_00001000, .result = (uint16_t)B00001000 },
  
  { .value = (uint16_t)B_1_0_00010000, .result = (uint16_t)B00010000 },
  { .value = (uint16_t)B_0_0_00010000, .result = (uint16_t)B00010000 },
  
  { .value = (uint16_t)B_1_0_00100000, .result = (uint16_t)B00100000 },
  { .value = (uint16_t)B_0_0_00100000, .result = (uint16_t)B00100000 },
  
  { .value = (uint16_t)B_1_0_01000000, .result = (uint16_t)B01000000 },
  { .value = (uint16_t)B_0_0_01000000, .result = (uint16_t)B01000000 },

  { .value = (uint16_t)B_1_0_10000000, .result = (uint16_t)B10000000 },
  { .value = (uint16_t)B_0_0_10000000, .result = (uint16_t)B10000000 },

};

K1533IR33::K1533IR33(void) {
  _devices = pin_map_1533_ir33;
  _values = values_1533_ir33;  
  _devices_count = sizeof(pin_map_1533_ir33)/sizeof(pin_map_1533_ir33[0]);
  _values_count = sizeof(values_1533_ir33)/sizeof(values_1533_ir33[0]);
}

const __FlashStringHelper * K1533IR33::menu(void) {
  return F("ИP33 (Регистр)");
}

const __FlashStringHelper * K1533IR33::description(void) {
    return F(
"KP1533ИP33\r\n"
"Регистр\r\n"
"DIP20\r\n"
"\t         20 - +5V        \r\n"
"\t         10 - GND        \r\n"
"\t      -------------      \r\n"
"\t  2 -| D1 | RG | 1 |- 19 \r\n"
"\t  3 -| D2 |    | 2 |- 18 \r\n"
"\t  4 -| D3 |    | 3 |- 17 \r\n"
"\t  5 -| D4 |    | 4 |- 16 \r\n"
"\t  6 -| D5 |    | 5 |- 15 \r\n"
"\t  7 -| D6 |    | 6 |- 14 \r\n"
"\t  8 -| D7 |    | 7 |- 13 \r\n"
"\t  9 -| D8 |    | 8 |- 12 \r\n"
"\t     |----|    |   |     \r\n"
"\t 11 -| C  |    |   |     \r\n"
"\t  1 -o E  |    |   |     \r\n"
"\t      -------------      \r\n"
    );
}

const __FlashStringHelper * K1533IR33::title(void) {
  return F("KP1533ИP33\r\nРегистр\r\nDIP20\r\n");
}
