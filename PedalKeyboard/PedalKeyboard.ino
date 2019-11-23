/*

https://compacttool.ru/viewtovar.php?id=683

На плате Pro Micro нет светодиода подключенного к 13 пину
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

#include <Keyboard.h>
#include "pitches.h"

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

void setup()
{
  // initialize control over the keyboard:
  Keyboard.begin();
  Serial.begin(9600);

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

void DoAction()
{
  Serial.println("DoAction");
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
  delay(10);
  Keyboard.releaseAll();  
}

void loop()
{
  delay(100);
  int sensorValue0 = analogRead(A0);
  if (sensorValue0 >= 200)
  {
    Serial.print("A0 = ");
    Serial.println(sensorValue0);
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
