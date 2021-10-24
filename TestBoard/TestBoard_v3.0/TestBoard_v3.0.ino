#include <Arduino.h>

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif

#define PIN_BUTTON  38  //PD7
#define PIN_LED1    41  //PG0
#define PIN_LED2    40  //PG1


/*
    PC0(37)[ 1]   [14]  VCC         PC0(37)[ 1]   [16]  VCC         PL0(40)[ 1]   [20]  VCC
    PC1(36)[ 2]   [13]PA0(22)       PC1(36)[ 2]   [15]PA0(22)       PC0(37)[ 2]   [19]PL1(48)
    PC2(35)[ 3]   [12]PA1(23)       PC2(35)[ 3]   [14]PA1(23)       PC1(36)[ 3]   [18]PA0(22)
    PC3(34)[ 4]   [11]PA2(24)       PC3(34)[ 4]   [13]PA2(24)       PC2(35)[ 4]   [17]PA1(23)
    PC4(33)[ 5]   [10]PA3(25)       PC4(33)[ 5]   [12]PA3(25)       PC3(34)[ 5]   [16]PA2(24)
    PC5(32)[ 6]   [ 9]PA4(26)       PC5(32)[ 6]   [11]PA4(26)       PC4(33)[ 6]   [15]PA3(25)
      GND  [ 7]   [ 8]PA5(27)       PC6(31)[ 7]   [10]PA5(27)       PC5(32)[ 7]   [14]PA4(26)
                                      GND  [ 8]   [ 9]PA6(28)       PC6(31)[ 8]   [13]PA5(27)
                                                                    PC7(30)[ 9]   [12]PA6(28)
                                                                      GND  [10]   [11]PA7(29)
*/

#define K1533_LN1_LN2_LN3_LN5_LN8
#define K1533_LA3_LA9_LA11_LA12_LA13_TL3
#define K1533_LI1_LI2
#define K1533_LE1_LE5_LE6
#define K1533_KP2
#define K1533_TM2
#define K1533_ID4

#include "DipI8O8Device.h"

#include "K1533_LN1_LN2_LN3_LN5_LN8.h"
#include "K1533_LA3_LA9_LA11_LA12_LA13_TL3.h"
#include "K1533_LI1_LI2.h"
#include "K1533_LE1_LE5_LE6.h"
#include "K1533_KP2.h"
#include "K1533_TM2.h"
#include "K1533_ID4.h"

#define DEBUG


TInput8Out8Dev * device = NULL;

void setup() {
  //Serial.println("!!!");  //ЭТО БАГ Aduino Mega, ПРИ НАЛИЧИИ СТРОКИ "!!!" ВЫЗЫВАЕТ ОШИБКУ ЗАГРУЗКИ, НАПРИМЕР: char text[128] = "!!!";

  DDRA = B00000000;   // Set input mode
  DDRC = B00000000;   // Set input mode
  DDRL = B00000000;   // Set input mode

  PORTA = B11111111;  // Set pullup mode
  PORTC = B11111111;  // Set pullup mode
  PORTL = B11111111;  // Set pullup mode


/*
  DDRA = B11111111;   // Set output mode
  DDRL = B11111111;   // Set output mode
  DDRC = B00000000;   // Set input mode

  PORTC = B11111111;   // Set pullup mode
  PORTA = B11111111;   // Set high level
  //PORTA = B00000000;   // Set high level
  PORTL = B11111111;   // Set high level
*/
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  // Initialize Serial
  Serial.begin(57600);
  while (!Serial);
  Serial.println(F("\nСтарт"));
  showMenu();
}

void showMenu() {
  Serial.println(F("1 - ЛН1 ЛН2 ЛН3 ЛН5 ЛН8 (6 элементов НЕ)"));
  Serial.println(F("2 - ЛА3 ЛА9 ЛА11 ЛА12 ЛА13 ТЛ3 (4 элемента 2И-НЕ)"));
  Serial.println(F("3 - ЛИ1 ЛИ2 (4 элемента 2И)"));
  Serial.println(F("4 - ЛЕ1 ЛЕ5 ЛЕ6 (4 элемента 2ИЛИ-НЕ)"));
  Serial.println(F("5 - ТМ2 (2 D-триггера)"));
  Serial.println(F("6 - КП2 (2 Мультиплексора)"));
  Serial.println(F("7 - ИД4 (2 Дешифратора)"));
  Serial.print(F("Ввведите команду:"));

  while (!Serial.available());
  char cmd = Serial.read();
  Serial.println(cmd);
  
  switch (cmd) {
    case '1':
      device = new K1533LN1LN2LN3LN5LN8();
      break;
    case '2':
      device = new K1533LA3LA9LA11LA12LA13TL3();
      break;
    case '3':
      device = new K1533LI1LI2();
      break;
    case '4':
      device = new K1533LE1LE5LE6();
      break;
    case '5':
      device = new K1533TM2();
      break;
    case '6':
      device = new K1533KP2();
      break;
    case '7':
      device = new K1533ID4();
      break;
  }
}

void loop() {
  if (device != NULL) {
    device->test();
  }
  else {
    testPortAPortC();
  }
  while (digitalRead(PIN_BUTTON) != LOW);
}

void testLed() {
  Serial.println(F("\nLED1 = X, LED2 = X"));
  digitalWrite(PIN_LED1, HIGH);
  digitalWrite(PIN_LED2, HIGH);
  delay(500);
  while (digitalRead(PIN_BUTTON) != LOW);
  
  Serial.println(F("\nLED1 = ., LED2 = ."));
  digitalWrite(PIN_LED1, LOW);
  digitalWrite(PIN_LED2, LOW);
  delay(500);
  while (digitalRead(PIN_BUTTON) != LOW);
  
  Serial.println(F("\nLED1 = X, LED2 = ."));
  digitalWrite(PIN_LED1, HIGH);
  digitalWrite(PIN_LED2, LOW);
  delay(500);
  while (digitalRead(PIN_BUTTON) != LOW);
  
  Serial.println(F("\nLED1 = ., LED2 = X"));
  digitalWrite(PIN_LED1, LOW);
  digitalWrite(PIN_LED2, HIGH);
  delay(500);
  while (digitalRead(PIN_BUTTON) != LOW);

}

void testPortAPortC() {
  PORTA = B00000000;
  DDRA  = B11111111;
  delay(200);
  for (int i = 0; i < 8; i++) {
    PORTA = 1 << i;
    delay(200);
  }
  PORTA = B00000000;

  PORTC = B00000000;
  DDRC  = B11111111;
  delay(200);
  for (int i = 0; i < 8; i++) {
    PORTC = 1 << i;
    delay(200);
  }
  PORTC = B00000000;
}
