#include "K565_RU5.h"

K565RU5_PA_t k565ru5_pa;
K565RU5_PL_t k565ru5_pl;
K565RU5_PC_t k565ru5_pc;

void info_565ru5(void) {
  Serial.println(F("К565РУ5                                         "));
  Serial.println(F("Динамическое ОЗУ                                "));
  Serial.println(F("DIP16                                           "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("               XXXXXXXXXXXXXXXXXX               "));
  Serial.println(F("               XXX    ВАЖНО   XXX               "));
  Serial.println(F("               XXX   8 - +5V  XXX               "));
  Serial.println(F("               XXX  16 - GND  XXX               "));
  Serial.println(F("               XXXXXXXXXXXXXXXXXX               "));
  Serial.println(F("                ----------------                "));
  Serial.println(F("PA0(22) <-> 5 -| A0  | RAM | DO |- 14<-> PC0(37)"));
  Serial.println(F("PA1(23) <-> 7 -| A1  | 64K |    |               "));
  Serial.println(F("PA2(24) <-> 6 -| A2  |     |    |               "));
  Serial.println(F("PA3(25) <->12 -| A3  |     |    |               "));
  Serial.println(F("PA4(26) <->11 -| A4  |     |    |               "));
  Serial.println(F("PA5(27) <->10 -| A5  |     |    |               "));
  Serial.println(F("PA6(28) <->13 -| A6  |     |    |               "));
  Serial.println(F("PA7(29) <-> 9 -| A7  |     |    |               "));
  Serial.println(F("               |-----|     |    |               "));
  Serial.println(F("PL0(49) <-> 2 -| DI  |     |    |               "));
  Serial.println(F("               |------     |    |               "));
  Serial.println(F("PL1(48) <-> 4 -o RAS |     |    |               "));
  Serial.println(F("PL2(47) <->15 -o CAS |     |    |               "));
  Serial.println(F("               |------     |    |               "));
  Serial.println(F("PL3(46) <-> 3 -o R/W |     |    |               "));
  Serial.println(F("                ----------------                "));
#endif
  Serial.println();
}

static inline void writeRamFast(int row, int col, byte value) {
  PORTA = row;
  PORTL = value | K565RU5_PL_CAS_MASK | K565RU5_PL_WE_MASK;
  PORTA = col;
  PORTL = value | K565RU5_PL_CAS_MASK;
  PORTL = value;
  _NOP();
  PORTL = value | K565RU5_PL_RAS_MASK | K565RU5_PL_CAS_MASK | K565RU5_PL_WE_MASK;
}

static inline uint8_t readRamFast(int row, int col, int value) {
  PORTA = row;
  PORTL = (!value) | K565RU5_PL_CAS_MASK | K565RU5_PL_WE_MASK;
  PORTA = col;
  PORTL = (!value) | K565RU5_PL_WE_MASK;
  _NOP();
  byte result = PINC;
  PORTL = (!value) | K565RU5_PL_RAS_MASK | K565RU5_PL_CAS_MASK | K565RU5_PL_WE_MASK;
  _NOP();
  return result & 1;
}

bool test_565ru5_fill(uint8_t data) {
#ifdef DETAIL_INFO
  Serial.print("Проверка на ");
  Serial.println(data);
#endif

  noInterrupts();
  uint8_t value;
  value = data;
  for (int col = 0; col < 256; col++) {
    for (int row = 0; row < 256; row++) {
      writeRamFast(row, col, value);
    }
  }
  for (int col = 0; col < 256; col++) {
    for (int row = 0; row < 256; row++) {
      uint8_t result = readRamFast(row, col, value);
      if (result != data) {
        interrupts();
        sprintf(text, "Ошибка row=%02X col=%02X %d", row, col, result);
        Serial.println(text);
        return false;
      }
    }
  }
  interrupts();
  return true;
}

bool test_565ru5_flipflop(uint8_t data) {
#ifdef DETAIL_INFO
  Serial.print("Запись, чередование ");
  Serial.print((int)data);
  Serial.print(" и ");
  Serial.println((int)!data);
#endif

  noInterrupts();
  uint8_t value;
  value = data;
  for (int col = 0; col < 256; col++) {
    for (int row = 0; row < 256; row++) {
      writeRamFast(row, col, value);
    }
  }
  for (int col = 0; col < 256; col++) {
    for (int row = 0; row < 256; row++) {
      uint8_t result = readRamFast(row, col, value);
      if (result != value) {
        interrupts();
        sprintf(text, "Ошибка row=%02X col=%02X %d", row, col, result);
        Serial.println(text);
        return false;
      }
      value = !value;
    }
  }
  interrupts();
  return true;
}

bool test_565ru5_random(int seed) {
#ifdef DETAIL_INFO
  Serial.print("Запись, random seed = ");
  Serial.println(seed);
#endif

  uint8_t value;
  randomSeed(seed);
  noInterrupts();
  for (int col = 0; col < 256; col++) {
    for (int row = 0; row < 256; row++) {
      value = random(0,2);
      writeRamFast(row, col, value);
      uint8_t result = readRamFast(row, col, value);
      if (result != value) {
        interrupts();
        sprintf(text, "Ошибка row=%02X col=%02X value=%d", row, col, result);
        Serial.println(text);
        return false;
      }
    }
  }  
  interrupts();
  return true;
}

bool test_K565_RU5() {
  info_565ru5();  
  delay(50);
  if (!test_565ru5_fill(0)) return false;
  if (!test_565ru5_fill(1)) return false;
  if (!test_565ru5_flipflop(0)) return false;
  if (!test_565ru5_flipflop(1)) return false;
  if (!test_565ru5_random(0x55)) return false;
  if (!test_565ru5_random(0xAA)) return false;
  return false;
}
