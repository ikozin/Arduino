/*
КР1533ИР23
параллельный регистр хранения данных
       --------------
 3  --| D0 | RG | 1  |-- 2
 4  --| D1 |    | 2  |-- 5
 7  --| D2 |    | 3  |-- 6
 8  --| D3 |    | 4  |-- 9
 13 --| D4 |    | 5  |-- 12
 14 --| D5 |    | 6  |-- 15
 17 --| D6 |    | 7  |-- 16
 18 --| D7 |    | 8  |-- 19
      |    |    |    |
 11 --| C  |    |    |
 1  --|~EO |    |    |
       --------------

КР1533ИР37
параллельный регистр хранения данных
       --------------
 2  --| D0 | RG | 1  |-- 19
 3  --| D1 |    | 2  |-- 18
 4  --| D2 |    | 3  |-- 17
 5  --| D3 |    | 4  |-- 16
 6  --| D4 |    | 5  |-- 15
 7  --| D5 |    | 6  |-- 14
 8  --| D6 |    | 7  |-- 13
 9  --| D7 |    | 8  |-- 12
      |    |    |    |
 11 --| C  |    |    |
 1  --|~EO |    |    |
       --------------

Плата ИР23, ИР37

    D0 D1 D2 D3 D4 D5 D6 D7 
    |  |  |  |  |  |  |  |
   ------------------------
  |                        |
  |          ----          |-- CLK
  |         |    |         |-- GND
  |         |    |         |-- VCC
  |         |    |         |
  |         |   *|         |
  |          ----          |
  |                        |
   ------------------------
    |  |  |  |  |  |  |  |
    1  2  3  4  5  6  7  8


            -------         -------
           | POWER |       |  USB  |
          ---------------------------
         |                           |---
         |                      AREF |   |
         |                       GND |   |
         |                        13 |   |
      ---|                        12 | X | CLK
     |   | RST                    11 |   |
     |   | +3V                    10 |   |
 VCC | X | +5V                     9 | X | D7
 GNG | X | GND                     8 | X | D6
     |   | GND                       |---
     |   | VIN                     7 | X | D5
      ---|                         6 | X | D4
     |   | A0                      5 | X | D3
     |   | A1                      4 | X | D2
     |   | A2                      3 | X | D1
     |   | A3                      2 | X | D0
     |   | A4                      1 |   |
     |   | A5                      0 |   |
      ---|                           |---
          ---------------------------
 
*/

#define DATA0   (2)
#define DATA1   (3)
#define DATA2   (4)
#define DATA3   (5)
#define DATA4   (6)
#define DATA5   (7)
#define DATA6   (8)
#define DATA7   (9)

#define CLK     (12)

#define DELAY_TIME    (1000)

void setup()
{
  pinMode(CLK, OUTPUT);
  digitalWrite(CLK, LOW);

  pinMode(DATA0, OUTPUT);
  pinMode(DATA1, OUTPUT);
  pinMode(DATA2, OUTPUT);
  pinMode(DATA3, OUTPUT);
  pinMode(DATA4, OUTPUT);
  pinMode(DATA5, OUTPUT);
  pinMode(DATA6, OUTPUT);
  pinMode(DATA7, OUTPUT);
  setData(0x00);

  // Serial
  Serial.begin(9600);
  while (!Serial) {}
}

void clockCycle()
{
  digitalWrite(CLK, HIGH);
  digitalWrite(CLK, LOW);
}

void setData(byte data)
{
  digitalWrite(DATA0, bitRead(data, 0));
  digitalWrite(DATA1, bitRead(data, 1));
  digitalWrite(DATA2, bitRead(data, 2));
  digitalWrite(DATA3, bitRead(data, 3));
  digitalWrite(DATA4, bitRead(data, 4));
  digitalWrite(DATA5, bitRead(data, 5));
  digitalWrite(DATA6, bitRead(data, 6));
  digitalWrite(DATA7, bitRead(data, 7));
}

void loadData(byte data)
{
  setData(data);
  clockCycle();
}

void test_loopData()
{
  loadData(0x00);
  delay(DELAY_TIME);
  loadData(0xFF);
  delay(DELAY_TIME);

  loadData(0x00);
  delay(DELAY_TIME);
  for (uint8_t data = B00000001; data > 0; data <<= 1)
  {
    loadData(data);
    delay(DELAY_TIME);
  }
  
  loadData(0x00);
  delay(DELAY_TIME);
  for (uint8_t data = B00000011; data > 0; data <<= 2)
  {
    loadData(data);
    delay(DELAY_TIME);
  }

  loadData(0x00);
  delay(DELAY_TIME);
  loadData(B01010101);
  delay(DELAY_TIME);
  loadData(B10101010);
  delay(DELAY_TIME);
  loadData(B01010101);
  delay(DELAY_TIME);
  loadData(B10101010);
  delay(DELAY_TIME);
}

void loop()
{
  Serial.println(F("TEST PARALLEL"));
  test_loopData();
}
