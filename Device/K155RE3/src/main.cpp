#include <Arduino.h>
#include <WString.h>
#include <StringUtils.h>
#include <ctype.h>

#define ECHO
#define ROMSIZE         32


uint8_t data[ROMSIZE] {};

String cmd;
char terminator = 0;
char text[64];

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
    Serial.println(F("OK"));
    Serial.flush();
}

void commandWrite() {
    Serial.println(F("OK"));
    Serial.flush();
}

void commandHelp() {
    Serial.println(F("H, ?, HELP - вывод подсказки по командам"));
    Serial.println(F("LB, LOAD BASE - загрузка данных через COM порт в BASE64 формате"));
    Serial.println(F("LX, LOAD HEX  - загрузка данных через COM порт в Intel Hex формате"));
    Serial.println(F("D, DUMP  - просмотр данных для записи(прожига)"));
    Serial.println(F("R, READ  - считывание данных из К155РЕ3"));
    Serial.println(F("W, WRITE - запись(прожиг) данных в К155РЕ3"));
    Serial.flush();
}

void proccessCommand(String& command) {
    Serial.println(command);
    Serial.flush();
    if (command == "H" || command == "?" || command.startsWith("HELP")) {
        commandHelp();
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
    cmd.reserve(127);
    Serial.begin(9600);
    while(!Serial) delay(1000);
    Serial.println(F("START, К155РЕ3 EEPROM:32x8"));
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
