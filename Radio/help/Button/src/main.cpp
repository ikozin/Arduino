#include <Arduino.h>

uint8_t pins[] = { 8, 9, 10, 11, 12 };
volatile uint8_t values[sizeof(pins)] = { 0, 0, 0, 0, 0 };

//typedef void (*isr_handler_t)(uint8_t, uint8_t);

uint8_t oldPINB = 0xFF;
// Обработчик запросов прерывания от пинов D8..D13
ISR (PCINT0_vect) {
    uint8_t value = PINB;
    uint8_t changedbits = value ^ oldPINB;
    oldPINB = value;

    if (changedbits & bit(PB0)) { // Изменился D8
        values[PB0] = value & bit(PB0);
    }

    if (changedbits & bit(PB1)) { // Изменился D9
        values[PB1] = value & bit(PB1);
    }

    if (changedbits & bit(PB2)) { // Изменился D10
        values[PB2] = value & bit(PB2);
    }

    if (changedbits & bit(PB3)) { // Изменился D11
        values[PB3] = value & bit(PB3);
    }

    if (changedbits & bit(PB4)) { // Изменился D12
        values[PB4] = value & bit(PB4);
    }
}


void setup() {
    Serial.begin(115200);
    Serial.println(F("Initialize Button"));

    // Разрешаем PCINT для указанных пинов
    PCMSK0 |= bit(PB0) | bit(PB1) | bit(PB2) | bit(PB3) | bit(PB4);
    // Очищаем признак запроса прерывания для соответствующей группы пинов
    PCIFR  |= 1;
    // Разрешаем PCINT для соответствующей группы пинов
    PCICR  |= 1;
    // for (uint8_t i = 0; i < sizeof(pins); i++) {
    //     *digitalPinToPCMSK(pins[i]) |= bit (digitalPinToPCMSKbit(pins[i])); // Разрешаем PCINT для указанного пина
    //     PCIFR  |= bit (digitalPinToPCICRbit(pins[i]));  // Очищаем признак запроса прерывания для соответствующей группы пинов
    //     PCICR  |= bit (digitalPinToPCICRbit(pins[i]));  // Разрешаем PCINT для соответствующей группы пинов
    // }

}

void loop() {
    delay(100);
    for (uint8_t i = 0; i < sizeof(pins); i++) {
        Serial.print(pins[i]);    
        Serial.print("(");    
        Serial.print(values[i]);    
        Serial.print(")");    
        Serial.print(" ");    
    }
    Serial.println();
}
