/*
AT28C256
https://docs-europe.electrocomponents.com/webdocs/1596/0900766b815963c9.pdf

Подключение к Arduino MEGA
https://arduinka.pro/blog/wp-content/uploads/2017/09/mega2560-pinout-1024x724.png

         -------                                                          -------
        | POWER |                                                        |  USB  |
      -----------------------------------------------------------------------------------------
     |                                                                                         |---
     |                                                                                    AREF |   |
     |                                                                                     GND |   |
     |                                                                                      13 |   |
  ---|                                                                                      12 |   |
 |   | RST                                                                                  11 |   |
 |   | 3V                                                                                   10 |   |
 | X | 5V                                                                                    9 |   |
 | X | GND                                                                                   8 |   |
 |   |                                                                                         |---
 |   | VIN                                                                                   7 | X | - !WE
  ---|                                                                                       6 | X | - !CE
 |   | A0                                                                                    5 | X | - !OE
 |   | A1                                                                                    4 |   |
 |   | A2                                                                                    3 |   |
 |   | A3                                                                                    2 |   |
 |   | A4                                                                                    1 |   |
 |   | A5                                                                                    0 |   |
 |   | A6                                                                                      |---
 |   | A7                                                                                   14 |   |
  ---|                                                                                      15 |   |
 |   | A8                                                                                   16 |   |
 |   | A9                                                                                   17 |   |
 |   | A10                                                                                  18 |   |
 |   | A11                                                                                  19 |   |
 |   | A12                                                                                  20 |   |
 |   | A13                                                                                  21 |   |
 |   | A14                                                                                     |---
 |   | A15                                                                                     |
  ---|                                                                                         |
     | GND| 52 | 50 | 48 | 46 | 44 | 42 | 40 | 38 | 36 | 34 | 32 | 30 | 28 | 26 | 24 | 22 | +5V|
      -----------------------------------------------------------------------------------------
     |    |    |    |    |    | D6 | D4 | D2 | D0 | A13| A12| A10| A8 | A6 | A4 | A2 | A0 |    |
     |    |    |    |    |    | D7 | D5 | D3 | D1 |    | A13| A11| A9 | A7 | A5 | A3 | A1 |    |
      -----------------------------------------------------------------------------------------
     | GND| 53 | 51 | 49 | 47 | 45 | 43 | 41 | 39 | 37 | 35 | 33 | 31 | 29 | 27 | 25 | 23 | +5V|
                              |                 ^ |                 ^ |                 ^ |
                              |               ключ|               ключ|               ключ|
                              |                4x2|                4x2|                4x2|
                              |                3+5|      2+1+1+1+1+1+1|                  8|
                              |         ключ D0,D3|    ключ A8,A10-A13|            ключ A0|


Распиновка AT28C256
      -------------
  1 -| A14     +5V |- 28
  2 -| A12     ~WE |- 27
  3 -| A7      A13 |- 26
  4 -| A6       A8 |- 25
  5 -| A5       A9 |- 24
  6 -| A4      A11 |- 23
  7 -| A3      ~OE |- 22
  8 -| A2      A10 |- 21
  9 -| A1      ~CE |- 20
 10 -| A0       D7 |- 19
 11 -| D0       D6 |- 18
 12 -| D1       D5 |- 17
 13 -| D2       D4 |- 16
 14 -| GND      D3 |- 15
	    -------------

*/

#if !defined(__AVR_ATmega2560__)
#error "Select board ATMEG2560"
#endif

#define ADDR0   (22)
#define ADDR1   (23)
#define ADDR2   (24)
#define ADDR3   (25)
#define ADDR4   (26)
#define ADDR5   (27)
#define ADDR6   (28)
#define ADDR7   (29)
#define ADDR8   (30)
#define ADDR9   (31)
#define ADDR10  (32)
#define ADDR11  (33)
#define ADDR12  (34)
#define ADDR13  (35)
#define ADDR14  (36)
#define ADDR15  (37)

#define D0      (38)
#define D1      (39)
#define D2      (40)
#define D3      (41)
#define D4      (42)
#define D5      (43)
#define D6      (44)
#define D7      (45)

#define WE      (7)
#define CE      (6)
#define OE      (5)

byte buffer[] = { 0xC3, 0x00, 0xF8 };

void enableWE() { digitalWrite(WE, LOW); }
void disableWE(){ digitalWrite(WE, HIGH);}

void enableCE() { digitalWrite(CE, LOW); }
void disableCE(){ digitalWrite(CE, HIGH);}

void enableOE() { digitalWrite(OE, LOW); }
void disableOE(){ digitalWrite(OE, HIGH);}

void setDataInMode()
{
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
}

