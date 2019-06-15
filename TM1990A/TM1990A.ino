//https://www.pjrc.com/teensy/td_libs_OneWire.html
//https://soltau.ru/index.php/arduino/item/394-kak-sdelat-kopiyu
//https://usamodelkina.ru/14759-kak-sdelat-svoimi-rukami-kopirovalschik-kontaktnyh-i-beskontaktnyh-kljuchej-domofona.html
//https://drive.google.com/file/d/1vGYt09DGuwuMr2_qt5IiN-aCOp-YOQBE/view


#include <OneWire.h>

#define IBUTTON_PIN (9)
OneWire  ds(IBUTTON_PIN);
byte addr[8];
char text[128];

/*

 GND  DATA
  |    |
  |    ^ - ключ
---------
| X | X |   1-Wire
---------
| X | X |   LED
---------
DATA подтягивать к +5V через ~ 4k3 (в datasheet стоит 5k)
LED через органичительный  ~ 300R

0106DA0BA000000E
014126510600009D
0193CB500600008E
01BC205106000039
01D5D60606000008
*/
 
void setup(void)
{
  Serial.begin(9600);
}
 
void loop(void)
{
  checkIButton();
  delay(500);
}

bool checkIButton()
{
  if (ds.search(addr))
  {
    ds.reset();
    if ( addr[0] != 0x01)
    {
      Serial.println("Device is not a DS1990A family device.\n");
      return false;
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!\n");
      return false;
    }

    sprintf(text, "%02X%02X%02X%02X%02X%02X%02X%02X",
        addr[0],
        addr[1],
        addr[2],
        addr[3],
        addr[4],
        addr[5],
        addr[6],
        addr[7]);
    Serial.println(text);
    return true;
  }
  ds.reset_search();
  return false;
}
