//////////////////////////////////////////////////////////////////////////////
// Основано на проекте https://github.com/alemorf/k155re3_k556rt4_programmer
//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <WString.h>
#include <StringUtils.h>
#include <ctype.h>
#include <GyverIO.h>
#include <GyverOLED.h>

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif


#define DEBUG
#define DELAY_MS(d)      for (int i = 0; i < (d); i++) delayMicroseconds(1000);

// #define ECHO

#define LED1_PIN        39
#define LED2_PIN        40
#define WR_PIN          41

GyverOLED<SSD1306_128x32, OLED_BUFFER>   oled(0x3C);

uint8_t data[256] {};

/*
12.53V
         К155РЕ3                    К556РТ4                   
    ┌────┬─────┬────┐          ┌────┬─────┬────┐              
 10 ┤  1 │ ROM │ 1  ├ 1     15 ┤ A1 │ ROM │ 1  ├ 12
 11 ┤  2 │     │ 2  ├ 2      7 ┤ A2 │     │ 2  ├ 11
 12 ┤  4 │     │ 3  ├ 3      6 ┤ A3 │     │ 3  ├ 10
 13 ┤  8 │     │ 4  ├ 4      5 ┤ A4 │     │ 4  ├ 9
 14 ┤ 16 │     │ 5  ├ 5      4 ┤ A5 │     │    │
    │    │     │ 6  ├ 6      3 ┤ A6 │     │    │
    ├────┤     │ 7  ├ 7      2 ┤ A7 │     │    │
 15 ┤ ~E │     │ 8  ├ 9      1 ┤ A8 │     │    │
    └────┴─────┴────┘          ├────┤     │    │
                            13 ┤ ~W │     │    │
                            14 ┤~CE │     │    │
                               └────┴─────┴────┘
*/

typedef struct {
    const size_t  chip_size;
    const uint8_t bit_size;
    const char*   name;
} EEPROM_SETTING;

EEPROM_SETTING k155re3 { .chip_size = 32, .bit_size = 8, .name = "К155РЕ3" };
EEPROM_SETTING k566rt4 { .chip_size = 256, .bit_size = 4, .name = "К556РТ4" };
EEPROM_SETTING *setting = &k155re3;

String cmd;
char terminator = 0;
char text[64];

inline void setLeds(bool led1, bool led2) {
    gio::write(LED1_PIN, led1);
    gio::write(LED2_PIN, led2);
}

inline void EEPROM_setWrite(bool isWrite) {
    gio::write(WR_PIN, !isWrite);
}

// data = PINL
inline uint8_t EEPROM_getData() {
    return PINL;
}

// PORTC = data
inline void EEPROM_setData(uint8_t data) {
    PORTC = ~data;
}

// PORTA = address
inline void EEPROM_setAddress(uint8_t addr) {
    PORTA = addr;  // Set address
}

void EEPROM_TestAddres(const EEPROM_SETTING *eeprom) {
    setLeds(false, false);
    EEPROM_setAddress(0);

    for (uint16_t addr = 0; addr < eeprom->chip_size; addr++) {
        EEPROM_setAddress(addr);
        Serial.println(addr, HEX);
        DELAY_MS(500);
    }
}

void EEPROM_TestData(const EEPROM_SETTING *eeprom) {
    setLeds(false, false);
    EEPROM_setAddress(0);

    for (int n = 0; n < eeprom->bit_size; n++) {
        const uint8_t mask = bit(n);
        EEPROM_setData(mask);
        DELAY_MS(500);
    }
    EEPROM_setData(0xFF);
}

void EEPROM_loadData(uint8_t* data, const EEPROM_SETTING *eeprom) {
    setLeds(false, false);
    EEPROM_setData(0xFF);
    uint16_t mask = bit(eeprom->bit_size + 1) - 1;
    for (uint16_t addr = 0; addr < eeprom->chip_size; addr++) {
        EEPROM_setAddress(addr);
        DELAY_MS(50);
        const uint8_t value = EEPROM_getData();
        data[addr] = value & mask;
    }
}

