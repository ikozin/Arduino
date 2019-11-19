/*
Программатор для EEPROM - AT28C256

Arduino MEGA
https://www.arduino.cc/en/Main/arduinoBoardMega/
Подключение к Arduino MEGA
https://arduinka.pro/blog/wp-content/uploads/2017/09/mega2560-pinout-1024x724.png
Комплектация:

1) Arduino MEGA
2) Макетная плата
3) Micro SD

4) Провод 4x2->8x1, контакт папа -> папа, для подключения Arduino MEGA к Макетной плате линни адреса A0-A7
5) Провод 4x2->2x1 + 1x1 + 1x1 + 1x1 + 1x1 + 1x1 + 1x1, контакт папа ->папа + папа(6 шт), для подключения Arduino MEGA к Макетной плате линни адреса A8-A9, A10, A11, A12, A13, A14, A15
6) Провод 4x2->2x1 + 3x1 + 5x1, контакт папа -> папа + папа, для подключения Arduino MEGA к Макетной плате линни данных D0-D2, D3-D7
7) Провод 2x2->4x1, контакт папа -> мама, для подключения Arduino MEGA к Micro SD

8) Провод 2x1->2x1, контакт папа -> папа, для подключения питания Arduino MEGA к Макетной плате
9) Провод 2x1->2x1, контакт мама -> папа, для подключения питания Micro SD к Макетной плате


Распиновка подключения к ATMEG2560
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
  ---|      SCK MISO                                                                           |
     | GND| 52 | 50 | 48 | 46 | 44 | 42 | 40 | 38 | 36 | 34 | 32 | 30 | 28 | 26 | 24 | 22 | +5V|
      -----------------------------------------------------------------------------------------
     |    |    |    |    |    | D6 | D4 | D2 | D0 | A14| A12| A10| A8 | A6 | A4 | A2 | A0 |    |
     |    |    |    |    |    | D7 | D5 | D3 | D1 | A15| A13| A11| A9 | A7 | A5 | A3 | A1 |    |
      -----------------------------------------------------------------------------------------
     | GND| 53 | 51 | 49 | 47 | 45 | 43 | 41 | 39 | 37 | 35 | 33 | 31 | 29 | 27 | 25 | 23 | +5V|
            SS  MOSI
           ---------           ------------------- ------------------- -------------------
          |       ^ |         |                 ^ |                 ^ |                 ^ |
          |     ключ|         |               ключ|               ключ|               ключ|
          |      2x2|         |                4x2|                4x2|                4x2|
          |        4|         |                3+5|      2+1+1+1+1+1+1|                  8|
          |         |         |         ключ D0,D3|    ключ A8,A10-A14|            ключ A0|
           ---------           ------------------- ------------------- -------------------

    ------------------- ---------
   |ключ               |ключ     |
   | ^                 | ^       |
    ------------------- ---------
     |    |    |    |    |    | 
   ------------------------------
   |SC  SCK  MOSI MISO  +5V  GND|
   |                            |
   |    --------------------    |
   |   |                    |   |
   |   |                    |   |
   |   |   MICRO SD CARD    |   |
   |   |                    |   |
   |   |                    |   |
   ------------------------------

https://static.chipdip.ru/lib/248/DOC000248438.pdf
Распиновка AT28C256
 ____      -------------        ____
|____|  1 -| A14     +5V |- 28 |____|
|____|  2 -| A12     ~WE |- 27 |____|
|    |  3 -| A7      A13 |- 26 |____|
|    |  4 -| A6       A8 |- 25 |  <-|
|    |  5 -| A5       A9 |- 24 |____|
|    |  6 -| A4      A11 |- 23 |____|
|    |  7 -| A3      ~OE |- 22 |____|
|    |  8 -| A2      A10 |- 21 |____|
|    |  9 -| A1      ~CE |- 20 |____|
|->__| 10 -| A0       D7 |- 19 |    |
|->  | 11 -| D0       D6 |- 18 |    |
|    | 12 -| D1       D5 |- 17 |    |
|____| 13 -| D2       D4 |- 16 |    |
|____| 14 -| GND      D3 |- 15 |__<-|
           -------------
    
*/

