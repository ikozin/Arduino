/*
Arduino MEGA
https://www.arduino.cc/en/Main/arduinoBoardMega/
Подключение к Arduino MEGA
https://arduinka.pro/blog/wp-content/uploads/2017/09/mega2560-pinout-1024x724.png

AT28C256
https://docs-europe.electrocomponents.com/webdocs/1596/0900766b815963c9.pdf

Комплектация:

1) Arduino MEGA
2) Макетная плата
3) Micro SD
4) Провод 18x2 -> папа, для подключения Arduino MEGA
	14x1 - папа, для подключения AT28C256, выводы  1 - 14
	14x1 - папа, для подключения AT28C256, выводы 15 - 28
	 4x1 - мама, для подключения Arduino MEGA к Micro SD
	 2x1 - мама, для подключения питания к Micro SD

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

    -----------------------------            https://static.chipdip.ru/lib/248/DOC000248438.pdf
   |                             |                  Распиновка AT28C256
   |                             |                      -------------
    -----------------------------                   1 -| A14     +5V |- 28
     |    |    |    |    |    |                     2 -| A12     ~WE |- 27
   ------------------------------                   3 -| A7      A13 |- 26
   |SC  SCK  MOSI MISO  +5V  GND|                   4 -| A6       A8 |- 25
   |                            |                   5 -| A5       A9 |- 24
   |    --------------------    |                   6 -| A4      A11 |- 23
   |   |                    |   |                   7 -| A3      ~OE |- 22
   |   |                    |   |                   8 -| A2      A10 |- 21
   |   |   MICRO SD CARD    |   |                   9 -| A1      ~CE |- 20
   |   |                    |   |                  10 -| A0       D7 |- 19
   |   |                    |   |                  11 -| D0       D6 |- 18
   ------------------------------                  12 -| D1       D5 |- 17
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
  while (!Serial) {}
  // Initialize SD
  if (!SD.begin(SD_CS)) {
    Serial.println(F("Initialization failed!"));
    for (;;);
  }
  Serial.println(F("SD card initialized."));
  displayHelp();
}

void displayHelp() {
  Serial.println();
  Serial.println(F("Reset Arduino after insert SD card"));
  Serial.println(F("List commnad:"));
  Serial.println(F("1 - Dump on screen  32 KB [AT28C256]"));
  Serial.println(F("2 - Read to file    32 KB [AT28C256]"));
  Serial.println(F("3 - Compare         32 KB [AT28C256]"));
  Serial.println(F("4 - Write from file 32 KB [AT28C256]"));
  Serial.println(F("5 - Clear           32 KB [AT28C256]"));
  Serial.println(F("6 - Check clearing  32 KB [AT28C256]"));
  Serial.println(F("7 - Disable Protect Mode"));
  Serial.println(F("8 - ERASE CHIP"));
  Serial.println(F("0 - TEST"));
  Serial.println();
  Serial.print(F("Enter commnad:"));
}

void displayInfo(uint16_t addr, uint16_t size) {
  Serial.print(F("Address: "));
  bin2hex(text, addr);
  Serial.print(text);
  Serial.print(F(" Size: "));
  bin2hex(text, size);
  Serial.println(text);
}

void displayDumpHelp() {
  Serial.println();
  Serial.println(F("Dump from EEPROM to Screen"));
  Serial.println(F("Dump  commnad:"));
  Serial.println(F("* - Dump  32 KB"));
  Serial.println(F("0 - Dump   2 KB [0000]"));
  Serial.println(F("1 - Dump   2 KB [0001]"));
  Serial.println(F("2 - Dump   2 KB [0010]"));
  Serial.println(F("3 - Dump   2 KB [0011]"));
  Serial.println(F("4 - Dump   2 KB [0100]"));
  Serial.println(F("5 - Dump   2 KB [0101]"));
  Serial.println(F("6 - Dump   2 KB [0110]"));
  Serial.println(F("7 - Dump   2 KB [0111]"));
  Serial.println(F("8 - Dump   2 KB [1000]"));
  Serial.println(F("9 - Dump   2 KB [1001]"));
  Serial.println(F("A - Dump   2 KB [1010]"));
  Serial.println(F("B - Dump   2 KB [1011]"));
  Serial.println(F("C - Dump   2 KB [1100]"));
  Serial.println(F("D - Dump   2 KB [1101]"));
  Serial.println(F("E - Dump   2 KB [1110]"));
  Serial.println(F("F - Dump   2 KB [1111]"));
  Serial.println();
  Serial.print(F("Enter Dump  command:"));
}

void displayReadHelp() {
  Serial.println();
  Serial.println(F("Read from EEPROM to File"));
  Serial.println(F("Read  commnad:"));
  Serial.println(F("* - Read  32 KB (DUMP.TXT)"));
  Serial.println(F("0 - Read   2 KB [0000] (0_DUMP.TXT)"));
  Serial.println(F("1 - Read   2 KB [0001] (1_DUMP.TXT)"));
  Serial.println(F("2 - Read   2 KB [0010] (2_DUMP.TXT)"));
  Serial.println(F("3 - Read   2 KB [0011] (3_DUMP.TXT)"));
  Serial.println(F("4 - Read   2 KB [0100] (4_DUMP.TXT)"));
  Serial.println(F("5 - Read   2 KB [0101] (5_DUMP.TXT)"));
  Serial.println(F("6 - Read   2 KB [0110] (6_DUMP.TXT)"));
  Serial.println(F("7 - Read   2 KB [0111] (7_DUMP.TXT)"));
  Serial.println(F("8 - Read   2 KB [1000] (8_DUMP.TXT)"));
  Serial.println(F("9 - Read   2 KB [1001] (9_DUMP.TXT)"));
  Serial.println(F("A - Read   2 KB [1010] (A_DUMP.TXT)"));
  Serial.println(F("B - Read   2 KB [1011] (B_DUMP.TXT)"));
  Serial.println(F("C - Read   2 KB [1100] (C_DUMP.TXT)"));
  Serial.println(F("D - Read   2 KB [1101] (D_DUMP.TXT)"));
  Serial.println(F("E - Read   2 KB [1110] (E_DUMP.TXT)"));
  Serial.println(F("F - Read   2 KB [1111] (F_DUMP.TXT)"));
  Serial.println();
  Serial.print(F("Enter Read  command:"));
}

void displayCheckHelp() {
  Serial.println();
  Serial.println(F("Check EEPROM from File"));
  Serial.println(F("Check commnad:"));
  Serial.println(F("* - Check 32 KB (DUMP.TXT)"));
  Serial.println(F("0 - Check  2 KB [0000] (0_DUMP.TXT)"));
  Serial.println(F("1 - Check  2 KB [0001] (1_DUMP.TXT)"));
  Serial.println(F("2 - Check  2 KB [0010] (2_DUMP.TXT)"));
  Serial.println(F("3 - Check  2 KB [0011] (3_DUMP.TXT)"));
  Serial.println(F("4 - Check  2 KB [0100] (4_DUMP.TXT)"));
  Serial.println(F("5 - Check  2 KB [0101] (5_DUMP.TXT)"));
  Serial.println(F("6 - Check  2 KB [0110] (6_DUMP.TXT)"));
  Serial.println(F("7 - Check  2 KB [0111] (7_DUMP.TXT)"));
  Serial.println(F("8 - Check  2 KB [1000] (8_DUMP.TXT)"));
  Serial.println(F("9 - Check  2 KB [1001] (9_DUMP.TXT)"));
  Serial.println(F("A - Check  2 KB [1010] (A_DUMP.TXT)"));
  Serial.println(F("B - Check  2 KB [1011] (B_DUMP.TXT)"));
  Serial.println(F("C - Check  2 KB [1100] (C_DUMP.TXT)"));
  Serial.println(F("D - Check  2 KB [1101] (D_DUMP.TXT)"));
  Serial.println(F("E - Check  2 KB [1110] (E_DUMP.TXT)"));
  Serial.println(F("F - Check  2 KB [1111] (F_DUMP.TXT)"));
  Serial.println();
  Serial.print(F("Enter Check command:"));
}

void displayWriteHelp() {
  Serial.println();
  Serial.println(F("Write from File to EEPROM"));
  Serial.println(F("Write commnad:"));
  Serial.println(F("* - Write 32 KB (DUMP.TXT)"));
  Serial.println(F("0 - Write  2 KB [0000] (0_DUMP.TXT)"));
  Serial.println(F("1 - Write  2 KB [0001] (1_DUMP.TXT)"));
  Serial.println(F("2 - Write  2 KB [0010] (2_DUMP.TXT)"));
  Serial.println(F("3 - Write  2 KB [0011] (3_DUMP.TXT)"));
  Serial.println(F("4 - Write  2 KB [0100] (4_DUMP.TXT)"));
  Serial.println(F("5 - Write  2 KB [0101] (5_DUMP.TXT)"));
  Serial.println(F("6 - Write  2 KB [0110] (6_DUMP.TXT)"));
  Serial.println(F("7 - Write  2 KB [0111] (7_DUMP.TXT)"));
  Serial.println(F("8 - Write  2 KB [1000] (8_DUMP.TXT)"));
  Serial.println(F("9 - Write  2 KB [1001] (9_DUMP.TXT)"));
  Serial.println(F("A - Write  2 KB [1010] (A_DUMP.TXT)"));
  Serial.println(F("B - Write  2 KB [1011] (B_DUMP.TXT)"));
  Serial.println(F("C - Write  2 KB [1100] (C_DUMP.TXT)"));
  Serial.println(F("D - Write  2 KB [1101] (D_DUMP.TXT)"));
  Serial.println(F("E - Write  2 KB [1110] (E_DUMP.TXT)"));
  Serial.println(F("F - Write  2 KB [1111] (F_DUMP.TXT)"));
  Serial.println();
  Serial.print(F("Enter Write command:"));
}

void displayClearHelp() {
  Serial.println();
  Serial.println(F("Clear EEPROM"));
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
  Serial.print(F("Enter Clear command:"));
}

void displayFillHelp() {
  Serial.println();
  Serial.println(F("Checking filling EEPROM for 0FFH"));
  Serial.println(F("Checking filling commnad:"));
  Serial.println(F("* - Checking filling 32 KB"));
  Serial.println(F("0 - Checking filling  2 KB [0000]"));
  Serial.println(F("1 - Checking filling  2 KB [0001]"));
  Serial.println(F("2 - Checking filling  2 KB [0010]"));
  Serial.println(F("3 - Checking filling  2 KB [0011]"));
  Serial.println(F("4 - Checking filling  2 KB [0100]"));
  Serial.println(F("5 - Checking filling  2 KB [0101]"));
  Serial.println(F("6 - Checking filling  2 KB [0110]"));
  Serial.println(F("7 - Checking filling  2 KB [0111]"));
  Serial.println(F("8 - Checking filling  2 KB [1000]"));
  Serial.println(F("9 - Checking filling  2 KB [1001]"));
  Serial.println(F("A - Checking filling  2 KB [1010]"));
  Serial.println(F("B - Checking filling  2 KB [1011]"));
  Serial.println(F("C - Checking filling  2 KB [1100]"));
  Serial.println(F("D - Checking filling  2 KB [1101]"));
  Serial.println(F("E - Checking filling  2 KB [1110]"));
  Serial.println(F("F - Checking filling  2 KB [1111]"));
  Serial.println();
  Serial.print(F("Enter Fill command:"));
}

char readChar() {
  for (;;) {
      while (!Serial.available());
      char cmd = Serial.read();
      if (cmd == '\r') continue;
      if (cmd == '\n') continue;
      Serial.println(cmd);
      return cmd;
  }
}

void loopAction(void (*help)(void), void (*action)(uint16_t, uint16_t, Stream*)) {
  for (;;) {
    help();
    char cmd = readChar();
    cmd = toUpperCase(cmd);
    if (cmd == '*') {
        displayInfo(0, CHIP_SIZE);
        action(0, CHIP_SIZE, &Serial);
        continue;
    } else if (isAlphaNumeric(cmd)) { // '0'-'9','A'-'F'
      cmd -= cmd >= 'A' ? 'A' - 10 : '0';
      if (cmd >= 0 && cmd <= 16) {
        uint16_t addr = cmd * CHIP_BLOCK_SIZE;
        displayInfo(addr, CHIP_BLOCK_SIZE);
        action(addr, CHIP_BLOCK_SIZE, &Serial);
        continue;
      }
    }
    return;
  }
}

void loopFileAction(void (*help)(void), void (*action)(uint16_t, uint16_t, char*)) {
  for (;;) {
    help();
    char cmd = readChar();
    cmd = toUpperCase(cmd);
    if (cmd == '*') {
        displayInfo(0, CHIP_SIZE);
        action(0, CHIP_SIZE, "DUMP.TXT");
        continue;
    } else if (isAlphaNumeric(cmd)) { // '0'-'9','A'-'F'
      byte block = cmd >= 'A' ? cmd -'A' + 10 : cmd - '0';
      if (block >= 0 && block <= 16) {
        fileName[0] = cmd;
        Serial.println(fileName);        
        uint16_t addr = block * CHIP_BLOCK_SIZE;
        displayInfo(addr, CHIP_BLOCK_SIZE);
        action(addr, CHIP_BLOCK_SIZE, fileName);
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
    case '8':         // 8 - Erase Chip
      eraseChip();
      break;
    case '0':          // 0 - TEST
      loopTest();
      break;
  }
  displayHelp();
}

void setDataInMode() {
	DDRL = B00000000;
}

void setDataOutMode() {
	DDRL = B11111111;
}


void setDataPort(byte data) {
  PORTL = data;
}

byte getDataPort() {
  return PINL;
}

void setAddress(uint16_t addr) {
  PORTA = lowByte(addr);
  PORTC = highByte(addr);
}

byte readData(uint16_t addr) {
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

void writeData(uint16_t addr, byte data) {
  setAddress(addr);
  setDataPort(data);
  enableCE();
  enableWE();
  delayMicroseconds(1);
  disableWE();
  disableCE();
  delayMicroseconds(2);
}

void dumpMemory(uint16_t address, uint16_t size, Stream* pStream) {
  uint16_t addr = 0;
  setDataInMode();
  size /= BLOCK_SIZE;
  // Читаем блоками по 16 байт (BLOCK_SIZE)
  for (uint16_t n = 0; n < size; n++) {
    bin2hex(text, addr);
    pStream->print(text);
    for (int i = 0; i < BLOCK_SIZE; i++) {
      dataRow[i] = readData(address);
      address++;
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

void readMemory(uint16_t addrress, uint16_t size, char* pFileName) {
  SD.remove(pFileName);
  File dataFile = SD.open(pFileName, FILE_WRITE);
  if (dataFile) {
    dumpMemory(addrress, size, &dataFile);
    dataFile.close();
  }
  else {
    Serial.print(F("Error create file: "));
    Serial.println(pFileName);
  }
}

void checkMemory(uint16_t address, uint16_t size, char* pFileName) {
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
      for (int i = 0; i < BLOCK_SIZE; i++) {
        error = readData(address + addr) != dataRow[i];
        if (error) {
          address = addr;
          break;
        }
        addr++;
      }
    }
    dataFile.close();
    if (error) {
      Serial.println(F("\nError!"));
      Serial.print(F("Address: "));
      bin2hex(text, address);
      Serial.println(text);
    }
  }
  else {
    Serial.print(F("Error open file: "));
    Serial.println(pFileName);
  }
}

void writeMemory(uint16_t address, uint16_t size, char* pFileName) {
  File dataFile = SD.open(pFileName);
  if (dataFile) {
    setDataOutMode();
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
      for (int i = 0; i < BLOCK_SIZE; i++) {
        writeData(address + addr, dataRow[i]);
        addr++;
      }
    }
    setDataInMode();
    dataFile.close();
    if (error) {
      Serial.println(F("\nError!"));
      Serial.print(F("Address: "));
      bin2hex(text, address);
      Serial.println(text);
    }        
  }
  else {
    Serial.print(F("Error open file: "));
    Serial.println(pFileName);
  }
}

void clearMemory(uint16_t address, uint16_t size) {
  setDataOutMode();
  for (int i = 0; i < BLOCK_SIZE; i++) {
    dataRow[i] = 0xFF;
  }
  size /= BLOCK_SIZE;
  for (uint16_t n = 0; n < size; n++) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      writeData(address, dataRow[i]);
      address++;
    }
  }
  setDataInMode();
}

void checkFillMemory(uint16_t address, uint16_t size) {
  setDataInMode();
  for (int i = 0; i < size; i++) {
    if (readData(address) != 0xFF) {
      Serial.print(F("\nError in Address: "));
      bin2hex(text, address);
      Serial.print(text);
    }
    address++;
  }
  Serial.println();
}

void disableProtectMode() {
  setDataOutMode();
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x80);
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x20);
  setDataInMode();
}

void eraseChip() {
  setDataOutMode();
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x80);
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0x10);
  setDataInMode();
}
/*
void enableProtectMode() {
  setDataOutMode();
  writeData(0x5555, 0xAA);
  writeData(0x2AAA, 0x55);
  writeData(0x5555, 0xA0);
  writeData(0x0000, 0xFF);
  readData(0x0000);
  setDataInMode();
}
*/

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
  for (int i = 0; i < 2; i++) {
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

void loopTest() {
  Serial.println(F("TEST"));
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

void testAllOn() {
  disableCE();
  disableOE();
  disableWE();
  setDataPort(0xFF); 
  setAddress(0xFFFF); 
}

void loopTestCrtl() {
  Serial.println(F("Control TEST: CE, OE, WE"));
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
}

void loopTestData() {
  Serial.println(F("Data TEST"));
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
