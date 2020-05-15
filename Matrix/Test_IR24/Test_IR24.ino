/*
КР1533ИР24
последовательный регистр хранения данных
       --------------
 11 --| DR | RG | PL |-- 8
      |    |<-->|    |
 12 --| C  |    | 1  |-- 7
      |    |    | 2  |-- 13
 1  --| SR |    | 3  |-- 6
 19 --| SL |    | 4  |-- 14
      |    |    | 5  |-- 5
 2  --| ~& |    | 6  |-- 15
 3  --| ~E |    | 7  |-- 4
      |    |    | 8  |-- 16
 9  --| ~R |    |    |
      |    |    |    |
 18 --| DL |    | PR |-- 16
       --------------

Плата ИР24
       -----------
      |           |
      |           |-- GND
 D0 --|    ---    |-- VCC
 D1 --|   |*  |   |
 D2 --|   |   |   |
 D3 --|   |   |   |
 D4 --|   |   |   |
 D5 --|   |   |   |
 D6 --|   |   |   |
 D7 --|    ---    |-- PR
      |           |-- DR
      |           |
       -----------
         |     |
         R     C


            -------         -------
           | POWER |       |  USB  |
          ---------------------------
         |                           |---
         |                      AREF |   |
         |                       GND |   |
         |                        13 | X | RST
      ---|                        12 | X | CLK
     |   | RST                    11 |   |
     |   | +3V                    10 |   |
     | X | +5V                     9 |   |
     | X | GND                     8 |   |
     |   | GND                       |---
     |   | VIN                     7 |   |
      ---|                         6 |   |
     |   | A0                      5 |   |
     |   | A1                      4 |   |
     |   | A2                      3 |   |
     |   | A3                      2 |   |
     |   | A4                      1 |   |
     |   | A5                      0 |   |
      ---|                           |---
          ---------------------------
 
*/

#define CLK         (12)
#define RST         (13)
// количество линий в одном блоке матрицы
#define LINE_COUNT  (8)
#define DELAY_TIME  (1000)

void setup()
{
  pinMode(CLK, OUTPUT);
  digitalWrite(CLK, LOW);

  pinMode(RST, OUTPUT);
  digitalWrite(RST, HIGH);

  resetAddress();

  // Serial
  Serial.begin(9600);
  while (!Serial) {}
}

void clockCycle()
{
  digitalWrite(CLK, HIGH);
  digitalWrite(CLK, LOW);
}

void resetAddress()
{
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
}

void test_loopShift()
{
  for (int i = 0; i < LINE_COUNT; i++)
  {
    clockCycle();
    delay(DELAY_TIME);
  }
  resetAddress();
  delay(DELAY_TIME);
}

void loop()
{
  Serial.println(F("TEST SHIFT"));
  test_loopShift();
}
