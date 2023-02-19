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

#include <matrix.h>

#define C             (12)
#define R             (13)

#define DELAY_TIME    (1000)
#define DELAY_FRAME   (1000)

Matrix matrix(R, C, 2, 3);


void test1(Matrix *matrix, unsigned long timeDelay);
void test2(Matrix *matrix, unsigned long timeDelay);
void test3(Matrix *matrix, unsigned long timeDelay);
void test4(Matrix *matrix, unsigned long timeDelay);


void setup(void) {
  matrix.init();
  matrix.fill(0x00);

  // Serial
  Serial.begin(57600);
  while (!Serial) {}
}

void loop(void) {

  matrix.resetAddress();
  Serial.println("reset");
  delay(1000);

  matrix.setData(B00000000);
  Serial.println("setdata");
  for (int i = 0; i < 32; i++)  {
    //delay(200);
    matrix.clockCycle();
    Serial.println("clockCycle");
  }

  matrix.resetAddress();
  Serial.println("reset");
  delay(1000);

  matrix.setData(B11111111);
  Serial.println("setdata");
  for (int i = 0; i < 32; i++)  {
    //delay(200);
    matrix.clockCycle();
    Serial.println("clockCycle");
  }

  matrix.resetAddress();
  Serial.println("reset");
  delay(1000);

  matrix.setData(B10101010);
  Serial.println("setdata");
  for (int i = 0; i < 32; i++)  {
    //delay(200);
    matrix.clockCycle();
    Serial.println("clockCycle");
  }

  matrix.resetAddress();
  Serial.println("reset");
  delay(1000);

  matrix.setData(B01010101);
  Serial.println("setdata");
  for (int i = 0; i < 32; i++)  {
    //delay(200);
    matrix.clockCycle();
    Serial.println("clockCycle");
  }

  // for (int i = 0; i < 4; i++)
  //   test1(&matrix, DELAY_TIME);

  // test2(&matrix, DELAY_TIME);

  // test3(&matrix, DELAY_TIME);

  // for (int i = 0; i < 32; i++)
  //   test4(&matrix, 18);

}
