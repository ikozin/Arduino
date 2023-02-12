#include <Arduino.h>

/*



  │ │ │ │ │ │ │ │      │ │ │ │ │ │ │ │      │ │ │ │ │ │ │ │  
┌─┴─┴─┴─┴─┴─┴─┴─┴─┐  ┌─┴─┴─┴─┴─┴─┴─┴─┴─┐  ┌─┴─┴─┴─┴─┴─┴─┴─┴─┐
│ 8 7 6 5 4 3 2 1 │  │ 8 7 6 5 4 3 2 1 │  │ 8 7 6 5 4 3 2 1 │
├─────────────────┤  ├─────────────────┤  ├─────────────────┤
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
│  К1533ИР23/37   │  │  К1533ИР23/37   │  │  К1533ИР23/37   │
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
└─────────────────┘  └─────────────────┘  └─────────────────┘

  C             R
  │             │
  │             ├────────────────────┬────────────────────┐
  │             │                    │                    │
  ├────────────────────┬────────────────────┐             │
  │             │      │             │      │             │
  │        ┌────────────────┐   ┌────────────────┐        │
  │    │   │    │      │    │   │    │      │    │   │    │
┌─┴─┬──┴─┬─┴──┬─┴─┐  ┌─┴─┬──┴─┬─┴──┬─┴─┐  ┌─┴─┬──┴─┬─┴──┬─┴─┐
│ C │ DR │ PR │ R │  │ C │ DR │ PR │ R │  │ C │ DR │ PR │ R │
├───┴────┴────┴───┤  ├───┴────┴────┴───┤  ├───┴────┴────┴───┤
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
│    К1533ИР24    │  │    К1533ИР24    │  │    К1533ИР24    │
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
└─────────────────┘  └─────────────────┘  └─────────────────┘

 VCC GND
  │   │
  ├────────────────────┬────────────────────┐
  │   │                │                    │ 
  │   ├────────────────────┬────────────────────┐
  │   │                │   │                │   │ 
┌─┴─┬─┴─┬─────────┐  ┌─┴─┬─┴─┬─────────┐  ┌─┴─┬─┴─┬─────────┐
│VCC│GND│         │  │VCC│GND│         │  │VCC│GND│         │
├───┴───┴─────────┤  ├───┴───┴─────────┤  ├───┴───┴─────────┤
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
│    К1533АП6     │  │    К1533АП6     │  │    К1533АП6     │
│                 │  │                 │  │                 │
│                 │  │                 │  │                 │
├─────────────────┤  ├─────────────────┤  ├─────────────────┤
│ 8 7 6 5 4 3 2 1 │  │ 8 7 6 5 4 3 2 1 │  │ 8 7 6 5 4 3 2 1 │
└─┬─┬─┬─┬─┬─┬─┬─┬─┘  └─┬─┬─┬─┬─┬─┬─┬─┬─┘  └─┬─┬─┬─┬─┬─┬─┬─┬─┘
  │ │ │ │ │ │ │ │      │ │ │ │ │ │ │ │      │ │ │ │ │ │ │ │


*/

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

long time;

uint8_t test1[] = {
  B11111111,
  B10000000,
  B10111111,
  B10100000,
  B10101111,
  B10101000,
  B10101011,
  B10101010,
  B10101010,
  B10101011,
  B10101000,
  B10101111,
  B10100000,
  B10111111,
  B10000000,
  B11111111,

  B11111111,
  B00000000,
  B11111111,
  B00000000,
  B11111111,
  B00000000,
  B11111111,
  B00000000,
  B00000000,
  B11111111,
  B00000000,
  B11111111,
  B00000000,
  B11111111,
  B00000000,
  B11111111,

  B11111111,
  B00000001,
  B11111101,
  B00000101,
  B11110101,
  B00010101,
  B11010101,
  B01010101,
  B01010101,
  B11010101,
  B00010101,
  B11110101,
  B00000101,
  B11111101,
  B00000001,
  B11111111,
};



