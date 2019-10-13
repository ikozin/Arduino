
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 7/*10*/, /* dc=*/ 6/*9*/, /* reset=*/ 8);

//#include <SD.h>
//#define PIN_SD  10
//File sFile;

void setup(void) {
  pinMode(9, OUTPUT);
  digitalWrite(9, 0); // default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0

  u8g2.begin();
}

void drawLogo(void)
{
    u8g2.setFontMode(1);  // Transparent
    u8g2.drawHLine(2, 35, 47);
    u8g2.drawHLine(3, 36, 47);
    u8g2.drawVLine(45, 32, 12);
    u8g2.drawVLine(46, 33, 12);
}

void drawURL(void)
{
#ifndef MINI_LOGO
  u8g2.setFont(u8g2_font_4x6_tr);
  if ( u8g2.getDisplayHeight() < 59 )
  {
    u8g2.drawStr(89,20,"github.com");
    u8g2.drawStr(73,29,"/olikraus/u8g2");
  }
  else
  {
    u8g2.drawStr(1,54,"github.com/olikraus/u8g2");
  }
#endif
}

void loop(void) {
  u8g2.clearBuffer();
  drawLogo();
  drawURL();
  u8g2.sendBuffer();
  delay(1000);
}


/*
Скетч использует 444 байт (1%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 9 байт (0%) динамической памяти, оставляя 2039 байт для локальных переменных. Максимум: 2048 байт.
*/
/*
  Serial.println("Initializing SD card...");
  if (!SD.begin(PIN_SD))
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
*/

/*
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  sFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (sFile)
  {
    Serial.print("Writing to test.txt...");
    sFile.println("testing 1, 2, 3.");
    // close the file:
    sFile.close();
    Serial.println("done.");
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  sFile = SD.open("test.txt");
  if (sFile)
  {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (sFile.available())
    {
      Serial.write(sFile.read());
    }
    // close the file:
    sFile.close();
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
*/  
