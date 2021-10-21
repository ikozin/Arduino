#ifdef K1533_KP2
#include "Input8Out8Device.h"

#define B_00_0_0000		B0000000
#define B_00_0_0001		B0000001
#define B_00_0_0010		B0000010
#define B_00_0_0011		B0000011
#define B_00_0_0100		B0000100
#define B_00_0_0101		B0000101
#define B_00_0_0110		B0000110
#define B_00_0_0111		B0000111
#define B_00_0_1000		B0001000
#define B_00_0_1001		B0001001
#define B_00_0_1010		B0001010
#define B_00_0_1011		B0001011
#define B_00_0_1100		B0001100
#define B_00_0_1101		B0001101
#define B_00_0_1110		B0001110
#define B_00_0_1111		B0001111
		                
#define B_01_0_0000		B0100000
#define B_01_0_0001		B0100001
#define B_01_0_0010		B0100010
#define B_01_0_0011		B0100011
#define B_01_0_0100		B0100100
#define B_01_0_0101		B0100101
#define B_01_0_0110		B0100110
#define B_01_0_0111		B0100111
#define B_01_0_1000		B0101000
#define B_01_0_1001		B0101001
#define B_01_0_1010		B0101010
#define B_01_0_1011		B0101011
#define B_01_0_1100		B0101100
#define B_01_0_1101		B0101101
#define B_01_0_1110		B0101110
#define B_01_0_1111		B0101111
		                
#define B_10_0_0000		B1000000
#define B_10_0_0001		B1000001
#define B_10_0_0010		B1000010
#define B_10_0_0011		B1000011
#define B_10_0_0100		B1000100
#define B_10_0_0101		B1000101
#define B_10_0_0110		B1000110
#define B_10_0_0111		B1000111
#define B_10_0_1000		B1001000
#define B_10_0_1001		B1001001
#define B_10_0_1010		B1001010
#define B_10_0_1011		B1001011
#define B_10_0_1100		B1001100
#define B_10_0_1101		B1001101
#define B_10_0_1110		B1001110
#define B_10_0_1111		B1001111
		                
#define B_11_0_0000		B1100000
#define B_11_0_0001		B1100001
#define B_11_0_0010		B1100010
#define B_11_0_0011		B1100011
#define B_11_0_0100		B1100100
#define B_11_0_0101		B1100101
#define B_11_0_0110		B1100110
#define B_11_0_0111		B1100111
#define B_11_0_1000		B1101000
#define B_11_0_1001		B1101001
#define B_11_0_1010		B1101010
#define B_11_0_1011		B1101011
#define B_11_0_1100		B1101100
#define B_11_0_1101		B1101101
#define B_11_0_1110		B1101110
#define B_11_0_1111		B1101111
	                
		                
#define B_00_1_0000		B0010000
#define B_00_1_0001		B0010001
#define B_00_1_0010		B0010010
#define B_00_1_0011		B0010011
#define B_00_1_0100		B0010100
#define B_00_1_0101		B0010101
#define B_00_1_0110		B0010110
#define B_00_1_0111		B0010111
#define B_00_1_1000		B0011000
#define B_00_1_1001		B0011001
#define B_00_1_1010		B0011010
#define B_00_1_1011		B0011011
#define B_00_1_1100		B0011100
#define B_00_1_1101		B0011101
#define B_00_1_1110		B0011110
#define B_00_1_1111		B0011111
		                
#define B_01_1_0000		B0110000
#define B_01_1_0001		B0110001
#define B_01_1_0010		B0110010
#define B_01_1_0011		B0110011
#define B_01_1_0100		B0110100
#define B_01_1_0101		B0110101
#define B_01_1_0110		B0110110
#define B_01_1_0111		B0110111
#define B_01_1_1000		B0111000
#define B_01_1_1001		B0111001
#define B_01_1_1010		B0111010
#define B_01_1_1011		B0111011
#define B_01_1_1100		B0111100
#define B_01_1_1101		B0111101
#define B_01_1_1110		B0111110
#define B_01_1_1111		B0111111
		                
