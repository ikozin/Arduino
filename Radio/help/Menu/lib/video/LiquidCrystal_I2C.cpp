#include "LiquidCrystal_I2C.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal_I2C constructor is called).

LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t i2caddr)
{
  _i2cAddr = i2caddr;

  // the I/O expander pinout
  _rs_pin = 7;
  _enable_pin = 6;
  _data_pins[0] = 5;  // really d4
  _data_pins[1] = 4;  // really d5
  _data_pins[2] = 3;  // really d6
  _data_pins[3] = 2;  // really d7
}


void LiquidCrystal_I2C::begin(uint8_t lines)
{
  _i2c.begin(_i2cAddr);

  _i2c.pinMode(1, OUTPUT); // backlight //	6pin
  _i2c.digitalWrite(1, HIGH); // backlight
    
  _i2c.pinMode(_rs_pin, OUTPUT);
  _i2c.pinMode(_enable_pin, OUTPUT);

  _numlines = lines;

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
  delayMicroseconds(50000); 
  // Now we pull both RS and R/W low to begin commands
  _digitalWrite(_rs_pin, LOW);
  _digitalWrite(_enable_pin, LOW);
  
  // this is according to the hitachi HD44780 datasheet
  // figure 24, pg 46

  // we start in 8bit mode, try to set 4 bit mode
  write4bits(0x03);
  delayMicroseconds(4500); // wait min 4.1ms

  // second try
  write4bits(0x03);
  delayMicroseconds(4500); // wait min 4.1ms
    
  // third go!
  write4bits(0x03); 
  delayMicroseconds(150);

  // finally, set to 8-bit interface
  write4bits(0x02); 

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);
}

/********** high level commands, for the user! */
void LiquidCrystal_I2C::clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C::home()
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if (row > _numlines)
  {
    row = _numlines - 1;  // we count rows starting w/0
  }
  
  command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LiquidCrystal_I2C::noDisplay()
{
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::display()
{
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_I2C::noCursor()
{
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::cursor()
{
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_I2C::noBlink()
{
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::blink()
{
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_I2C::scrollDisplayLeft(void)
{
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LiquidCrystal_I2C::scrollDisplayRight(void)
{
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_I2C::leftToRight(void)
{
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_I2C::rightToLeft(void)
{
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_I2C::autoscroll(void)
{
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_I2C::noAutoscroll(void)
{
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_I2C::createChar(uint8_t location, uint8_t charmap[])
{
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i = 0; i < 8; i++)
  {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void LiquidCrystal_I2C::command(uint8_t value)
{
  send(value, LOW);
}

inline  size_t LiquidCrystal_I2C::write(uint8_t value)
{
  send(value, HIGH);
  return 1;
}

/************ low level data pushing commands **********/

// little wrapper for i/o writes
void  LiquidCrystal_I2C::_digitalWrite(uint8_t p, uint8_t d)
{
  _i2c.digitalWrite(p, d);
}

// Allows to set the backlight, if the LCD backpack is used
void LiquidCrystal_I2C::setBacklight(uint8_t status)
{
  _digitalWrite(1, status); // backlight is on pin 7
}

// little wrapper for i/o directions
void  LiquidCrystal_I2C::_pinMode(uint8_t p, uint8_t d)
{
  _i2c.pinMode(p, d);
}

void LiquidCrystal_I2C::send(uint8_t value, uint8_t mode)
{
  _digitalWrite(_rs_pin, mode);
  write4bits(value >> 4);
  write4bits(value);
}

void LiquidCrystal_I2C::pulseEnable(void)
{
  _digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);    
  _digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  _digitalWrite(_enable_pin, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
}

void LiquidCrystal_I2C::write4bits(uint8_t value)
{
  for (int i = 0; i < 4; i++)
  {
    _pinMode(_data_pins[i], OUTPUT);
    _digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }
  pulseEnable();
}
