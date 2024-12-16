#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

void setup() {
    pinMode(TFT_BL, OUTPUT);
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(random(0xFFFF));

    tft.setCursor(0, 0, 2);
    tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
    tft.println("Hello World!");

    tft.setTextColor(TFT_YELLOW); tft.setTextFont(7);
    tft.println(1234.56);

    tft.setTextColor(TFT_RED,TFT_BLACK);    tft.setTextFont(4);
    tft.println((long)3735928559, HEX); // Should print DEADBEEF

    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    tft.setTextFont(4);
    tft.println("Groop");
    tft.println("I implore thee,");

    tft.setTextFont(2);
    tft.println(F("my foonting turlingdromes.")); // Can store strings in FLASH to save RAM
    tft.println("And hooptiously drangle me");
    tft.println("with crinkly bindlewurdles,");
    tft.println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!");

    float fnumber = 123.45;
    tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
    tft.print("Float = "); tft.println(fnumber);           // Print floating point number
    tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
    tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
}

void loop() {
    digitalWrite(TFT_BL, HIGH);
    delay(2000);
    digitalWrite(TFT_BL, LOW);
    delay(2000);}
