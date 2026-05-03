/*
PCF8574A
https://static.chipdip.ru/lib/205/DOC000205430.pdf

Распиновка PCF8574A
    --------------
 1-|~INT		P7|-20
 2-|SCL			P6|-19
 3-|              |-18
 4-|SDA         P5|-17
 4-|+5V         P4|-16
 6-|A0         GND|-15
 7-|A1          P3|-14
 8-|              |-13
 9-|A2          P2|-12
10-|P0          P1|-11
	--------------

Распиновка платы
	--------------------
   |                    |
   |    A0 A1 A2        |
   |                    |
   | (X) 0x01  0x80 (X) |
   | (X) 0x02  0x40 (X) |
   | (X) 0x04  0x20 (X) |
   | (X) 0x08  0x10 (X) |
    --------------------
      |   |     |   |
     VCC GND   SCL SDA

Arduino
 SCL   A5
 SDA   A4
Адрес, базовый 0x38
 00 00 01 01 01 A2 A1 A0
*/
#include <Wire.h>

#define   ADDRESS_KEYBOARD  0x38

char text[128];

void setup()
{
  Wire.begin();
  Wire.beginTransmission(ADDRESS_KEYBOARD);
  Wire.write(B11111111);    //Конфигурация, все порты PCF8574P как вход
  Wire.endTransmission();

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("Start"));
}

void displayBoard(byte data)
{
  if (data == 0) return;
  
  Serial.println();
  sprintf(text, "Address: 0x%02X ", ADDRESS_KEYBOARD);
  Serial.println(text);
  sprintf(text, "Data   : 0x%02X ", data);
  Serial.println(text);
  Serial.println();
  
  Serial.println(F("-------"));

  Serial.print(F("| "));
  Serial.print((data & 0x01) > 0 ? 'X' : '.');
  Serial.print(F(" "));
  Serial.print((data & 0x80) > 0 ? 'X' : '.');
  Serial.println(F(" |"));
    
  Serial.print(F("| "));
  Serial.print((data & 0x02) > 0 ? 'X' : '.');
  Serial.print(F(" "));
  Serial.print((data & 0x40) > 0 ? 'X' : '.');
  Serial.println(F(" |"));
    
  Serial.print(F("| "));
  Serial.print((data & 0x04) > 0 ? 'X' : '.');
  Serial.print(F(" "));
  Serial.print((data & 0x20) > 0 ? 'X' : '.');
  Serial.println(F(" |"));
    
  Serial.print(F("| "));
  Serial.print((data & 0x08) > 0 ? 'X' : '.');
  Serial.print(F(" "));
  Serial.print((data & 0x10) > 0 ? 'X' : '.');
  Serial.println(F(" |"));
    
  Serial.println(F("-------"));
  delay(500);
}

void loop()
{
  Wire.requestFrom(ADDRESS_KEYBOARD,1);
  while (!Wire.available());
  byte data = Wire.read();  //читаем состояние портов PCF8574P(кнопок)
  displayBoard(data);
}
