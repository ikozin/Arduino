#include <Arduino.h>
#include <Wire.h>
#include <Keyboard.h>
#include <GyverIO.h>
#include <FastLED.h>
#include <PinChangeInterrupt.h>

#define DEBUG_INFO

#define MAX_KEY         16
#define FUNC_KEYCODE    0xFFFF
#define NO_KEYCODE      0x0000

#define STRIP_PIN   (4)   // пин ленты
CRGB leds[MAX_KEY];
CRGB colors[] = { CRGB::Red, CRGB::Yellow, CRGB::Green, CRGB::Cyan, CRGB::Blue , CRGB::Magenta };
const size_t colCnt = sizeof(colors)/sizeof(colors[0]);

volatile byte keyCnt0 = 0;
volatile byte keyCnt1 = 0;

void keyboard0(void) {
    keyCnt0++;
}

void keyboard1(void) {
    keyCnt1++;
}

void setup() {
#ifdef DEBUG_INFO
    // Для мониторинга скорость ДОЛЖНА быть 9600, после заливки порт меняется,
    // специфика работы micro, по скрости порта определяется режим
    Serial.begin(9600);
    while (!Serial);
    Serial.println(F("Start"));
#endif
    FastLED.addLeds<WS2812, STRIP_PIN, GRB>(leds, MAX_KEY);  // GRB ordering is typical
    fill_solid(leds, MAX_KEY, CRGB::White);
    FastLED.show();
    delay(500);
    fill_solid(leds, MAX_KEY, CRGB::Black);
    FastLED.show();
    delay(500);

    Wire.begin();
    Wire.setClock(400000);
    
    Wire.beginTransmission(0x20);
    Wire.write(B11111111);    //Конфигурация, все порты PCF8574P как вход
    Wire.endTransmission();

    Wire.beginTransmission(0x21);
    Wire.write(B11111111);    //Конфигурация, все порты PCF8574P как вход
    Wire.endTransmission();
    
    Keyboard.begin();

    attachPCINT(digitalPinToPCINT(16), keyboard0, CHANGE);
    attachPCINT(digitalPinToPCINT(14), keyboard1, CHANGE);
    delay(100);
    keyCnt0 = 0;
    keyCnt1 = 0;
}


void loop() {
    static int index = 0;
    static int timeCnt = 0;
    if (timeCnt == 0) {
        fill_solid(leds, MAX_KEY, colors[index++]);
        FastLED.show();
        if (index == colCnt) index = 0;
    }
    Serial.print(keyCnt0);
    Serial.print(',');
    Serial.print(keyCnt1);
    Serial.println();
    keyCnt0 = 0;
    keyCnt1 = 0;
    delay(100);
    timeCnt++;
    if (timeCnt == 10) timeCnt = 0;
}