#define B_10_1_0000		B1010000
#define B_10_1_0001		B1010001
#define B_10_1_0010		B1010010
#define B_10_1_0011		B1010011
#define B_10_1_0100		B1010100
#define B_10_1_0101		B1010101
#define B_10_1_0110		B1010110
#define B_10_1_0111		B1010111
#define B_10_1_1000		B1011000
#define B_10_1_1001		B1011001
#define B_10_1_1010		B1011010
#define B_10_1_1011		B1011011
#define B_10_1_1100		B1011100
#define B_10_1_1101		B1011101
#define B_10_1_1110		B1011110
#define B_10_1_1111		B1011111
		                
#define B_11_1_0000		B1110000
#define B_11_1_0001		B1110001
#define B_11_1_0010		B1110010
#define B_11_1_0011		B1110011
#define B_11_1_0100		B1110100
#define B_11_1_0101		B1110101
#define B_11_1_0110		B1110110
#define B_11_1_0111		B1110111
#define B_11_1_1000		B1111000
#define B_11_1_1001		B1111001
#define B_11_1_1010		B1111010
#define B_11_1_1011		B1111011
#define B_11_1_1100		B1111100
#define B_11_1_1101		B1111101
#define B_11_1_1110		B1111110
#define B_11_1_1111		B1111111

Input8Out8DevPin pin_map_1533_kp2[2] =
{
  // Входы     D0  D1  D2  D3   S   1   2
  { .Input = { 32, 33, 34, 35, 37, 23, 36, 0 }, .Output = { 31, 0, 0, 0, 0, 0, 0, 0 }},
  { .Input = { 27, 26, 25, 24, 22, 23, 36, 0 }, .Output = { 28, 0, 0, 0, 0, 0, 0, 0 }},
};

