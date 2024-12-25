#include "K1533_TM8.h"

const static TDevicePin PROGMEM pin_map_1533_tm8[] =
{
  // Входы     D1  D2  D3  D4   C   R             Выходы      1       2       3       4
  { .Input = {  4,  5, 12, 13,  9,  1,  0,  0 }, .Output = {  2,  3,  7,  6, 10, 11, 15, 14 }},
};

const static TDeviceVal PROGMEM values_1533_tm8[] =
{  
  { .value = (uint16_t)B_0_0_0000, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_0001, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_0010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_0011, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_0100, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_0101, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_0110, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_0111, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1000, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1001, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1011, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1100, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1101, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1110, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_0_1111, .result = (uint16_t)B10101010 },

  { .value = (uint16_t)B_0_1_0000, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_0001, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_0010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_0011, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_0100, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_0101, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_0110, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_0111, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1000, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1001, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1010, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1011, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1100, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1101, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1110, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_0_1_1111, .result = (uint16_t)B10101010 },

  { .value = (uint16_t)B_1_0_0000, .result = (uint16_t)B10101010 },

  { .value = (uint16_t)B_1_1_0000, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_1_0_0000, .result = (uint16_t)B10101010 },
  { .value = (uint16_t)B_1_1_0001, .result = (uint16_t)B10101001 },
  { .value = (uint16_t)B_1_0_0001, .result = (uint16_t)B10101001 },
  { .value = (uint16_t)B_1_1_0010, .result = (uint16_t)B10100110 },
  { .value = (uint16_t)B_1_0_0010, .result = (uint16_t)B10100110 },
  { .value = (uint16_t)B_1_1_0011, .result = (uint16_t)B10100101 },
  { .value = (uint16_t)B_1_0_0011, .result = (uint16_t)B10100101 },
  { .value = (uint16_t)B_1_1_0100, .result = (uint16_t)B10011010 },
  { .value = (uint16_t)B_1_0_0100, .result = (uint16_t)B10011010 },
  { .value = (uint16_t)B_1_1_0101, .result = (uint16_t)B10011001 },
  { .value = (uint16_t)B_1_0_0101, .result = (uint16_t)B10011001 },
  { .value = (uint16_t)B_1_1_0110, .result = (uint16_t)B10010110 },
  { .value = (uint16_t)B_1_0_0110, .result = (uint16_t)B10010110 },
  { .value = (uint16_t)B_1_1_0111, .result = (uint16_t)B10010101 },
  { .value = (uint16_t)B_1_0_0111, .result = (uint16_t)B10010101 },
  { .value = (uint16_t)B_1_1_1000, .result = (uint16_t)B01101010 },
  { .value = (uint16_t)B_1_0_1000, .result = (uint16_t)B01101010 },
  { .value = (uint16_t)B_1_1_1001, .result = (uint16_t)B01101001 },
  { .value = (uint16_t)B_1_0_1001, .result = (uint16_t)B01101001 },
  { .value = (uint16_t)B_1_1_1010, .result = (uint16_t)B01100110 },
  { .value = (uint16_t)B_1_0_1010, .result = (uint16_t)B01100110 },
  { .value = (uint16_t)B_1_1_1011, .result = (uint16_t)B01100101 },
  { .value = (uint16_t)B_1_0_1011, .result = (uint16_t)B01100101 },
  { .value = (uint16_t)B_1_1_1100, .result = (uint16_t)B01011010 },
  { .value = (uint16_t)B_1_0_1100, .result = (uint16_t)B01011010 },
  { .value = (uint16_t)B_1_1_1101, .result = (uint16_t)B01011001 },
  { .value = (uint16_t)B_1_0_1101, .result = (uint16_t)B01011001 },
  { .value = (uint16_t)B_1_1_1110, .result = (uint16_t)B01010110 },
  { .value = (uint16_t)B_1_0_1110, .result = (uint16_t)B01010110 },
  { .value = (uint16_t)B_1_1_1111, .result = (uint16_t)B01010101 },
  { .value = (uint16_t)B_1_0_1111, .result = (uint16_t)B01010101 },
};

K1533TM8::K1533TM8() {
  _devices = pin_map_1533_tm8;
  _values = values_1533_tm8;  
  _devices_count = sizeof(pin_map_1533_tm8)/sizeof(pin_map_1533_tm8[0]);
  _values_count = sizeof(values_1533_tm8)/sizeof(values_1533_tm8[0]);
}

const __FlashStringHelper * K1533TM8::menu(void) {
  return F("TM8 (Регистр)");
}

const __FlashStringHelper * K1533TM8::description(void) {
    return F(
"KP1533TM8\r\n"
"Регистр\r\n"
"DIP16\r\n"
"\t        16 - +5V         \r\n"
"\t         8 - GND         \r\n"
"\t      -------------      \r\n"
"\t  4 -| D1 | RG | 1 |- 2  \r\n"
"\t  5 -| D2 |    |   o- 3  \r\n"
"\t 12 -| D3 |    | 2 |- 7  \r\n"
"\t 13 -| D4 |    |   o- 6  \r\n"
"\t     |    |    | 3 |- 10 \r\n"
"\t  9 -/ C  |    |   o- 11 \r\n"
"\t     |    |    | 4 |- 15 \r\n"
"\t  1 -o R  |    |   o- 14 \r\n"
"\t      -------------      \r\n"
    );
}

const __FlashStringHelper * K1533TM8::title(void) {
  return F("KP1533TM8\r\nРегистр\r\nDIP16\r\n");
}
