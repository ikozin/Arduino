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
#define ROMSIZE         32

#define LED1_PIN        39
#define LED2_PIN        40
#define WR_PIN          41

GyverOLED<SSD1306_128x32, OLED_BUFFER>   oled(0x3C);

uint8_t data[ROMSIZE] {};

String cmd;
char terminator = 0;
char text[64];

uint16_t chip_size = ROMSIZE;
uint8_t chip_addr_shift = 3; 

inline void setLeds(bool led1, bool led2) {
    gio::write(LED1_PIN, led1);
    gio::write(LED2_PIN, led2);
}

inline void EEPROM_setWrite(bool isWrite) {
    gio::write(WR_PIN, !isWrite);
}

inline uint8_t EEPROM_getData() {
    return PINL;
}

inline void EEPROM_setData(uint8_t data) {
    PORTC = ~data;
}

// PORTA = address
inline void EEPROM_setAddress(uint8_t addr) {
    addr = (addr & 0xF0) >> 4 | (addr & 0x0F) << 4;
    addr = (addr & 0xCC) >> 2 | (addr & 0x33) << 2;
    addr = (addr & 0xAA) >> 1 | (addr & 0x55) << 1;
    PORTA = addr;  // Set address
}

void EEPROM_loadData(size_t chip_size, uint8_t* data, uint8_t shift, uint8_t bit_size) {
    setLeds(false, false);
    EEPROM_setData(0xFF);
    uint16_t mask = bit(bit_size + 1) - 1;
    for (uint16_t addr = 0; addr < chip_size; addr++) {
        EEPROM_setAddress(addr << shift);
        DELAY_MS(50);
        const uint8_t value = EEPROM_getData();
        data[addr] = value & mask;
    }
}

bool EEPROM_saveData(size_t chip_size, uint8_t* data, uint8_t shift, uint8_t bit_size) {
    setLeds(false, false);
    for (uint16_t addr = 0; addr < chip_size; addr++) {
        EEPROM_setAddress(addr << shift);
        DELAY_MS(50);
        const uint8_t value = data[addr];
        uint8_t current = EEPROM_getData();

        sprintf(text, "Address[0x%02X] = 0x%02X", addr, value);
        Serial.println(text);
        Serial.flush();

        for (int n = 0; n < bit_size; n++) {
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
        current = EEPROM_getData();
        if (value != current) {
            setLeds(true, true);
            sprintf(text, "Write=0x%02X, Read=0x%02X", value, current);
            Serial.println(text);
            Serial.flush();
            return false;
        }
    }
    return true;
}

void oledEEPROM() {
    oled.clear();
    oled.setCursor(1, 1);
    oled.print("К155РЕ3 (32x8)");
    oled.rect(0, 0, 127, 31, OLED_STROKE);
    oled.update();
}
void commandK155RE3() {
    Serial.println(F("EEPROM = К155РЕ3 (EEPROM:32x8)"));
    Serial.println(F("OK"));
    Serial.flush();
}

void commandK556RT4() {
    Serial.println(F("EEPROM = К556РТ4 (EEPROM:256x4)"));
    Serial.println(F("OK"));
    Serial.flush();
}

void commandLoadData() {
    Serial.println(F("Enter data:"));
    Serial.flush();
    while (!Serial.available()) delay(100);
    cmd = Serial.readStringUntil(terminator);
}

void commandLoadIntelHex() {
    Serial.println(F("Enter IntelHex data:"));
    Serial.flush();
    while (true) {
        uint8_t value = 0;
        uint8_t size  = 0;
        uint8_t type  = 0;
        uint8_t ext  = 0;
        uint16_t addr = 0;
        uint16_t sum  = 0;
        char symb;
    
        cmd = Serial.readStringUntil(terminator);
        cmd.trim();
        if (cmd.length() == 0) break;
        if (cmd.length() < 11) {
            Serial.println(F("Error data format (length)"));
            return;
        }
        symb = cmd[0];
        if (symb != ':') {
            Serial.println(F("Error data format (start)"));
            return;
        }

        symb = cmd[1];
        size = (isdigit(symb)? symb - '0' : (symb - 'A' + 10)) << 4;
        symb = cmd[2];
        size |= isdigit(symb)? symb - '0' : (symb - 'A' + 10);
        sum += size;
        if (size > ROMSIZE) {
            Serial.println(F("Error data (size)"));
            return;
        }

        symb = cmd[3];
        value = (isdigit(symb)? symb - '0' : (symb - 'A' + 10)) << 4;
        symb = cmd[4];
        value |= isdigit(symb)? symb - '0' : (symb - 'A' + 10);
        sum += value;
        addr = value << 8;
        symb = cmd[5];
        value = (isdigit(symb)? symb - '0' : (symb - 'A' + 10)) << 4;
        symb = cmd[6];
        value |= isdigit(symb)? symb - '0' : (symb - 'A' + 10);
        sum += value;
        addr |= value;
        if (addr + size > ROMSIZE) {
            Serial.println(F("Error data (overflow)"));
            return;
        }

        symb = cmd[7];
        type = (isdigit(symb)? symb - '0' : (symb - 'A' + 10)) << 4;
        symb = cmd[8];
        type |= isdigit(symb)? symb - '0' : (symb - 'A' + 10);
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
            symb = cmd[9 + (i << 1)];
            value = (isdigit(symb)? symb - '0' : (symb - 'A' + 10)) << 4;
            symb = cmd[10 + (i << 1)];
            value |= isdigit(symb)? symb - '0' : (symb - 'A' + 10);
            sum += value;
            data[addr + i] = value;
        }
    
        symb = cmd[9 + (size << 1)];
        ext = (isdigit(symb)? symb - '0' : (symb - 'A' + 10)) << 4;
        symb = cmd[10 + (size << 1)];
        ext |= isdigit(symb)? symb - '0' : (symb - 'A' + 10);
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

void commandLoadBase64() {
    Serial.println(F("Enter base64 data:"));
    while (!Serial.available()) delay(100);
    cmd = Serial.readStringUntil(terminator);
    size_t dlen = su::b64::decodedLen((void *)cmd.c_str(), cmd.length());
    if (dlen != ROMSIZE) {
        sprintf(text, "Error Read. decoded length data = %d", cmd.length());
        Serial.println(text);
        return;
    }
    su::b64::decode(data);
    Serial.println(F("OK"));
    Serial.flush();
}

void commandDump() {
    Serial.print(F("      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"));
    for (size_t i = 0; i < ROMSIZE; i++) {
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

void commandRead() {
    EEPROM_loadData(ROMSIZE, data, 3, 8);
    Serial.println(F("OK"));
    Serial.flush();
}

void commandWrite() {
    bool isDone = EEPROM_saveData(ROMSIZE, data, 3, 8);
    if (isDone) Serial.println(F("OK"));
    else Serial.println(F("ERROR"));
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
    Serial.println(F("R, READ  - считывание данных из EEPROM"));
    Serial.println(F("W, WRITE - запись(прожиг) данных в EEPROM"));
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
        commandLoadData();
        return;
    }
    if (command == "LB" || command.startsWith("LOAD BASE")) {
        commandLoadBase64();
        return;
    }
    if (command == "LX" || command.startsWith("LOAD HEX")) {
        commandLoadIntelHex();
        return;
    }
    if (command == "D" || command.startsWith("DUMP")) {
        commandDump();
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
}

void setup() {
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

    oledEEPROM();
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
