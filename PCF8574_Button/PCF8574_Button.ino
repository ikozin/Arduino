/*
PCF8574A
https://static.chipdip.ru/lib/205/DOC000205430.pdf

    Плата
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

void loop()
{
  Wire.requestFrom(ADDRESS_KEYBOARD,1);
  while (!Wire.available());
  byte data = Wire.read();  //читаем состояние портов PCF8574P(кнопок)
  Serial.println(data, HEX);
  delay(1000);
}
