//#define INSIDE_IRQ
#define LOG_CONSOLE
#include <MsTimer2.h>
#include <DHT.h>
#include "ledDisplay.h"
#include "DS3231.h"

/*
Adafruit Unified Sensor
DHT sensor library
MsTimer2
 
https://www.arduino.cc/en/Tutorial/ArduinoToBreadboard
http://codius.ru/articles/Arduino_UNO_4%D1%80%D0%B0%D0%B7%D1%80%D1%8F%D0%B4%D0%BD%D1%8B%D0%B9_7%D1%81%D0%B5%D0%B3%D0%BC%D0%B5%D0%BD%D1%82%D0%BD%D1%8B%D0%B9_%D0%B8%D0%B4%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80_12_pin_3641BS_red
https://masterkit.ru/images/sets_scheme/nm7039box_sx.jpg
https://ecs7.tokopedia.net/img/product-1/2016/11/17/2550072/2550072_fa6ef4d0-76c7-4839-b123-9a678cd10d10.jpg

Плата: ATmega328 on a breadboard (8MHz internal clock)
       
Распиновка atmega328
	--------------------------------------------------
 1-|   | ~RST  | PC6 |             |  PC5 |  SCL | A5 |-28
 2-| 0 | RXD   | PD0 |             |  PC4 |  SDA | A4 |-27
 3-| 1 | TXD   | PD1 |             |  PC3 |      | A3 |-26
 4-| 2 |       | PD2 |             |  PC2 |      | A2 |-25
 5-| 3 |       | PD3 |             |  PC1 |      | A1 |-24
 6-| 4 |       | PD4 |             |  PC0 |      | A0 |-23
 7-|   | VCC   |     |             |  GND |      |    |-22
 8-|   | GND   |     |             | AREF |      |    |-21
 9-|   | XTAL1 | PB6 |             |  VCC |      |    |-20
10-|   | XTAL2 | PB7 |             |  PB5 |  SCK | 13 |-19
11-| 5 |       | PD5 |             |  PB4 | MISO | 12 |-18
12-| 6 |       | PD6 |             |  PB3 | MOSI | 11 |-17
13-| 7 |       | PD7 |             |  PB2 |   SS | 10 |-16
14-| 8 |       | PB0 |             |  PB1 |      |  9 |-15
	--------------------------------------------------

	   4-разрядный 7-сегментный индикатор с общим анодом
            1  A  F   2  3  B
 ___________|__|__|___|__|__|____________
|         |         |         |         |
|    A    |    A    |    A    |    A    |
| F     B | F     B | F     B | F     B |
|    G    |    G    |    G    |    G    |
| E     C | E     C | E     C | E     C |
|    D    |    D    |    D    |    D    |
|_______dp|_______dp|_______dp|_______dp|
            |  |  |   |  |  |
            E  D  dp  C  G  4


      ____________________________________________________________________________
     |                                                                            |
     |                          ___   ___   ___   ___                             |
     |                         |   | |   | |   | |   |                            |
     |                         |___| |___| |___| |___|                            |
     |                         |   | |   | |   | |   |                            |
     |                         |___|.|___|.|___|.|___|.                           |
     |                                                                            |
     |               ATmega328 on a breadboard (8MHz internal clock)              |
RST -|                                                                            |
RST -|                          RXD TXD                                           |
     |____________________________________________________________________________|
      |   |   |   |   |   |      |   |   |   |   |   |   |   |      |   |   |   |
     RST TXD RXD VCC     GND     0   1   2   3   4   5   6   7     SCL SDA VCC GND

     DTR TXO RXI VCC     GND                                 |     SCL SDA VCC GND
    __|___|___|___|___|___|__                                |    __|___|___|___|__
   |                         |                               |   |                 |
   |                         |                               |   |     DS3231      |
   |                         |                               |   |       RTC       |
   |                         |                               |   |     EEPROM      |
   |                         |                               |   |_________________|
   |_________________________|
            |       |                                        D  VCC GND
            |  USB  |                                      __|___|___|__
            |_______|                                     |             |
                                                          |   AM2301    |
                                                          |_____________|


*/

DHT dht(7, AM2301);
DS3231 ds3231;

long time = 0;
long temp = 0;
long hum = 0;

void setup()
{
  LED_DISPLAY::begin();
  dht.begin();
  ds3231.begin();
#ifdef LOG_CONSOLE
  Serial.begin(57600);
  Serial.println("Start");
#endif
  //ds3231.setDate(2, 4, 2022);  //day, month, year
  //ds3231.setTime(0, 34, 14);    //second, minute, hour
  //ds3231.setAgingOffset(-1);
}

byte cnt = 0;
void displayInfo()
{
  if (cnt & 0x08)
  {
    if (cnt & 0x04)
      LED_DISPLAY::setHumidity(hum);
    else
      LED_DISPLAY::setTemperature(temp);
  }
  else LED_DISPLAY::setTime(time);
}

void loop()
{
  time = ds3231.getTime();
  if (cnt & 0x04)
  {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t))
    {
      temp = lrint(t);
      hum = lrint(h);
    }
  }
#ifdef LOG_CONSOLE
  //Serial.println(time, HEX);
  Serial.print(ds3231.getTextDate());
  Serial.print(", ");
  Serial.print(ds3231.getTextTime());
  Serial.println();

  Serial.print(temp);
  Serial.println(" C");
  
   Serial.print(hum);
  Serial.println(" H");
#endif
  displayInfo();
  delay(500);
  cnt++;
}
