#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_LiquidCrystal.h"
/*
https://masterkit.ru/shop/1319439

..................................

Adafruit_LiquidCrystal::Adafruit_LiquidCrystal(uint8_t i2caddr, TwoWire *wire) {
  _i2cAddr = i2caddr <= 0x07 ? 0x20 | i2caddr : i2caddr;
  _wire = wire;

  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

  // the I/O expander pinout
  _rs_pin = 7;
  _rw_pin = 255;
  _enable_pin = 6;
  _data_pins[0] = 5; // really d4
  _data_pins[1] = 4; // really d5
  _data_pins[2] = 3; // really d6
  _data_pins[3] = 2; // really d7

  // we can't begin() yet :(
}

..................................

void Adafruit_LiquidCrystal::setBacklight(uint8_t value) {
  // check if i2c or SPI
  if ((_i2cAddr != 255) || (_SPIclock != 255)) {
    // backlight is on pin 7
    if (value)
      _digitalWrite(1, HIGH);
    else
      _digitalWrite(1, LOW);
  }
}
..................................

*/

//LiquidCrystal lcd(0);
Adafruit_LiquidCrystal lcd(0, &Wire);

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