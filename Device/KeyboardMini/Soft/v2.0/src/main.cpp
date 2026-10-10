#include <Arduino.h>
#include <Wire.h>
#include <Keyboard.h>
#include <GyverIO.h>
#include <FastLED.h>
#include <PinChangeInterrupt.h>

// #define DEBUG_INFO
#define KEYBOARD_V2

#define MAX_KEY         16
#define FUNC_KEYCODE    0xFFFF
#define NO_KEYCODE      0x0000

#ifdef KEYBOARD_V2

#define STRIP_PIN   (4)   // пин ленты

CRGB leds[MAX_KEY];

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
    
    Wire.begin();
    Wire.setClock(400000);
    
    Wire.beginTransmission(0x38);
    Wire.write(B11111111);    //Конфигурация, все порты PCF8574P как вход
    Wire.endTransmission();

    Wire.beginTransmission(0x39);
    Wire.write(B11111111);    //Конфигурация, все порты PCF8574P как вход
    Wire.endTransmission();
    
    Keyboard.begin();

    attachPCINT(digitalPinToPCINT(14), keyboard0, CHANGE);
    attachPCINT(digitalPinToPCINT(16), keyboard1, CHANGE);

    FastLED.addLeds<WS2812, STRIP_PIN, GRB>(leds, MAX_KEY);  // GRB ordering is typical
}

void loop() {
    fill_solid(leds, MAX_KEY, CRGB::Red);
    FastLED.show();
    delay(1000);

    fill_solid(leds, MAX_KEY, CRGB::Green);
    FastLED.show();
    delay(1000);

    fill_solid(leds, MAX_KEY, CRGB::Blue);
    FastLED.show();
    delay(1000);
}

#else
volatile char   valueKeyCode    = 0;
int8_t  indexFuncKey    = -1;

uint16_t layoutDef[MAX_KEY] {
    makeWord(0, KEY_ESC),
    makeWord(0, KEY_BACKSPACE),
    makeWord(0, KEY_TAB),
    makeWord(0, KEY_RETURN),

    makeWord(KEY_LEFT_CTRL, 'c'),
    makeWord(KEY_LEFT_CTRL, 'v'),
    NO_KEYCODE,
    NO_KEYCODE,

    makeWord(KEY_LEFT_ALT, 0),
    makeWord(0, 'q'),
    makeWord(0, KEY_UP_ARROW),
    makeWord(0, 'e'),
    
    FUNC_KEYCODE,
    makeWord(0, KEY_LEFT_ARROW),
    makeWord(0, KEY_DOWN_ARROW),
    makeWord(0, KEY_RIGHT_ARROW),
};

typedef struct _KEYCODE_EXT_ {
    uint8_t     lo;
    uint8_t     hi;
} KEYCODE_EXT;

typedef union _KEYCODE_ {
    KEYCODE_EXT ext;
    uint16_t    word;
} KEYCODE; 

typedef struct _KEYDATA_ {
    uint32_t    time;
    uint8_t     pin;
    uint8_t     pressed;
    KEYCODE     keyCode; 
} KEYDATA;


// Распиновка кнопок на плате v2.0
// ┌─────┬─────┬─────┬─────┐
// │  D2 │  D9 │ D18 │ D10 │
// ├─────┼─────┼─────┼─────┤
// │  D3 │  D8 │ D19 │ D16 │
// ├─────┼─────┼─────┼─────┤
// │  D4 │  D7 │ D20 │ D14 │
// ├─────┼─────┼─────┼─────┤
// │  D5 │  D6 │ D21 │ D15 │
// └─────┴─────┴─────┴─────┘
KEYDATA keys[MAX_KEY] = {
    { .time = 0, .pin =  2, .pressed = 0 },
    { .time = 0, .pin =  9, .pressed = 0 },
    { .time = 0, .pin = 18, .pressed = 0 },
    { .time = 0, .pin = 10, .pressed = 0 },

    { .time = 0, .pin =  3, .pressed = 0 },
    { .time = 0, .pin =  8, .pressed = 0 },
    { .time = 0, .pin = 19, .pressed = 0 },
    { .time = 0, .pin = 16, .pressed = 0 },


    { .time = 0, .pin =  4, .pressed = 0 },
    { .time = 0, .pin =  7, .pressed = 0 },
    { .time = 0, .pin = 20, .pressed = 0 },
    { .time = 0, .pin = 14, .pressed = 0 },

    { .time = 0, .pin =  5, .pressed = 0 },
    { .time = 0, .pin =  6, .pressed = 0 },
    { .time = 0, .pin = 21, .pressed = 0 },
    { .time = 0, .pin = 15, .pressed = 0 },
};

#ifdef DEBUG_INFO
char text[512];
#endif

