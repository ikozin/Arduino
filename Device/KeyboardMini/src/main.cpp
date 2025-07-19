#include <Arduino.h>
#include <Keyboard.h>
#include <GyverIO.h>

// #define DEBUG_INFO
#define PCB_V_1_0
// #define PCB_V_2_0

#define MAX_KEY         16
#define FUNC_KEYCODE    0xFF

volatile char   valueKeyCode    = 0;
int8_t  indexFuncKey    = -1;

uint16_t layoutDef[MAX_KEY] {
    KEY_ESC,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_RETURN,

    ' ',
    ' ',
    ' ',
    ' ',

    ' ',
    'q',
    KEY_UP_ARROW,
    'e',
    
    FUNC_KEYCODE,
    KEY_LEFT_ARROW,
    KEY_DOWN_ARROW,
    KEY_RIGHT_ARROW,
};

typedef struct _KEYDATA_ {
    uint32_t    time;
    uint8_t     pin;
    uint8_t     pressed;
    uint8_t     keyCode;
} KEYDATA;


#ifdef PCB_V_1_0
// Распиновка кнопок на плате v1.0
// ┌─────┬─────┬─────┬─────┐
// │  D2 │  D3 │ D21 │ D10 │
// ├─────┼─────┼─────┼─────┤
// │  D4 │  D5 │ D20 │ D16 │
// ├─────┼─────┼─────┼─────┤
// │  D6 │  D7 │ D19 │ D14 │
// ├─────┼─────┼─────┼─────┤
// │  D8 │  D9 │ D18 │ D15 │
// └─────┴─────┴─────┴─────┘
KEYDATA keys[MAX_KEY] = {
    { .time = 0, .pin =  2, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  3, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 21, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 10, .pressed = 0, .keyCode = 0 },

    { .time = 0, .pin =  4, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  5, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 20, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 16, .pressed = 0, .keyCode = 0 },

    { .time = 0, .pin =  6, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  7, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 19, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 14, .pressed = 0, .keyCode = 0 },

    { .time = 0, .pin =  8, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  9, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 18, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 15, .pressed = 0, .keyCode = 0 },
};
#endif

#ifdef PCB_V_2_0
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
    { .time = 0, .pin =  2, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  9, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 18, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 10, .pressed = 0, .keyCode = 0 },

    { .time = 0, .pin =  3, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  8, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 19, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 16, .pressed = 0, .keyCode = 0 },


    { .time = 0, .pin =  4, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  7, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 20, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 14, .pressed = 0, .keyCode = 0 },

    { .time = 0, .pin =  5, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin =  6, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 21, .pressed = 0, .keyCode = 0 },
    { .time = 0, .pin = 15, .pressed = 0, .keyCode = 0 },
};
#endif

#ifdef DEBUG_INFO
char text[512];
#endif

void setLayout(uint16_t layout[]) {
    for (int16_t i = 0; i < MAX_KEY; i++) {
        keys[i].keyCode = layout[i];
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

    Keyboard.begin();
    for (int i = 0; i < MAX_KEY; i++) {
        gio::init(keys[i].pin, INPUT_PULLUP);
    }
    setLayout(layoutDef);
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
                if (keys[i].keyCode) {

                    if (keys[i].keyCode == FUNC_KEYCODE) {
                        if (!value) {
                            Keyboard.releaseAll();
                            valueKeyCode = 0;
                        }
                    }
                    else {
                        if (value) {
                            if (keys[indexFuncKey].pressed) {
                                proccessFunkKeyPress(keys[i].keyCode);
                            }
                            else {
                                Keyboard.press(keys[i].keyCode);
#ifdef DEBUG_INFO
                                sprintf(text, "index=%d, pin=%d, value=%d, code=%02X =press", i, keys[i].pin, value, (uint8_t)keys[i].keyCode);
                                Serial.println(text);
#endif
                            }
                        }
                        else {
                            if (keys[indexFuncKey].pressed) {
                                proccessFunkKeyRelease(keys[i].keyCode);
                            }
                            else {
                                Keyboard.release(keys[i].keyCode);
#ifdef DEBUG_INFO
                                sprintf(text, "index=%d, pin=%d, value=%d, code=%02X =release", i, keys[i].pin, value, (uint8_t)keys[i].keyCode);
                                Serial.println(text);
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
