#include "K1533_KP2.h"

void info_1533kp2(void) {
  Serial.println(F("КР1533КП2                                "));
  Serial.println(F("Мультиплексор                            "));
  Serial.println(F("DIP16                                    "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("                16 - +5V                 "));
  Serial.println(F("                 8 - GND                 "));
  Serial.println(F("                ---------                "));
  Serial.println(F("PA0(22) <-> 6 -| D0 | MS |- 7 <-> PC0(37)"));
  Serial.println(F("PA1(23) <-> 5 -| D1 |    |               "));
  Serial.println(F("PA2(24) <-> 4 -| D2 |    |               "));
  Serial.println(F("PA3(25) <-> 3 -| D3 |    |               "));
  Serial.println(F("               |----|    |               "));
  Serial.println(F("PL0(49) <-> 1 -o S  |    |               "));
  Serial.println(F("               |---------|               "));
  Serial.println(F("PA4(26) <->10 -| D0 | MS |- 9 <-> PC1(36)"));
  Serial.println(F("PA5(27) <->11 -| D1 |    |               "));
  Serial.println(F("PA6(28) <->12 -| D2 |    |               "));
  Serial.println(F("PA7(29) <->13 -| D3 |    |               "));
  Serial.println(F("               |----|    |               "));
  Serial.println(F("PL1(48) <->15 -o S  |    |               "));
  Serial.println(F("               |----|    |               "));
  Serial.println(F("PL2(47) <->14 -| 1  |    |               "));
  Serial.println(F("PL3(46) <-> 2 -| 2  |    |               "));
  Serial.println(F("                ---------                "));
#endif
  Serial.println();
}

bool test_K1533_KP2() {
  info_1533kp2();
  K1533KP2_PA_t pa = { .value = 0x00 };
  K1533KP2_PL_t pl = { .value = 0x00 };

  pl.S_0 = 1;
  pl.S_1 = 1;
  pa.value = 0xFF;
  PORTA = pa.value;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 1 из 7"));
  Serial.print(F("PA="));
  printBin(pa.value);
  Serial.println();
#endif
  if (!test_KP2_check_0(&pl)) return false;

  pl.S_0 = 1;
  pl.S_1 = 1;
  pa.value = 0x00;
  PORTA = pa.value;
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 2 из 7"));
  Serial.print(F("PA="));
  printBin(pa.value);
  Serial.println();
#endif
  if (!test_KP2_check_0(&pl)) return false;

  pl.S_0 = 0;
  pl.S_1 = 0;
  pa.value = 0x00;
  PORTA = pa.value;
#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 3 из 7"));
  Serial.print(F("PA="));
  printBin(pa.value);
  Serial.println();
#endif
  if (!test_KP2_check_0(&pl)) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 4 из 7"));
#endif
  pl.S_0 = 0;
  pl.S_1 = 0;
  if (!test_KP2_check_1(&pl, 0)) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 5 из 7"));
#endif
  pl.S_0 = 0;
  pl.S_1 = 0;
  if (!test_KP2_check_1(&pl, 1)) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 6 из 7"));
#endif
  pl.S_0 = 0;
  pl.S_1 = 0;
  if (!test_KP2_check_1(&pl, 2)) return false;

#ifdef DETAIL_INFO
  Serial.println(F("Проверка, шаг 7 из 7"));
#endif
  pl.S_0 = 0;
  pl.S_1 = 0;
  if (!test_KP2_check_1(&pl, 3)) return false;

  return true;
}

bool test_KP2_check_0(K1533KP2_PL_t* pl) {
  K1533KP2_PC_t pc;
  for (int i = 0; i < 4; i++) {
    pl->Addr = i;
    PORTL = pl->value;
    delay(1);
    pc.value = PINC;
#ifdef DETAIL_INFO
    println_PL_PC(pl->value, pc.value & K1533KP2_PC_MASK);
#endif
    if (pc.Data_0 != 0) return false;
    if (pc.Data_1 != 0) return false;
  }
  return true;
}

bool test_KP2_check_1(K1533KP2_PL_t* pl, int data) {
  K1533KP2_PC_t pc;
  K1533KP2_PA_t pa = { .value = 0x00 };

  pa.value = 1 << data;
  PORTA = pa.value;

#ifdef DETAIL_INFO
  Serial.print(F("PA="));
  printBin(pa.value);
  Serial.println();
#endif
  
  for (int i = 0; i < 4; i++) {
    pl->Addr = i;
    PORTL = pl->value;
    delay(1);
    pc.value = PINC;

#ifdef DETAIL_INFO
    println_PL_PC(pl->value, pc.value & K1533KP2_PC_MASK);
#endif
    
    if (i == data && pc.Data_0 != 1) return false;
    if (i != data && pc.Data_0 != 0) return false;
    //if (pc.Data_1 != 0) return false;
  }
  
  pa.value = (1 << data) << 4;
  PORTA = pa.value;

#ifdef DETAIL_INFO
  Serial.print(F("PA="));
  printBin(pa.value);
  Serial.println();
#endif

  for (int i = 0; i < 4; i++) {
    pl->Addr = i;
    PORTL = pl->value;
    delay(1);
    pc.value = PINC;

#ifdef DETAIL_INFO
    println_PL_PC(pl->value, pc.value & K1533KP2_PC_MASK);
#endif

    if (i == data && pc.Data_1 != 1) return false;
    if (i != data && pc.Data_1 != 0) return false;
    //if (pc.Data_0 != 0) return false;
  }
  
  return true;
}
