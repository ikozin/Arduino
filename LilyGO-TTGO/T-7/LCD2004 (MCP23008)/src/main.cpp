#include <Arduino.h>

//#define LCD1602
#define LCD2004

#if (!defined(LCD1602) && !defined(LCD2004)) || (defined(LCD1602) && defined(LCD2004))
    #error define LCD1602 or LCD2004
#endif

#ifdef LCD1602
#define LCD_ROWS    (2)
#define LCD_COLS    (16)
#endif
#ifdef LCD2004
#define LCD_ROWS    (4)
#define LCD_COLS    (20)
#endif

#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0);

void setup() {
    Serial.begin(9600);
    lcd.begin(LCD_ROWS);
    lcd.clear();
    lcd.println("HELLO WORLD!");
}

int showChar(int index, int x, int height) {
    lcd.clear();
    for (int y = 0; y < height; y++) {
        lcd.setCursor(x, y);
        for (size_t i = 0; i < 16; i++ ) {
            lcd.print((char)index++);
        }
    }
    return index;
}

void loop() {
    delay(1000);
    lcd.clear();
    lcd.noDisplay();
    delay(1000);
    lcd.display();

    int start = 0;
    while (start < 256) {
        delay(1000);
        start = showChar(start, 0, LCD_ROWS);
    }
}
