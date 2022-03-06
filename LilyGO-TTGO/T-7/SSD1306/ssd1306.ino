#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <Preferences.h>
#include <FS.h>
#include <SPIFFS.h>

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif


uint64_t timeStamp;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define ADAFRUIT

#if defined(ADAFRUIT)
/*
Скетч использует 275605 байт (21%) памяти устройства. Всего доступно 1310720 байт.
Глобальные переменные используют 17588 байт (5%) динамической памяти, оставляя 310092 байт для локальных переменных. Максимум: 327680 байт.

*/
  //#define SSD1306_NO_SPLASH 
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  
  #define OLED_RESET     -1   // Reset pin # (or -1 if sharing Arduino reset pin)
  #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
  
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

//#include "funky.h"
//#include "blueye.h"

void setup() {
  Serial.begin(115200);

#if defined(ADAFRUIT)
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
#endif
}

void loop() {
#if defined(ADAFRUIT)
  display.clearDisplay();
  timeStamp = millis();
  testdrawchar();      // Draw characters of the default font
  timeStamp = millis() - timeStamp;
  Serial.printf("testdrawchar = %llu\r\n", timeStamp);
  delay(2000);

  display.clearDisplay();
  timeStamp = millis();
  testdrawstyles();    // Draw 'stylized' characters
  timeStamp = millis() - timeStamp;
  Serial.printf("testdrawstyles = %llu\r\n", timeStamp);
  delay(2000);

  display.clearDisplay();
  timeStamp = millis();
  //display.drawBitmap(0, 0, blueye_black_bkn__ra_d, 64, 64, SSD1306_WHITE);
  display.display(); // Show the display buffer on the screen
  timeStamp = millis() - timeStamp;
  Serial.printf("drawBitmap= %llu\r\n", timeStamp);
  delay(2000);

  display.clearDisplay();
  timeStamp = millis();
  //display.drawBitmap(0, 0, funky_black_bkn__ra_d, 64, 64, SSD1306_WHITE);
  display.display(); // Show the display buffer on the screen
  timeStamp = millis() - timeStamp;
  Serial.printf("drawBitmap= %llu\r\n", timeStamp);
  delay(2000);
#endif
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
}
