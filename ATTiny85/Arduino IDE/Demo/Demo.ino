// #include <Arduino.h>
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
// void setup() {
//   pinMode(PB0, OUTPUT);
//   pinMode(PB1, OUTPUT);
//   digitalWrite(PB0, LOW);
//   digitalWrite(PB1, LOW);
// }

// void loop() {
//   digitalWrite(PB1, LOW);
//   digitalWrite(PB0, HIGH);
//   delay(500);
//   digitalWrite(PB0, LOW);
//   digitalWrite(PB1, HIGH);
//   delay(500);
// }

#include <Arduino.h>
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

#define STRIP_PIN PB1  // пин ленты
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB> _strip;

void setup() {
  pinMode(STRIP_PIN, OUTPUT);
}

void loop() {
  _strip.fill(COLORS::mRed);
  _strip.show();
  delay(1000);
  _strip.fill(COLORS::mGreen);
  _strip.show();
  delay(1000);
  _strip.fill(COLORS::mBlue);
  _strip.show();
  delay(1000);
  _strip.fill(COLORS::mBlack);
  _strip.show();
  delay(1000);
}