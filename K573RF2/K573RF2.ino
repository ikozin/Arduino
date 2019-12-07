/*
К573РФ2
http://www.inp.nsk.su/~kozak/mem/mem18.htm
http://www.eandc.ru/pdf/mikroskhema/k573rf2.pdf
http://vip-cxema.org/index.php/home/mikrokontrollery/357-prostoj-kopirovshchik-rpzu-k573rf2-5

Arduino MEGA
https://www.arduino.cc/en/Main/arduinoBoardMega/

Подключение к Arduino MEGA
https://arduinka.pro/blog/wp-content/uploads/2017/09/mega2560-pinout-1024x724.png

1) Arduino MEGA
2) плата К573РФ2
3) SD CARD
4) Провод 18x2 -> папа, для подключения Arduino MEGA
  11x1 - мама, для подключения линий адреса к плате К573РФ2
   8x1 - мама, для подключения линий данных к плате К573РФ2
   2x1 - мама, для подключения линий управления к плате К573РФ2
   2x1 - мама, для подключения питания к плате К573РФ2
   8x1 - мама, для подключения Arduino MEGA к SD CARD


Распиновка платы SD CARD
    ------------------- -------------------
   |ключ                                   |
   | ^                                     |
    ------------------- -------------------
     |    |    |    |    |    |    X    X
   ----------------------------------------
   |GND MISO  SCK MOSI  CS   +5V  +3V  GND|
   |                                      |
   |    ------------------------------    |
   |   |                              |   |
   |   |                              |   |
   |   |           SD CARD            |   |
   |   |                              |   |
   |   |                              |   |
   ----------------------------------------

Распиновка платы К573РФ2
                     -----
                    | ключ|
                    |   ^ |
                     -----
                     CE OE
                     |  |
 ------         ------------------------
|      | A10 --|                        |
|      | A9  --|                        |
|      | A8  --|                        |
|      | A7  --|                        |        ------
|      | A6  --|                        |-- GND |      |
|      | A5  --|                        |-- VCC |<-ключ|
|      | A4  --|                        |        ------
|      | A3  --|                        |
|      | A2  --|                        |
|      | A1  --|                        |
|ключ->| A0  --|                        |
 ------         ------------------------
                 |  |  |   |   |   |  |
                 D0 D1 D2 D3 D4 D5 D6 D7
                ------------------------
               | ^                      |
               |ключ                    |
                ------------------------               
------------------------------------------------------------------------
Входы                      Выходы     Режим работы
------------------------------------------------------------------------
A0...A10  -CE  -OE  Vpp    D0...D7   
------------------------------------------------------------------------
  L/H      L    L    5v      Out      Считывание
  L/H      H    H   24v      L/H      Запись
   X       L    H    5v       Z       Невыбор
   X       H    X    5v       Z       Хранение(пониженная мощность)
   X       L    H   24v       Z       Запрет записи
  L/H      L    L   24v      Out      Проверка записи
------------------------------------------------------------------------

Распиновка К573РФ2
      -------------
  1 -| A7      +5V |- 24
  2 -| A6       A8 |- 23
  3 -| A5       A9 |- 22
  4 -| A4      Vpp |- 21
  5 -| A3      ~OE |- 20
  6 -| A2      A10 |- 19
  7 -| A1      ~CE |- 18
  8 -| A0       D7 |- 17
  9 -| D0       D6 |- 16
 10 -| D1       D5 |- 15
 11 -| D2       D4 |- 14
 12 -| GND      D3 |- 13
      -------------

Распиновка подключения к ATMEGA2560
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
 |   | VIN                                                                                   7 |   |
  ---|                                                                                       6 |   |
 |   | A0                                                                                    5 |   |
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
     | GND| SCK|MISO| D1 | D3 | D5 | D7 |~CE |    | A9 |    |    |    | A6 | A4 | A2 | A0 | +5V|
     | GND| SS |MOSI| D0 | D2 | D4 | D6 |~OE |    | A8 | A10|    |    | A7 | A5 | A3 | A1 | +5V|
      -----------------------------------------------------------------------------------------
     | GND| 53 | 51 | 49 | 47 | 45 | 43 | 41 | 39 | 37 | 35 | 33 | 31 | 29 | 27 | 25 | 23 | +5V|
                                                                                            ^
                                                                                           ключ


 */

