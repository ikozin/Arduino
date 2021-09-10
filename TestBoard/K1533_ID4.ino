#include "K1533_ID4.h"


void info_1533id4(void) {
  Serial.println(F("КР1533ИД4                                    "));
  Serial.println(F("Два дешифратора                              "));
  Serial.println(F("DIP14                                        "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("                  14 - +5V                   "));
  Serial.println(F("                   7 - GND                   "));
  Serial.println(F("                -------------                "));
  Serial.println(F("PA2(24) <->14 -o &  | DC | 0 o- 9 <-> PC0(37)"));
  Serial.println(F("PA3(25) <->15 -o S0 |    | 1 o-10 <-> PC1(36)"));
  Serial.println(F("               |----|    | 2 o-11 <-> PC2(35)"));
  Serial.println(F("PA0(22) <->13 -| 1  |    | 3 o-12 <-> PC3(34)"));
  Serial.println(F("PA1(23) <-> 3 -| 2  |    |---|               "));
  Serial.println(F("               |----|    | 0 o- 7 <-> PC4(33)"));
  Serial.println(F("PA4(26) <-> 1 -o &  |    | 1 o- 6 <-> PC5(32)"));
  Serial.println(F("PA5(27) <-> 2 -o S1 |    | 2 o- 5 <-> PC6(31)"));
  Serial.println(F("               |    |    | 3 o- 4 <-> PC7(30)"));
  Serial.println(F("                -------------                "));
#endif
  Serial.println();
}

bool test_K1533_ID4() {
  info_1533id4();
  return false;
}