#ifndef __AVR_ATmega2560__
#error "Select board ATMEG2560"
#endif

#include <SPI.h>
#include <SD.h>

#define ADDR0       (22)
#define ADDR1       (23)
#define ADDR2       (24)
#define ADDR3       (25)
#define ADDR4       (26)
#define ADDR5       (27)
#define ADDR6       (28)
#define ADDR7       (29)
#define ADDR8       (30)
#define ADDR9       (31)
#define ADDR10      (32)
#define ADDR11      (33)
#define ADDR12      (34)
#define ADDR13      (35)
#define ADDR14      (36)
#define ADDR15      (37)

#define D0          (38)
#define D1          (39)
#define D2          (40)
#define D3          (41)
#define D4          (42)
#define D5          (43)
#define D6          (44)
#define D7          (45)

#define SD_CS       (53)

#define WE          (7) // Write Enable
#define CE          (6) // Chip Enable
#define OE          (5) // Output Enable

#define CHIP_SIZE       32768
#define CHIP_MIN_SIZE   2048
#define BLOCK_SIZE      16
#define TEXT_SIZE       64

uint8_t dataRow[BLOCK_SIZE];
char text[TEXT_SIZE];

char fileName[] = "X_DUMP.TXT";

void enableWE() { digitalWrite(WE, LOW); }
void disableWE() { digitalWrite(WE, HIGH); }

void enableCE() { digitalWrite(CE, LOW); }
void disableCE() { digitalWrite(CE, HIGH); }

void enableOE() { digitalWrite(OE, LOW); }
void disableOE() { digitalWrite(OE, HIGH); }

void  setup()
{
    pinMode(WE, OUTPUT);
    pinMode(CE, OUTPUT);
    pinMode(OE, OUTPUT);
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
    pinMode(ADDR15, OUTPUT);
    setDataInMode();

    // Initialize Serial
    Serial.begin(9600);
    while (!Serial) {}
    // Initialize SD
    if (!SD.begin(SD_CS))
    {
        Serial.println(F("Initialization failed!"));
        for (;;);
    }
    Serial.println(F("SD card initialized."));
    displayHelp();
}

void displayHelp()
{
    Serial.println();
    Serial.println(F("Reset Arduino after insert SD card"));
    Serial.println(F("List commnad:"));
    Serial.println(F("1 - Dump  32 KB [AT28C256]"));
    Serial.println(F("2 - Read  32 KB [AT28C256] (DUMP.TXT)"));
    Serial.println(F("3 - Check 32 KB [AT28C256] (DUMP.TXT)"));
    Serial.println(F("4 - Write 32 KB [AT28C256] (DUMP.TXT)"));
    Serial.println(F("5 - Clear 32 KB [AT28C256]"));
    Serial.println();
    Serial.print(F("Enter commnad:"));
}

void displayInfo(uint16_t addr, uint16_t size)
{
    Serial.print(F("Address: "));
    bin2hex(text, addr);
    Serial.print(text);
    Serial.print(F(" Size: "));
    bin2hex(text, size);
    Serial.println(text);
}

