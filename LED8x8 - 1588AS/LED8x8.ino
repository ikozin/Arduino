#include <Arduino.h>

/*
http://toplightusa.com/product/pdf/A-1588AS.pdf

Распиновка платы

   16  15  14  13  12  11  10   9
    |   |   |   |   |   |   |   |
  --------------------------------
 | C8  C7  R2  C1  R4  C6  C4  R1 |
 |  O   O   O   O   O   O   O   O |
 |  O   O   O   O   O   O   O   O |
 |  O   O   O   O   O   O   O   O |
 |  O   O   O   O   O   O   O   O |
 |  O   O   O   O   O   O   O   O |
 |  O   O   O   O   O   O   O   O |
 |  O   O   O   O   O   O   O   O |
 |  O   O   O   O   O   O   O   O |
 | R5  R7  C2  C3  R8  C5  R6  R3 |
  --------------------------------
   |   |   |   |   |   |   |   |
   1   2   3   4   5   6   7   8

схема платы
      C1 C2 C3 C4 C5 C6 C7 C8 
      13  3  4 10  6 11 15 16
       |  |  |  |  |  |  |  |
R1  9 -/--/--/--/--/--/--/--/   C (+5V)
R2 14 -/--/--/--/--/--/--/--/     |
R3  8 -/--/--/--/--/--/--/--/    _|_
R4 12 -/--/--/--/--/--/--/--/    \_/
R5  1 -/--/--/--/--/--/--/--/    ---
R6  7 -/--/--/--/--/--/--/--/     |
R7  2 -/--/--/--/--/--/--/--/   R (GND)
R8  5 -/--/--/--/--/--/--/--/
 
*/

#define R1  2
#define R2  3
#define R3  4
#define R4  5
#define R5  6
#define R6  7
#define R7  8
#define R8  9

void setup()
{
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  digitalWrite(R5, HIGH);
  digitalWrite(R6, HIGH);
  digitalWrite(R7, HIGH);
  digitalWrite(R8, HIGH);

  Serial.begin(9600);
  while (!Serial) {}  
  Serial.println(F("Start"));
}

void loop()
{
}
