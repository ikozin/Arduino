//#define RAW_DATA 1
#include <Arduino.h>

/*
http://tixer.ru/catalog/modules/Joysticks-btns/modul_dzhoystika/

*/

#define PIN_AXIS_X  A0
#define PIN_AXIS_Y  A1
#define PIN_BTN     11

void setup()
{
  pinMode(PIN_AXIS_X, INPUT);
  pinMode(PIN_AXIS_Y, INPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
  // Serial
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("Start"));
}

void loop()
{
#ifdef RAW_DATA
  int x = analogRead(PIN_AXIS_X);
  int y = analogRead(PIN_AXIS_Y);
  int btn = !digitalRead(PIN_BTN);
  Serial.print("X=");
  Serial.print(x);
  Serial.print(",Y=");
  Serial.print(y);
  Serial.print(",BTN=");
  Serial.print(btn);
  Serial.println();  
#else
  int x = map(analogRead(PIN_AXIS_X), 0, 1023, 0, 255);
  int y = map(analogRead(PIN_AXIS_Y), 0, 1023, 0, 255);
  int btn = !digitalRead(PIN_BTN);
  Serial.print("X=");
  Serial.print(x);
  Serial.print(",Y=");
  Serial.print(y);
  Serial.print(",BTN=");
  Serial.print(btn);
  Serial.println();  
#endif
}
