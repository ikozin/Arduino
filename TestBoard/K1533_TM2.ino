#include "K1533_TM2.h"

void info_1533tm2(void) {
  Serial.println(F("КР1533ТМ2                               "));
  Serial.println(F("2 D-триггера                            "));
  Serial.println(F("DIP14                                   "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("               14 - +5V                 "));
  Serial.println(F("                7 - GND                 "));
  Serial.println(F("                --------                "));
  Serial.println(F("PA0(22) <-> 1 -o R | TT |- 5 <-> PC0(37)"));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA1(23) <-> 2 -| D |    |               "));
  Serial.println(F("PA2(24) <-> 3 -/ С |    |               "));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA3(25) <-> 4 -o S |    o- 6 <-> PC1(36)"));
  Serial.println(F("                --------                "));
  Serial.println(F("                --------                "));
  Serial.println(F("PA4(26) <->13 -o R | TT |- 9 <-> PC2(35)"));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA5(27) <->12 -| D |    |               "));
  Serial.println(F("PA6(28) <->11 -/ С |    |               "));
  Serial.println(F("               |---|    |               "));
  Serial.println(F("PA7(29) <->10 -o S |    o- 8 <-> PC3(34)"));
  Serial.println(F("                --------                "));
#endif
  Serial.println();
}

bool test_K1533_TM2() {
  info_1533tm2();
  K1533TM2_PA_t pa = { .value = 0x00 };
  K1533TM2_PC_t pc = { .value = 0x00 };
  
  PORTA = pa.value;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 1 из 8"));
#endif
  test_K1533_TM2_setmode(&pa, &pc);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 1) return false;
  
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 2 из 8"));
#endif
  test_K1533_TM2_storemode(&pa, &pc);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 1) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 3 из 8"));
#endif
  test_K1533_TM2_resetmode(&pa, &pc);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 0) return false;
  
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 4 из 8"));
#endif
  test_K1533_TM2_storemode(&pa, &pc);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 0) return false;
  
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 5 из 8"));
#endif
  test_K1533_TM2_setdata(&pa, &pc, 1);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 0) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 6 из 8"));
#endif
  test_K1533_TM2_clock(&pa, &pc);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 1) return false;
  
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 7 из 8"));
#endif
  test_K1533_TM2_setdata(&pa, &pc, 0);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 1) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 8 из 8"));
#endif
  test_K1533_TM2_clock(&pa, &pc);
  if (pc.Data_0 == pc.DataNot_0) return false;
  if (pc.Data_1 == pc.DataNot_1) return false;
  if (pc.Data_0 != pc.Data_1 && pc.Data_0 != 0) return false;

  return true;
}

void test_K1533_TM2_storemode(K1533TM2_PA_t *pa, K1533TM2_PC_t *pc) {
  pa->TT.R0 = 1;
  pa->TT.R1 = 1;
  pa->TT.S0 = 1;
  pa->TT.S1 = 1;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;

#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533TM2_PC_MASK);
#endif
}

void test_K1533_TM2_setmode(K1533TM2_PA_t *pa, K1533TM2_PC_t *pc) {
  pa->TT.R0 = 1;
  pa->TT.R1 = 1;
  pa->TT.S0 = 0;
  pa->TT.S1 = 0;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;

#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533TM2_PC_MASK);
#endif
}

void test_K1533_TM2_resetmode(K1533TM2_PA_t *pa, K1533TM2_PC_t *pc) {
  pa->TT.R0 = 0;
  pa->TT.R1 = 0;
  pa->TT.S0 = 1;
  pa->TT.S1 = 1;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;

#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533TM2_PC_MASK);
#endif
}

void test_K1533_TM2_setdata(K1533TM2_PA_t *pa, K1533TM2_PC_t *pc, uint8_t data) {
  pa->TT.D0 = data > 0;
  pa->TT.D1 = data > 0;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;

#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533TM2_PC_MASK);
#endif
}

void test_K1533_TM2_clock(K1533TM2_PA_t *pa, K1533TM2_PC_t *pc) {
  pa->TT.C0 = 1;
  pa->TT.C1 = 1;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;

#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533TM2_PC_MASK);
#endif
  pa->TT.C0 = 0;
  pa->TT.C1 = 0;
  PORTA = pa->value;
  delay(1);
  pc->value = PINC;

#ifdef DETAIL_INFO
  println_PA_PC(pa->value, pc->value & K1533TM2_PC_MASK);
#endif
}