#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#ifndef __AVR_ATmega2560__
#error Select board ATMEG2560
#endif

#define ADDR0   (22)  //PA0
#define ADDR1   (23)  //PA1
#define ADDR2   (24)  //PA2
#define ADDR3   (25)  //PA3
#define ADDR4   (26)  //PA4
#define ADDR5   (27)  //PA5
#define ADDR6   (28)  //PA6
#define ADDR7   (29)  //PA7
#define ADDR8   (37)  //PC0
#define ADDR9   (36)  //PC1
#define ADDR10  (35)  //PC2

#define D0      (49)  //PL0
#define D1      (48)  //PL1
#define D2      (47)  //PL2
#define D3      (46)  //PL3
#define D4      (45)  //PL4
#define D5      (44)  //PL5
#define D6      (43)  //PL6
#define D7      (42)  //PL7

#define CE      (40)  //PG1
#define OE      (41)  //PG0
#define SD_CS   (53)  //

#define CHIP_SIZE   2048
#define BLOCK_SIZE  16
#define TEXT_SIZE   64

uint8_t dataRow[BLOCK_SIZE];
char text[TEXT_SIZE];
char fileName[] = "DUMP.TXT";

void setup() {
  // Адрес, контакты 22-29, 35-37, порты A и C
  DDRA  = B11111111;
  DDRC  = B11111111;
  // Данные, контакты 42-49, порт L
  DDRL  = B00000000;

  // К573РФ2
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  SetDisableMode();
  setDataInMode();

  // Serial
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("Start"));

  // SD
  Wire.begin();
  if (!SD.begin(SD_CS)) {
    Serial.println(F("Initialization failed!"));
    for (;;);
  }
  Serial.println(F("SD card initialized."));
}

void showMenu() {
  Serial.println();
  Serial.println(F("0 - TEST"));
  Serial.println(F("1 - Check               (EEPROM value compare with 0xFF)"));
  Serial.println(F("2 - Dump                (Read EEPROM value into Console)"));
  Serial.println(F("3 - Read    [DUMP.TXT]  (Read EEPROM value into DUMP.TXT)"));
  Serial.println(F("4 - Write   [DUMP.TXT]  (Write from DUMP.TXT into EEPROM)"));
  Serial.println(F("5 - Comapre [DUMP.TXT[  (EEPROM value compare with DUMP.TXT)"));
  Serial.println();
}

char getCommand() {
  while (!Serial.available());
  return Serial.read();
}

void loop() {
  showMenu();
  char cmd = getCommand();
  switch (cmd) {
    case '0': // TEST
      loopTest();
      break;
    case '1': // Check
      checkClear();
      break;
    case '2': // Dump
      dumpMemory(&Serial);
      break;
    case '3': // Read
      readMemory(fileName);
      break;
    case '4': // Write
      writeMemory(fileName);
      break;
    case '5': // Comapre
      checkMemory(fileName);
      break;
  }
}

void readMemory(char *pFileName){
  SD.remove(pFileName);
  File dataFile = SD.open(pFileName, FILE_WRITE);
  if (dataFile) {
    dumpMemory(&dataFile);
    dataFile.close();
  }
  else {
    Serial.print(F("Error create file: "));
    Serial.println(pFileName);
  }
}

