#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#include "GyverOLED.h"  // https://github.com/GyverLibs/GyverOLED
#include "EncButton.h"  // https://github.com/GyverLibs/EncButton
#include "main.h"

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif

#define PIN_ENC_BTN         (10)
#define PIN_ENC_S1          (9)
#define PIN_ENC_S2          (8)

GyverOLED<SSD1306_128x64, OLED_BUFFER> display;
EncButtonT<PIN_ENC_S1, PIN_ENC_S2, PIN_ENC_BTN> encoder;

#define VPP         (39)  //PG2
#define CE          (40)  //PG1
#define OE          (41)  //PG0

#define SD_CS       (53)  //

#define CHIP_SIZE   (2048)

#define WRITE_COUNT (5)

void handlerTestMenu();
void handlerProgMenu();

MenuAction menuRoot[] = {
    { " ПРОВЕРКА ", handlerTestMenu },
    { "  ЗАПИСЬ  ", handlerProgMenu },
};
const int menuSize = sizeof(menuRoot)/sizeof(menuRoot[0]);

FileEntry fileEntries[32] = { {"<MENU>"} };
uint8_t fileEntryCount = 1;

static void showRootMenu(int selected) {
    display.clear();
    display.autoPrintln(false);
    display.setCursor(0, 1);
    display.setScale(2);
    for (uint8_t i = 0; i < menuSize; i++) {
        display.invertText(i == selected);
        display.println(menuRoot[i].text);
    }
    display.update();
}

static void loadFileInfo() {
    fileEntryCount = 1;
    File dir = SD.open("/");    
    while (true) {
        File entry =  dir.openNextFile();
        if (! entry) {
            break;
        }
        if (!entry.isDirectory()) {
            strncpy(fileEntries[fileEntryCount].name, entry.name(), 15);
            fileEntries[fileEntryCount].name[15] = 0;
            fileEntryCount++;
            if (fileEntryCount >= sizeof(fileEntries)/sizeof(fileEntries[0])) {
                break;
            }
        }
        entry.close();
    }
    dir.close();
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

inline void setDataInMode() {
    DDRL = B00000000;
    PORTL = B11111111;
}

inline void setDataOutMode() {
    DDRL = B11111111;
}

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

static void writeData(uint16_t addr, byte data) {
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

static bool writeMemoryBin(int selected) {
    File dataFile = SD.open(fileEntries[selected].name);    
    if (dataFile) {
        uint16_t addr = 0;
        bool error = false;
        writeBegin();
        while (!error) {
            int data = dataFile.read();      
            if (data == -1) break;

            noInterrupts();
            writeData(addr++, data);
            interrupts();

            // Serial.print(addr - 1, HEX);
            // Serial.print(":");
            // Serial.print(data, HEX);
            // Serial.println();

            if (addr >= CHIP_SIZE) {
                break;
            }
        }
        writeEnd();
        dataFile.close();
        return true;
    }
    else {
        return false;
    }
}

static bool checkMemoryBin(int selected) {
    bool error = false;
    File dataFile = SD.open(fileEntries[selected].name);    
    if (dataFile) {
        uint16_t addr = 0;
        readBegin();
        while (true) {
            int result = dataFile.read();
            if (result == -1) break;
      
            noInterrupts();
            byte data = readData(addr++);
            interrupts();
            
            // Serial.print(addr - 1, HEX);
            // Serial.print(":");
            // Serial.print(result, HEX);
            // Serial.print(":");
            // Serial.print(data, HEX);
            // Serial.println();

            if (data != result) {
                error = true;
            }
            if (error) {
                break;
            }
        }
        readEnd();
        dataFile.close();
    }
    return !error;
}

void handlerTestMenu() {
    display.clear();
    display.home();
    display.setScale(2);
    display.println("  Нажмите ");
    display.println("кнопку для");
    display.println("  начала");
    display.update();
    
    while (true) {
        encoder.tick();
        if (encoder.click()) {
            break;
        }
    }
    writeBegin();
    
    display.clear();
    display.home();
    display.println("  Нажмите ");
    display.println("кнопку для");
    display.println("завершения");
    display.update();

    while (true) {
        encoder.tick();
        if (encoder.click()) {
            break;
        }
    }
    writeEnd();
}

void handlerProgMenu() {
    static int index = 0;
    int step;
    display.setScale(1);
    while (true) {
        int line = 0;
        if (fileEntryCount > 7) {
            line = (index - 3 >= 0) ? index - 3 : 0;
            line = (index >= fileEntryCount - 4) ? fileEntryCount - 8: line;
        }
        display.clear();
        display.home();
        for (int i = 0; i < 8;  i++) {
            if (line + i >= fileEntryCount) break;
            display.invertText(index == line + i);
            display.println(fileEntries[line + i].name);
        }
        display.update();
        while (true) {
            encoder.tick();
            if (encoder.turn()) {
                step = (encoder.fast()) ? 7: 1;
                if (encoder.dir() > 0) {
                    index += step;
                    index = constrain(index, 0, fileEntryCount - 1);
                } else {
                    index -= step;
                    index = constrain(index, 0, fileEntryCount - 1);
                }
                break;
            }

            if (encoder.click()) {
                if (index == 0) {
                    return;
                }
            }
            if (encoder.hold()) {
                display.clear();
                display.home();
                display.invertText(false);
                display.println(fileEntries[index].name);
                for (int n = 0; n < WRITE_COUNT; n++) {
                    display.print("ЗАПИСЬ: ");
                    display.update();
                    if (writeMemoryBin(index))
                        display.print("ПОРЯДОК");
                    else
                        display.print("ОШИБКА");
                    display.println();
                    display.update();
                }
                display.print("ПРОВЕРКА: ");
                if (checkMemoryBin(index))
                    display.print("ПОРЯДОК");
                else
                    display.print("ОШИБКА");
                display.println();
                display.update();
                delay(5000);
                break;
            }
        }
    }
}

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

    // Initialize Serial
    Serial.begin(57600);
    while (!Serial);
    delay(5000); // Pause for 2 seconds
    
    display.init();
    display.clear();
    display.home();
    display.flipV(true);
    display.flipH(true);
 
    // SD
    Wire.begin();
    if (!SD.begin(SD_CS)) {
        display.println(F("SD failed!"));
        Serial.println(F("SD failed!"));
        display.update();
        for (;;);
    }
    loadFileInfo();
    showRootMenu(0);
}

void loop() {
    static int index = 0;
    int step;

    encoder.tick();
    switch (encoder.action()) {
        case EB_HOLD:
            break;
        case EB_CLICK:
            menuRoot[index].handler();
            showRootMenu(index);
            break;
        case EB_TURN:
            step = (encoder.fast()) ? 7: 1;
            if (encoder.dir() > 0) {
                index += step;
                index = constrain(index, 0, menuSize - 1);
            } else {
                index -= step;
                index = constrain(index, 0, menuSize - 1);
            }
            showRootMenu(index);
            break;
        default:
            break;
    }
}
