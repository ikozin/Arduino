#include <Arduino.h>

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif

#define PIN_BUTTON  38  //PD7
#define PIN_LED1    41  //PG0
#define PIN_LED2    40  //PG1


/*
    PC0   VCC       PC0   VCC       PL0   VCC
    PC1   PA0       PC1   PA0       PC0   PL1
    PC2   PA1       PC2   PA1       PC1   PA0
    PC3   PA2       PC3   PA2       PC2   PA1
    PC4   PA3       PC4   PA3       PC3   PA2
    PC5   PA4       PC5   PA4       PC4   PA3
    GND   PA5       PC6   PA5       PC5   PA4
                    GND   PA6       PC6   PA5
                                    PC7   PA6
                                    GND   PA7
*/

#include "Input8Out1Device.h"
#define DEBUG

//#define K1533_LA3_LA9_LA11_LA12_LA13_TL3
#define K1533_LA3_LI1_LI2


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

}

void loop() {
#ifdef K1533_LA3_LA9_LA11_LA12_LA13_TL3
  test_1533_la3_la9_la11_la12_la13_tl3();
#endif
#ifdef K1533_LA3_LI1_LI2
  test_1533_li1_li2();
#endif
  //testPortAPortC();
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