void clockCycle() {
  digitalWrite(C, HIGH);
  digitalWrite(C, LOW);
}

void resetAddress() {
  digitalWrite(R, LOW);
  digitalWrite(R, HIGH);
}

void setData(uint8_t data) {
  digitalWrite(D0, bitRead(data, 0));
  digitalWrite(D1, bitRead(data, 1));
  digitalWrite(D2, bitRead(data, 2));
  digitalWrite(D3, bitRead(data, 3));
  digitalWrite(D4, bitRead(data, 4));
  digitalWrite(D5, bitRead(data, 5));
  digitalWrite(D6, bitRead(data, 6));
  digitalWrite(D7, bitRead(data, 7));
}

void loadData(uint8_t data) {
  setData(data);
  clockCycle();
}

void set(uint8_t data) {
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++)
    for (int l = 0; l < LINE_COUNT; l++)
      loadData(data);
}

void inline clear() {
  set(0x00);
}

void inline fill() {
  set(0xFF);
}

void testBit(uint8_t bitCount) {
  setData(B00000000);
  delay(200);
  uint8_t data = B00000001;
  for (int i = 1; i < bitCount; i++) {
    setData(data);
    delay(200);
    data <<= 1;
    data |= B00000001;
  }
  for (; data > 0; data <<= 1) {
    loadData(data);
    delay(200);
  }
}

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  setData(0x00);

  pinMode(R, OUTPUT);
  pinMode(C, OUTPUT);

  digitalWrite(C, LOW);
  digitalWrite(R, HIGH);

  clear();

  // Serial
  Serial.begin(57600);
  while (!Serial) {}

}

void loop() {
  // for (int n = 1; n < 8; n++) {
  //   testBit(n);
  // }


  for (int n = 0; n < 4; n++) {
    time = micros();
    clear();
    time = micros() - time;
    Serial.print("time:");
    Serial.println(time);
    delay(DELAY_TIME);

    time = micros();
    fill();
    time = micros() - time;
    Serial.print("time:");
    Serial.println(time);
    delay(DELAY_TIME);
  }

  time = micros();
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++) {
    for (uint8_t data = B00000001; data > 0; data <<= 1) {
      loadData(data);
    }
  }
  time = micros() - time;
  Serial.print("time:");
  Serial.println(time);
  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++) {
    for (uint8_t data = B00000011; data > 0; data <<= 2) {
      loadData(data);
      loadData(data);
    }
  }
  time = micros() - time;
  Serial.print("time:");
  Serial.println(time);
  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++) {
    for (uint8_t data = B00001111; data > 0; data <<= 4) {
      loadData(data);
      loadData(data);
      loadData(data);
      loadData(data);
    }
  }
  time = micros() - time;
  Serial.print("time:");
  Serial.println(time);
  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++) {
    for (uint8_t data = B11110000; data > 0; data >>= 4) {
      loadData(data);
      loadData(data);
      loadData(data);
      loadData(data);
    }
  }
  time = micros() - time;
  Serial.print("time:");
  Serial.println(time);
  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++) {
    for (uint8_t data = B11000000; data > 0; data >>= 2) {
      loadData(data);
      loadData(data);
    }
  }
  time = micros() - time;
  Serial.print("time:");
  Serial.println(time);
  delay(DELAY_TIME);

  time = micros();
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++) {
    for (uint8_t data = B10000000; data > 0; data >>= 1) {
      loadData(data);
    }
  }
  time = micros() - time;
  Serial.print("time:");
  Serial.println(time);
  delay(DELAY_TIME);

  time = micros();
  int index = 0;
  resetAddress();
  for (int b = 0; b < BLOCK_COUNT; b++)
    for (int l = 0; l < LINE_COUNT; l++)
      loadData(test1[index++]);
  time = micros() - time;
  Serial.print("time:");
  Serial.println(time);
  delay(DELAY_TIME);

}
