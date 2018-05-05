#include <MsTimer2.h>
#include "ledDisplay.h"
#include "DHT.h"
#include "DS3231.h"

/*
http://codius.ru/articles/Arduino_UNO_4%D1%80%D0%B0%D0%B7%D1%80%D1%8F%D0%B4%D0%BD%D1%8B%D0%B9_7%D1%81%D0%B5%D0%B3%D0%BC%D0%B5%D0%BD%D1%82%D0%BD%D1%8B%D0%B9_%D0%B8%D0%B4%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80_12_pin_3641BS_red
https://masterkit.ru/images/sets_scheme/nm7039box_sx.jpg
https://ecs7.tokopedia.net/img/product-1/2016/11/17/2550072/2550072_fa6ef4d0-76c7-4839-b123-9a678cd10d10.jpg
       
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
            E  D dp   C  G  4

                     ------
      RESET - PC6 --| *    |-- PC5 -  SCL  - A5
 0 -   RXD  - PD0 --|      |-- PC4 -  SDA  - A4
 1 -   TXD  - PD1 --|      |-- PC3 -       - A3
 2 -        - PD2 --|      |-- PC2 -       - A2
 3 -        - PD3 --|      |-- PC1 -       - A1
 4 -        - PD4 --|      |-- PC0 -       - A0
   -   VCC  -     --|      |-- GND -  
   -   GND  -     --|      |-- AREF-  
   -  XTAL1 - PB6 --|      |-- VCC
   -  XTAL2 - PB7 --|      |-- PB5 -  SCK  - 13
 5 -        - PD5 --|      |-- PB4 - MISO  - 12
 6 -        - PD6 --|      |-- PB3 - MOSI  - 11
 7 -        - PD7 --|      |-- PB2 -  SS   - 10
 8 -        - PB0 --|      |-- PB1 -       - 9
                     ------
 
*/

DHT dht(7, AM2301);
DS3231 ds3231;

char text[128];
void setup()
{
  Serial.begin(9600);
  LED_DISPLAY::begin();
  dht.begin();
  ds3231.begin();
  Serial.println("Start");
}

int minute = 0;
int hour = 0;
void loop()
{
  uint16_t value = ds3231.getTime();
  LED_DISPLAY::setTime(value);
  Serial.println(value, HEX);

  delay(2000);
/*
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (!isnan(h) && !isnan(t))
  {
    long value;
    Serial.print("Humidity: ");
    value = lrint(h);
    //LED_DISPLAY::setTemperature(value);
    Serial.println(value);
    value = lrint(t);
    //LED_DISPLAY::setHumidity(value);
    Serial.println(value);
  }
*/
}