void displayDumpHelp()
{
    Serial.println();
    Serial.println(F("Dump commnad:"));
    Serial.println(F("* - Dump 32 KB"));
    Serial.println(F("0 - Dump  2 KB [0000]"));
    Serial.println(F("1 - Dump  2 KB [0001]"));
    Serial.println(F("2 - Dump  2 KB [0010]"));
    Serial.println(F("3 - Dump  2 KB [0011]"));
    Serial.println(F("4 - Dump  2 KB [0100]"));
    Serial.println(F("5 - Dump  2 KB [0101]"));
    Serial.println(F("6 - Dump  2 KB [0110]"));
    Serial.println(F("7 - Dump  2 KB [0111]"));
    Serial.println(F("8 - Dump  2 KB [1000]"));
    Serial.println(F("9 - Dump  2 KB [1001]"));
    Serial.println(F("A - Dump  2 KB [1010]"));
    Serial.println(F("B - Dump  2 KB [1011]"));
    Serial.println(F("C - Dump  2 KB [1100]"));
    Serial.println(F("D - Dump  2 KB [1101]"));
    Serial.println(F("E - Dump  2 KB [1110]"));
    Serial.println(F("F - Dump  2 KB [1111]"));
    Serial.println();
    Serial.print(F("Enter dump commnad:"));
}

void loopDump()
{
    displayDumpHelp();
    uint16_t addr;
    for (;;)
    {
        char cmd = toUpperCase(Serial.read());
        switch(cmd)
        {
          case -1:
              break;
          case '*':
              Serial.println(cmd);
              addr = 0;
              displayInfo(addr, CHIP_SIZE);
              dumpMemory(addr, CHIP_SIZE, &Serial);
              return;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
              Serial.println(cmd);
              addr = (cmd - '0') * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              dumpMemory(addr, CHIP_MIN_SIZE, &Serial);
              return;
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          case 'E':
          case 'F':
              Serial.println(cmd);
              addr = (cmd - 'A' + 10 ) * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              dumpMemory(addr, CHIP_MIN_SIZE, &Serial);
              return;
          default:
              Serial.println(cmd);
              displayDumpHelp();
              break;
        }
    }
}

void displayReadHelp()
{
    Serial.println();
    Serial.println(F("Read commnad:"));
    Serial.println(F("* - Read 32 KB"));
    Serial.println(F("0 - Read  2 KB [0000]"));
    Serial.println(F("1 - Read  2 KB [0001]"));
    Serial.println(F("2 - Read  2 KB [0010]"));
    Serial.println(F("3 - Read  2 KB [0011]"));
    Serial.println(F("4 - Read  2 KB [0100]"));
    Serial.println(F("5 - Read  2 KB [0101]"));
    Serial.println(F("6 - Read  2 KB [0110]"));
    Serial.println(F("7 - Read  2 KB [0111]"));
    Serial.println(F("8 - Read  2 KB [1000]"));
    Serial.println(F("9 - Read  2 KB [1001]"));
    Serial.println(F("A - Read  2 KB [1010]"));
    Serial.println(F("B - Read  2 KB [1011]"));
    Serial.println(F("C - Read  2 KB [1100]"));
    Serial.println(F("D - Read  2 KB [1101]"));
    Serial.println(F("E - Read  2 KB [1110]"));
    Serial.println(F("F - Read  2 KB [1111]"));
    Serial.println();
    Serial.print(F("Enter read commnad:"));
}

void loopRead()
{
    displayReadHelp();
    uint16_t addr;
    for (;;)
    {
        char cmd = toUpperCase(Serial.read());
        switch(cmd)
        {
          case -1:
              break;
          case '*':
              Serial.println(cmd);
              addr = 0;
              displayInfo(addr, CHIP_SIZE);
              readMemory(addr, CHIP_SIZE, "DUMP.TXT");
              return;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
              Serial.println(cmd);
              fileName[0] = cmd;
              addr = (cmd - '0') * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              readMemory(addr, CHIP_MIN_SIZE, fileName);
              return;
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          case 'E':
          case 'F':
              Serial.println(cmd);
              fileName[0] = cmd;
              addr = (cmd - 'A' + 10) * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              readMemory(addr, CHIP_MIN_SIZE, fileName);
              return;
          default:
              Serial.println(cmd);
              displayReadHelp();
              break;
        }
    }
}

