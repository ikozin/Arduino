#include "K1533_TM2.h"

void info_1533tm2(void) {
  Serial.println(F("КР1533ТМ2                               "));
  Serial.println(F("2 D-триггера                            "));
  Serial.println(F("DIP14                                   "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("               14 - +5V                 "));
  Serial.println(F("                7 - GND                 "));
  Serial.println(F("                --------                "));
  Serial.println(F("PA0(22) <-> 1 -| R | TT |- 5 <-> PC0(37)"));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA1(23) <-> 2 -| D |    |               "));
  Serial.println(F("PA2(24) <-> 3 -/ С |    |               "));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA3(25) <-> 4 -| S |    o- 6 <-> PC1(36)"));
  Serial.println(F("                --------                "));
  Serial.println(F("                --------                "));
  Serial.println(F("PA4(26) <->13 -| R | TT |- 9 <-> PC2(35)"));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA5(27) <->12 -| D |    |               "));
  Serial.println(F("PA6(28) <->11 -/ С |    |               "));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA7(29) <->10 -| S |    o- 8 <-> PC3(34)"));
  Serial.println(F("                --------                "));
#endif
  Serial.println();
}

bool test_K1533_TM2() {
  info_1533tm2();
  K1533TM2_PA_t pa = { .value = 0x00 };
  K1533KP2_PC_t pl = { .value = 0x00 };

#ifdef DETAIL_INFO
  Serial.print(F("Проверка, шаг 1 из X"));
#endif
  pa.TT.D0 = 1;
  Serial.println();
  printBin(pa.value);
  pa.TT.D1 = 1;
  Serial.println();
  printBin(pa.value);

  return true;
}
