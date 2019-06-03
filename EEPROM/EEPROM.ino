/*
Программатор для EEPROM - AT28C256, AT28C64

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

#ifndef __AVR_ATmega2560__
#error "Select board ATMEG2560"
#endif

#include <SPI.h>
#include <SD.h>

#define ADDR0      (22)		//PA0
#define ADDR1      (23)		//PA1
#define ADDR2      (24)		//PA2
#define ADDR3      (25)		//PA3
#define ADDR4      (26)		//PA4
#define ADDR5      (27)		//PA5
#define ADDR6      (28)		//PA6
#define ADDR7      (29)		//PA7
#define ADDR8      (37)     //PC0
#define ADDR9      (36)     //PC1
#define ADDR10     (35)     //PC2
#define ADDR11     (34)     //PC3
#define ADDR12     (33)     //PC4
#define ADDR13     (33)     //PC5
#define ADDR14     (31)     //PC6
#define ADDR15     (30)     //PC7

#define D0         (49)     //PL0
#define D1         (48)     //PL1
#define D2         (47)     //PL2
#define D3         (46)     //PL3
#define D4         (45)     //PL4
#define D5         (44)     //PL5
#define D6         (43)     //PL6
#define D7         (42)     //PL7

#define SD_CS      (53)

#define WE          (7)
#define CE          (6)
#define OE          (5)

#define BLOCK_SIZE    16
uint8_t dataRow[BLOCK_SIZE];
#define TEXT_SIZE     64
char text[TEXT_SIZE];

byte buffer[] = { 0xC3, 0x00, 0xF8 };

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
    //debugAddr();
}


void  loop()
{
    int cmd = Serial.read();
    switch (cmd)
    {
    case '1':					// 1 - Dump  32768 KB [AT28C256]
        dumpMemory(32768);
        displayHelp();
        break;

    case '3':					// 3 - Read  32768 KB [AT28C256]
        readMemory(32768);
        displayHelp();
        break;

    //case '5':					// 5 - Check 32768 KB [AT28C256]
    //    checkMemory(32768);
    //    displayHelp();
    //    break;

    case '7':					// 7 - Write 32768 KB [AT28C256]
        writeMemory(32768);
        displayHelp();
        break;
    }
}


void displayHelp()
{
    Serial.println();
    Serial.println(F("Reset Arduino after insert SD card"));
    Serial.println(F("Enter commnad:"));
    Serial.println();
    Serial.println(F("1 - Dump  32768 KB [AT28C256]"));
    Serial.println();
    Serial.println(F("3 - Read  32768 KB [AT28C256] (DUMP.TXT)"));
    Serial.println();
    //Serial.println(F("5 - Check 32768 KB [AT28C256] (DUMP.TXT)"));
    //Serial.println();
    Serial.println(F("7 - Write 32768 KB [AT28C256] (DUMP.TXT)"));
    Serial.println();
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
    delayMicroseconds(2);
    byte data = 0;
    if (digitalRead(D0) == HIGH) bitSet(data, 0);
    if (digitalRead(D1) == HIGH) bitSet(data, 1);
    if (digitalRead(D2) == HIGH) bitSet(data, 2);
    if (digitalRead(D3) == HIGH) bitSet(data, 3);
    if (digitalRead(D4) == HIGH) bitSet(data, 4);
    if (digitalRead(D5) == HIGH) bitSet(data, 5);
    if (digitalRead(D6) == HIGH) bitSet(data, 6);
    if (digitalRead(D7) == HIGH) bitSet(data, 7);
    return data;
}


void dumpMemory(uint16_t size)
{
    setDataInMode();

    Serial.println(size);
    enableCE();
    enableOE();
    size /= BLOCK_SIZE;
    uint16_t addr = 0;
    // Читаем блоками по 16 байт (BLOCK_SIZE)
    for (uint16_t n = 0; n < size; n++)
    {
        sprintf(text, "%04X ", addr);
        Serial.print(text); // Выводим адрес
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            sprintf(text, " %02X", readData(addr));
            Serial.print(text);
            addr++;
        }
        Serial.println();
    }
    disableOE();
    disableCE();
}


void readMemory(uint16_t size)
{
    SD.remove("DUMP.TXT");
    File dataFile = SD.open("DUMP.TXT", FILE_WRITE);
    if (dataFile)
    {
        setDataInMode();
        Serial.println(size);
        enableCE();
        enableOE();
        size /= BLOCK_SIZE;
        uint16_t addr = 0;
        for (uint16_t n = 0; n < size; n++)
        {
            bin2hex(text, addr);
            dataFile.print(text);
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
            dataFile.println(text);
        }
        dataFile.close();
        disableOE();
        disableCE();
    }
    else
    {
        Serial.println(F("Error create file: DUMP.TXT"));
    }
}


void writeMemory(uint16_t size)
{
    File dataFile = SD.open("DUMP.TXT");
    if (dataFile)
    {
        setDataOutMode();
        enableCE();
        disableOE();

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
                uint16_t addr = address + i;
                setAddres(addr);
                delayMicroseconds(1);

                uint8_t data = dataRow[i];
                digitalWrite(D0, bitRead(data, 0));
                digitalWrite(D1, bitRead(data, 1));
                digitalWrite(D2, bitRead(data, 2));
                digitalWrite(D3, bitRead(data, 3));
                digitalWrite(D4, bitRead(data, 4));
                digitalWrite(D5, bitRead(data, 5));
                digitalWrite(D6, bitRead(data, 6));
                digitalWrite(D7, bitRead(data, 7));

                delayMicroseconds(3);
                enableWE();
                delayMicroseconds(2);
                disableWE();
                delayMicroseconds(3);
            }
        }

        dataFile.close();
        disableOE();
        disableCE();
        setDataInMode();
        if (error) Serial.println(F("\nError!"));
    }
    else
    {
        Serial.println(F("Error open file: DUMP.TXT"));
    }
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

void debugAddr()
{
  while(true)
  {
    uint16_t addr = 1;
    for (int i = 0; i < 16; i++)
    {
      setAddres(addr);
      delay(1000);
      addr <<= 1;
    }
  }
}
