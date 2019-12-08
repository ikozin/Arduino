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
  |          ----          |--  C
  |         |    |         |-- GND
  |         |    |         |-- VCC
  |         |    |         |
  |         |   *|         |
  |          ----          |
  |                        |
   ------------------------
    |  |  |  |  |  |  |  |
    1  2  3  4  5  6  7  8


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
       ------------
      |            |
      |            |-- GND
 D0 --|     ---    |-- VCC
 D1 --|    |*  |   |
 D2 --|    |   |   |
 D3 --|    |   |   |
 D4 --|    |   |   |
 D5 --|    |   |   |
 D6 --|    |   |   |
 D7 --|     ---    |-- PR
      |            |-- DR
      |            |
       ------------
          |     |
          R     C


*/

#define D0            (2)
#define D1            (3)
#define D2            (4)
#define D3            (5)
#define D4            (6)
#define D5            (7)
#define D6            (8)
#define D7            (9)

#define C             (12)
#define R             (13)

#define LINE_COUNT    (8)   // количество линий в одном блоке матрицы
#define BLOCK_COUNT   (6)   // количество блоков матрицы (3x2)

#define DELAY_TIME    (1000)
#define DELAY_FRAME   (1000)

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(C, OUTPUT);

  digitalWrite(C, LOW);
  digitalWrite(R, HIGH);
  resetAddress();
  setData(0x00);

  // Serial
  Serial.begin(9600);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
}

void loop() {
  //loopShift();
  loopData();
}

void resetAddress() {
  digitalWrite(R, LOW);
  digitalWrite(R, HIGH);
}

void clockCycle() {
  digitalWrite(C, HIGH);
  digitalWrite(C, LOW);
}

void setData(byte data) {
  digitalWrite(D0, bitRead(data, 0));
  digitalWrite(D1, bitRead(data, 1));
  digitalWrite(D2, bitRead(data, 2));
  digitalWrite(D3, bitRead(data, 3));
  digitalWrite(D4, bitRead(data, 4));
  digitalWrite(D5, bitRead(data, 5));
  digitalWrite(D6, bitRead(data, 6));
  digitalWrite(D7, bitRead(data, 7));
}

void loopShift() {
  long time = micros();
  
  for (int i = 0; i < LINE_COUNT * BLOCK_COUNT; i++) {
    setData(0xFF);
    clockCycle();
    delay(DELAY_TIME);
  }
  resetAddress();
  
  time = micros() - time;
  Serial.println(time);

  delay(DELAY_FRAME);
}

void loopData() {
  long time = micros();

  testDataLoad(0xFF);
  delay(DELAY_FRAME);
  testDataLoad(0x00);
  delay(DELAY_FRAME);
  
  time = micros() - time;
  Serial.println(time);
}

void testDataLoad(byte data) {
  setData(data);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
}
