/*
К573РФ2
http://www.inp.nsk.su/~kozak/mem/mem18.htm
http://www.eandc.ru/pdf/mikroskhema/k573rf2.pdf
http://vip-cxema.org/index.php/home/mikrokontrollery/357-prostoj-kopirovshchik-rpzu-k573rf2-5

Arduino MEGA
https://www.arduino.cc/en/Main/arduinoBoardMega/

Подключение к Arduino MEGA
https://arduinka.pro/blog/wp-content/uploads/2017/09/mega2560-pinout-1024x724.png

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
     | GND| SCK|MISO| D1 | D3 | D5 | D7 | ~CE|    | A9 |    |    |    | A6 | A4 | A2 | A0 | +5V|
     | GND| SS |MOSI| D0 | D2 | D4 | D6 | ~OE| VPP| A8 | A10|    |    | A7 | A5 | A3 | A1 | +5V|
      -----------------------------------------------------------------------------------------
     | GND| 53 | 51 | 49 | 47 | 45 | 43 | 41 | 39 | 37 | 35 | 33 | 31 | 29 | 27 | 25 | 23 | +5V|

A0-A10 = PA0-PA7, PC0-PC2
D0-D7 = PL0-PL7
~OE~ = PG0
~CE~ = PG1
UPR = PG2
 */

#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#ifndef __AVR_ATmega2560__
#error Select board ATMEG2560
#endif

/*
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
*/
#define VPP     (39)  //PG2
#define CE      (40)  //PG1
#define OE      (41)  //PG0

#define SD_CS   (53)  //

#define CHIP_SIZE   2048
#define BLOCK_SIZE  16
#define TEXT_SIZE   64

#define REPEAT_COUNT  10

uint8_t dataRow[BLOCK_SIZE];
char text[TEXT_SIZE];
char fileNameDump[] = "DUMP.TXT";
char fileNameBin[]  = "DUMP.BIN";

