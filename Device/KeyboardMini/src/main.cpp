#include <Arduino.h>
#include <Keyboard.h>
#include <GyverIO.h>

#define MAX_KEY 16

typedef struct _KEYDATA_ {
    int16_t     pin;
    int16_t     value;
    uint32_t    time;
} KEYDATA;


KEYDATA keys[MAX_KEY] = {
    { .pin = 2, .value = 1, .time = 0 },    // PD1
    { .pin = 3, .value = 1, .time = 0 },    // PD0
    { .pin = 4, .value = 1, .time = 0 },    // PD4
    { .pin = 5, .value = 1, .time = 0 },    // PC6
    { .pin = 6, .value = 1, .time = 0 },    // PD7
    { .pin = 7, .value = 1, .time = 0 },    // PE6
    { .pin = 8, .value = 1, .time = 0 },    // PB4
    { .pin = 9, .value = 1, .time = 0 },    // PB5
    { .pin = 10, .value = 1, .time = 0 },    // PB6
    { .pin = 14, .value = 1, .time = 0 },    // PB3
    { .pin = 15, .value = 1, .time = 0 },    // PB1
    { .pin = 16, .value = 1, .time = 0 },    // PB2
    { .pin = 18, .value = 1, .time = 0 },    // PF7
    { .pin = 19, .value = 1, .time = 0 },    // PF6
    { .pin = 20, .value = 1, .time = 0 },    // PF5
    { .pin = 21, .value = 1, .time = 0 },    // PF4
};

void setup() {
    Serial.begin(115200);
    Keyboard.begin();
    for (int i = 0; i < MAX_KEY; i++) {
        gio::init(keys[i].pin, INPUT_PULLUP);
    }
    Serial.println(F("Start"));
}

void loop() {
    uint32_t time = millis();
    for (int i = 0; i < MAX_KEY; i++) {
        int16_t value = gio::read(keys[i].pin);
        if (value != keys[i].value) {
            if (time - keys[i].time > 50) {
                Serial.println(keys[i].pin);
                keys[i].value = value;
            }
            keys[i].time = time;
        }
    }
}
