#include <Arduino.h>
#include <TinyWireM.h>
#include <microLED.h>
#include <color_utility.h>


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
[flag] [1..21 color]

[flag] [time] [color]
[flag] [time] [color][count][1..count]
[flag] [time] [1..21 color]
*/

#define MASK_TIME   (0x80U)
#define MASK_MODE   (0x7FU)

#define MODE_FILL   (0)
#define MODE_COUNT  (1)
#define MODE_RAW    (2)


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

uint8_t  data[sizeof(LedColorRaw)+1];
uint32_t address = 0x0000;

//#define BUFFER_SIZE   sizeof(_data)
//static_assert(false, "ERROR");

#define STRIP_PIN PB1  // пин ленты
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB, CLI_HIGH, SAVE_MILLIS> _strip;

uint8_t readEepromByte(uint32_t& addr) {
  TinyWireM.beginTransmission(DEVICE_EEPROM);
  TinyWireM.write(highByte(addr));
  TinyWireM.write(lowByte(addr));
  TinyWireM.endTransmission();
  delay(10);
  addr += sizeof(uint8_t);
  TinyWireM.requestFrom(DEVICE_EEPROM,1);
  delay(5);
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
  for (uint16_t i = 0; i < size; i++ ) {
    if (TinyWireM.available()) buffer[i] = TinyWireM.read();
    else buffer[i] = 0xFF;
  }
}

void setup() {
  TinyWireM.begin();
  _strip.fill(COLORS::mRed);
  _strip.show();
  delay(200);
  _strip.fill(COLORS::mGreen);
  _strip.show();
  delay(200);
  _strip.fill(COLORS::mBlue);
  _strip.show();
  delay(200);
  _strip.fill(COLORS::mBlack);
  _strip.show();
  delay(1000);
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
  for (int i = 0; i < sizeof(data); i++) data[i] = 0xFF;
  switch (flag & MASK_MODE)
  {
    case MODE_FILL: {
      readEepromData(address, data, sizeof(LedColor));
      LedColor* ptr = reinterpret_cast<LedColor*>(data);
      mData color = mData(ptr->r, ptr->g, ptr->b);

      _strip.fill(color);
      break;
    }
    case MODE_COUNT: {
      readEepromData(address, data, sizeof(LedColorCount));
      LedColorCount* ptr = reinterpret_cast<LedColorCount*>(data);
      mData color = mData(ptr->Color.r, ptr->Color.g, ptr->Color.b);

      uint8_t count = ptr->Count;
      readEepromData(address, data, count);
      for (int i = 0; i < count; i++) {
        _strip.set(data[i], color);
      }
      break;
    }
    case MODE_RAW: {
      readEepromData(address, data, sizeof(LedColorRaw));
      LedColorRaw* ptr = reinterpret_cast<LedColorRaw*>(data);
      for (int i = 0; i < NUMLEDS; i++) {
        mData color = mData(ptr->LED[i].r, ptr->LED[i].g, ptr->LED[i].b);
        _strip.set(i, color);
      }
      break;
    }
    default:
      address = 0;
      return;
  }
  
  if (pause) {
    _strip.show();
    delay(pause);
  }

  if (address >= 0xFFFFU) {
    address = 0;
    return;
  }
}