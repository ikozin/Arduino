#include <MsTimer2.h>
#include "ledDisplay.h"
#include "DHT.h"

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

char text[128];
void setup()
{
  Serial.begin(9600);
  LED_DISPLAY::begin();
  dht.begin();
  Serial.println("Start");
}

void loop()
{
  delay(2000);
  LED_DISPLAY::print(0, 1, 2, 3);
  delay(2000);
  LED_DISPLAY::print(1, 2, 3, 4);
/*
  delay(2000);
  LED_DISPLAY::print(2, 3, 4, 5);
  delay(2000);
  LED_DISPLAY::print(3, 4, 5, 6);
  delay(2000);
  LED_DISPLAY::print(4, 5, 6, 7);
  delay(2000);
  LED_DISPLAY::print(5, 6, 7, 8);
  delay(2000);
  LED_DISPLAY::print(6, 7, 8, 9);
  delay(2000);
  LED_DISPLAY::print(DISPLAY_SPACE, DISPLAY_SPACE, DISPLAY_SPACE, DISPLAY_SPACE);
  delay(2000);
  LED_DISPLAY::print(DISPLAY_SPACE, DISPLAY_MINUS, DISPLAY_CELCIUS, DISPLAY_HUMIDITY);
  delay(2000);
*/
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (!isnan(h) && !isnan(t))
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.println();
  }
}

uint8_t bcd2dec(uint8_t n)
{
  return n - 6 * (n/16); 
}

uint8_t dec2bcd(uint8_t n)
{
  byte b = (n * 103) >> 10;
  return (b * 16 + n-(b*10));  
}

