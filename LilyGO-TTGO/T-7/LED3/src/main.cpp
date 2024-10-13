#include <Arduino.h>
#include "GyverIO.h"

#define PIN_RED     (16)
#define PIN_GREEN   (17)

int freq = 5000;
int ledChannelRed   = 14;
int ledChannelGreen = 15;

int resolution = 8;

int dutyCycleRed = 32;
int dutyCycleGreen = 4;

void setup() {
    Serial.begin(115200);
    // gio::mode(PIN_RED, OUTPUT);
    // gio::mode(PIN_GREEN, OUTPUT);
    // gio::low(PIN_RED);
    // gio::low(PIN_GREEN);

    ledcSetup(ledChannelRed, freq, resolution);
    ledcSetup(ledChannelGreen, freq, resolution);

    ledcAttachPin(PIN_RED, ledChannelRed);
    ledcAttachPin(PIN_GREEN, ledChannelGreen);
}

void loop() {
    ledcWrite(ledChannelRed, 0);
    ledcWrite(ledChannelGreen, 0);
    delay(1000);
    ledcWrite(ledChannelRed, 0);
    ledcWrite(ledChannelGreen, dutyCycleGreen);
    delay(1000);
    ledcWrite(ledChannelRed, dutyCycleRed);
    ledcWrite(ledChannelGreen, dutyCycleGreen);
    delay(1000);
    ledcWrite(ledChannelRed, dutyCycleRed);
    ledcWrite(ledChannelGreen, 0);
    delay(1000);

    // gio::low(PIN_RED);
    // gio::high(PIN_GREEN);
    // delay(1000);
    // gio::high(PIN_RED);
    // gio::high(PIN_GREEN);
    // delay(1000);
    // gio::high(PIN_RED);
    // gio::low(PIN_GREEN);
    // delay(1000);
}