Input8Out8DevVal values_1533_kp2[128] =
{	
  { { .value = B_00_0_0000 }, { .result = 0 } },
  { { .value = B_00_0_0001 }, { .result = 1 } },
  { { .value = B_00_0_0010 }, { .result = 0 } },
  { { .value = B_00_0_0011 }, { .result = 1 } },
  { { .value = B_00_0_0100 }, { .result = 0 } },
  { { .value = B_00_0_0101 }, { .result = 1 } },
  { { .value = B_00_0_0110 }, { .result = 0 } },
  { { .value = B_00_0_0111 }, { .result = 1 } },
  { { .value = B_00_0_1000 }, { .result = 0 } },
  { { .value = B_00_0_1001 }, { .result = 1 } },
  { { .value = B_00_0_1010 }, { .result = 0 } },
  { { .value = B_00_0_1011 }, { .result = 1 } },
  { { .value = B_00_0_1100 }, { .result = 0 } },
  { { .value = B_00_0_1101 }, { .result = 1 } },
  { { .value = B_00_0_1110 }, { .result = 0 } },
  { { .value = B_00_0_1111 }, { .result = 1 } },

  { { .value = B_01_0_0000 }, { .result = 0 } },
  { { .value = B_01_0_0001 }, { .result = 0 } },
  { { .value = B_01_0_0010 }, { .result = 1 } },
  { { .value = B_01_0_0011 }, { .result = 1 } },
  { { .value = B_01_0_0100 }, { .result = 0 } },
  { { .value = B_01_0_0101 }, { .result = 0 } },
  { { .value = B_01_0_0110 }, { .result = 1 } },
  { { .value = B_01_0_0111 }, { .result = 1 } },
  { { .value = B_01_0_1000 }, { .result = 0 } },
  { { .value = B_01_0_1001 }, { .result = 0 } },
  { { .value = B_01_0_1010 }, { .result = 1 } },
  { { .value = B_01_0_1011 }, { .result = 1 } },
  { { .value = B_01_0_1100 }, { .result = 0 } },
  { { .value = B_01_0_1101 }, { .result = 0 } },
  { { .value = B_01_0_1110 }, { .result = 1 } },
  { { .value = B_01_0_1111 }, { .result = 1 } },

  { { .value = B_10_0_0000 }, { .result = 0 } },
  { { .value = B_10_0_0001 }, { .result = 0 } },
  { { .value = B_10_0_0010 }, { .result = 0 } },
  { { .value = B_10_0_0011 }, { .result = 0 } },
  { { .value = B_10_0_0100 }, { .result = 1 } },
  { { .value = B_10_0_0101 }, { .result = 1 } },
  { { .value = B_10_0_0110 }, { .result = 1 } },
  { { .value = B_10_0_0111 }, { .result = 1 } },
  { { .value = B_10_0_1000 }, { .result = 0 } },
  { { .value = B_10_0_1001 }, { .result = 0 } },
  { { .value = B_10_0_1010 }, { .result = 0 } },
  { { .value = B_10_0_1011 }, { .result = 0 } },
  { { .value = B_10_0_1100 }, { .result = 1 } },
  { { .value = B_10_0_1101 }, { .result = 1 } },
  { { .value = B_10_0_1110 }, { .result = 1 } },
  { { .value = B_10_0_1111 }, { .result = 1 } },

  { { .value = B_11_0_0000 }, { .result = 0 } },
  { { .value = B_11_0_0001 }, { .result = 0 } },
  { { .value = B_11_0_0010 }, { .result = 0 } },
  { { .value = B_11_0_0011 }, { .result = 0 } },
  { { .value = B_11_0_0100 }, { .result = 0 } },
  { { .value = B_11_0_0101 }, { .result = 0 } },
  { { .value = B_11_0_0110 }, { .result = 0 } },
  { { .value = B_11_0_0111 }, { .result = 0 } },
  { { .value = B_11_0_1000 }, { .result = 1 } },
  { { .value = B_11_0_1001 }, { .result = 1 } },
  { { .value = B_11_0_1010 }, { .result = 1 } },
  { { .value = B_11_0_1011 }, { .result = 1 } },
  { { .value = B_11_0_1100 }, { .result = 1 } },
  { { .value = B_11_0_1101 }, { .result = 1 } },
  { { .value = B_11_0_1110 }, { .result = 1 } },
  { { .value = B_11_0_1111 }, { .result = 1 } },

  { { .value = B_00_1_0000 }, { .result = 0 } },
  { { .value = B_00_1_0001 }, { .result = 0 } },
  { { .value = B_00_1_0010 }, { .result = 0 } },
  { { .value = B_00_1_0011 }, { .result = 0 } },
  { { .value = B_00_1_0100 }, { .result = 0 } },
  { { .value = B_00_1_0101 }, { .result = 0 } },
  { { .value = B_00_1_0110 }, { .result = 0 } },
  { { .value = B_00_1_0111 }, { .result = 0 } },
  { { .value = B_00_1_1000 }, { .result = 0 } },
  { { .value = B_00_1_1001 }, { .result = 0 } },
  { { .value = B_00_1_1010 }, { .result = 0 } },
  { { .value = B_00_1_1011 }, { .result = 0 } },
  { { .value = B_00_1_1100 }, { .result = 0 } },
  { { .value = B_00_1_1101 }, { .result = 0 } },
  { { .value = B_00_1_1110 }, { .result = 0 } },
  { { .value = B_00_1_1111 }, { .result = 0 } },

  { { .value = B_01_1_0000 }, { .result = 0 } },
  { { .value = B_01_1_0001 }, { .result = 0 } },
  { { .value = B_01_1_0010 }, { .result = 0 } },
  { { .value = B_01_1_0011 }, { .result = 0 } },
  { { .value = B_01_1_0100 }, { .result = 0 } },
  { { .value = B_01_1_0101 }, { .result = 0 } },
  { { .value = B_01_1_0110 }, { .result = 0 } },
  { { .value = B_01_1_0111 }, { .result = 0 } },
  { { .value = B_01_1_1000 }, { .result = 0 } },
  { { .value = B_01_1_1001 }, { .result = 0 } },
  { { .value = B_01_1_1010 }, { .result = 0 } },
  { { .value = B_01_1_1011 }, { .result = 0 } },
  { { .value = B_01_1_1100 }, { .result = 0 } },
  { { .value = B_01_1_1101 }, { .result = 0 } },
  { { .value = B_01_1_1110 }, { .result = 0 } },
  { { .value = B_01_1_1111 }, { .result = 0 } },

  { { .value = B_10_1_0000 }, { .result = 0 } },
  { { .value = B_10_1_0001 }, { .result = 0 } },
  { { .value = B_10_1_0010 }, { .result = 0 } },
  { { .value = B_10_1_0011 }, { .result = 0 } },
  { { .value = B_10_1_0100 }, { .result = 0 } },
  { { .value = B_10_1_0101 }, { .result = 0 } },
  { { .value = B_10_1_0110 }, { .result = 0 } },
  { { .value = B_10_1_0111 }, { .result = 0 } },
  { { .value = B_10_1_1000 }, { .result = 0 } },
  { { .value = B_10_1_1001 }, { .result = 0 } },
  { { .value = B_10_1_1010 }, { .result = 0 } },
  { { .value = B_10_1_1011 }, { .result = 0 } },
  { { .value = B_10_1_1100 }, { .result = 0 } },
  { { .value = B_10_1_1101 }, { .result = 0 } },
  { { .value = B_10_1_1110 }, { .result = 0 } },
  { { .value = B_10_1_1111 }, { .result = 0 } },

  { { .value = B_11_1_0000 }, { .result = 0 } },
  { { .value = B_11_1_0001 }, { .result = 0 } },
  { { .value = B_11_1_0010 }, { .result = 0 } },
  { { .value = B_11_1_0011 }, { .result = 0 } },
  { { .value = B_11_1_0100 }, { .result = 0 } },
  { { .value = B_11_1_0101 }, { .result = 0 } },
  { { .value = B_11_1_0110 }, { .result = 0 } },
  { { .value = B_11_1_0111 }, { .result = 0 } },
  { { .value = B_11_1_1000 }, { .result = 0 } },
  { { .value = B_11_1_1001 }, { .result = 0 } },
  { { .value = B_11_1_1010 }, { .result = 0 } },
  { { .value = B_11_1_1011 }, { .result = 0 } },
  { { .value = B_11_1_1100 }, { .result = 0 } },
  { { .value = B_11_1_1101 }, { .result = 0 } },
  { { .value = B_11_1_1110 }, { .result = 0 } },
  { { .value = B_11_1_1111 }, { .result = 0 } },
	};

