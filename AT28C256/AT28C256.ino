/*
Arduino MEGA
https://www.arduino.cc/en/Main/arduinoBoardMega/
https://www.arduino.cc/en/Reference/PortManipulation
Подключение к Arduino MEGA
https://arduinka.pro/blog/wp-content/uploads/2017/09/mega2560-pinout-1024x724.png

AT28C256
https://static.chipdip.ru/lib/160/DOC011160426.pdf

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
 |   | 5V                                                                                    9 |   |
 |   | GND                                                                                   8 |   |
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
     | GND| SCK|MISO| D1 | D3 | D5 | D7 |~OE |    | A9 | A11| A13|    | A6 | A4 | A2 | A0 | +5V|
     | GND| SS |MOSI| D0 | D2 | D4 | D6 |~CE |~WE | A8 | A10| A12| A14| A7 | A5 | A3 | A1 | +5V|
      -----------------------------------------------------------------------------------------
     | GND| 53 | 51 | 49 | 47 | 45 | 43 | 41 | 39 | 37 | 35 | 33 | 31 | 29 | 27 | 25 | 23 | +5V|
                                                                                            ^
                                                                                           ключ
     SS  SCK  MOSI MISO +5V  GND
     |    |    |    |    |    |
    -----------------------------           https://static.chipdip.ru/lib/248/DOC000248438.pdf
   |                             |                   Распиновка AT28C256
   |                             |                      -------------
    -----------------------------                   1 -| A14     +5V |- 28
     |    |    |    |    |    |    |    |           2 -| A12     ~WE |- 27
   ----------------------------------------         3 -| A7      A13 |- 26
   |GND  MISO SCK  MOSI  CS  +5V  3V3  GND|         4 -| A6       A8 |- 25
   |                                      |         5 -| A5       A9 |- 24
   |       ------------------------       |         6 -| A4      A11 |- 23
   |      |                        |      |         7 -| A3      ~OE |- 22
   |      |                        |      |         8 -| A2      A10 |- 21
   |      |        SD CARD         |      |         9 -| A1      ~CE |- 20
   |      |                        |      |        10 -| A0       D7 |- 19
   |      |                        |      |        11 -| D0       D6 |- 18
   ----------------------------------------        12 -| D1       D5 |- 17
                                                   13 -| D2       D4 |- 16
                                                   14 -| GND      D3 |- 15
                                                        -------------
 D0  D1  D2  D3  D4  D5  D6  D7
 11  12  13  15  16  17  18  19

 A0  A1  A2  A3  A4  A5  A6  A7
 10   9   8   7   6   5   4   3

 A8  A9 A10 A11 A12 A13 A14
 25  24  21  23   2  26   1
*/

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif

#include <SPI.h>
#include <SD.h>
/*
#define ADDR0   (22)    //PA0
#define ADDR1   (23)    //PA1
#define ADDR2   (24)    //PA2
#define ADDR3   (25)    //PA3
#define ADDR4   (26)    //PA4
#define ADDR5   (27)    //PA5
#define ADDR6   (28)    //PA6
#define ADDR7   (29)    //PA7
#define ADDR8   (37)    //PC0
#define ADDR9   (36)    //PC1
#define ADDR10  (35)    //PC2
#define ADDR11  (34)    //PC3
#define ADDR12  (33)    //PC4
#define ADDR13  (32)    //PC5
#define ADDR14  (31)    //PC6

#define D0      (49)    //PL0
#define D1      (48)    //PL1
#define D2      (47)    //PL2
#define D3      (46)    //PL3
#define D4      (45)    //PL4
#define D5      (44)    //PL5
#define D6      (43)    //PL6
#define D7      (42)    //PL7
*/

#define CE      (41)    //PG0 - Chip Enable
#define OE      (40)    //PG1 - Output Enable
#define WE      (39)    //PG2 - Write Enable
#define SD_CS   (53)    //

#define CHIP_SIZE       32768
#define CHIP_BLOCK_SIZE 2048
#define BLOCK_SIZE      16
#define TEXT_SIZE       1024

uint8_t dataRow[BLOCK_SIZE];
char text[TEXT_SIZE];

const char fileChip[] = "DUMP.TXT";
char fileBlock[] = "X_DUMP.TXT";

void enableWE() { digitalWrite(WE, LOW); }
void disableWE() { digitalWrite(WE, HIGH); }

void enableCE() { digitalWrite(CE, LOW); }
void disableCE() { digitalWrite(CE, HIGH); }

