//#define DEBUG_CONSOLE

#include <Arduino.h>

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif

#define PIN_BUTTON  38  //PD7
#define PIN_LED1    41  //PG0
#define PIN_LED2    40  //PG1

//               DIP 14
//    PC0(37) [ 1]   [14]  VCC
//    PC1(36) [ 2]   [13] PA0(22)
//    PC2(35) [ 3]   [12] PA1(23)
//    PC3(34) [ 4]   [11] PA2(24)
//    PC4(33) [ 5]   [10] PA3(25)
//    PC5(32) [ 6]   [ 9] PA4(26)
//      GND   [ 7]   [ 8] PA5(27)
//
//
//
//               DIP 16
//    PC0(37) [ 1]   [16]  VCC
//    PC1(36) [ 2]   [15] PA0(22)
//    PC2(35) [ 3]   [14] PA1(23)
//    PC3(34) [ 4]   [13] PA2(24)
//    PC4(33) [ 5]   [12] PA3(25)
//    PC5(32) [ 6]   [11] PA4(26)
//    PC6(31) [ 7]   [10] PA5(27)
//      GND   [ 8]   [ 9] PA6(28)
//
//
//
//               DIP 20
//    PL0(49) [ 1]   [20]  VCC
//    PC0(37) [ 2]   [19] PL1(48)
//    PC1(36) [ 3]   [18] PA0(22)
//    PC2(35) [ 4]   [17] PA1(23)
//    PC3(34) [ 5]   [16] PA2(24)
//    PC4(33) [ 6]   [15] PA3(25)
//    PC5(32) [ 7]   [14] PA4(26)
//    PC6(31) [ 8]   [13] PA5(27)
//    PC7(30) [ 9]   [12] PA6(28)
//      GND   [10]   [11] PA7(29)
//
//
//
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//    !! DIP 14(ИЕ2, ИЕ4, ИЕ5) !!
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//    PC0(37) [ 1]   [14] PA0(22)
//    PC1(36) [ 2]   [13] 
//    PC2(35) [ 3]   [12] PA1(24)
//            [ 4]   [11] PA2(25)
//      VCC   [ 5]   [10]  GND 
//    PC4(34) [ 6]   [ 9] PA3(26)
//    PC5(33) [ 7]   [ 8] PA4(27)
//
//
//
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//    !! DIP 16(ИД1, ИМ3, ТМ7) !!
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//    PC0(37) [ 1]   [16] PA0(22)
//    PC1(36) [ 2]   [15] PA1(23)
//    PC2(35) [ 3]   [14] PA2(24)
//    PC3(34) [ 4]   [13] PA3(25)
//      VCC   [ 5]   [12]  GND 
//    PC4(33) [ 6]   [11] PA4(26)
//    PC5(32) [ 7]   [10] PA5(27)
//    PC6(31) [ 8]   [ 9] PA6(28)
//
//
//

#include <DevicePackage.h>
#include <K555.h>
#include <K565.h>
#include <K580.h>
#include <K1533.h>

DevicePackage* packList[] = {
  new K555_Pack(),
  new K565_Pack(),
  new K580_Pack(),
  new K1533_Pack(),
};

int _selected;

// Не стандартная разводка питания: ИЕ5, ТМ5, ТМ7
void showMenu() {
  _selected = -1;
  Serial.println();
  if (digitalRead(PIN_BUTTON) == LOW) return;

  for (uint8_t i = 0; i < (sizeof(packList)/sizeof(packList[0])); i++) {
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(packList[i]->title());
  }
  Serial.print("Введите команду:");
  while (!Serial.available());
  String cmd = Serial.readStringUntil('\r');
  Serial.println(cmd);
  Serial.println();
  _selected = cmd.toInt();
  packList[_selected]->menu();
}

void setup() {
  //Serial.println("!!!");  //ЭТО БАГ Aduino Mega, ПРИ НАЛИЧИИ СТРОКИ "!!!" ВЫЗЫВАЕТ ОШИБКУ ЗАГРУЗКИ, НАПРИМЕР: char text[128] = "!!!";

  DDRA = B00000000;   // Set input mode
  DDRC = B00000000;   // Set input mode
  DDRL = B00000000;   // Set input mode

  PORTA = B11111111;  // Set pullup mode
  PORTC = B11111111;  // Set pullup mode
  PORTL = B11111111;  // Set pullup mode

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  // Initialize Serial
  Serial.begin(57600);
  while (!Serial);
  Serial.println(F("\nCтapт"));
  showMenu();
}

void testLed() {
  digitalWrite(PIN_LED1, HIGH);
  digitalWrite(PIN_LED2, HIGH);
  delay(500);
  
  digitalWrite(PIN_LED1, LOW);
  digitalWrite(PIN_LED2, LOW);
  delay(500);
  
  digitalWrite(PIN_LED1, HIGH);
  digitalWrite(PIN_LED2, LOW);
  delay(500);
  
  digitalWrite(PIN_LED1, LOW);
  digitalWrite(PIN_LED2, HIGH);
  delay(500);
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

void loop() {
  if (_selected != -1) {
    packList[_selected]->test();
    while (digitalRead(PIN_BUTTON) != LOW);
  }
  else {
    //testPortAPortC();
    testLed();
  }
}