void displayCheckHelp()
{
    Serial.println();
    Serial.println(F("Check commnad:"));
    Serial.println(F("* - Check 32 KB"));
    Serial.println(F("0 - Check  2 KB [0000]"));
    Serial.println(F("1 - Check  2 KB [0001]"));
    Serial.println(F("2 - Check  2 KB [0010]"));
    Serial.println(F("3 - Check  2 KB [0011]"));
    Serial.println(F("4 - Check  2 KB [0100]"));
    Serial.println(F("5 - Check  2 KB [0101]"));
    Serial.println(F("6 - Check  2 KB [0110]"));
    Serial.println(F("7 - Check  2 KB [0111]"));
    Serial.println(F("8 - Check  2 KB [1000]"));
    Serial.println(F("9 - Check  2 KB [1001]"));
    Serial.println(F("A - Check  2 KB [1010]"));
    Serial.println(F("B - Check  2 KB [1011]"));
    Serial.println(F("C - Check  2 KB [1100]"));
    Serial.println(F("D - Check  2 KB [1101]"));
    Serial.println(F("E - Check  2 KB [1110]"));
    Serial.println(F("F - Check  2 KB [1111]"));
    Serial.println();
    Serial.print(F("Enter Check commnad:"));
}

void loopCheck()
{
    displayCheckHelp();
    uint16_t addr;
    for (;;)
    {
        char cmd = toUpperCase(Serial.read());
        switch(cmd)
        {
          case -1:
              break;
          case '*':
              Serial.println(cmd);
              addr = 0;
              displayInfo(addr, CHIP_SIZE);
              checkMemory(addr, CHIP_SIZE, "DUMP.TXT");
              return;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
              Serial.println(cmd);
              fileName[0] = cmd;
              addr = (cmd - '0') * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              checkMemory(addr, CHIP_MIN_SIZE, fileName);
              return;
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          case 'E':
          case 'F':
              Serial.println(cmd);
              fileName[0] = cmd;
              addr = (cmd - 'A' + 10) * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              checkMemory(addr, CHIP_MIN_SIZE, fileName);
              return;
          default:
              Serial.println(cmd);
              displayCheckHelp();
              break;
        }
    }
}

void displayWriteHelp()
{
    Serial.println();
    Serial.println(F("Write commnad:"));
    Serial.println(F("* - Write 32 KB"));
    Serial.println(F("0 - Write  2 KB [0000]"));
    Serial.println(F("1 - Write  2 KB [0001]"));
    Serial.println(F("2 - Write  2 KB [0010]"));
    Serial.println(F("3 - Write  2 KB [0011]"));
    Serial.println(F("4 - Write  2 KB [0100]"));
    Serial.println(F("5 - Write  2 KB [0101]"));
    Serial.println(F("6 - Write  2 KB [0110]"));
    Serial.println(F("7 - Write  2 KB [0111]"));
    Serial.println(F("8 - Write  2 KB [1000]"));
    Serial.println(F("9 - Write  2 KB [1001]"));
    Serial.println(F("A - Write  2 KB [1010]"));
    Serial.println(F("B - Write  2 KB [1011]"));
    Serial.println(F("C - Write  2 KB [1100]"));
    Serial.println(F("D - Write  2 KB [1101]"));
    Serial.println(F("E - Write  2 KB [1110]"));
    Serial.println(F("F - Write  2 KB [1111]"));
    Serial.println();
    Serial.print(F("Enter write commnad:"));
}

void loopWrite()
{
    displayWriteHelp();
    uint16_t addr;
    for (;;)
    {
        char cmd = toUpperCase(Serial.read());
        switch(cmd)
        {
          case -1:
              break;
          case '*':
              Serial.println(cmd);
              addr = 0;
              displayInfo(addr, CHIP_SIZE);
              writeMemory(addr, CHIP_SIZE, "DUMP.TXT");
              return;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
              Serial.println(cmd);
              fileName[0] = cmd;
              addr = (cmd - '0') * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              writeMemory(addr, CHIP_MIN_SIZE, fileName);
              return;
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          case 'E':
          case 'F':
              Serial.println(cmd);
              fileName[0] = cmd;
              addr = (cmd - 'A' + 10) * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              writeMemory(addr, CHIP_MIN_SIZE, fileName);
              return;
          default:
              Serial.println(cmd);
              displayWriteHelp();
              break;
        }
    }
}

