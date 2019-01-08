//#define RAW_DATA 1
#include <Arduino.h>
#include "keymatrix.h"

/*
http://tixer.ru/catalog/modules/Joysticks-btns/matrichnaya_klaviatura_iz_taktovykh_knopok_4kh4/

Распиновка платы
     --------------------------
    |                          |
K1 -|Y0  S1    S2    S3    S4  | 
K2 -|Y1                        |
K3 -|Y2  S5    S6    S7    S8  |
K4 -|Y3                        |
K5 -|X0  S9    s10   S11   S12 |
K6 -|X1                        |
K7 -|X2  S13   s14   S15   S16 | 
K8 -|X3                        |
     --------------------------
Схема платы
          Y0   Y1   Y2   Y3
          |    |    |    |
     X0---/S1--/S2--/S3--/S4
     X1---/S5--/S6--/S7--/S8
     X2---/S9--/S10-/S11-/S12
     X3---/S13-/S14-/S15-/S16

*/
#define K1  9
#define K2  8
#define K3  7
#define K4  6
#define K5  5
#define K6  4
#define K7  3
#define K8  2

byte row[] = {K5, K6, K7, K8};
byte col[] = {K4, K3, K2, K1};
KeyMatrix matrix;

void setup()
{
  Serial.begin(9600);
  matrix.begin(row, sizeof(row)/sizeof(row[0]), col, sizeof(col)/sizeof(col[0]));
  while (!Serial) {}  
  Serial.println(F("Start"));
}

void loop()
{
#ifdef RAW_DATA
  for (int i = 0; i < sizeof(row) / sizeof(row[0]); i++)
  {
    digitalWrite(row[i], LOW);
    for (int n = 0; n < sizeof(col) / sizeof(col[0]); n++)
    {
      Serial.print(!digitalRead(col[n]));
    }
    digitalWrite(row[i], HIGH);
    Serial.println();
  }
  Serial.println();
  delay(2000);
#else
  int key = matrix.GetKeyPressed();
  if (!key) return;
  Serial.println(key);
#endif
}