void setup() {
  // Адрес, контакты 22-29, 35-37, порты A и C
  DDRA  = B11111111;   // Настраиваем на вывод данных, Шина Адреса (ША)
  DDRC  = B11111111;   // Настраиваем на вывод данных, Шина Адреса (ША)
  // Данные, контакты 42-49, порт L
  DDRL  = B00000000;   // Настраиваем на ввод данных, Шина Данных (ШД)

  // Изначально выставим необходимые уровни
  // это нужно для выводов подтянутых к +5V,
  // так как если не выставить до переключения вывода на выход,
  // то изначально он будет низким,
  // таким образом исключаем передергивание уровней
  digitalWrite(CE, HIGH);   // На плате подтянут к +5V
  digitalWrite(OE, HIGH);   // На плате подтянут к +5V
  digitalWrite(VPP, LOW);   // На плате подтянут к земле
  pinMode(CE, OUTPUT);      // CE   H HHL L   █ ... █
  pinMode(OE, OUTPUT);      // OE   H HLL L   █ ... █
  pinMode(VPP, OUTPUT);     // VPP  L LLL L   ▄ ... ▄

  // Serial
  Serial.begin(57600);
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

static void showMenu() {
  Serial.println();
  Serial.println(F("При замене SD карты перезагрузите устройство"));
  Serial.println(F("1 - Вывести дамп EEPROM на экран"));
  Serial.println(F("2 - Записать дамп EEPROM в файл DUMP.TXT"));
  Serial.println(F("3 - Записать данные EEPROM в файл DUMP.BIN"));
  Serial.println(F("4 - Записать файл DUMP.TXT в EEPROM"));
  Serial.println(F("5 - Записать файл DUMP.BIN в EEPROM"));
  Serial.println(F("6 - Проверить EEPROM на 0xFF"));
  Serial.println(F("7 - Сравнить EEPROM с файлом DUMP.TXT"));
  Serial.println(F("8 - Сравнить EEPROM с файлом DUMP.BIN"));
  Serial.println(F("9 - List SD"));
 
  Serial.println(F("0 - TEST"));
  Serial.println(F("Введите команду: "));
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

void loop() {
  showMenu();
  char cmd = readChar();
  switch (cmd) {
    case '0':	// TEST
      loopTest();
      break;
    case '1':	// 1 - Вывести дамп EEPROM на экран
      dumpMemory(&Serial);
      break;
    case '2': // 2 - Записать дамп EEPROM в файл DUMP.TXT
      readMemoryDump();
      break;
    case '3': // 3 - Записать данные EEPROM в файл DUMP.BIN
      readMemoryBin();
      break;
    case '4':	// 4 - Записать файл DUMP.TXT в EEPROM
      writeMemoryDump();
      break;
    case '5': // 5 - Записать файл DUMP.BIN в EEPROM
      writeMemoryBin();
      break;
    case '6': // 6 - Проверить EEPROM на 0xFF
      checkClear();
      break;
    case '7': // 7 - Сравнить EEPROM с файлом DUMP.TXT"));
      checkMemoryDump();
      break;
    case '8': // 8 - Сравнить EEPROM с файлом DUMP.BIN"));
      checkMemoryBin();
      break;
    case '9':  // 9 - List SD
      listSD();
      break;
  }
}

static void readMemoryDump() {
  char* pFileName = fileNameDump;
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

static void writeMemoryDump() {
  char* pFileName = fileNameDump;
  File dataFile = SD.open(pFileName);
  if (dataFile) {
    writeBegin();
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
      
      noInterrupts();
      for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int k = 0; k < REPEAT_COUNT; k++) {
          writeData(addr, dataRow[i]);
        }
        addr++;
      }
      interrupts();
    }
    writeEnd();
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

static void checkMemoryDump() {
  char* pFileName = fileNameDump;
  File dataFile = SD.open(pFileName);
  if (dataFile) {
    readBegin();
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
      
      noInterrupts();
      for (int i = 0; i < BLOCK_SIZE; i++) {
        byte data = readData(addr);
        if (data != dataRow[i]) {
          interrupts();
          error = true;
          char* pdata = bin2hex(text, addr);
          *pdata++ = ' ';
          pdata = bin2hex(pdata, data);
          *pdata++ = ' ';
          bin2hex(pdata, dataRow[i]);
          Serial.println(text);
          Serial.flush();
          noInterrupts();
        }
        addr++;
      }
      interrupts();
    }
    readEnd();
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

static void dumpMemory(Stream* pStream) {
  uint16_t addr = 0;
  readBegin();
  uint16_t size = CHIP_SIZE / BLOCK_SIZE;
  // Читаем блоками по 16 байт (BLOCK_SIZE)
  for (uint16_t n = 0; n < size; n++) {
    bin2hex(text, addr);
    pStream->print(text);
	  pStream->flush();

    noInterrupts();
    for (int i = 0; i < BLOCK_SIZE; i++) {
      dataRow[i] = readData(addr);
      addr++;
    }
    interrupts();

    char* pdata = text;
    for (int i = 0; i < BLOCK_SIZE; i++) {
      *pdata++ = ' ';
      pdata = bin2hex(pdata, dataRow[i]);
    }
    pStream->println(text);
  }
  readEnd();
}

static void checkClear() {
  noInterrupts();
  readBegin();
  bool error = false;
  for (uint16_t addr = 0; addr < CHIP_SIZE; addr++) {
    byte data = readData(addr);
    if (data != 0xFF) {
      interrupts();
      error = true;
      char* pdata = bin2hex(text, addr);
      *pdata++ = ' ';
      bin2hex(pdata, data);
      Serial.println(text);
      Serial.flush();
      noInterrupts();
    }
  }
  readEnd();
  interrupts();
  if (error) Serial.println("\nError!");  
}

static void readMemoryBin() {
  char* pFileName = fileNameBin;
  SD.remove(pFileName);
  File dataFile = SD.open(pFileName, FILE_WRITE);
  if (dataFile) {
    uint16_t addr = 0;
    readBegin();
    uint16_t size = CHIP_SIZE / BLOCK_SIZE;
    // Читаем блоками по 16 байт (BLOCK_SIZE)
    for (uint16_t n = 0; n < size; n++) {
      noInterrupts();
      for (int i = 0; i < BLOCK_SIZE; i++) {
        dataRow[i] = readData(addr);
        addr++;
      }
      interrupts();
      dataFile.write(dataRow, BLOCK_SIZE);
    }
    readEnd();
    dataFile.close();
  }
  else {
    Serial.print(F("Error create file: "));
    Serial.println(pFileName);
  }
}

static void writeMemoryBin() {
  char* pFileName = fileNameBin;
  File dataFile = SD.open(pFileName);
  if (dataFile) {
    writeBegin();
    uint16_t addr = 0;
    bool error = false;
    while (!error) {
      int result = dataFile.read(dataRow, BLOCK_SIZE);      
      if (result == 0) break;
      if (result != BLOCK_SIZE) {
        error = true;
        break;
      }
      
      noInterrupts();
      for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int k = 0; k < REPEAT_COUNT; k++) {
          writeData(addr, dataRow[i]);
        }
        addr++;
      }
      interrupts();
    }
    writeEnd();
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

static void checkMemoryBin() {
  char* pFileName = fileNameBin;
  File dataFile = SD.open(pFileName);
  if (dataFile) {
    readBegin();
    uint16_t addr = 0;
    bool error = false;
    while (true) {
      int result = dataFile.read(dataRow, BLOCK_SIZE);
      if (result == 0) break;
      if (result != BLOCK_SIZE) {
        error = true;
        break;
      }      
      noInterrupts();
      for (int i = 0; i < BLOCK_SIZE; i++) {
        byte data = readData(addr);
        if (data != dataRow[i]) {
          interrupts();
          error = true;
          char* pdata = bin2hex(text, addr);
          *pdata++ = ' ';
          pdata = bin2hex(pdata, data);
          *pdata++ = ' ';
          bin2hex(pdata, dataRow[i]);
          Serial.println(text);
          Serial.flush();
          noInterrupts();
        }
        addr++;
      }
      interrupts();
    }
    readEnd();
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

static void listSD() {
  File root = SD.open("/");
  printDirectory(root, 0);
  Serial.println();
}

static void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

inline byte getDataPort() {
  return PINL;
}

inline void setDataPort(byte data) {
  PORTL = data;
}

inline void setAddress(uint16_t addr) {
  PORTA = lowByte(addr);
  PORTC = highByte(addr);
}

/*
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
*/

static void readBegin() {
  setDataInMode();
  digitalWrite(VPP, LOW);   // CE   H HHL L   █ ██▄ ▄ ... ▄
  digitalWrite(OE, LOW);    // OE   H HLL L   █ ██▄ ▄ ... ▄
  digitalWrite(CE, LOW);    // VPP  L LLL L   ▄ ▄▄▄ ▄ ... ▄
}

static byte readData(uint16_t addr) {
  setAddress(addr);
  delayMicroseconds(2);     // CE   L L       ▄ ... ▄
  byte data = getDataPort();// OE   L L       ▄ ... ▄
  return data;              // VPP  L L       ▄ ... ▄
}

static void readEnd() {
  digitalWrite(VPP, LOW);   // CE   L LLH H   ▄ ▄▄█ █ ... █
  digitalWrite(OE, HIGH);   // OE   L LHH H   ▄ ▄██ █ ... █
  digitalWrite(CE, HIGH);   // VPP  L LLL L   ▄ ▄▄▄ ▄ ... ▄
}

/*
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
*/

static void writeBegin() {
  setDataOutMode();
  digitalWrite(CE, LOW);    // CE   H LLL L   █ ▄▄▄ ▄ ... ▄
  digitalWrite(OE, HIGH);   // OE   H HHH H   █ ███ █ ... █
  digitalWrite(VPP, HIGH);  // VPP  L LLH H   ▄ ▄▄█ █ ... █
  delayMicroseconds(1);
}

static bool writeData(uint16_t addr, byte data) {
  setAddress(addr);
  setDataPort(data);
  delayMicroseconds(10);
  digitalWrite(CE, HIGH);   // CE   L HL L    ▄ █50ms█▄ ▄ ... ▄
  delayMicroseconds(50);    // OE   H HH H    █ █50ms██ █ ... █
  digitalWrite(CE, LOW);    // VPP  H HH H    █ █50ms██ █ ... █
  delayMicroseconds(1);
}

static void writeEnd() {
  digitalWrite(VPP, LOW);   // CE   L LH H    ▄ ▄█ █ ... █
  delayMicroseconds(1);     // OE   H HH H    █ ██ █ ... █
  digitalWrite(CE, HIGH);   // VPP  H LL L    █ ▄▄ ▄ ... ▄
  delayMicroseconds(1);
}


inline void setDataInMode() {
  DDRL = B00000000;
  PORTL = B11111111;
}

inline void setDataOutMode() {
  DDRL = B11111111;
}

//////////////////////////////////////////
void loopTest() {
  for (;;) {
    showTestMenu();
    char cmd = readChar();
    switch (cmd) {
      case '1': // Address
        while (true) loopTestAddress();
      case '2': // Data
        while (true) loopTestData();
      case '3': // Control
        while (true) loopTestControl();
      case '4': //
        while (true) loopTestVpp();
      case '5': //
        while (true) analizeReading();
      case '6': //
        while (true) analizeWriting();
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
  Serial.println(F("1 - ТЕСТ ША (Шины Адреса)"));
  Serial.println(F("2 - ТЕСТ ШД (Шины Данных)"));
  Serial.println(F("3 - ТЕСТ Линий управления (ВНИМАНИЕ +24V)"));
  Serial.println(F("4 - ТЕСТ VPP ВНИМАНИЕ +24V"));
  Serial.println(F("5 - Анилиз сигналов чтения данных (ВНИМАНИЕ +24V)"));
  Serial.println(F("6 - Анилиз сигналов записи данных (ВНИМАНИЕ +24V)"));
  Serial.println(F("Введите команду: "));
}

void loopTestAddress() {
  Serial.println(F("ТЕСТ ША (Шины Адреса)"));

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
  Serial.println(F("ТЕСТ ШД (Шины Данных)"));

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
  Serial.println(F("ТЕСТ Линий управления (ВНИМАНИЕ +24V)"));

  digitalWrite(OE, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(VPP, HIGH);
  delay(1000);
  digitalWrite(OE, LOW);
  digitalWrite(CE, HIGH);
  digitalWrite(VPP, HIGH);
  delay(1000);
  digitalWrite(OE, HIGH);
  digitalWrite(CE, LOW);
  digitalWrite(VPP, HIGH);
  delay(1000);
  digitalWrite(OE, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(VPP, LOW);
  delay(1000);
  digitalWrite(OE, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(VPP, LOW);
  delay(1000);
}

void loopTestVpp() {
  Serial.println(F("ТЕСТ VPP ВНИМАНИЕ +24V"));
  digitalWrite(VPP, HIGH);
  delay(5000);
  digitalWrite(VPP, LOW);
  delay(5000);
}

#define ANALIZE_SIZE  16
static void analizeReading() {
  noInterrupts();
  readBegin();
  for (uint16_t addr = 0; addr < ANALIZE_SIZE; addr++) {
    readData(addr);
  }
  readEnd();
  interrupts();
  delay(10);
}

static void analizeWriting() {
  noInterrupts();
  writeBegin();
  for (uint16_t addr = 0; addr < ANALIZE_SIZE; addr++) {
    writeData(addr, 0xFF);
  }
  writeEnd();
  interrupts();
  delay(10);
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