void enableOE() { digitalWrite(OE, LOW); }
void disableOE() { digitalWrite(OE, HIGH); }

void  setup() {
  pinMode(WE, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  disableWE();
  disableOE();
  disableCE();
  DDRA = B11111111;   // Set output Address lines
  DDRC = B11111111;   // Set output Address lines
  setDataInMode();

  // Initialize Serial
  Serial.begin(57600);
  while (!Serial);
  // Initialize SD
  if (!SD.begin(SD_CS)) {
    Serial.println(F("\r\nОшибка инициализации SD карты!"));
    for (;;);
  }
  Serial.println(F("\r\nSD карта инициализирована."));
  displayHelp();
}

static void displayHelp() {
  Serial.println(F("\r\n\r\n------------------------------------------------------------\r\nПерезагрузите Arduino после вставки SD карты"));
  Serial.println(F("Список команд [AT28C256]:"));
  Serial.println(F("1 - Вывести содержимое EEPROM на экран"));
  Serial.println(F("2 - Записать содержимое EEPROM в файл на SD карте"));
  Serial.println(F("3 - Сравнить содержимое EEPROM с файлом на SD карте"));
  Serial.println(F("4 - Записать содержимое файла SD карты в EEPROM"));
  Serial.println(F("5 - Заполнить содержимое EEPROM байтом 0xFF"));
  Serial.println(F("6 - Проверить содержимое EEPROM на заполненость байтом 0xFF"));
  Serial.println(F("7 - ОТКЛЮЧИТЬ защиту от записи"));
  Serial.println(F("8 - ВКЛЮЧИТЬ защиту от записи"));
  Serial.println(F("9 - СТЕРЕТЬ содержимое EEPROM"));
  Serial.println(F("0 - TEST (запускать без EEPROM)"));
  Serial.print(F("\r\n------------------------------------------------------------\r\nВведите команду:"));
}

static void displayInfo(uint16_t addr, uint16_t size) {
  sprintf(text, "Адрес (HEX): %04X, Размер (HEX): %04X\r\n", addr, size);
  Serial.println(text);
}

static void displayDumpHelp() {
  Serial.println(F("\r\nВывести содержимое EEPROM на экран\r\nСписок команд:"));
  Serial.println(F("* - Вывести\t32 KB"));
  for (int i = 0; i < 16; i++) {
    sprintf(text, "%X - Вывести\t 2 KB [%d%d%d%d]", i, bitRead(i, 3), bitRead(i, 2), bitRead(i, 1), bitRead(i, 0));
    Serial.println(text);
  }
  Serial.print(F("\r\nВведите команду:"));
}

static void displayReadHelp() {
  Serial.println(F("\r\nЗаписать содержимое EEPROM в файл на SD карте\r\nСписок команд:"));
  Serial.println(F("* - Записать\t32 KB (DUMP.TXT)"));
  for (int i = 0; i < 16; i++) {
    sprintf(text, "%X - Записать\t 2 KB [%d%d%d%d] (%X_DUMP.TXT)", i, bitRead(i, 3), bitRead(i, 2), bitRead(i, 1), bitRead(i, 0), i);
    Serial.println(text);
  }
  Serial.print(F("\r\nВведите команду:"));
}

static void displayCheckHelp() {
  Serial.println(F("\r\nСравнить содержимое EEPROM с файлом на SD карте\r\nСписок команд:"));
  Serial.println(F("* - Сравнить\t32 KB (DUMP.TXT)"));
  for (int i = 0; i < 16; i++) {
    sprintf(text, "%X - Сравнить\t 2 KB [%d%d%d%d] (%X_DUMP.TXT)", i, bitRead(i, 3), bitRead(i, 2), bitRead(i, 1), bitRead(i, 0), i);
    Serial.println(text);
  }
  Serial.print(F("\r\nВведите команду:"));
}

static void displayWriteHelp() {
  Serial.println(F("\r\nЗаписать содержимое файла SD карты в EEPROM\r\nСписок команд:"));
  Serial.println(F("* - Записать\t32 KB (DUMP.TXT)"));
  for (int i = 0; i < 16; i++) {
    sprintf(text, "%X - Записать\t 2 KB [%d%d%d%d] (%X_DUMP.TXT)", i, bitRead(i, 3), bitRead(i, 2), bitRead(i, 1), bitRead(i, 0), i);
    Serial.println(text);
  }
  Serial.print(F("\r\nВведите команду:"));
}

static void displayClearHelp() {
  Serial.println(F("\r\nЗаполнить содержимое EEPROM байтом 0xFF\r\nСписок команд:"));
  Serial.println(F("* - Заполнить\t32 KB"));
  for (int i = 0; i < 16; i++) {
    sprintf(text, "%X - Заполнить\t 2 KB [%d%d%d%d]", i, bitRead(i, 3), bitRead(i, 2), bitRead(i, 1), bitRead(i, 0));
    Serial.println(text);
  }
  Serial.print(F("\r\nВведите команду:"));
}

static void displayFillHelp() {
  Serial.println(F("\r\nПроверить содержимое EEPROM на заполненость байтом 0xFF\r\nСписок команд:"));
  Serial.println(F("* - Проверить\t32 KB"));
  for (int i = 0; i < 16; i++) {
    sprintf(text, "%X - Проверить\t 2 KB [%d%d%d%d]", i, bitRead(i, 3), bitRead(i, 2), bitRead(i, 1), bitRead(i, 0));
    Serial.println(text);
  }
  Serial.print(F("\r\nВведите команду:"));
}

static char readChar() {
  for (;;) {
      while (!Serial.available());
      char cmd = Serial.read();
      if (cmd == '\r') continue;
      if (cmd == '\n') continue;
      Serial.println(cmd);
      return cmd;
  }
}

static void loopAction(void (*help)(void), void (*action)(uint16_t, uint16_t, Stream*)) {
  for (;;) {
    help();
    char cmd = readChar();
    cmd = toUpperCase(cmd);
    if (cmd == '*') {
        action(0, CHIP_SIZE, &Serial);
        continue;
    } else if (isAlphaNumeric(cmd)) { // '0'-'9','A'-'F'
      cmd -= cmd >= 'A' ? 'A' - 10 : '0';
      if (cmd >= 0 && cmd <= 15) {
        uint16_t addr = cmd * CHIP_BLOCK_SIZE;
        action(addr, CHIP_BLOCK_SIZE, &Serial);
        continue;
      }
    }
    return;
  }
}

static void loopFileAction(void (*help)(void), void (*action)(uint16_t, uint16_t, char*)) {
  for (;;) {
    help();
    char cmd = readChar();
    cmd = toUpperCase(cmd);
    if (cmd == '*') {
        action(0, CHIP_SIZE, fileChip);
        continue;
    } else if (isAlphaNumeric(cmd)) { // '0'-'9','A'-'F'
      byte block = cmd >= 'A' ? cmd -'A' + 10 : cmd - '0';
      if (block >= 0 && block <= 15) {
        fileBlock[0] = cmd;
        Serial.println(fileBlock);        
        uint16_t addr = block * CHIP_BLOCK_SIZE;
        action(addr, CHIP_BLOCK_SIZE, fileBlock);
        continue;
      }
    }
    return;
  }
}

void  loop() {
  char cmd = readChar();
  switch (cmd) {
    case '1':					// 1 - Dump  [AT28C256]
      loopAction(displayDumpHelp, dumpMemory);
      break;
    case '2':					// 2 - Read  [AT28C256]
      loopFileAction(displayReadHelp, readMemory);
      break;
    case '3':					// 3 - Check [AT28C256]
      loopFileAction(displayCheckHelp, checkMemory);
      break;
    case '4':					// 4 - Write [AT28C256]
      loopFileAction(displayWriteHelp, writeMemory);
      break;
    case '5':					// 5 - Clear [AT28C256]
      loopAction(displayClearHelp, clearMemory);
      break;
    case '6':         // 6 - Fill  [AT28C256]
      loopAction(displayFillHelp, checkFillMemory);
      break;
    case '7':         // 7 - Disable Protect Mode
      disableProtectMode();
      break;
    case '8':         // 8 - Enable Protect Mode
      enableProtectMode();
      break;
    case '9':         // 9 - Erase Chip
      eraseChip();
      break;
    case '0':         // 0 - TEST
      loopTest();
      break;
  }
  displayHelp();
}

inline void setDataInMode() {
	DDRL = B00000000;
}

inline void setDataOutMode() {
	DDRL = B11111111;
}

inline void setDataPort(byte data) {
  PORTL = data;
}

inline byte getDataPort() {
  return PINL;
}

inline void setAddress(uint16_t addr) {
  PORTA = lowByte(addr);
  PORTC = highByte(addr);
}

static byte readData(uint16_t addr) {
  setAddress(addr);
  enableCE();
  enableOE();
  delayMicroseconds(1);
  byte data = getDataPort();
  disableOE();
  disableCE();
  delayMicroseconds(1);
  return data;
}

static void writeData(uint16_t addr, byte data, int delayMs = 1) {
  setAddress(addr);
  setDataPort(data);
  enableCE();
  enableWE();
  delayMicroseconds(delayMs);
  disableCE();
  disableWE();
  delayMicroseconds(delayMs);
}

static void writeDataBlock(uint16_t addr, byte *pdata, byte size) {
  disableOE();
  for (int i = 0; i < size; i++) {
    setAddress(addr);
    setDataPort(*pdata);
    enableCE();
    enableWE();
    addr++;
    pdata++;
    delayMicroseconds(1);
    disableCE();
    disableWE();
    delayMicroseconds(1);
  }
  enableOE();
}

static void dumpMemory(uint16_t address, uint16_t size, Stream* pStream) {
  displayInfo(address, size);

  uint16_t addr = 0;
  setDataInMode();
  size /= BLOCK_SIZE;
  // Читаем блоками по 16 байт (BLOCK_SIZE)
  for (uint16_t n = 0; n < size; n++) {
    sprintf(text, "%04X", addr);
    pStream->print(text);
    pStream->flush();
    noInterrupts();
    for (int i = 0; i < BLOCK_SIZE; i++) {
      dataRow[i] = readData(address);
      address++;
      addr++;
    }
    interrupts();
    for (int i = 0; i < BLOCK_SIZE; i++) {
      sprintf(text, " %02X", dataRow[i]);
      pStream->print(text);
    }
    pStream->println();
    pStream->flush();
  }
}

static void readMemory(uint16_t address, uint16_t size, char* pFileName) {
  displayInfo(address, size);

  SD.remove(pFileName);
  File dataFile = SD.open(pFileName, FILE_WRITE);
  if (dataFile) {
    dumpMemory(address, size, &dataFile);
    dataFile.close();
  }
  else {
    Serial.print(F("\r\nОшибка создания файла: "));
    Serial.println(pFileName);
  }
}

static void checkMemory(uint16_t address, uint16_t size, char* pFileName) {
  displayInfo(address, size);

  File dataFile = SD.open(pFileName);
  if (dataFile) {
    bool error = false;
    while (!error) {
      int result;
      result = readLine(&dataFile, text, TEXT_SIZE);
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
      noInterrupts();
      for (int i = 0; i < BLOCK_SIZE; i++) {
        error = readData(address + addr) != dataRow[i];
        if (error) {
          address = addr;
          break;
        }
        addr++;
      }
      interrupts();
    }
    dataFile.close();
    if (error) {
      sprintf(text, "\r\n--- ОШИБКА ---\r\nАдрес (HEX): %04X", address);
      Serial.println(text);
    } else {
      Serial.println(F("\r\nOK!"));
    }
  }
  else {
    Serial.print(F("\r\nОшибка открытия файла: "));
    Serial.println(pFileName);
  }
}

static void writeMemory(uint16_t address, uint16_t size, char* pFileName) {
  displayInfo(address, size);

  File dataFile = SD.open(pFileName);
  if (dataFile) {
    setDataOutMode();
    disableOE();
    bool error = false;
    while (!error) {
      int result;
      result = readLine(&dataFile, text, TEXT_SIZE);
      if (result == 0) break;
      Serial.println(text);
      Serial.flush();
      int addr, hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7, hex8, hex9, hexA, hexB, hexC, hexD, hexE, hexF;
      result = sscanf(text, "%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
        &addr, &hex0, &hex1, &hex2, &hex3, &hex4, &hex5, &hex6, &hex7, &hex8, &hex9, &hexA, &hexB, &hexC, &hexD, &hexE, &hexF);
      if (result != BLOCK_SIZE + 1) {
        error = true;
        break;
      }
      dataRow[0x00] = hex0 & 0xFF;
      dataRow[0x01] = hex1 & 0xFF;
      dataRow[0x02] = hex2 & 0xFF;
      dataRow[0x03] = hex3 & 0xFF;
      dataRow[0x04] = hex4 & 0xFF;
      dataRow[0x05] = hex5 & 0xFF;
      dataRow[0x06] = hex6 & 0xFF;
      dataRow[0x07] = hex7 & 0xFF;
      dataRow[0x08] = hex8 & 0xFF;
      dataRow[0x09] = hex9 & 0xFF;
      dataRow[0x0A] = hexA & 0xFF;
      dataRow[0x0B] = hexB & 0xFF;
      dataRow[0x0C] = hexC & 0xFF;
      dataRow[0x0D] = hexD & 0xFF;
      dataRow[0x0E] = hexE & 0xFF;
      dataRow[0x0F] = hexF & 0xFF;
      noInterrupts();
      writeDataBlock(address + addr, dataRow, BLOCK_SIZE);
      addr += BLOCK_SIZE;
/*
      for (int i = 0; i < BLOCK_SIZE; i++) {
        writeData(address + addr, dataRow[i]);
        addr++;
      }
*/
      interrupts();
    }
    enableOE();
    setDataInMode();
    dataFile.close();
    if (error) {
      sprintf(text, "\r\n--- ОШИБКА ---\r\nАдрес (HEX): %04X", address);
      Serial.println(text);
    } else {
      Serial.println(F("\r\nOK!"));
    }
  }
  else {
    Serial.print(F("\r\nОшибка открытия файла: "));
    Serial.println(pFileName);
  }
}

static void clearMemory(uint16_t address, uint16_t size) {
  displayInfo(address, size);

  setDataOutMode();
  disableOE();
  
  for (int i = 0; i < BLOCK_SIZE; i++) {
    dataRow[i] = 0xFF;
  }
  size /= BLOCK_SIZE;
  noInterrupts();
  for (uint16_t n = 0; n < size; n++) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      writeData(address, dataRow[i]);
      address++;
    }
  }
  interrupts();
  enableOE();
  setDataInMode();
}

