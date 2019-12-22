/*

https://compacttool.ru/viewtovar.php?id=683

На плате Pro Micro нет светодиода подключенного к 13 пину
                     -----
                    | USB |
             ---------------------
      TX 0  | TX0             RAW | (7-12V)
      RX 1  | RX1             GND |
            | GND             RST |    RST
            | GND             VCC |
     SDA 2  | 2                A3 | 21 A3
 PWM SCL 3  | 3                A2 | 20 A2
      A6 4  | 4                A1 | 19 A1
 PWM     5  | 5                A0 | 18 A0
 PWM  A7 6  | 6   ---    ---   15 | 15 SCLK
         7  | 7  |RX-|  |TX-|  14 | 14 MISO
      A8 8  | 8  |LED|  |LED|  16 | 16 MOSI
 PWM  A9 9  | 9   ---    ---   10 | 10 A10  PWM
             ---------------------

Помигать можно так
const int LED_RX = 17;
const int LED_TX = 24;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_RX, OUTPUT);
}
void loop()
{
  Serial.println ("Hello World!");
  digitalWrite(LED_RX, LOW);
  delay(1000);
  digitalWrite(LED_RX, HIGH);
  delay(1000);
}

*/
#define RAW_VALUE
#include <Keyboard.h>
#include "pitches.h"

#define KEYS_SIZE   10
typedef struct {
  uint16_t value;
  uint16_t press;
  uint16_t delay;
  uint8_t  keyCode[KEYS_SIZE];
} KeyInfo;

#define NO_VALUE    0xFFFF
#define NO_KEY      0xFF

#define PROFILES_SIZE   4
byte selectedProfile = 0;
KeyInfo keyProfiles[PROFILES_SIZE] = {
  { 600, 100, 1000, { KEY_LEFT_CTRL, 'f', NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY } },
  { NO_VALUE, NO_VALUE, NO_VALUE, { NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY } },
  { NO_VALUE, NO_VALUE, NO_VALUE, { NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY } },
  { NO_VALUE, NO_VALUE, NO_VALUE, { NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY } },
};

// notes in the melody:
int melody[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

char text[64];

const void playMelody() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(5, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(5);
  }
}

void printKeyCode(uint8_t key) {
  switch(key) {
    case KEY_LEFT_CTRL: {
      Serial.print(F("KEY_LEFT_CTRL"));
      break;
    }
    case KEY_LEFT_SHIFT: {
      Serial.print(F("KEY_LEFT_SHIFT"));
      break;
    }
    case KEY_LEFT_ALT: {
      Serial.print(F("KEY_LEFT_ALT"));
      break;
    }
    case KEY_LEFT_GUI: {
      Serial.print(F("KEY_LEFT_GUI"));
      break;
    }
    case KEY_RIGHT_CTRL: {
      Serial.print(F("KEY_RIGHT_CTRL"));
      break;
    }
    case KEY_RIGHT_SHIFT: {
      Serial.print(F("KEY_RIGHT_SHIFT"));
      break;
    }
    case KEY_RIGHT_ALT: {
      Serial.print(F("KEY_RIGHT_ALT"));
      break;
    }
    case KEY_RIGHT_GUI: {
      Serial.print(F("KEY_RIGHT_GUI"));
      break;
    }
    case KEY_UP_ARROW: {
      Serial.print(F("KEY_UP_ARROW"));
      break;
    }
    case KEY_DOWN_ARROW: {
      Serial.print(F("KEY_DOWN_ARROW"));
      break;
    }
    case KEY_LEFT_ARROW: {
      Serial.print(F("KEY_LEFT_ARROW"));
      break;
    }
    case KEY_RIGHT_ARROW: {
      Serial.print(F("KEY_RIGHT_ARROW"));
      break;
    }
    case KEY_BACKSPACE: {
      Serial.print(F("KEY_BACKSPACE"));
      break;
    }
    case KEY_TAB: {
      Serial.print(F("KEY_TAB"));
      break;
    }
    case KEY_RETURN: {
      Serial.print(F("KEY_RETURN"));
      break;
    }
    case KEY_ESC: {
      Serial.print(F("KEY_ESC"));
      break;
    }
    case KEY_INSERT: {
      Serial.print(F("KEY_INSERT"));
      break;
    }
    case KEY_DELETE: {
      Serial.print(F("KEY_DELETE"));
      break;
    }
    case KEY_PAGE_UP: {
      Serial.print(F("KEY_PAGE_UP"));
      break;
    }
    case KEY_PAGE_DOWN: {
      Serial.print(F("KEY_PAGE_DOWN"));
      break;
    }
    case KEY_HOME: {
      Serial.print(F("KEY_HOME"));
      break;
    }
    case KEY_END: {
      Serial.print(F("KEY_END"));
      break;
    }
    case KEY_CAPS_LOCK: {
      Serial.print(F("KEY_CAPS_LOCK"));
      break;
    }
    case KEY_F1: {
      Serial.print(F("KEY_F1"));
      break;
    }
    case KEY_F2: {
      Serial.print(F("KEY_F2"));
      break;
    }
    case KEY_F3: {
      Serial.print(F("KEY_F3"));
      break;
    }
    case KEY_F4: {
      Serial.print(F("KEY_F4"));
      break;
    }
    case KEY_F5: {
      Serial.print(F("KEY_F5"));
      break;
    }
    case KEY_F6: {
      Serial.print(F("KEY_F6"));
      break;
    }
    case KEY_F7: {
      Serial.print(F("KEY_F7"));
      break;
    }
    case KEY_F8: {
      Serial.print(F("KEY_F8"));
      break;
    }
    case KEY_F9: {
      Serial.print(F("KEY_F9"));
      break;
    }
    case KEY_F10: {
      Serial.print(F("KEY_F10"));
      break;
    }
    case KEY_F11: {
      Serial.print(F("KEY_F11"));
      break;
    }
    case KEY_F12: {
      Serial.print(F("KEY_F12"));
      break;
    }
    case KEY_F13: {
      Serial.print(F("KEY_F13"));
      break;
    }
    case KEY_F14: {
      Serial.print(F("KEY_F14"));
      break;
    }
    case KEY_F15: {
      Serial.print(F("KEY_F15"));
      break;
    }
    case KEY_F16: {
      Serial.print(F("KEY_F16"));
      break;
    }
    case KEY_F17: {
      Serial.print(F("KEY_F17"));
      break;
    }
    case KEY_F18: {
      Serial.print(F("KEY_F18"));
      break;
    }
    case KEY_F19: {
      Serial.print(F("KEY_F19"));
      break;
    }
    case KEY_F20: {
      Serial.print(F("KEY_F20"));
      break;
    }
    case KEY_F21: {
      Serial.print(F("KEY_F21"));
      break;
    }
    case KEY_F22: {
      Serial.print(F("KEY_F22"));
      break;
    }
    case KEY_F23: {
      Serial.print(F("KEY_F23"));
      break;
    }
    case KEY_F24: {
      Serial.print(F("KEY_F24"));
      break;
    }
    default: {
      if (isPrintable(key)) {
        sprintf(text, "%c [0x%02X]", key, key);
      }
      else {
        sprintf(text, "0x%02X", key);
      }
      Serial.print(text);
      return;
    }
  }
  sprintf(text, " [0x%02X]", key);
  Serial.print(text);
}