void setLayout(uint16_t layout[]) {
    for (int16_t i = 0; i < MAX_KEY; i++) {
        keys[i].keyCode.word = layout[i];
        if (layout[i] == FUNC_KEYCODE) {
            indexFuncKey = i;
#ifdef DEBUG_INFO
            Serial.println(indexFuncKey);
#endif
        }
    }
}
void setup() {
#ifdef DEBUG_INFO
    // Для мониторинга скорость ДОЛЖНА быть 9600, после заливки порт меняется,
    // специфика работы micro, по скрости порта определяется режим
    Serial.begin(9600);
    while (!Serial);
    Serial.println(F("Start"));
#endif

    for (int i = 0; i < MAX_KEY; i++) {
        gio::init(keys[i].pin, INPUT_PULLUP);
    }
    setLayout(layoutDef);
    Keyboard.begin();
}

bool proccessFunkKeyRelease(uint8_t code) {
    switch (code) {
        case KEY_UP_ARROW:
        case KEY_DOWN_ARROW:
        case KEY_LEFT_ARROW:
        case KEY_RIGHT_ARROW:
            return true;
    }
    return false;
}

bool proccessFunkKeyPress(uint8_t code) {
    switch (code) {
        case KEY_UP_ARROW:
            if (valueKeyCode > 0) {
                Keyboard.write(KEY_BACKSPACE);
            }
            if (valueKeyCode == 0) {
                valueKeyCode = 'a' - 1;
            }
            valueKeyCode += 1;
            if (valueKeyCode > 'z') {
                valueKeyCode = 'a';
            }
            Keyboard.write(valueKeyCode);
            return true;

        case KEY_DOWN_ARROW:
            if (valueKeyCode > 0) {
                Keyboard.write(KEY_BACKSPACE);
            }
            if (valueKeyCode == 0) {
                valueKeyCode = 'z' + 1;
            }
            valueKeyCode --;
            if (valueKeyCode < 'a') {
                valueKeyCode = 'z';
            }
            Keyboard.write(valueKeyCode);
            return true;

        case KEY_LEFT_ARROW:
            if (valueKeyCode > 0) {
                Keyboard.write(KEY_BACKSPACE);
            }
            if (valueKeyCode == 0) {
                valueKeyCode = 'm';
            }
            valueKeyCode -= 4;
            if (valueKeyCode < 'a') {
                valueKeyCode = 'z';
            }
            Keyboard.write(valueKeyCode);
            return true;

        case KEY_RIGHT_ARROW:
            if (valueKeyCode > 0) {
                Keyboard.write(KEY_BACKSPACE);
            }
            if (valueKeyCode == 0) {
                valueKeyCode = 'm';
            }
            valueKeyCode += 4;
            if (valueKeyCode > 'z') {
                valueKeyCode = 'a';
            }
            Keyboard.write(valueKeyCode);
            return true;
    }
    return false;
}

void loop() {
    uint32_t time = millis();
    for (int i = 0; i < MAX_KEY; i++) {
        uint8_t value = !gio::read(keys[i].pin);
        if (value != keys[i].pressed) {
            if (time - keys[i].time > 50) {
                keys[i].pressed = value;
                if (keys[i].keyCode.word) {
                    if (keys[i].keyCode.word == FUNC_KEYCODE) {
                        if (!value) {
                            Keyboard.releaseAll();
                            valueKeyCode = 0;
                        }
                    }
                    else {
                        if (value) {
                            if (keys[indexFuncKey].pressed) {
                                proccessFunkKeyPress(keys[i].keyCode.ext.lo);
                            }
                            else {
                                if (keys[i].keyCode.ext.hi) Keyboard.press(keys[i].keyCode.ext.hi);
                                if (keys[i].keyCode.ext.lo) Keyboard.press(keys[i].keyCode.ext.lo);
#ifdef DEBUG_INFO
                                sprintf(text, "index=%d, pin=%d, value=%d, code=%02X =press", i, keys[i].pin, value, (uint8_t)keys[i].keyCode.word);
                                Serial.println(text);
                                Serial.print("ERROR:");
                                Serial.println(Keyboard.getWriteError());
#endif
                            }
                        }
                        else {
                            if (keys[indexFuncKey].pressed) {
                                proccessFunkKeyRelease(keys[i].keyCode.ext.lo);
                            }
                            else {
                                // Keyboard.releaseAll();
                                if (keys[i].keyCode.ext.lo) Keyboard.release(keys[i].keyCode.ext.lo);
                                if (keys[i].keyCode.ext.hi) Keyboard.release(keys[i].keyCode.ext.hi);
#ifdef DEBUG_INFO
                                sprintf(text, "index=%d, pin=%d, value=%d, code=%02X =release", i, keys[i].pin, value, (uint8_t)keys[i].keyCode.word);
                                Serial.println(text);
                                Serial.print("ERROR:");
                                Serial.println(Keyboard.getWriteError());
#endif
                            }
                        }
                    }
                }
            }
            keys[i].time = time;
        }
    }
}
#endif