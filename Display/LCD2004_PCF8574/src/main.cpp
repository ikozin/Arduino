#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);

void setup() {
    //Serial.begin(115200);
    // while(!Serial);
    Serial.println("LCD Character Backpack I2C Test.");
    // set up the LCD's number of rows and columns:
    lcd.begin(20, 4);

    // Print a message to the LCD.
    lcd.print("Hello world");
}

void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis()/1000);

    lcd.setBacklight(HIGH);
    delay(500);
    lcd.setBacklight(LOW);
    delay(500);
}