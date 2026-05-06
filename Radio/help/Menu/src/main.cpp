#include <Arduino.h>
#include <Wire.h>
#include <StringN.h>
#include <GyverMenu.h>
#include <LiquidCrystal_I2C.h>
#include <MCP23008.h>

#ifndef ARDUINO_AVR_PRO
#error Select board: Arduino Pro Mini 
#endif

const int lcdLines = 4;
const int lcdRows = 20;

LiquidCrystal_I2C lcd(0);
String64 text; 

const int pinControl = 3;
const int pinUp = 4;
const int pinDown = 5;
const int pinLeft = 6;
const int pinRight = 7;

GyverMenu menu(lcdRows, lcdLines);


byte _L1[8] = { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 };
byte _L2[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000 };
byte _L3[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B11111, B11111 };
byte _B1[8] = { B00111, B01111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B2[8] = { B11100, B11110, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B3[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B01111, B00111 };
byte _B4[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11110, B11100 };

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

bool btns, lbls;

uint8_t tab;
int val;
bool sw;

void setup() {
    Serial.begin(115200);

    pinMode(pinControl, INPUT_PULLUP);
    pinMode(pinUp, INPUT_PULLUP);
    pinMode(pinDown, INPUT_PULLUP);
    pinMode(pinLeft, INPUT_PULLUP);
    pinMode(pinRight, INPUT_PULLUP);

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

    Serial.println(F("Menu"));

    menu.onPrint([](const char* str, size_t len) {
        if (str) lcd.Print::write(str, len);
    });
    menu.onCursor([](uint8_t row, bool chosen, bool active) -> uint8_t {
        lcd.setCursor(0, row);
        lcd.print(chosen && !active ? '>' : ' ');
        return 1;
    });

    menu.onBuild([](gm::Builder& b) {
        if (b.Tabs(&tab, "btns;labels;ints;switch")) b.refresh();

        switch (tab) {
            case 0:
                for (int i = 0; i < 5; i++) {
                    if (b.Button(String16("Button ") + i)) Serial.println(String16("Button") + i);
                }
                break;

            case 1:
                b.ValueStr("label", "value 1");
                b.ValueStr("label", "value 2");
                b.ValueStr("label", "value 3");
                b.ValueStr("label", "value 4");
                break;

            case 2:
                b.ValueInt("int 1", &val, -10, 10, 2);
                b.ValueInt("int 2", &val, -10, 10, 2);
                break;

            case 3:
                b.Switch("Switch 1", &sw);
                b.Switch("Switch 2", &sw);
                b.Switch("Switch 3", &sw);
                b.Switch("Switch 4", &sw);
                break;
        }
    });

    menu.refresh();
}

void loop() {
  if (digitalRead(pinControl) == LOW) {
      menu.set();
  }
  if (digitalRead(pinUp) == LOW) {
      menu.up();
  }
  if (digitalRead(pinDown) == LOW) {
      menu.down();
  }
  if (digitalRead(pinLeft) == LOW) {
      menu.left();
  }
  if (digitalRead(pinRight) == LOW) {
      menu.right();
  }
  delay(100);
}