bool EEPROM_saveData(const uint8_t* data, const EEPROM_SETTING *eeprom) {
    setLeds(false, false);
    EEPROM_setAddress(0);

    for (uint16_t addr = 0; addr < eeprom->chip_size; addr++) {
        EEPROM_setAddress(addr);
        DELAY_MS(50);
        const uint8_t value = data[addr];
        uint8_t current = EEPROM_getData();

        sprintf(text, "Address[0x%02X] = 0x%02X", addr, value);
        Serial.println(text);
        Serial.flush();

        for (int n = 0; n < eeprom->bit_size; n++) {
            const uint8_t mask = bit(n);
            if ((value & mask) == 0) continue;
            if ((current & mask) != 0) continue;

            noInterrupts();
            setLeds(false, true);
            EEPROM_setData(mask);
            DELAY_MS(300 * 3);
            setLeds(true, true);
            EEPROM_setWrite(true);
            DELAY_MS(300 * 1);
            EEPROM_setWrite(false);
            setLeds(false, false);
            EEPROM_setData(0xFF);
            DELAY_MS(300 * 4);
            interrupts();
            
            if ((EEPROM_getData() & mask) == 0) {
                setLeds(true, true);
                sprintf(text, "BIT[%d]", n);
                Serial.println(text);
                Serial.flush();
                return false;
            }
        }
        DELAY_MS(300 * 1);
        current = EEPROM_getData();
        if (value != current) {
            setLeds(true, true);
            sprintf(text, "Write=0x%02X, Read=0x%02X", value, current);
            Serial.println(text);
            Serial.flush();
            return false;
        }
    }
    EEPROM_setAddress(0);
    return true;
}

void oledEEPROM(const EEPROM_SETTING* eeprom) {
    oled.clear();
    oled.setCursor(24, 1);
    oled.setScale(2);
    oled.print(eeprom->name);
    oled.setScale(1);
    oled.rect(0, 0, 127, 31, OLED_STROKE);
    oled.update();
}

void commandK155RE3() {
    setting = &k155re3;
    Serial.println(F("EEPROM = К155РЕ3 (EEPROM:32x8)"));
    Serial.println(F("OK"));
    Serial.flush();
    oledEEPROM(setting);
}

void commandK556RT4() {
    setting = &k566rt4;
    Serial.println(F("EEPROM = К556РТ4 (EEPROM:256x4)"));
    Serial.println(F("OK"));
    Serial.flush();
    oledEEPROM(setting);
}

uint16_t hexToWord(char** buffer, int maxLen = 4) {
    char symb = **buffer;
    if (!isxdigit(symb)) return 0;
    uint16_t word = isdigit(symb)? (symb - '0') : (symb - 'A' + 10);
    while ((symb = *(++(*buffer))) != '\0' && --maxLen > 0) {
        if (!isxdigit(symb)) break;
        word <<= 4;
        word |= isdigit(symb)? (symb - '0') : (symb - 'A' + 10);
    }
    return word;
}

// 0000: 81 CF 23 0B 4D 19 11 CB 01 09 41 15 B1 07 31 71

// 0000: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
// 0010: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

// 0000: FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
// 0010: FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
void commandLoadData(const EEPROM_SETTING* eeprom) {
    Serial.println(F("Enter data:"));
    Serial.flush();
    while (!Serial.available()) delay(100);
    cmd = Serial.readStringUntil(terminator);
    Serial.println(cmd);
    Serial.flush();

    cmd.toUpperCase();
    cmd.trim();

    char* buffer = cmd.begin();
    uint16_t address = hexToWord(&buffer);
    if (address > eeprom->chip_size) {
        Serial.println(F("Error address"));
        return;
    }
    if (*buffer++ != ':') {
        Serial.println(F("Error data format (:)"));
        return;
    }
    while (*buffer != '\0') {
        while (isblank(*buffer)) buffer++;
        data[address++] = (uint8_t)hexToWord(&buffer);
        if (address > eeprom->chip_size) {
            Serial.println(F("Error address"));
            return;
        }
    }
    Serial.println(F("OK"));
    Serial.flush();
    return;
}

