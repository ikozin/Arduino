/*

Распиновка платы
       -----------------
 16 --|                 |
 15 --|   X    X    X   |-- GND
 14 --|   X    X    X   |-- VCC  (+5V)
 13 --|   DL   SL   E   |
 12 --|                 |
 11 --|                 |
 10 --|                 |-- PR
 9  --|                 |-- PL
 8  --|                 |-- C
 7  --|                 |-- E   (pullup)
 6  --|                 |-- R   (pullup)
 5  --|                 |-- SR  (pullup)
 4  --|                 |-- SL  (pullup)
 3  --|  DR    R    SR  |-- DL  (pullup)
 2  --|   X    X    X   |-- DR  (pullup)
 1  --|   X    X    X   |
       -----------------

*/
#define PR  2
#define PL  3
#define C   4
#define E   5
#define R   6
#define SR  7
#define SL  8
#define DL  9
#define DR  10

void setup()
{
  pinMode(PR, INPUT);
  pinMode(PL, INPUT);
  pinMode(C,  OUTPUT);
  pinMode(E,  OUTPUT);
  pinMode(R,  OUTPUT);
  pinMode(SR, OUTPUT);
  pinMode(SL, OUTPUT);
  pinMode(DL, OUTPUT);
  pinMode(DR, OUTPUT);

  digitalWrite(C,  LOW);
  digitalWrite(E,  HIGH);
  digitalWrite(R,  HIGH);
  digitalWrite(SR, HIGH);
  digitalWrite(SL, HIGH);
  digitalWrite(DL, HIGH);
  digitalWrite(DR, HIGH);

  Serial.begin(9600);
}

void loop()
{
  writeData(B00000000);
  writeData(B00000001);
  writeData(B00000011);
  writeData(B00000111);
  writeData(B00001111);
  writeData(B00011111);
  writeData(B00111111);
  writeData(B01111111);
  writeData(B11111111);
  writeData(B11111110);
  writeData(B11111100);
  writeData(B11111000);
  writeData(B11110000);
  writeData(B11100000);
  writeData(B11000000);
  writeData(B10000000);
}
void writeData(uint8_t data)
{
  digitalWrite(C,  LOW);
  shiftOut(DR, C, MSBFIRST, data);
  delay(200);
}

/*
void loop() {
  Serial.write("Shift Up");

  digitalWrite(SR, HIGH);
  digitalWrite(SL, LOW);
  digitalWrite(E,  LOW);
  Reset();
  digitalWrite(DR, HIGH);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  
  digitalWrite(DR, LOW);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
  Clk();
  delay(200);
}

void Reset()
{
  digitalWrite(SR, HIGH);
  delay(100);
  digitalWrite(SR, LOW);
  delay(100);
  digitalWrite(SR, HIGH);
}

void Clk()
{
  digitalWrite(C, HIGH);
  delay(1);
  digitalWrite(C, LOW);
}
*/
