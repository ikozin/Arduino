#include <Arduino.h>
#include "bindef.h"
#include "K565_RU5.h"
#include "K1533_KP2.h"
#include "K1533_TM2.h"
#include "K1533_IE5.h"

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif

#define DETAIL_INFO
#define DETAIL_GRAPHIC

typedef struct {
  int count;
  byte in_mask;
  byte out_mask;
  byte *in_data;
  byte *out_data;
} TemplCheckLogic;

char text[128];

void  setup() {
  //Serial.println("!!!");  //ЭТО БАГ Aduino Mega, ПРИ НАЛИЧИИ СТРОКИ "!!!" ВЫЗЫВАЕТ ОШИБКУ ЗАГРУЗКИ, НАПРИМЕР: char text[128] = "!!!";

  DDRA = B11111111;   // Set output mode
  DDRL = B11111111;   // Set output mode
  DDRC = B00000000;   // Set input mode

  PORTC = B11111111;   // Set pullup mode
  PORTA = B11111111;   // Set high level
  //PORTA = B00000000;   // Set high level
  PORTL = B11111111;   // Set high level


  // Initialize Serial
  Serial.begin(57600);
  while (!Serial);
  Serial.println(F("\nСтарт"));
}

void  loop() {
  //if (!test_K1553_LA1_LA6_LA7()) while (true);
  //if (!test_K1553_LA3_LA9_LA11_LA12_LA13()) while (true);
  //if (!test_K1553_LE1_LE5_LE6()) while (true);
  //if (!test_K1553_LI1_LI2()) while (true);
  //if (!test_K1553_LN1_LN2_LN3_LN5_LN8()) while (true);
  
  //if (!test_K1533_KP2()) while (true);
  //if (!test_K1533_TM2()) while (true);
  //if (!test_K1533_IE5()) while (true);
  
  if (!test_K565_RU5()) delay(1000);
  Serial.println(F("\nТЕСТИРОВАНИЕ ПРОЙДЕНО!"));
  delay(1000);
}
/*
PA0 - 22
PA1 - 23
PA2 - 24
PA3 - 25
PA4 - 26
PA5 - 27
PA6 - 28
PA7 - 29

PC0 - 37
PC1 - 36
PC2 - 35
PC3 - 34
PC4 - 33
PC5 - 32
PC6 - 31
PC7 - 30

PL0 - 49
PL1 - 48
PL2 - 47
PL3 - 46
PL4 - 45
PL5 - 44
PL6 - 43
PL7 - 42

*/

bool checkLogic(void (*info)(void), TemplCheckLogic *pData) {
  info();
  for (int i = 0; i < pData->count; i++) {
#ifdef DETAIL_INFO
    sprintf(text, "Проверка, шаг %d из %d", (int)i + 1, (int)pData->count);
    Serial.println(text);

    Serial.print(F("Вход: "));
#endif
    byte data = pData->in_data[i];
    data &= pData->in_mask;
#ifdef DETAIL_INFO
    printBin(data);
#endif
    PORTA = data;
    delay(1);
#ifdef DETAIL_INFO
    Serial.print(F(", Выход: "));
#endif
    data = PINC;
    data &= pData->out_mask;
#ifdef DETAIL_INFO
    printBin(data);
    Serial.print(", ");
#endif
    if (pData->out_data[i] == data) {
#ifdef DETAIL_INFO
      Serial.println(F("Проверено"));
#endif
    } else {
      Serial.print(F("Ошибка!"));
#ifdef DETAIL_INFO
      Serial.print(", ожидалось: ");
      printBin(pData->out_data[i]);
#endif
      Serial.println();
      return false;
    }
  }
  return true;
}
  
void printBin(byte data) {
  byte bit;
  for (int i = 7; i >= 0; i--) {
    bit = (data >> i) & 1;
    Serial.print(bit);    
  }
  sprintf(text, " [%02X]", data);
  Serial.print(text);
}

void println_PA_PC(uint8_t pa, uint8_t pc) {
  Serial.print(F("PA="));
  printBin(pa);
  Serial.print(F(", PC="));
  printBin(pc);
  Serial.println();
}

void println_PL_PC(uint8_t pl, uint8_t pc) {
  Serial.print(F("PL="));
  printBin(pl);
  Serial.print(F(", PC="));
  printBin(pc);
  Serial.println();
}

/*
void setDataInMode() {
  DDRL = B00000000;
}

void setDataOutMode() {
  DDRL = B11111111;
}

void setDataPort(byte data) {
  PORTL = data;
}

byte getDataPort() {
  return PINL;
}

void setAddress(uint16_t addr) {
  PORTA = lowByte(addr);
  PORTC = highByte(addr);
}

*/
