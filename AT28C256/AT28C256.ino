/*
AT28C256
https://docs-europe.electrocomponents.com/webdocs/1596/0900766b815963c9.pdf

------------------------------------------------------------------------
Входы                      Выходы     Режим работы
------------------------------------------------------------------------
A0...A14  -CE  -OE  -WE    D0...D7   
------------------------------------------------------------------------
  L/H      L    L    H       Out      Считывание
  L/H      H    H    L       L/H      Запись
------------------------------------------------------------------------
                                  Подключение к Arduino MEGA
         -------                                                          -------
        } POWER |                                                        |  USB  |
      -------------------------------------------------------------------------------
     |                                                                               |---
     |                                                                          AREF |   |
     |                                                                           GND |   |
     |                                                                            13 |   |
  ---|                                                                            12 |   |
 |   | RST                                                                        11 |   |
 |   | 3V                                                                         10 |   |
 | X | 5V                                                                          9 |   |
 | X | GND                                                                         8 |   |
 |   |                                                                               |---
 |   | VIN                                                                         7 | X | - !WE
  ---|                                                                             6 | X | - !CE
 |   | A0                                                                          5 | X | - !OE
 |   | A1                                                                          4 |   |
 |   | A2                                                                          3 |   |
 |   | A3                                                                          2 |   |
 |   | A4                                                                          1 |   |
 |   | A5                                                                          0 |   |
 |   | A6                                                                            |---
 |   | A7                                                                         14 | X | - D0
  ---|                                                                            15 | X | - D1
 |   | A8                                                                         16 | X | - D2
 |   | A9                                                                         17 | X | - D3
 |   | A10                                                                        18 | X | - D4
 |   | A11                                                                        19 | X | - D5
 |   | A12                                                                        20 | X | - D6
 |   | A13                                                                        21 | X | - D7
 |   | A14                                                                           |---
 |   | A15                                                                           |
  ---|
     | 52 | 50 | 48 | 46 | 44 | 42 | 40 | 38 | 36 | 34 | 32 | 30 | 28 | 26 | 24 | 22 |
      -------------------------------------------------------------------------------
     |    |    |    |    |    |    |    |    | XX | XX | XX | XX | XX | XX | XX | XX | 
     |    |    |    |    |    |    |    |    |    | XX | XX | XX | XX | XX | XX | XX |
      -------------------------------------------------------------------------------
     | 53 | 51 | 49 | 47 | 45 | 43 | 41 | 39 | 37 | 35 | 33 | 31 | 29 | 27 | 25 | 23 |

*/

#if !defined(__AVR_ATmega2560__)
#error "Select board ATMEG2560"
#endif

//#define PORT_ADDRES

#if !defined(PORT_ADDRES)
#define ADDR0   (22)  // PA 0 ** 22 ** D22
#define ADDR1   (23)  // PA 1 ** 23 ** D23
#define ADDR2   (24)  // PA 2 ** 24 ** D24
#define ADDR3   (25)  // PA 3 ** 25 ** D25
#define ADDR4   (26)  // PA 4 ** 26 ** D26
#define ADDR5   (27)  // PA 5 ** 27 ** D27
#define ADDR6   (28)  // PA 6 ** 28 ** D28
#define ADDR7   (29)  // PA 7 ** 29 ** D29
#define ADDR8   (30)  // PC 7 ** 30 ** D30
#define ADDR9   (31)  // PC 6 ** 31 ** D31
#define ADDR10  (32)  // PC 5 ** 32 ** D32
#define ADDR11  (33)  // PC 4 ** 33 ** D33
#define ADDR12  (34)  // PC 3 ** 34 ** D34
#define ADDR13  (35)  // PC 2 ** 35 ** D35
#define ADDR14  (36)  // PC 1 ** 36 ** D36
#endif

#define D0  14
#define D1  15
#define D2  16
#define D3  17
#define D4  18
#define D5  19
#define D6  20
#define D7  21

#define WE   7
#define CE   6
#define OE   5

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

#if defined(PORT_ADDRES)
  DDRA = B11111111;
  DDRC = B11111111;
#else
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
#endif
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
#if defined(PORT_ADDRES)
      PORTA = lowByte(addr);
      PORTC = highByte(addr);      
#else
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
#endif
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
#if defined(PORT_ADDRES)
    PORTA = lowByte(addr);
    PORTC = highByte(addr);      
#else
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
#endif
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