void info_1533_kp2(void) {
  Serial.println(F("КР1533КП2                            "));
  Serial.println(F("Мультиплексор                        "));
  Serial.println(F("DIP16                                "));
  Serial.println(F("              16 - +5V               "));
  Serial.println(F("               8 - GND               "));
  Serial.println(F("              ---------              "));
  Serial.println(F("    (32)  6 -| D0 | MS |- 7 (31)     "));
  Serial.println(F("    (33)  5 -| D1 |    |             "));
  Serial.println(F("    (34)  4 -| D2 |    |             "));
  Serial.println(F("    (35)  3 -| D3 |    |             "));
  Serial.println(F("             |----|    |             "));
  Serial.println(F("    (37)  1 -o S  |    |             "));
  Serial.println(F("             |---------|             "));
  Serial.println(F("    (27) 10 -| D0 | MS |- 9 (28)     "));
  Serial.println(F("    (26) 11 -| D1 |    |             "));
  Serial.println(F("    (25) 12 -| D2 |    |             "));
  Serial.println(F("    (24) 13 -| D3 |    |             "));
  Serial.println(F("             |----|    |             "));
  Serial.println(F("    (22) 15 -o S  |    |             "));
  Serial.println(F("             |----|    |             "));
  Serial.println(F("    (23) 14 -| 1  |    |             "));
  Serial.println(F("    (36)  2 -| 2  |    |             "));
  Serial.println(F("              ---------              "));
  Serial.println();
}

void test_1533_kp2(void) {
  info_1533_kp2();
  init_Input8Out8Dev(pin_map_1533_kp2, 2);
  int result = check_Input8Out8Dev(pin_map_1533_kp2, 2, values_1533_kp2, 128);
  if (result == 0) {
    Serial.println(F("\nТЕСТ ПРОЙДЕН"));
  }
  else {
    Serial.println(F("\n!!! ОШИБКА !!!"));
    Serial.print(F("Кол-во ошибок = "));
    Serial.println(result);
  }
  done_Input8Out8Dev();
}

#endif
