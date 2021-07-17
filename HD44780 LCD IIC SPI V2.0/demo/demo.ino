#include "LiquidCrystal.h"

LiquidCrystal lcd(0);  // 0 = I2C LCD address 0x20, 1 = I2C LCD address 0x21

void setup()
{
  //lcd.begin(16,2);
  lcd.begin(20,4);
}


void loop()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Hello, world!");
  delay(1000);

  flipDisplay();
  flipBacklight();
  waitAnimation(3);
  //displayCharset16x2();
  displayCharset20x4();
}

void flipDisplay() {
  lcd.noDisplay();
  delay(1000);
  lcd.display();
  delay(1000);
  lcd.noDisplay();
  delay(1000);
  lcd.display();
  delay(1000);
}

void flipBacklight() {
  lcd.setBacklight(0); 
  delay(1000);
  lcd.setBacklight(1); 
  delay(1000);
  lcd.setBacklight(0); 
  delay(1000);
  lcd.setBacklight(1); 
}

void waitAnimation(int count) {
  for (int i = 0; i < count; i++) {
    lcd.setCursor(8,1);
    lcd.print('\x7C');  // '|'
    delay(500);

    lcd.setCursor(8,1);
    lcd.print('\x2F');  // '/'
    delay(500);
  
    lcd.setCursor(8,1);
    lcd.print('\x2D');  // '-'
    delay(500);
  
    lcd.setCursor(8,1);
    lcd.print('\x5C');  // '\'
    delay(500);
  } 
}

void displayCharset16x2() {
  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0x00; i <= 0x0F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0x10; i <= 0x1F; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0x20; i <= 0x2F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0x30; i <= 0x3F; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0x40; i <= 0x4F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0x50; i <= 0x5F; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0x60; i <= 0x6F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0x70; i <= 0x7F; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0x80; i <= 0x8F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0x90; i <= 0x9F; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0xA0; i <= 0xAF; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0xB0; i <= 0xBF; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0xC0; i <= 0xCF; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0xD0; i <= 0xDF; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); for (int i = 0xE0; i <= 0xEF; i++) lcd.print((char)i);
  lcd.setCursor(0,1); for (int i = 0xF0; i <= 0xFF; i++) lcd.print((char)i);
  delay(2000);
}

void displayCharset20x4() {
  lcd.clear();
  lcd.setCursor(0,0); //lcd.print("00: "); /for (int i = 0x00; i <= 0x4F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); lcd.print("10: "); for (int i = 0x10; i <= 0x1F; i++) lcd.print((char)i);
  lcd.setCursor(0,2); lcd.print("20: "); for (int i = 0x20; i <= 0x2F; i++) lcd.print((char)i);
  lcd.setCursor(0,3); lcd.print("30: "); for (int i = 0x30; i <= 0x3F; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("40: "); for (int i = 0x40; i <= 0x4F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); lcd.print("50: "); for (int i = 0x50; i <= 0x5F; i++) lcd.print((char)i);
  lcd.setCursor(0,2); lcd.print("60: "); for (int i = 0x60; i <= 0x6F; i++) lcd.print((char)i);
  lcd.setCursor(0,3); lcd.print("70: "); for (int i = 0x70; i <= 0x7F; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("80: "); for (int i = 0x80; i <= 0x8F; i++) lcd.print((char)i);
  lcd.setCursor(0,1); lcd.print("90: "); for (int i = 0x90; i <= 0x9F; i++) lcd.print((char)i);
  lcd.setCursor(0,2); lcd.print("A0: "); for (int i = 0xA0; i <= 0xAF; i++) lcd.print((char)i);
  lcd.setCursor(0,3); lcd.print("B0: "); for (int i = 0xB0; i <= 0xBF; i++) lcd.print((char)i);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("C0: "); for (int i = 0xC0; i <= 0xCF; i++) lcd.print((char)i);
  lcd.setCursor(0,1); lcd.print("D0: "); for (int i = 0xD0; i <= 0xDF; i++) lcd.print((char)i);
  lcd.setCursor(0,2); lcd.print("E0: "); for (int i = 0xE0; i <= 0xEF; i++) lcd.print((char)i);
  lcd.setCursor(0,3); lcd.print("F0: "); for (int i = 0xF0; i <= 0xFF; i++) lcd.print((char)i);
  delay(2000);
}
