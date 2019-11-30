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
typedef struct
{
  uint16_t value;
  uint16_t delay;
  uint8_t  keyCodeControl[7];
  uint8_t  keyCode[5];
} KeyInfo;

byte selectedProfile = 0;
KeyInfo keyProfiles[] =
{
  { 600, 1000, { KEY_LEFT_CTRL, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }, { 'f', 0xFF, 0xFF, 0xFF, 0xFF } },
  { 600, 1000, { KEY_LEFT_CTRL, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }, { 'f', 0xFF, 0xFF, 0xFF, 0xFF } },
};

// notes in the melody:
int melody[] =
{
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] =
{
  4, 8, 8, 4, 4, 4, 4, 4
};


void playMelody()
{
  for (int thisNote = 0; thisNote < 8; thisNote++)
  {
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

void printKeyCode(uint8_t key)
{
  switch(key)
  {
    case KEY_LEFT_CTRL:
    {
      Serial.print(F("KEY_LEFT_CTRL"));
      break;
    }
    case KEY_LEFT_SHIFT:
    {
      Serial.print(F("KEY_LEFT_SHIFT"));
      break;
    }
    case KEY_LEFT_ALT:
    {
      Serial.print(F("KEY_LEFT_ALT"));
      break;
    }
    case KEY_LEFT_GUI:
    {
      Serial.print(F("KEY_LEFT_GUI"));
      break;
    }
    case KEY_RIGHT_CTRL:
    {
      Serial.print(F("KEY_RIGHT_CTRL"));
      break;
    }
    case KEY_RIGHT_SHIFT:
    {
      Serial.print(F("KEY_RIGHT_SHIFT"));
      break;
    }
    case KEY_RIGHT_ALT:
    {
      Serial.print(F("KEY_RIGHT_ALT"));
      break;
    }
    case KEY_RIGHT_GUI:
    {
      Serial.print(F("KEY_RIGHT_GUI"));
      break;
    }
    case KEY_UP_ARROW:
    {
      Serial.print(F("KEY_UP_ARROW"));
      break;
    }
    case KEY_DOWN_ARROW:
    {
      Serial.print(F("KEY_DOWN_ARROW"));
      break;
    }
    case KEY_LEFT_ARROW:
    {
      Serial.print(F("KEY_LEFT_ARROW"));
      break;
    }
    case KEY_RIGHT_ARROW:
    {
      Serial.print(F("KEY_RIGHT_ARROW"));
      break;
    }
    case KEY_BACKSPACE:
    {
      Serial.print(F("KEY_BACKSPACE"));
      break;
    }
    case KEY_TAB:
    {
      Serial.print(F("KEY_TAB"));
      break;
    }
    case KEY_RETURN:
    {
      Serial.print(F("KEY_RETURN"));
      break;
    }
    case KEY_ESC:
    {
      Serial.print(F("KEY_ESC"));
      break;
    }
    case KEY_INSERT:
    {
      Serial.print(F("KEY_INSERT"));
      break;
    }
    case KEY_DELETE:
    {
      Serial.print(F("KEY_DELETE"));
      break;
    }
    case KEY_PAGE_UP:
    {
      Serial.print(F("KEY_PAGE_UP"));
      break;
    }
    case KEY_PAGE_DOWN:
    {
      Serial.print(F("KEY_PAGE_DOWN"));
      break;
    }
    case KEY_HOME:
    {
      Serial.print(F("KEY_HOME"));
      break;
    }
    case KEY_END:
    {
      Serial.print(F("KEY_END"));
      break;
    }
    case KEY_CAPS_LOCK:
    {
      Serial.print(F("KEY_CAPS_LOCK"));
      break;
    }
    case KEY_F1:
    {
      Serial.print(F("KEY_F1"));
      break;
    }
    case KEY_F2:
    {
      Serial.print(F("KEY_F2"));
      break;
    }
    case KEY_F3:
    {
      Serial.print(F("KEY_F3"));
      break;
    }
    case KEY_F4:
    {
      Serial.print(F("KEY_F4"));
      break;
    }
    case KEY_F5:
    {
      Serial.print(F("KEY_F5"));
      break;
    }
    case KEY_F6:
    {
      Serial.print(F("KEY_F6"));
      break;
    }
    case KEY_F7:
    {
      Serial.print(F("KEY_F7"));
      break;
    }
    case KEY_F8:
    {
      Serial.print(F("KEY_F8"));
      break;
    }
    case KEY_F9:
    {
      Serial.print(F("KEY_F9"));
      break;
    }
    case KEY_F10:
    {
      Serial.print(F("KEY_F10"));
      break;
    }
    case KEY_F11:
    {
      Serial.print(F("KEY_F11"));
      break;
    }
    case KEY_F12:
    {
      Serial.print(F("KEY_F12"));
      break;
    }
    case KEY_F13:
    {
      Serial.print(F("KEY_F13"));
      break;
    }
    case KEY_F14:
    {
      Serial.print(F("KEY_F14"));
      break;
    }
    case KEY_F15:
    {
      Serial.print(F("KEY_F15"));
      break;
    }
    case KEY_F16:
    {
      Serial.print(F("KEY_F16"));
      break;
    }
    case KEY_F17:
    {
      Serial.print(F("KEY_F17"));
      break;
    }
    case KEY_F18:
    {
      Serial.print(F("KEY_F18"));
      break;
    }
    case KEY_F19:
    {
      Serial.print(F("KEY_F19"));
      break;
    }
    case KEY_F20:
    {
      Serial.print(F("KEY_F20"));
      break;
    }
    case KEY_F21:
    {
      Serial.print(F("KEY_F21"));
      break;
    }
    case KEY_F22:
    {
      Serial.print(F("KEY_F22"));
      break;
    }
    case KEY_F23:
    {
      Serial.print(F("KEY_F23"));
      break;
    }
    case KEY_F24:
    {
      Serial.print(F("KEY_F24"));
      break;
    }
    default:
    {
      break;
    }
  }
}

void diplayhelp()
{
  Serial.println();
  Serial.println("? - help");
  Serial.println("l - list profiles");
  Serial.println("! - change profiles");
    
}

void setup()
{
  // initialize control over the keyboard:
  Keyboard.begin();
  Serial.begin(9600);
  playMelody();
}

void DoAction()
{
#ifdef RAW_VALUE
  Serial.println("DoAction");
#endif
  for (byte i = 0; i < 2; i++)
  {
    uint8_t value = keyProfiles[selectedProfile].keyCodeControl[i];
    if (value == 0xFF) break;
#ifdef RAW_VALUE
    Serial.println(value);
#endif
    Keyboard.press(value);
  }
  for (byte i = 0; i < 2; i++)
  {
    uint8_t value = keyProfiles[selectedProfile].keyCode[i];
    if (value == 0xFF) break;
#ifdef RAW_VALUE
    Serial.println(value);
#endif
    Keyboard.write(value);
  }
  delay(10);
  Keyboard.releaseAll();  
  delay(keyProfiles[selectedProfile].delay);
}

void loop()
{
  int value = analogRead(A0);
#ifdef RAW_VALUE
  Serial.println(value);
#endif
  if (value >= keyProfiles[selectedProfile].value)
  {
    DoAction();
  }

  
/*
  //Keyboard.print("Hello World!");
  // CTRL-ALT-DEL:
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  // Enter
  delay(1000);
  Keyboard.write(KEY_RETURN);
  while (1) {}
*/
}
