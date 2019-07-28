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
  |          ----          |--  C
  |         |    |         |-- GND
  |         |    |         |-- VCC
  |         |    |         |
  |         |   *|         |
  |          ----          |
   ------------------------
    |  |  |  |  |  |  |  |
    1  2  3  4  5  6  7  8

*/
#define IN_1  (2)
#define IN_2  (3)
#define IN_3  (4)
#define IN_4  (5)
#define IN_5  (6)
#define IN_6  (7)
#define IN_7  (8)
#define IN_8  (9)
#define IN_C  (10)
#define DELAY_TIME (200)
void setup()
{
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(IN_5, OUTPUT);
  pinMode(IN_6, OUTPUT);
  pinMode(IN_7, OUTPUT);
  pinMode(IN_8, OUTPUT);
  pinMode(IN_C, OUTPUT);

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  digitalWrite(IN_5, LOW);
  digitalWrite(IN_6, LOW);
  digitalWrite(IN_7, LOW);
  digitalWrite(IN_8, LOW);
  digitalWrite(IN_C, LOW);

  loadData();

  // Serial
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("Start"));
}

void loop()
{
  blink();
  for (byte data = 0x01; data > 0; data <<= 1)
    setData(data);

  blink();
  for (byte data = 0x01; data > 0; data <<= 1)
    setData(~data);
}

void setData(byte data)
{
  digitalWrite(IN_1, bitRead(data, 0));
  digitalWrite(IN_2, bitRead(data, 1));
  digitalWrite(IN_3, bitRead(data, 2));
  digitalWrite(IN_4, bitRead(data, 3));
  digitalWrite(IN_5, bitRead(data, 4));
  digitalWrite(IN_6, bitRead(data, 5));
  digitalWrite(IN_7, bitRead(data, 6));
  digitalWrite(IN_8, bitRead(data, 7));
  loadData();
  delay(DELAY_TIME);
}

void loadData()
{
  digitalWrite(IN_C,  HIGH);
  digitalWrite(IN_C,  LOW);
}

void blink()
{
  setData(0x00);
  setData(0x00);
  setData(0xFF);
  setData(0xFF);
  setData(0x00);
  setData(0x00);
}