// :1000000081CF230B4D1911CB01094115B107317176
// :1000000000000000000000000000000000000000F0
// :00000001FF
// :1000000000000000000000000000000000000000F0
// :1000000000000000000000000000000000000000F0
// :00000001FF
// :10000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF100
// :10000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF100
// :00000001FF
void commandLoadIntelHex(const EEPROM_SETTING* eeprom) {
    Serial.println(F("Enter IntelHex data:"));
    Serial.flush();
    while (true) {
        uint8_t size  = 0;
        uint8_t type  = 0;
        uint8_t ext  = 0;
        uint16_t addr = 0;
        uint16_t sum  = 0;
        
        while (!Serial.available()) delay(100);
        delay(2000);
        cmd = Serial.readStringUntil(terminator);
        Serial.println(cmd);
        Serial.flush();
        cmd.toUpperCase();
        cmd.trim();

        if (cmd.length() == 0) break;
        if (cmd.length() < 11) {
            Serial.println(F("Error data format (length)"));
            return;
        }
        char* buffer = cmd.begin();
        if (*buffer++ != ':') {
            Serial.println(F("Error data format (start)"));
            return;
        }
        size = hexToWord(&buffer, 2);
        sum += size;
        if (size > eeprom->chip_size) {
            Serial.println(F("Error data (size)"));
            return;
        }

        addr = hexToWord(&buffer);
        sum += addr & 0xFF;
        sum += addr >> 8;
        if (addr + size > eeprom->chip_size) {
            Serial.println(F("Error data (overflow)"));
            return;
        }
        
        type = hexToWord(&buffer, 2);
        sum += type;
        if (type != 0 && type != 1) {
            Serial.println(F("Error data (type)"));
            return;
        }
        if (cmd.length() != (size << 1) + 11U) {
            Serial.println(F("Error data (length)"));
            return;
        }
        for (int i = 0; i < size; i++) {
            uint8_t value = hexToWord(&buffer, 2);
            sum += value;
            data[addr + i] = value;
        }
    
        ext = hexToWord(&buffer, 2);
        sum += ext;
        if ((sum & 0xFF) != 0) {
            Serial.print(F("Error data format (checksum):"));
            sprintf(text, "%04X", sum);
            Serial.println(text);
            return;
        }
        if (type == 1) break;
    }

    while (Serial.available()) Serial.read();
    Serial.println(F("OK"));
    Serial.flush();
}

// gc8jC00ZEcsBCUEVsQcxcQAAAAAAAAAAAAAAAAAAAAA=
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=
// //////////////////////////////////////////8=
void commandLoadBase64(const EEPROM_SETTING* eeprom) {
    Serial.println(F("Enter base64 data:"));
    while (!Serial.available()) delay(100);
    cmd = Serial.readStringUntil(terminator);
    Serial.println(cmd);
    Serial.flush();
    cmd.trim();
    size_t dlen = su::b64::decodedLen(cmd.c_str(), cmd.length());
    if (dlen != eeprom->chip_size) {
        sprintf(text, "Error Read. decoded length data = %u", cmd.length());
        Serial.println(text);
        return;
    }
    su::b64::decode(data, cmd.c_str());
    Serial.println(F("OK"));
    Serial.flush();
}

void commandDump(const EEPROM_SETTING* eeprom) {
    Serial.print(F("      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"));
    for (size_t i = 0; i < eeprom->chip_size; i++) {
        if (i % 16 == 0) {
            Serial.println();
            sprintf(text, "[%02X]:", i);
            Serial.print(text);
        }
        uint8_t d = data[i];
        sprintf(text, " %02X", d);
        Serial.print(text);
    }
    Serial.println();
    Serial.flush();
}

void commandDumpBase(const EEPROM_SETTING* eeprom) {
    cmd = "";
    su::b64::encode(cmd, data, eeprom->chip_size, false);
    Serial.println(F("BASE64:"));
    Serial.println(cmd);
    Serial.println(F("OK"));
    Serial.flush();
}

void commandDumpIntel(const EEPROM_SETTING* eeprom) {
    cmd = "";
    uint8_t type = 0;
    uint8_t block_size = 16;
    uint16_t addr = 0;
    Serial.println(F("IntelHex:"));
    uint8_t* buffer = &data[0];    

    for (size_t n = 0; n < eeprom->chip_size / block_size; n++) {
        uint16_t sum  = block_size + (addr & 0xFF) + (addr >> 8) + type;
        sprintf(text, ":%02X%04X%02X", block_size, addr, type);
        Serial.print(text);
        for (size_t i = 0; i < block_size; i++) {
            uint8_t value = buffer[i];
            sprintf(text, "%02X", value);
            Serial.print(text);
            sum += value;        
        }
        buffer += block_size;
        sum = 0x100 - (sum & 0xFF);
        sprintf(text, "%02X", sum);
        Serial.println(text);
    }
    Serial.println(":00000001FF");
    Serial.println(F("OK"));
    Serial.flush();
}

void commandRead() {
    EEPROM_loadData(data, setting);
    Serial.println(F("OK"));
    Serial.flush();
}

void commandWrite() {
    bool isDone = EEPROM_saveData(data, setting);
    if (isDone) Serial.println(F("OK"));
    else Serial.println(F("ERROR"));
    Serial.flush();
}

void commandTestData(EEPROM_SETTING* eeprom) {
    EEPROM_TestData(setting);
    Serial.println(F("OK"));
    Serial.flush();
}

void commandTestAddress(EEPROM_SETTING* eeprom) {
    EEPROM_TestAddres(setting);
    Serial.println(F("OK"));
    Serial.flush();
}

