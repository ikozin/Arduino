#include <Arduino.h>
#include <Wire.h>
#include <StringN.h>
#include <LiquidCrystal_I2C.h>
#include <MCP23008.h>

#ifndef ARDUINO_AVR_PRO
#error Select board: Arduino Pro Mini 
#endif

const int lcdLines = 4;
const int lcdRows = 20;

LiquidCrystal_I2C lcd(0);
String64 text; 

byte _L1[8] = { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 };
byte _L2[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000 };
byte _L3[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B11111, B11111 };
byte _B1[8] = { B00111, B01111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B2[8] = { B11100, B11110, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B3[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B01111, B00111 };
byte _B4[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11110, B11100 };

const char digit_0_top[] = "\x04""\x02""\x05 ";
const char digit_1_top[] = "\x02""\x05""\x20 ";
const char digit_2_top[] = "\x02""\x03""\x05 ";
const char digit_3_top[] = "\x02""\x03""\x07 ";
const char digit_4_top[] = "\x04""\x01""\xFF ";
const char digit_5_top[] = "\x06""\x03""\x02 ";
const char digit_6_top[] = "\x04""\x03""\x02 ";
const char digit_7_top[] = "\x02""\x02""\x05 ";
const char digit_8_top[] = "\x06""\x03""\x07 ";
const char digit_9_top[] = "\x06""\x03""\x05 ";

const char *const digits_top[] = {
    digit_0_top,
    digit_1_top,
    digit_2_top,
    digit_3_top,
    digit_4_top,
    digit_5_top,
    digit_6_top,
    digit_7_top,
    digit_8_top,
    digit_9_top,
};

const char digit_0_bottom[] = "\x06""\x01""\x07 ";
const char digit_1_bottom[] = "\x01""\xFF""\x01 ";
const char digit_2_bottom[] = "\x04""\x03""\x01 ";
const char digit_3_bottom[] = "\x01""\x03""\x05 ";
const char digit_4_bottom[] = "\x20""\x20""\xFF ";
const char digit_5_bottom[] = "\x01""\x03""\x05 ";
const char digit_6_bottom[] = "\x06""\x03""\x05 ";
const char digit_7_bottom[] = "\x20""\x20""\xFF ";
const char digit_8_bottom[] = "\x04""\x03""\x05 ";
const char digit_9_bottom[] = "\x01""\x03""\x07 ";

const char *const digits_bottom[] = {
    digit_0_bottom,
    digit_1_bottom,
    digit_2_bottom,
    digit_3_bottom,
    digit_4_bottom,
    digit_5_bottom,
    digit_6_bottom,
    digit_7_bottom,
    digit_8_bottom,
    digit_9_bottom,
};

const char months[12][9] = {
  "\xC7\xBD\xB3""ap\xC4",
  "\xE4""e\xB3pa\xBB\xC4",
  "\xBC""ap\xBF",
  "a\xBEpe\xBB\xC4",
  "\xBC""a\xB9",
  "\xB8\xC6\xBD\xC4",
  "\xB8\xC6\xBB\xC4",
  "a\xB3\xB4yc\xBF",
  "ce\xBD\xBF\xC7\xB2p\xC4",
  "o\xBA\xBF\xC7\xB2p\xC4",
  "\xBDo\xC7\xB2p\xC4",
  "\xE3""e\xBA""a\xB2p\xC4",
};

uint16_t year = 2026;
uint8_t month = 1;
uint8_t day = 1;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;


void displayDate(uint8_t day, uint8_t month, uint16_t year) {
    text = "  ";
    text += day;
    text += ' ';
    text += months[month - 1];
    text += ' ';
    text += year;
    text += "  ";
    lcd.setCursor((lcdRows - text.length()) >> 1, 0);
    lcd.print(text);
}

void displayTime(uint8_t hour, uint8_t minute) {
    uint8_t cnt;

    cnt = 0;
    while (hour >= 10) {
        cnt += 1;
        hour -= 10;
    }
    lcd.setCursor(2, 2);
    lcd.print(digits_top[cnt]);
    lcd.print(digits_top[hour]);
    lcd.setCursor(2, 3);
    lcd.print(digits_bottom[cnt]);
    lcd.print(digits_bottom[hour]);

    cnt = 0;
    while (minute >= 10) {
        cnt += 1;
        minute -= 10;
    }    
    lcd.setCursor(10, 2);
    lcd.print(digits_top[cnt]);
    lcd.print(digits_top[minute]);
    lcd.setCursor(10, 3);
    lcd.print(digits_bottom[cnt]);
    lcd.print(digits_bottom[minute]);
}

void setup() {
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);  // По умолчанию 100000 = 981, при 400000 = 385 
    Serial.println(F("Initialize Video"));
    lcd.begin(lcdLines);
    lcd.clear();
    // для того чтобы использовать print, кодируем ситмволы с 1, а не с 0, так как 0 признак конца строки
    lcd.createChar(1, _L1);
    lcd.createChar(2, _L2);
    lcd.createChar(3, _L3);
    lcd.createChar(4, _B1);
    lcd.createChar(5, _B2);
    lcd.createChar(6, _B3);
    lcd.createChar(7, _B4);
}

void loop() {
    unsigned long time = millis();
    displayDate(day, month, year);
    displayTime(hour, minute);
    time = millis() - time;
    Serial.println(time);

    minute++;
    if (minute == 60) {
      minute = 0;
      hour++;
      if (hour == 24) hour = 0;
    }
    day++;
    if (day == 31) {
      day = 1;
      month++;
      if (month == 13) {
        month = 1;
        year++;
      }
    }
}
