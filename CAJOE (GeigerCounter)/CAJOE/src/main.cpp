#include <Arduino.h>

// #define RAD_PIN 2
// #define RAD_PIN A0
#define RAD_PIN 32

#define _ADVANCED_

#ifndef _ADVANCED_
#if defined(__AVR__)
    #if defined(__AVR_ATmega328P__) && RAD_PIN != 2 && RAD_PIN != 3
        #error Для ATmega328P доступны пины: 2, 3
    #endif
    #if defined(__AVR_ATmega2560__) && RAD_PIN != 2 && RAD_PIN != 3 && RAD_PIN != 21 && RAD_PIN != 20 && RAD_PIN != 19 && RAD_PIN != 18
        #error Для ATmega2560 доступны пины: 2, 3, 21, 20, 19, 18
    #endif
#endif

#if defined(ESP32)
#endif

// https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/

#define LOG_PERIOD 15000  
#define MAX_PERIOD 60000  

volatile uint16_t counter;
uint16_t cpm;
uint16_t multiplier;
uint32_t previousMillis;
double usv;

void radInterruptHandler() {
    counter++;
}

void setup() {
    Serial.begin(115200);
    counter = 0;
    cpm = 0;
    multiplier = MAX_PERIOD / LOG_PERIOD;

    attachInterrupt(digitalPinToInterrupt(RAD_PIN), radInterruptHandler, FALLING);
    Serial.println("Start");
}

void loop() {
    uint32_t currentMillis = millis();
    if (currentMillis - previousMillis > LOG_PERIOD) {
        previousMillis = currentMillis;
        cpm = counter * multiplier;
        usv = (double)cpm / 151;

        Serial.print("CPM=");
        Serial.print(cpm);
        Serial.print(", value=");
        Serial.print(usv, 4);
        Serial.print(" uSv/h, counter=");
        Serial.print(counter);
        Serial.println();

        counter = 0;
    }
}
#else
#if defined(__AVR__)

#include <avr_pci.h>

#define LOG_PERIOD 15000  
#define MAX_PERIOD 60000  

volatile uint16_t counter;
uint16_t cpm;
uint16_t multiplier;
uint32_t previousMillis;
double usv;

void radInterruptHandler(uint8_t value) {
    if (value) return;
    counter++;
}

void setup() {
    Serial.begin(115200);
    counter = 0;
    cpm = 0;
    multiplier = MAX_PERIOD / LOG_PERIOD;

    pciSetup(RAD_PIN, radInterruptHandler);
    Serial.println("Start");
}

void loop() {
    uint32_t currentMillis = millis();
    if (currentMillis - previousMillis > LOG_PERIOD) {
        previousMillis = currentMillis;
        cpm = counter * multiplier;
        usv = (double)cpm / 151;

        Serial.print("CPM=");
        Serial.print(cpm);
        Serial.print(", value=");
        Serial.print(usv, 4);
        Serial.print(" uSv/h, counter=");
        Serial.print(counter);
        Serial.println();

        counter = 0;
    }
}
#else

#include <esp32_pcnt.h>

#define LOG_PERIOD 1000//15000  
#define MAX_PERIOD 60000  

uint16_t cpm;
uint16_t multiplier;
double usv;

pcnt_unit_t pcnt_unit = PCNT_UNIT_0;

void pulseCounterHandler(void* parameter) {
    gpio_num_t pin = (gpio_num_t)RAD_PIN;
    cpm = 0;
    multiplier = MAX_PERIOD / LOG_PERIOD;

    pcntSetup(pin, pcnt_unit, PCNT_CHANNEL_0);
    for (;;) {
        delay(LOG_PERIOD);

        int16_t counter = 0;
        pcnt_get_counter_value(pcnt_unit, &counter);
        // pcnt_counter_pause(pcnt_unit);
        // pcnt_counter_clear(pcnt_unit);
        // pcnt_counter_resume(pcnt_unit);
        cpm = counter * multiplier;
        usv = (double)cpm / 151;

        Serial.print("CPM=");
        Serial.print(cpm);
        Serial.print(", value=");
        Serial.print(usv, 4);
        Serial.print(" uSv/h, counter=");
        Serial.print(counter);
        Serial.println();
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("BEGIN");
    
    gpio_num_t pcnt_pin = (gpio_num_t)RAD_PIN;
    Serial.println("Start ADVANCED");

    TaskHandle_t    task;
    xTaskCreate(pulseCounterHandler, "pcnt", 4096, nullptr, 100, &task);
}

void loop() {
    delay(MAX_PERIOD);
}

#endif

#endif