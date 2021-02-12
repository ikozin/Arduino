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

//#define TEST_PARALLEL
//#define TEST_SHIFT
#define TEST_BLOCK

#define C             (12)
#define R             (13)

#define D0            (2)
#define D1            (3)
#define D2            (4)
#define D3            (5)
#define D4            (6)
#define D5            (7)
#define D6            (8)
#define D7            (9)


#define LINE_COUNT    (8)   // количество линий в одном блоке матрицы
#define BLOCK_COUNT   (6)   // количество блоков матрицы (3x2)

#define DELAY_TIME    (1000)
#define DELAY_FRAME   (1000)

void setup() {
  pinMode(C, OUTPUT);
  digitalWrite(C, LOW);

#if defined(TEST_PARALLEL) || defined(TEST_BLOCK)
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  setData(0x00);
#endif

#if defined(TEST_SHIFT) || defined(TEST_BLOCK)
  pinMode(R, OUTPUT);
  digitalWrite(R, HIGH);
  resetAddress();
#endif

  // Serial
  Serial.begin(9600);
  while (!Serial) {}
}

void clockCycle() {
  digitalWrite(C, HIGH);
  digitalWrite(C, LOW);
}

void resetAddress() {
  digitalWrite(R, LOW);
  digitalWrite(R, HIGH);
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

void loadData(byte data) {
  setData(data);
  clockCycle();
}

void test_loopShift() {
  long time = micros();
  
  for (int i = 0; i < LINE_COUNT; i++) {
    clockCycle();
    delay(DELAY_TIME);
  }
  resetAddress();
  
  time = micros() - time;
  Serial.println(time);

  delay(DELAY_FRAME);
}

void test_loopData() {
  loadData(0x00);
  delay(DELAY_TIME);
  loadData(0xFF);
  delay(DELAY_TIME);

  loadData(0x00);
  delay(DELAY_TIME);
  for (uint8_t data = B00000001; data > 0; data <<= 1) {
    loadData(data);
    delay(DELAY_TIME);
  }
  
  loadData(0x00);
  delay(DELAY_TIME);
  for (uint8_t data = B00000011; data > 0; data <<= 2) {
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

void test_loopBlock() {
  long time = micros();
  resetAddress();
  loadData(0x00);
  loadData(0x00);
  loadData(0x00);
  loadData(0x00);
  loadData(0x00);
  loadData(0x00);
  loadData(0x00);
  loadData(0x00);
  time = micros() - time;
  Serial.println(time);
  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  loadData(0x55);
  loadData(0x55);
  loadData(0x55);
  loadData(0x55);
  loadData(0x55);
  loadData(0x55);
  loadData(0x55);
  loadData(0x55);
  time = micros() - time;
  Serial.println(time);

  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  loadData(0xAA);
  loadData(0xAA);
  loadData(0xAA);
  loadData(0xAA);
  loadData(0xAA);
  loadData(0xAA);
  loadData(0xAA);
  loadData(0xAA);
  time = micros() - time;
  Serial.println(time);

  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  loadData(0xFF);
  loadData(0xFF);
  loadData(0xFF);
  loadData(0xFF);
  loadData(0xFF);
  loadData(0xFF);
  loadData(0xFF);
  loadData(0xFF);
  time = micros() - time;
  Serial.println(time);

  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  loadData(0x01);
  loadData(0x02);
  loadData(0x04);
  loadData(0x08);
  loadData(0x10);
  loadData(0x20);
  loadData(0x40);
  loadData(0x80);
  time = micros() - time;
  Serial.println(time);

  delay(DELAY_TIME);
}

void loop() {
#if defined(TEST_PARALLEL)
  Serial.println(F("TEST PARALLEL"));
  test_loopData();
#endif

#if defined(TEST_SHIFT)
  Serial.println(F("TEST SHIFT"));
  test_loopShift();
#endif

#if defined(TEST_BLOCK)
  Serial.println(F("TEST BLOCK"));
  test_loopBlock();
#endif
}