void setDataOutMode()
{
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void  setup ( )
{
  Serial.begin(9600);     // Status message will be sent to PC at 9600 baud
  pinMode(WE,  OUTPUT);
  pinMode(CE,  OUTPUT);
  pinMode(OE,  OUTPUT);
  disableWE();
  disableOE();
  disableCE();
  pinMode(ADDR0,  OUTPUT);
  pinMode(ADDR1,  OUTPUT);
  pinMode(ADDR2,  OUTPUT);
  pinMode(ADDR3,  OUTPUT);
  pinMode(ADDR4,  OUTPUT);
  pinMode(ADDR5,  OUTPUT);
  pinMode(ADDR6,  OUTPUT);
  pinMode(ADDR7,  OUTPUT);
  pinMode(ADDR8,  OUTPUT);
  pinMode(ADDR9,  OUTPUT);
  pinMode(ADDR10, OUTPUT);
  pinMode(ADDR11, OUTPUT);
  pinMode(ADDR12, OUTPUT);
  pinMode(ADDR13, OUTPUT);
  pinMode(ADDR14, OUTPUT);
  setDataInMode();
  displayHelp();
}

void displayHelp()
{
  Serial.println();
  Serial.println("Enter commnad:");
  Serial.println("0 - Read  2048 KB");
  Serial.println("1 - Read 32768 KB");
  Serial.println("2 - Write");
  Serial.println();
}

void setAddres(uint16_t addr)
{
  digitalWrite(ADDR14, bitRead(addr, 14));
  digitalWrite(ADDR13, bitRead(addr, 13));
  digitalWrite(ADDR12, bitRead(addr, 12));
  digitalWrite(ADDR11, bitRead(addr, 11));
  digitalWrite(ADDR10, bitRead(addr, 10));
  digitalWrite(ADDR9,  bitRead(addr, 9));
  digitalWrite(ADDR8,  bitRead(addr, 8));
  digitalWrite(ADDR7,  bitRead(addr, 7));
  digitalWrite(ADDR6,  bitRead(addr, 6));
  digitalWrite(ADDR5,  bitRead(addr, 5));
  digitalWrite(ADDR4,  bitRead(addr, 4));
  digitalWrite(ADDR3,  bitRead(addr, 3));
  digitalWrite(ADDR2,  bitRead(addr, 2));
  digitalWrite(ADDR1,  bitRead(addr, 1));
  digitalWrite(ADDR0,  bitRead(addr, 0));
}

void readMemory(uint16_t size)
{
  setDataInMode();
  
  char text[32];
  Serial.println(size);
  enableCE();
  enableOE();
  size /= 16;
  uint16_t addr = 0;
  // Максимум читаем 32кБ (32768), 2048 x 16 = 32768
  for (uint16_t n = 0; n < size; n++)
  {
    sprintf(text, "%04X ", addr);
    Serial.print(text);
    for (int i = 0; i < 16; i++)
    {
      setAddres(addr);
      delayMicroseconds(1);
      byte data = 0;
      if (digitalRead(D0) == HIGH) bitSet(data, 0);
      if (digitalRead(D1) == HIGH) bitSet(data, 1);
      if (digitalRead(D2) == HIGH) bitSet(data, 2);
      if (digitalRead(D3) == HIGH) bitSet(data, 3);
      if (digitalRead(D4) == HIGH) bitSet(data, 4);
      if (digitalRead(D5) == HIGH) bitSet(data, 5);
      if (digitalRead(D6) == HIGH) bitSet(data, 6);
      if (digitalRead(D7) == HIGH) bitSet(data, 7);
      sprintf(text, " %02X", data);
      Serial.print(text);
      addr++;
    }
    Serial.println();
  }

  disableOE();
  disableCE();
}

void writeMemory()
{
  setDataOutMode();

  uint16_t size = sizeof(buffer);
  Serial.println(size);
  enableCE();
  disableOE();
  uint16_t addr = 0;
  for (int i = 0; i < size; i++)
  {
    setAddres(addr);
    delayMicroseconds(1);
    byte data = buffer[i];
    digitalWrite(D0, bitRead(data, 0));
    digitalWrite(D1, bitRead(data, 1));
    digitalWrite(D2, bitRead(data, 2));
    digitalWrite(D3, bitRead(data, 3));
    digitalWrite(D4, bitRead(data, 4));
    digitalWrite(D5, bitRead(data, 5));
    digitalWrite(D6, bitRead(data, 6));
    digitalWrite(D7, bitRead(data, 7));
    delayMicroseconds(1);
    enableWE();
    delayMicroseconds(1);
    disableWE();
    delayMicroseconds(1);
    addr++;
  }
  disableOE();
  disableCE();
}



void  loop ( )
{
  int cmd = Serial.read();
  switch (cmd)
  {
    case '0':
      readMemory(2048);
      displayHelp();
      break;
    case '1':
      readMemory(32768);
      displayHelp();
      break;
    case '2':
      writeMemory();
      displayHelp();
      break;
  }
}
