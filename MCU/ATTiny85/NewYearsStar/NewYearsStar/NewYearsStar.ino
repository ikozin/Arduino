#include <Arduino.h>
#include <TinyWireM.h>
#include <FastLED.h>

/*
Необходимо установить поддержку ATTiny85 для Arduino IDE https://github.com/damellis/attiny

Параметры для прошивки
Board: "ATtiny25/45/85" 
Clock: "Internal 8 MHz"
Processor: "ATtiny85"
Programmer: "Arduino as ISP"

 ┌───────┬───────┬───────┬───────┬────┬────────┬─────┐    ┌──────────┐    ┌─────┬─────────────────────────────────────────────┐
 │       │ ADC0  │       │ RESET │ A0 │ PCINT5 │ PB5 │   ─┤          ├─   │ +5V │                                             │
 ├───────┼───────┼───────┼───────┼────┼────────┼─────┤    │          │    ├─────┼────────┬────┬──────┬─────┬───────────┬──────┤
 │ XTAL1 │ ADC3  │       │       │ A3 │ PCINT3 │ PB3 │   ─┤ ATTINY85 ├─   │ PB2 │ PCINT2 │ A1 │ SCK  │ SCL │           │ ADC1 │
 ├───────┼───────┼───────┼───────┼────┼────────┼─────┤    │          │    ├─────┼────────┼────┼──────┼─────┼───────────┼──────┤
 │ XTAL2 │ ADC2  │  OC1B │       │ A2 │ PCINT4 │ PB4 │   ─┤          ├─   │ PB1 │ PCINT1 │    │ MISO │     │ OC0B/OC1A │      │
 ├───────┴───────┴───────┴───────┴────┴────────┼─────┤    │          │    ├─────┼────────┼────┼──────┼─────┼───────────┤──────┤
 │                                             │ GND │   ─┤          ├─   │ PB0 │ PCINT0 │    │ MOSI │ SDA │    OC0A   │ AREF │
 └─────────────────────────────────────────────┴─────┘    └──────────┘    └─────┴────────┴────┴──────┴─────┴───────────┴──────┘
*/

// константы для удобства
#define NUMLEDS 21      // кол-во светодиодов
#define DEVICE_EEPROM 0x50
/*
[flag] [color]
[flag] [color][count][1..count]
[flag] [color][color][count][1..count]
[flag] [1..21 color]

[flag] [time] [color]
[flag] [time] [color][count][1..count]
[flag] [time] [color][color][count][1..count]
[flag] [time] [1..21 color]
*/

#define MASK_TIME   (0x80U)
#define MASK_MODE   (0x7FU)

#define MODE_FILL       (0)
#define MODE_COUNT      (1)
#define MODE_RAW        (2)
#define MODE_FILL_COUNT (3)


//////////////////////////////////////////////////////////////
typedef struct __attribute__((packed)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} LedColor;

typedef struct __attribute__((packed)) {
    LedColor Color;
    uint8_t Count;
} LedColorCount;

typedef struct __attribute__((packed)) {
    LedColor LED[NUMLEDS];
} LedColorRaw;

typedef struct __attribute__((packed)) {
    LedColor        Back;
    LedColorCount   data;
} LedColorColorCount;

uint8_t  data[32];
uint32_t address = 0x0000;

//#define BUFFER_SIZE   sizeof(_data)
//static_assert(false, "ERROR");

#define STRIP_PIN PB1  // пин ленты

CRGB leds[NUMLEDS];

uint8_t readEepromByte(uint32_t& addr) {
    TinyWireM.beginTransmission(DEVICE_EEPROM);
    TinyWireM.write(highByte(addr));
    TinyWireM.write(lowByte(addr));
    TinyWireM.endTransmission();
    delay(5);
    addr += sizeof(uint8_t);
    TinyWireM.requestFrom(DEVICE_EEPROM,1);
    return TinyWireM.receive();
}