void writeMemory(char *pFileName){
  File dataFile = SD.open(pFileName);
  if (dataFile) {
    setDataOutMode();
    bool error = false;
    while (!error) {
      int result = readLine(&dataFile, text, TEXT_SIZE);
      if (result == 0) break;
      int addr, hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7, hex8, hex9, hexA, hexB, hexC, hexD, hexE, hexF;
      result = sscanf(text, "%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
        &addr, &hex0, &hex1, &hex2, &hex3, &hex4, &hex5, &hex6, &hex7, &hex8, &hex9, &hexA, &hexB, &hexC, &hexD, &hexE, &hexF);
      if (result != BLOCK_SIZE + 1) {
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
      for (int i = 0; i < BLOCK_SIZE; i++) {
        writeData(addr, dataRow[i]);
        addr++;
      }
    }
    dataFile.close();
    if (error) {
      Serial.println(F("\nError!"));
    }        
  }
  else {
    Serial.print(F("Error open file: "));
    Serial.println(pFileName);
  }
}

void checkMemory(char* pFileName) {
  File dataFile = SD.open(pFileName);
  if (dataFile) {
    setDataInMode();
    bool error = false;
    while (true) {
      int result = readLine(&dataFile, text, TEXT_SIZE);
      if (result == 0) break;
      uint16_t addr, hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7, hex8, hex9, hexA, hexB, hexC, hexD, hexE, hexF;
      result = sscanf(text, "%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
        &addr, &hex0, &hex1, &hex2, &hex3, &hex4, &hex5, &hex6, &hex7, &hex8, &hex9, &hexA, &hexB, &hexC, &hexD, &hexE, &hexF);
      if (result != BLOCK_SIZE + 1) {
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
      
      for (int i = 0; i < BLOCK_SIZE; i++) {
        byte data = readData(addr);
        if (data != dataRow[i]) {
          error = true;
          char* pdata = bin2hex(text, addr);
          *pdata++ = ' ';
          bin2hex(pdata, data);
          *pdata++ = ' ';
          bin2hex(pdata, dataRow[i]);
          Serial.println(text);
        }
        addr++;
      }
    }
    dataFile.close();
    if (error) {
      Serial.println(F("\nError!"));
    }        
  }
  else {
    Serial.print(F("Error open file: "));
    Serial.println(pFileName);
  }
}

void dumpMemory(Stream* pStream) {
  uint16_t addr = 0;
  setDataInMode();
  uint16_t size = CHIP_SIZE / BLOCK_SIZE;
  // Читаем блоками по 16 байт (BLOCK_SIZE)
  for (uint16_t n = 0; n < size; n++) {
    bin2hex(text, addr);
    pStream->print(text);
    for (int i = 0; i < BLOCK_SIZE; i++) {
      dataRow[i] = readData(addr);
      addr++;
    }
    char* pdata = text;
    for (int i = 0; i < BLOCK_SIZE; i++) {
      *pdata++ = ' ';
      pdata = bin2hex(pdata, dataRow[i]);
    }
    pStream->println(text);
  }
}

void checkClear() {
  setDataInMode();
  bool error = false;
  for (uint16_t addr = 0; addr < CHIP_SIZE; addr++) {
    byte data = readData(addr);
    if (data != 0xFF) {
      error = true;
      char* pdata = bin2hex(text, addr);
      *pdata++ = ' ';
      bin2hex(pdata, data);
      Serial.println(text);
    }
  }
  if (error) Serial.println("\nError!");  
}

byte readData(uint16_t addr) {
  setAddress(addr);
  SetReadMode();
  delayMicroseconds(1);
  byte data = getDataPort();
  SetDisableMode();
  return data;
}

void writeData(uint16_t addr, byte data) {
  setAddress(addr);
  setDataPort(data);
  SetWriteMode();
  delayMicroseconds(100);
  SetDisableMode();
}

void setAddress(uint16_t addr) {
  PORTA = lowByte(addr);
  PORTC = highByte(addr);
}

// Хранение(пониженная мощность) К573РФ2
void SetDisableMode() {
	digitalWrite(OE, LOW);
	digitalWrite(CE, HIGH);
}

// Считывание К573РФ2
void SetReadMode() {
	digitalWrite(OE, LOW);
	digitalWrite(CE, LOW);
}

// Запись К573РФ2
void SetWriteMode() {
	digitalWrite(OE, HIGH);
	digitalWrite(CE, HIGH);
}

void setDataInMode() {
  DDRL = B00000000;
}

void setDataOutMode() {
  DDRL = B11111111;
}

byte getDataPort() {
  return PINL;
}

void setDataPort(byte data) {
  PORTL = data;
}

//////////////////////////////////////////
void loopTest() {
  for (;;) {
    showTestMenu();
    char cmd = getCommand();
    switch (cmd) {
      case '1': // Address
        while (1) loopTestAddress();
      case '2': // Data
        while (1) loopTestData();
      case '3': // Control
        while (1) loopTestControl();
    }
  }
}

void showTestMenu() {
  Serial.println(F("      -------------     "));
  Serial.println(F("  1 -| A7      +5V |- 24"));
  Serial.println(F("  2 -| A6       A8 |- 23"));
  Serial.println(F("  3 -| A5       A9 |- 22"));
  Serial.println(F("  4 -| A4      Vpp |- 21"));
  Serial.println(F("  5 -| A3      ~OE |- 20"));
  Serial.println(F("  6 -| A2      A10 |- 19"));
  Serial.println(F("  7 -| A1      ~CE |- 18"));
  Serial.println(F("  8 -| A0       D7 |- 17"));
  Serial.println(F("  9 -| D0       D6 |- 16"));
  Serial.println(F(" 10 -| D1       D5 |- 15"));
  Serial.println(F(" 11 -| D2       D4 |- 14"));
  Serial.println(F(" 12 -| GND      D3 |- 13"));
  Serial.println(F("      -------------     "));
  Serial.println();
  Serial.println(F("1 - Address TEST"));
  Serial.println(F("2 - Data TEST"));
  Serial.println(F("3 - Control TEST (WARNING +25V)"));
  Serial.println();
}

void loopTestAddress() {
  Serial.println(F("Address TEST"));

  setAddress(0xFFFF); 
  delay(1000);
  setAddress(0x0000); 
  delay(1000);
  setAddress(0x0001); 
  delay(200);
  setAddress(0x0002); 
  delay(200);
  setAddress(0x0004); 
  delay(200);
  setAddress(0x0008); 
  delay(200);
  setAddress(0x0010); 
  delay(200);
  setAddress(0x0020); 
  delay(200);
  setAddress(0x0040); 
  delay(200);
  setAddress(0x0080); 
  delay(200);
  setAddress(0x0100); 
  delay(200);
  setAddress(0x0200); 
  delay(200);
  setAddress(0x0400); 
  delay(200);
  setAddress(0x0800); 
  delay(200);
  setAddress(0x1000); 
  delay(200);
  setAddress(0x2000); 
  delay(200);
  setAddress(0x4000); 
  delay(200);
  setAddress(0x8000); 
  delay(200);
  setAddress(0x0000);
  delay(1000);
}

void loopTestData() {
  setDataOutMode();
  Serial.println(F("Data TEST"));

  setDataPort(0xFF); 
  delay(1000);
  setDataPort(0x00); 
  delay(1000);
  setDataPort(0x01); 
  delay(200);
  setDataPort(0x02); 
  delay(200);
  setDataPort(0x04); 
  delay(200);
  setDataPort(0x08); 
  delay(200);
  setDataPort(0x10); 
  delay(200);
  setDataPort(0x20); 
  delay(200);
  setDataPort(0x40); 
  delay(200);
  setDataPort(0x80); 
  delay(200);
  setDataPort(0x00);
  delay(1000);
}

void loopTestControl() {
  Serial.println(F("Control TEST: CE, OE, VPP"));

  digitalWrite(OE, HIGH);
  digitalWrite(CE, HIGH);
  delay(5000);
  digitalWrite(OE, LOW);
  digitalWrite(CE, HIGH);
  delay(5000);
  digitalWrite(OE, HIGH);
  digitalWrite(CE, LOW);
  delay(5000);
  digitalWrite(OE, LOW);
  digitalWrite(CE, LOW);
  delay(5000);
}

int readLine(File* pFile, char* pText, int maxSize) {
  maxSize--;
  int i = 0;
  while (i < maxSize) {
    char value = pFile->read();
    // Конец файла
    if (value == -1) {
      break;
    }
    //Конец строки = 13, 10
    if (value == 13) {
      pFile->read(); // Вычитываем следом за символом 13 символ 10
      break;
    }
    pText[i++] = value;
  }
  pText[i] = 0;
  return i;
}

char* bin2hex(char* pText, uint8_t value) {
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

char* bin2hex(char* pText, uint16_t value) {
  pText = bin2hex(pText, highByte(value));
  pText = bin2hex(pText, lowByte(value));
  return pText;
}
