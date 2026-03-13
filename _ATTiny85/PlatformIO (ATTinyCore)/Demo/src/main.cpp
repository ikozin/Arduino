#include <Arduino.h>

#define PIN_LED1    PB0
#define PIN_LED2    PB1

#define PIN_PWR     PB2

#define PIN_BTN     PB4

bool state = false;

static void ledGreen() {
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED1, HIGH);
}

static void ledRed() {
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, HIGH);
}

static inline void powerOn() {
    digitalWrite(PIN_PWR, HIGH);
    ledGreen();
}

static inline void powerOff() {
    digitalWrite(PIN_PWR, LOW);
    ledRed();
}

void setup() {
    // LED
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    // POWER
    pinMode(PIN_PWR, OUTPUT);
    // BUTTON
    pinMode(PIN_BTN, INPUT);

    ledRed();
}

void loop() {
    // Проверяем нажатие
    if (digitalRead(PIN_BTN) == LOW) {
        // Ждем отжатия
        while (digitalRead(PIN_BTN) != HIGH) delay(10);
        // Переключаем состояние
        state = !state;
        if (state) {
            powerOn();
        }
        else {
            powerOff();
        }
        // Задержка для исключения дребезга
        delay(250);
    }
}