void displayClearHelp()
{
    Serial.println();
    Serial.println(F("Clear commnad:"));
    Serial.println(F("* - Clear 32 KB"));
    Serial.println(F("0 - Clear  2 KB [0000]"));
    Serial.println(F("1 - Clear  2 KB [0001]"));
    Serial.println(F("2 - Clear  2 KB [0010]"));
    Serial.println(F("3 - Clear  2 KB [0011]"));
    Serial.println(F("4 - Clear  2 KB [0100]"));
    Serial.println(F("5 - Clear  2 KB [0101]"));
    Serial.println(F("6 - Clear  2 KB [0110]"));
    Serial.println(F("7 - Clear  2 KB [0111]"));
    Serial.println(F("8 - Clear  2 KB [1000]"));
    Serial.println(F("9 - Clear  2 KB [1001]"));
    Serial.println(F("A - Clear  2 KB [1010]"));
    Serial.println(F("B - Clear  2 KB [1011]"));
    Serial.println(F("C - Clear  2 KB [1100]"));
    Serial.println(F("D - Clear  2 KB [1101]"));
    Serial.println(F("E - Clear  2 KB [1110]"));
    Serial.println(F("F - Clear  2 KB [1111]"));
    Serial.println();
    Serial.print(F("Enter clear commnad:"));
}


void loopClear()
{
    displayClearHelp();
    uint16_t addr;
    for (;;)
    {
        char cmd = toUpperCase(Serial.read());
        switch(cmd)
        {
          case -1:
              break;
          case '*':
              Serial.println(cmd);
              addr = 0;
              displayInfo(addr, CHIP_SIZE);
              clearMemory(addr, CHIP_SIZE);
              return;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
              Serial.println(cmd);
              addr = (cmd - '0') * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              clearMemory(addr, CHIP_MIN_SIZE);
              return;
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          case 'E':
          case 'F':
              Serial.println(cmd);
              addr = (cmd - 'A' + 10) * CHIP_MIN_SIZE;
              displayInfo(addr, CHIP_MIN_SIZE);
              clearMemory(addr, CHIP_MIN_SIZE);
              return;
          default:
              Serial.println(cmd);
              displayClearHelp();
              break;
        }
    }
}

void  loop()
{
    char cmd = Serial.read();
    switch (cmd)
    {
      case '1':					// 1 - Dump  [AT28C256]
          Serial.println(cmd);
          loopDump();
          displayHelp();
          break;
      case '2':					// 2 - Read  [AT28C256]
          Serial.println(cmd);
          loopRead();
          displayHelp();
          break;
      case '3':					// 3 - Check [AT28C256]
          Serial.println(cmd);
          loopCheck();
          displayHelp();
          break;
      case '4':					// 4 - Write [AT28C256]
          Serial.println(cmd);
          loopWrite();
          displayHelp();
          break;
      case '5':					// 5 - Clear [AT28C256]
          Serial.println(cmd);
          loopClear();
          displayHelp();
          break;
    }
}

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

void setAddres(uint16_t addr)
{
    digitalWrite(ADDR15, bitRead(addr, 15));
    digitalWrite(ADDR14, bitRead(addr, 14));
    digitalWrite(ADDR13, bitRead(addr, 13));
    digitalWrite(ADDR12, bitRead(addr, 12));
    digitalWrite(ADDR11, bitRead(addr, 11));
    digitalWrite(ADDR10, bitRead(addr, 10));
    digitalWrite(ADDR9,  bitRead(addr,  9));
    digitalWrite(ADDR8,  bitRead(addr,  8));
    digitalWrite(ADDR7,  bitRead(addr,  7));
    digitalWrite(ADDR6,  bitRead(addr,  6));
    digitalWrite(ADDR5,  bitRead(addr,  5));
    digitalWrite(ADDR4,  bitRead(addr,  4));
    digitalWrite(ADDR3,  bitRead(addr,  3));
    digitalWrite(ADDR2,  bitRead(addr,  2));
    digitalWrite(ADDR1,  bitRead(addr,  1));
    digitalWrite(ADDR0,  bitRead(addr,  0));
}

