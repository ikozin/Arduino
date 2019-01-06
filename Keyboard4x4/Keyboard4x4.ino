#include <Arduino.h>

/*
http://tixer.ru/catalog/modules/Joysticks-btns/matrichnaya_klaviatura_iz_taktovykh_knopok_4kh4/

     -----------------------
    |                       |
K1 -| S1    S2    S3    S4  | 
K2 -|                       |
K3 -| S5    S6    S7    S8  |
K4 -|                       |
K5 -| S9    s10   S11   S12 |
K6 -|                       |
K7 -| S13   s14   S15   S16 | 
K8 -|                       |
     -----------------------


*/
#define K1  9
#define K2  8
#define K3  7
#define K4  6
#define K5  5
#define K6  4
#define K7  3
#define K8  2


byte col[] = {K4, K3, K2, K1};
byte row[] = {K5, K6, K7, K8};

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < sizeof(row)/sizeof(row[0]); i++)
  {
    pinMode(row[i], OUTPUT);
    digitalWrite(row[i], HIGH);
  }
  for (int i = 0; i < sizeof(col)/sizeof(col[0]); i++)
  {
    pinMode(col[i], INPUT_PULLUP);
  }
  while (!Serial) {}  
  
  Serial.println(F("Start"));
  
}

int getKeyPresses()
{
  int keyIndex = 0;
  for (int i = 0; i < sizeof(row)/sizeof(row[0]); i++)
  {
    digitalWrite(row[i], LOW);
    for (int n = 0; n < sizeof(col)/sizeof(col[0]); n++)
    {
      if (!digitalRead(col[n]))
      {
        digitalWrite(row[i], HIGH);
        return keyIndex + n + 1;
      }
    }
    digitalWrite(row[i], HIGH);
    keyIndex += 4;
  }
  return 0;
}

void loop()
{
  int key = getKeyPresses();
  if (!key) return;
  Serial.println(key);
  
/*  
  for (int i = 0; i < sizeof(row)/sizeof(row[0]); i++)
  {
    digitalWrite(row[i], LOW);
    for (int n = 0; n < sizeof(col)/sizeof(col[0]); n++)
    {
      Serial.print(!digitalRead(col[n]));
    }
    digitalWrite(row[i], HIGH);
    Serial.println();
  }
  Serial.println();
  delay(2000);
*/

}