void commandHelp() {
    Serial.println(F("H, ?, HELP - вывод подсказки по командам"));
    Serial.println(F("3, RE3 - выбор К155РЕ3 (EEPROM:32x8)"));
    Serial.println(F("4, RT4 - выбор К556РТ4 (EEPROM:256x4)"));
    Serial.println(F("A, ADDR - ввод данных через COM порт, формат ввода ""ADDR: XX XX XX XX XX XX XX XX"""));
    Serial.println(F("LB, LOAD BASE - загрузка данных через COM порт в BASE64 формате"));
    Serial.println(F("LX, LOAD HEX  - загрузка данных через COM порт в Intel Hex формате"));
    Serial.println(F("D, DUMP  - просмотр данных для записи(прожига)"));
    Serial.println(F("DB, DUMP BASE - просмотр данных для записи(прожига) в BASE64 формате"));
    Serial.println(F("DX, DUMP HEX - просмотр данных для записи(прожига) в Intel Hex формате"));
    Serial.println(F("R, READ  - считывание данных из EEPROM"));
    Serial.println(F("W, WRITE - запись(прожиг) данных в EEPROM"));
    Serial.println(F("TD, TEST DATA - тест шины данных"));
    Serial.println(F("TA, TEST ADDRESS - тест шины адреса"));
    Serial.flush();
}

void proccessCommand(String& command) {
    Serial.println(command);
    Serial.flush();
    if (command == "H" || command == "?" || command.startsWith("HELP")) {
        commandHelp();
        return;
    }
    if (command == "3" || command.startsWith("RE3")) {
        commandK155RE3();
        return;
    }
    if (command == "4" || command.startsWith("RT4")) {
        commandK556RT4();
        return;
    }
    if (command == "A" || command.startsWith("ADDR")) {
        commandLoadData(setting);
        return;
    }
    if (command == "LB" || command.startsWith("LOAD BASE")) {
        commandLoadBase64(setting);
        return;
    }
    if (command == "LX" || command.startsWith("LOAD HEX")) {
        commandLoadIntelHex(setting);
        return;
    }
    if (command == "D" || command.startsWith("DUMP")) {
        commandDump(setting);
        return;
    }
    if (command == "DB" || command.startsWith("DUMP BASE")) {
        commandDumpBase(setting);
        return;
    }
    if (command == "DX" || command.startsWith("DUMP HEX")) {
        commandDumpIntel(setting);
        return;
    }
    if (command == "R" || command.startsWith("READ")) {
        commandRead();
        return;
    }
    if (command == "W" || command.startsWith("WRITE")) {
        commandWrite();
        return;
    }
    if (command == "TD" || command.startsWith("TEST DATA")) {
        commandTestData(setting);
        return;
    }
    if (command == "TA" || command.startsWith("TEST ADDRESS")) {
        commandTestAddress(setting);
        return;
    }
}

void setup() {
    cmd.reserve(1024);
    oled.init(SDA, SCL);    // инициализация
    Wire.setClock(800000L); // макс. 800'000
    oled.flipV(true);
    oled.flipH(true);
    oled.clear();
    oled.setScale(2);
    oled.setCursor(9, 1);
    oled.print(F("СТАРТ ..."));
    oled.setScale(1);
    oled.rect(0, 0, 127, 31, OLED_STROKE);
    oled.update();

    // Port Address
    DDRA = B11111111;   // Set output mode
    PORTA = B00000000;  // Set data
    // Port Write
    DDRC = B11111111;   // Set output mode
    PORTC = B11111111;  // Set data
    // Port Read
    DDRL = B00000000;   // Set input mode
    PORTL = B11111111;  // Set pullup mode

    gio::init(LED1_PIN, OUTPUT);
    gio::init(LED2_PIN, OUTPUT);
    gio::init(WR_PIN, OUTPUT);
    
    EEPROM_setWrite(false);
    EEPROM_setData(0xFF);
    EEPROM_setAddress(0);

    setLeds(true, true);
    delay(500);
    setLeds(false, false);

    oled.clear();
    oled.setCursor(8, 1);
    oled.print(F("ЖДЕМ ТЕРМИНАЛ (COM)"));
    oled.rect(0, 0, 127, 31, OLED_STROKE);
    oled.update();

    cmd.reserve(127);
    Serial.begin(115200);
    while(!Serial) delay(1000);
    Serial.println(F("START"));

    commandK155RE3();
    
    //commandWrite();
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        if (c == '\r' || c == '\n') {
            if (!terminator) {
                terminator = c;
            }
            if (cmd.length() == 0) return;
#ifdef ECHO
            Serial.println();
            Serial.flush();
#endif
            cmd.trim();
            cmd.toUpperCase();
            proccessCommand(cmd);
            cmd = "";
        }
#ifdef ECHO
        Serial.print(c);
#endif
        cmd += c;
    }
    else {
        delay(100);
    }
}