byte readData(uint16_t addr)
{
    setAddres(addr);
    enableCE();
    enableOE();
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
    disableOE();
    disableCE();
    return data;
}

void writeData(uint16_t addr, byte data)
{
    setAddres(addr);
    digitalWrite(D0, bitRead(data, 0));
    digitalWrite(D1, bitRead(data, 1));
    digitalWrite(D2, bitRead(data, 2));
    digitalWrite(D3, bitRead(data, 3));
    digitalWrite(D4, bitRead(data, 4));
    digitalWrite(D5, bitRead(data, 5));
    digitalWrite(D6, bitRead(data, 6));
    digitalWrite(D7, bitRead(data, 7));
    enableCE();
    enableWE();
    delayMicroseconds(1);
    disableWE();
    disableCE();
}

void dumpMemory(uint16_t addr, uint16_t size, Stream* pStream)
{
    setDataInMode();
    size /= BLOCK_SIZE;
    // Читаем блоками по 16 байт (BLOCK_SIZE)
    for (uint16_t n = 0; n < size; n++)
    {
        bin2hex(text, addr);
        pStream->print(text);
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            dataRow[i] = readData(addr);
            addr++;
        }
        char* pdata = text;
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            *pdata++ = ' ';
            pdata = bin2hex(pdata, dataRow[i]);
        }
        pStream->println(text);
    }
}

void readMemory(uint16_t addr, uint16_t size, char* pFileName)
{
    SD.remove(pFileName);
    File dataFile = SD.open(pFileName, FILE_WRITE);
    if (dataFile)
    {
        dumpMemory(addr, size, &dataFile);
        dataFile.close();
    }
    else
    {
        Serial.print(F("Error create file: "));
        Serial.println(pFileName);
    }
}

void checkMemory(uint16_t addr, uint16_t size, char* pFileName)
{
    File dataFile = SD.open(pFileName);
    if (dataFile)
    {
        bool error = false;
        while (!error)
        {
            int result;
            result = readLine(&dataFile, text, TEXT_SIZE);
            if (result == 0) break;
            int address, hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7, hex8, hex9, hexA, hexB, hexC, hexD, hexE, hexF;
            result = sscanf(text, "%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
              &address, &hex0, &hex1, &hex2, &hex3, &hex4, &hex5, &hex6, &hex7, &hex8, &hex9, &hexA, &hexB, &hexC, &hexD, &hexE, &hexF);
            if (result != BLOCK_SIZE + 1)
            {
                error = true;
                break;
            }
            dataRow[0x00] = hex0;// & 0xFF;
            dataRow[0x01] = hex1;// & 0xFF;
            dataRow[0x02] = hex2;// & 0xFF;
            dataRow[0x03] = hex3;// & 0xFF;
            dataRow[0x04] = hex4;// & 0xFF;
            dataRow[0x05] = hex5;// & 0xFF;
            dataRow[0x06] = hex6;// & 0xFF;
            dataRow[0x07] = hex7;// & 0xFF;
            dataRow[0x08] = hex8;// & 0xFF;
            dataRow[0x09] = hex9;// & 0xFF;
            dataRow[0x0A] = hexA;// & 0xFF;
            dataRow[0x0B] = hexB;// & 0xFF;
            dataRow[0x0C] = hexC;// & 0xFF;
            dataRow[0x0D] = hexD;// & 0xFF;
            dataRow[0x0E] = hexE;// & 0xFF;
            dataRow[0x0F] = hexF;// & 0xFF;
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
				error = readData(address) != dataRow[i];
                if (error) break;
                address++;
            }
        }
        dataFile.close();
        if (error)
        {
			
            Serial.println(F("\nError!"));
            Serial.print(F("Address: "));
            bin2hex(text, addr);
            Serial.println(text);
        }
    }
    else
    {
        Serial.print(F("Error open file: "));
        Serial.println(pFileName);
    }
}

