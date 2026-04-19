#include <Arduino.h>
#include <TinyWireM.h>
#define COLOR_DEBTH 3
#include <microLED.h>   // подключаем библу
#include <color_utility.h>


/*
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

typedef struct __attribute__((packed)) {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} COLOR_LED;

typedef struct __attribute__((packed)) {
  uint16_t  time;
  COLOR_LED LED[NUMLEDS];
} STRIP_DATA;

STRIP_DATA  _data;
uint16_t _address = 0x0000;

//#define BUFFER_SIZE   sizeof(_data)
//static_assert(false, "ERROR");

#define STRIP_PIN PB1  // пин ленты
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB> _strip;

void EEPROM_Read(uint16_t address) {
  uint8_t* buffer = reinterpret_cast<uint8_t*>(&_data);
  TinyWireM.beginTransmission(DEVICE_EEPROM);
  TinyWireM.write(highByte(address));
  TinyWireM.write(lowByte(address));
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(DEVICE_EEPROM,(uint8_t)sizeof(_data));
  for (uint16_t i = 0; i < sizeof(_data); i++ ) {
    if (TinyWireM.available()) buffer[i] = TinyWireM.read();
  }
}

void setup() {
  TinyWireM.begin();

  _strip.fill(COLORS::mRed);
  _strip.show();
  delay(250);
  _strip.fill(COLORS::mGreen);
  _strip.show();
  delay(250);
  _strip.fill(COLORS::mBlue);
  _strip.show();
  delay(250);
  _strip.fill(COLORS::mBlack);
  _strip.show();
  delay(250);
}

void loop() {
  EEPROM_Read(_address);
  if (_data.time == 0xFFFF) {
    _address = 0;
    return;
  }
  
  for (int i = 0; i < NUMLEDS; i++) _strip.set(i, mRGB(_data.LED[i].r, _data.LED[i].g, _data.LED[i].b));
  _strip.show();
  delay(_data.time);

  uint16_t next = _address += sizeof(_data);
  if (next < _address) {
    _address = 0;
    return;
  }
  _address = next;
}