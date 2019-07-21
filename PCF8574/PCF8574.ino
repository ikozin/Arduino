/*
PCF8574A
https://static.chipdip.ru/lib/205/DOC000205430.pdf

Распиновка PCF8574A
	  --------------
 1-|~INT	      P7|-20
 2-|SCL			    P6|-19
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
 --| 0x01          0x80 |--
 --| 0x02          0x40 |--
 --| 0x04          0x20 |--
 --| 0x08          0x10 |--
    --------------------
      |   |     |   |
     VCC GND   SCL SDA

Arduino
 SCL   A5
 SDA   A4
Адрес, базовый 0x38
 00 00 01 01 01 A2 A1 A0

  -----
 |     |- GND
 |     |- LED BLUE
 |     |- LED GREEN
 |     |- LED RED
 |     |- LED YELLOW
  -----
 
*/
#include <Wire.h>

#define   ADDRESS_DEVICE  0x39

byte data = 0x00;
char text[128];

void setup()
{
  Wire.begin();
  Wire.beginTransmission(ADDRESS_DEVICE);
  Wire.write(B00000000);    //Конфигурация, все порты PCF8574P как выход
  Wire.endTransmission();

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("Start"));
}

void displayBoard(byte data)
{
  Serial.println();
  sprintf(text, "Address: 0x%02X ", ADDRESS_DEVICE);
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
}

void loop()
{
  data = 0x00;
  Wire.beginTransmission(ADDRESS_DEVICE);
  Wire.write(data);
  Wire.endTransmission();
  displayBoard(data);
  delay(1000);

  data = 0xFF;
  Wire.beginTransmission(ADDRESS_DEVICE);
  Wire.write(data);
  Wire.endTransmission();
  displayBoard(data);
  delay(1000);

  for (data = 0x01; data > 0; data <<= 1)
  {
    Wire.beginTransmission(ADDRESS_DEVICE);
    Wire.write(data);
    Wire.endTransmission();
    displayBoard(data);
    delay(1000);
  }
}