void writeMemory(uint16_t addr, uint16_t size, char* pFileName)
{
    File dataFile = SD.open(pFileName);
    if (dataFile)
    {
        setDataOutMode();
        bool error = false;
        while (!error)
        {
            int result;
            result = readLine(&dataFile, text, TEXT_SIZE);
            if (result == 0) break;
            int address, hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7, hex8, hex9, hexA, hexB, hexC, hexD, hexE, hexF;
            result = sscanf(text, "%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
              &address, &hex0, &hex1, &hex2, &hex3, &hex4, &hex5, &hex6, &hex7, &hex8, &hex9, &hexA, &hexB, &hexC, &hexD, &hexE, &hexF);
            if (result != BLOCK_SIZE + 1)
            {
                error = true;
                break;
            }
            dataRow[0x00] = hex0;// & 0xFF;
            dataRow[0x01] = hex1;// & 0xFF;
            dataRow[0x02] = hex2;// & 0xFF;
            dataRow[0x03] = hex3;// & 0xFF;
            dataRow[0x04] = hex4;// & 0xFF;
            dataRow[0x05] = hex5;// & 0xFF;
            dataRow[0x06] = hex6;// & 0xFF;
            dataRow[0x07] = hex7;// & 0xFF;
            dataRow[0x08] = hex8;// & 0xFF;
            dataRow[0x09] = hex9;// & 0xFF;
            dataRow[0x0A] = hexA;// & 0xFF;
            dataRow[0x0B] = hexB;// & 0xFF;
            dataRow[0x0C] = hexC;// & 0xFF;
            dataRow[0x0D] = hexD;// & 0xFF;
            dataRow[0x0E] = hexE;// & 0xFF;
            dataRow[0x0F] = hexF;// & 0xFF;
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                writeData(address, dataRow[i]);
                address++;
            }
        }
        setDataInMode();
        dataFile.close();
        if (error) Serial.println(F("\nError!"));
    }
    else
    {
        Serial.print(F("Error open file: "));
        Serial.println(pFileName);
    }
}

void clearMemory(uint16_t addr, uint16_t size)
{
    setDataOutMode();
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        dataRow[i] = 0xFF;
    }
    size /= BLOCK_SIZE;
    for (uint16_t n = 0; n < size; n++)
    {
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            writeData(addr, dataRow[i]);
            addr++;
        }
    }
    setDataInMode();
}

int readLine(File* pFile, char* pText, int maxSize)
{
    maxSize--;
    int i = 0;
    while (i < maxSize)
    {
        char value = pFile->read();
        if (value == -1)     // Конец файла
        {
            break;
        }
        if (value == 13) //Конец строки = 13, 10
        {
            pFile->read(); // Вычитываем следом за символом 13 символ 10
            break;
        }
        pText[i++] = value;
    }
    pText[i] = 0;
    return i;
}

char* bin2hex(char* pText, uint8_t value)
{
    for (int i = 0; i < 2; i++)
    {
        byte v = (byte)((value & 0xF0) >> 4);
        v = (v > 9) ? v + 55 : v + 48;
        *pText++ = (char)v;
        value <<= 4;
    }
    *pText = '\0';
    return pText;
}

char* bin2hex(char* pText, uint16_t value)
{
    pText = bin2hex(pText, highByte(value));
    pText = bin2hex(pText, lowByte(value));
    return pText;
}
