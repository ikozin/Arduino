/*
PCF8574A
https://static.chipdip.ru/lib/205/DOC000205430.pdf

    Плата
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
*/
#include <Wire.h>

#define   ADDRESS_DEVICE  0x38

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

void loop()
{
  Wire.beginTransmission(ADDRESS_DEVICE);
  Wire.write(B00000000);
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(ADDRESS_DEVICE);
  Wire.write(B11111111);
  Wire.endTransmission();
  delay(1000);
}