uint16_t readEepromWord(uint32_t& addr) {
    uint16_t result = 0;
    TinyWireM.beginTransmission(DEVICE_EEPROM);
    TinyWireM.write(highByte(addr));
    TinyWireM.write(lowByte(addr));
    TinyWireM.endTransmission();
    delay(5);
    addr += sizeof(uint16_t);
    TinyWireM.requestFrom(DEVICE_EEPROM, 2);
    result = TinyWireM.receive();
    result |= (TinyWireM.receive() << 8);
    return result;
}

void readEepromData(uint32_t& addr, uint8_t* buffer, uint8_t size) { 
    TinyWireM.beginTransmission(DEVICE_EEPROM);
    TinyWireM.write(highByte(addr));
    TinyWireM.write(lowByte(addr));
    TinyWireM.endTransmission();
    delay(5);
    addr += size;
    TinyWireM.requestFrom(DEVICE_EEPROM, size);
    delay(5);
    for (uint16_t i = 0; i < size; i++ ) {
        if (TinyWireM.available()) buffer[i] = TinyWireM.receive();
        else buffer[i] = 0;
    }
}

void setup() {
    TinyWireM.begin();
    FastLED.addLeds<WS2812, STRIP_PIN, GRB>(leds, NUMLEDS);  // GRB ordering is typical

    fill_solid(leds, NUMLEDS, CRGB::Red);
    FastLED.show();
    delay(200);

    fill_solid(leds, NUMLEDS, CRGB::Green);
    FastLED.show();
    delay(200);

    fill_solid(leds, NUMLEDS, CRGB::Blue);
    FastLED.show();
    delay(200);
}

void loop() {
    uint16_t pause = 0;
    uint8_t flag = readEepromByte(address);
    if (flag == 0xFFU) {
        address = 0;
        return;
    }
    if (flag & MASK_TIME) {
        pause = readEepromWord(address);
    }
    switch (flag & MASK_MODE)
    {
        case MODE_FILL: {
            readEepromData(address, data, sizeof(LedColor));
            LedColor* ptr = reinterpret_cast<LedColor*>(data);
            fill_solid(leds, NUMLEDS, CRGB(ptr->r, ptr->g, ptr->b));
            break;
        }
        case MODE_COUNT: {
            readEepromData(address, data, sizeof(LedColorCount));
            LedColorCount* ptr = reinterpret_cast<LedColorCount*>(data);
            CRGB color = CRGB(ptr->Color.r, ptr->Color.g, ptr->Color.b);
            uint8_t count = ptr->Count;
            if (count) readEepromData(address, data, count);
            for (int i = 0; i < count; i++) {
                leds[data[i]] = color;
            }
            break;
        }
        case MODE_RAW: {
            LedColor* ptr = reinterpret_cast<LedColor*>(data);
            for (int i = 0; i < NUMLEDS; i++) {
                readEepromData(address, data, sizeof(LedColor));
                leds[i] = CRGB(ptr->r, ptr->g, ptr->b);
            }
            break;
        }
        case MODE_FILL_COUNT: {
            readEepromData(address, data, sizeof(LedColorColorCount));
            LedColorColorCount* ptr = reinterpret_cast<LedColorColorCount*>(data);
            CRGB back = CRGB(ptr->Back.r, ptr->Back.g, ptr->Back.b);
            CRGB color = CRGB(ptr->data.Color.r, ptr->data.Color.g, ptr->data.Color.b);
            uint8_t count = ptr->data.Count;
            if (count) readEepromData(address, data, count);
            fill_solid(leds, NUMLEDS, back);
            for (int i = 0; i < count; i++) {
                leds[data[i]] = color;
            }
            break;
        }
        default:
            address = 0;
            return;
    }
 
    if (pause) {
        FastLED.show();
        delay(pause);
    }
    if (address >= 0xFFFFU) {
        address = 0;
        return;
    }
}