const void diplayHelp() {
  Serial.println();
  for (int i = 0; i < PROFILES_SIZE; i++) {
    sprintf(text, "%d: ", i + 1);
    Serial.print(text);
    if (keyProfiles[i].value == NO_VALUE) {
      Serial.print(F("Empty"));
    }
    else {
      KeyInfo *p = &keyProfiles[i];
      sprintf(text, "Value: %d, Press: %d, Delay: %d, Keys: ", p->value, p->press, p->delay);
      Serial.print(text);
      for (int n = 0; n < KEYS_SIZE; n++) {
        uint8_t key = p->keyCode[n];
        if (key == NO_KEY) {
          break;
        }
        printKeyCode(key);
        Serial.print(F(" + "));
      }
    }
    Serial.println();
  }
  Serial.println();
  Serial.println(F("Press 1-4 for Edit Profile or <Space> to exit"));
  Serial.print(F("Enter command:"));
}

const void clearSerialInput() {
  while (Serial.available()) Serial.read();
}

bool editValue(KeyInfo *p, int *pvalue, __FlashStringHelper *message) {
  clearSerialInput();
  Serial.print(message);
  while (!Serial.available());
  String str = Serial.readString();
  Serial.println(str);

  int value = str.toInt();

  if (value == 0) {
    return false;
  }

  if (value < 0) {
    p->value = NO_VALUE;
    p->press = NO_VALUE;
    p->delay = NO_VALUE;
    for (int n = 0; n < KEYS_SIZE; n++) {
      p->keyCode[n] = NO_KEY;
    }
    return false;
  }
  
  *pvalue = value;
  return true;
}

void editProfile(byte index) {
  KeyInfo *p = &keyProfiles[index];
  if (!editValue(p, &p->value, F("Enter Value, 0 - exit, -1 - delete profile [600]):"))) return;
  if (!editValue(p, &p->press, F("Enter Press, 0 - exit, -1 - delete profile [100]):"))) return;
  if (!editValue(p, &p->delay, F("Enter Delay, 0 - exit, -1 - delete profile [1000]):"))) return;
  int n = 0;
  for (; n < KEYS_SIZE; n++) {
    clearSerialInput();
    Serial.print(F("Enter Key Code [0 - exit, -1 - clear, sample: 'A', 65, 0x41]:"));
    while (!Serial.available());
    String str = Serial.readString();
    Serial.println(str);
    
    if (str == "0") return;
    if (str == "-1") break;

    if (str[0] == '\'') {
      if (str.length() < 3 || str[2] != '\'') {
        Serial.println("error");
        break;
      }
      p->keyCode[n] = toLowerCase(str[1]);
    }
    
    if (str[0] == '0') {
      if (str.length() < 3 || str[1] != 'x') {
        Serial.println("error");
        break;
      }
      str.remove(0, 2);
      int value;
      if (sscanf(str.c_str(), "%02X", &value) != 1) {
        Serial.println("error");
        break;
      }
      p->keyCode[n] = (uint8_t)value;
    }
  }
  for (; n < KEYS_SIZE; n++) {
    p->keyCode[n] = NO_KEY;
  }  
}

void loopDialog() {
  if (Serial.available()) {
    clearSerialInput();
    while (true) {
      diplayHelp();
      while (!Serial.available());
      char cmd = Serial.read();
      Serial.println(cmd);
      switch (cmd) {
        case '1': case '2': case '3': case '4': {
          editProfile(cmd - '1');
          break;
        }
        case ' ': {
          return;
        }
      }
    }
  }
}

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  playMelody();
}

void DoAction() {
  KeyInfo *p = &keyProfiles[selectedProfile];
  for (byte i = 0; i < KEYS_SIZE; i++) {
    uint8_t value = p->keyCode[i];
    if (value == 0xFF) break;
    Keyboard.press(value);
  }
  delay(p->press);
  Keyboard.releaseAll();  
  delay(p->delay);
}

void loop() {
  int value = analogRead(A0);
#ifdef RAW_VALUE
  Serial.println(value);
#endif
  if (value >= keyProfiles[selectedProfile].value) {
    DoAction();
  }
  loopDialog();
}