static void checkFillMemory(uint16_t address, uint16_t size) {
  displayInfo(address, size);

  setDataInMode();
  noInterrupts();
  for (int i = 0; i < size; i++) {
    byte data = readData(address++);
    if (data != 0xFF) {
      interrupts();

      sprintf(text, "\r\n--- ОШИБКА ---\r\nАдрес (HEX): %04X", address);
      Serial.println(text);
      Serial.flush();
      
      noInterrupts();
    }
  }
  interrupts();
  Serial.println();
}

static void disableProtectMode() {
  noInterrupts();
  disableOE();
  setDataOutMode();
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x80);
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x20);
  setDataInMode();
  enableOE();
  interrupts();
}

static void eraseChip() {
  noInterrupts();
  disableOE();
  setDataOutMode();
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x80);
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x10, 20);
  setDataInMode();
  enableOE();
  interrupts();
}

static void enableProtectMode() {
  noInterrupts();
  disableOE();
  setDataOutMode();
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0xA0);
  setDataInMode();
  enableOE();
  interrupts();
}


static int readLine(File* pFile, char* pText, int maxSize) {
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

static char* bin2hex(char* pText, uint8_t value) {
  for (int i = 0; i < 2; i++) {
    byte v = (byte)((value & 0xF0) >> 4);
    v = (v > 9) ? v + 55 : v + 48;
    *pText++ = (char)v;
    value <<= 4;
  }
  *pText = '\0';
  return pText;
}

static char* bin2hex(char* pText, uint16_t value) {
  pText = bin2hex(pText, highByte(value));
  pText = bin2hex(pText, lowByte(value));
  return pText;
}

static void loopTest() {
  Serial.println(F("ТЕСТИРОВАНИЕ"));
  Serial.flush();
  
  testAllOn();
  while (1) {
    loopTestCrtl();
    loopTestCrtl();
    loopTestCrtl();
    testAllOn();

    loopTestData();
    loopTestData();
    loopTestData();
    testAllOn();

    loopTestAddress();
    loopTestAddress();
    loopTestAddress();
    testAllOn();
  }
}

static void testAllOn() {
  noInterrupts();

  disableCE();
  disableOE();
  disableWE();
  setDataPort(0xFF); 
  setAddress(0xFFFF); 
  
  interrupts();
}

static void loopTestCrtl() {
  Serial.println(F("Тест сигналов управления: CE, OE, WE"));
  Serial.flush();

  noInterrupts();
  
  disableCE();
  disableOE();
  disableWE();
  delay(1000);
  enableCE();
  delay(1000);
  enableOE();
  delay(1000);
  enableWE();
  delay(1000);

  interrupts();
}

static void loopTestData() {
  Serial.println(F("Тест ШД (Шины Данных)"));
  Serial.flush();
  
  noInterrupts();

  setDataOutMode();

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

  interrupts();
}

static void loopTestAddress() {
  Serial.println(F("Тест ША (Шины Адреса)"));
  Serial.flush();
  
  noInterrupts();

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
  
  interrupts();
}
