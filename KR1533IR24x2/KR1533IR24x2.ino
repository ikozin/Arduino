/*

Распиновка платы
       ----------------------
 16 --|                      |
 15 --|   X     |X|    |X|   |-- GND
 14 --|   X     |X|    |X|   |-- VCC  (+5V)
 13 --|   DL     SL     E    |
 12 --|                      |
 11 --|                      |
 10 --|                      |-- PR
 9  --|                      |-- PL
 8  --|                      |-- C            - 4
 7  --|                      |-- E   (pullup)
 6  --|                      |-- R   (pullup) - 6
 5  --|                      |-- SR  (pullup)
 4  --|                      |-- SL  (pullup)
 3  --|   DR     R      SR   |-- DL  (pullup)
 2  --|   X      X      X    |-- DR  (pullup) - 10
 1  --|   X      X      X    |
       ----------------------

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

void reset()
{
  digitalWrite(R,  LOW);
  digitalWrite(R,  HIGH);
}

void blink()
{
  writeData(makeWord(0xFF, 0xFF));
  delay(500);
  writeData(makeWord(0x00, 0x00));
  delay(500);
}


void loop()
{
  reset();
  blink();
  for (uint16_t data = 0x0001; data > 0; data <<= 1)
  {
    writeData(data);
    delay(200);
  }

  reset();
  blink();
  writeData(makeWord(0x00, 0x01));
  delay(200);
  for (uint16_t data = 0x0003; data > 0; data <<= 1)
  {
    writeData(data);
    delay(200);
  }
}
void writeData(uint16_t data)
{
  digitalWrite(C,  LOW);
  shiftOut(DR, C, MSBFIRST, highByte(data));
  shiftOut(DR, C, MSBFIRST, lowByte(data));
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
