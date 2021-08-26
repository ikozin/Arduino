#include "K1533_IE5.h"

void info_1533ie5(void) {
  Serial.println(F("КР1533ИЕ5                                     "));
  Serial.println(F("Двоичный счетчик                              "));
  Serial.println(F("DIP14                                         "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("              XXXXXXXXXXXXXXXXXX              "));
  Serial.println(F("              XXX    ВАЖНО   XXX              "));
  Serial.println(F("              XXX  5 - +5V   XXX              "));
  Serial.println(F("              XXX 10 - GND   XXX              "));
  Serial.println(F("              XXXXXXXXXXXXXXXXXX              "));
  Serial.println(F("                --------------                "));
  Serial.println(F("PA0(22) <->14 -\\ C1 | CT2 | 1 |- 12<-> PC0(37)"));
  Serial.println(F("PA1(23) <-> 1 -\\ C2 |     | 2 |- 9 <-> PC0(36)"));
  Serial.println(F("               |----|     | 4 |- 8 <-> PC0(35)"));
  Serial.println(F("PA2(24) <-> 2 -| &  |     | 8 |-11 <-> PC0(34)"));
  Serial.println(F("PA3(25) <-> 3 -| R  |     |   |               "));
  Serial.println(F("                --------------                "));
#endif
  Serial.println();
}

bool test_K1533_IE5() {
  info_1533ie5();
  K1533IE5_PA_t pa = { .value = 0x00 };
  K1533IE5_PC_t pc = { .value = 0x00 };

  pa.R0 = 1;
  pa.R1 = 1;
  PORTA = pa.value;
  delay(1);
  pc.value = PINC;
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 1 из 10"));
  println_PA_PC(pa.value, pc.value & K1533IE5_PC_MASK);
#endif
  if (pc.D1 != 0) return false;
  if (pc.D2 != 0) return false;
  if (pc.D4 != 0) return false;
  if (pc.D8 != 0) return false;
  
  pa.R0 = 0;
  pa.R1 = 0;
  PORTA = pa.value;
  delay(1);
  pc.value = PINC;
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 2 из 10"));
  println_PA_PC(pa.value, pc.value & K1533IE5_PC_MASK);
#endif
  if (pc.D1 != 0) return false;
  if (pc.D2 != 0) return false;
  if (pc.D4 != 0) return false;
  if (pc.D8 != 0) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 3 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 1) return false;
  if (pc.D8 != 0) return false;
  
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 4 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 0) return false;
  if (pc.D8 != 1) return false;
  
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 5 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 1) return false;
  if (pc.D8 != 1) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 6 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 0) return false;
  if (pc.D8 != 0) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 7 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 1) return false;
  if (pc.D8 != 0) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 8 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 0) return false;
  if (pc.D8 != 1) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 9 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 1) return false;
  if (pc.D8 != 1) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 10 из 10"));
#endif
  if (!test_K1533_IE5_clock(&pa, &pc)) return false;
  if (pc.D4 != 0) return false;
  if (pc.D8 != 0) return false;

  return true     ;
}

bool test_K1533_IE5_clock(K1533IE5_PA_t *pa, K1533IE5_PC_t *pc) {
  pa->C1 = 1;
  pa->C2 = 1;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;
  if (pc->D1 != 0) return false;
  if (pc->D2 != 0) return false;
#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533IE5_PC_MASK);
#endif

  pa->C1 = 0;
  pa->C2 = 0;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;
  if (pc->D1 != 1) return false;
  if (pc->D2 != 1) return false;
#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533IE5_PC_MASK);
#endif

  pa->C1 = 1;
  pa->C2 = 1;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;
  if (pc->D1 != 1) return false;
  if (pc->D2 != 1) return false;
#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533IE5_PC_MASK);
#endif

  pa->C1 = 0;
  pa->C2 = 0;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;
  if (pc->D1 != 0) return false;
  if (pc->D2 != 0) return false;
#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533IE5_PC_MASK);
#endif

  return true;
}
