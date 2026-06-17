#include <Arduino.h>

uint8_t pins[] = { 8, 9, 10, 11, 12, 13 };
volatile uint8_t values[sizeof(pins)] = { 0, 0, 0, 0, 0, 0 };

//typedef void (*isr_handler_t)(uint8_t, uint8_t);

uint8_t oldPINB = 0xFF;
// Обработчик запросов прерывания от пинов D8..D13
ISR (PCINT0_vect) {
    uint8_t value = PINB;
    uint8_t changedbits = value ^ oldPINB;
    oldPINB = value;

    if (changedbits & (1 << PB0)) { // Изменился D8
        values[PB0] = value & (1 << PB0);
    }

    if (changedbits & (1 << PB1)) { // Изменился D9
        values[PB1] = value & (1 << PB1);
    }

    if (changedbits & (1 << PB2)) { // Изменился D10
        values[PB2] = value & (1 << PB2);
    }

    if (changedbits & (1 << PB3)) { // Изменился D11
        values[PB3] = value & (1 << PB3);
    }

    if (changedbits & (1 << PB4)) { // Изменился D12
        values[PB4] = value & (1 << PB4);
    }

    if (changedbits & (1 << PB5)) { // Изменился D13
        values[PB5] = value & (1 << PB5);
    }
}


void setup() {
    Serial.begin(115200);
    Serial.println(F("Initialize Button"));

    PCMSK0 |= 31;
    for (uint8_t i = 0; i < sizeof(pins); i++) {
        *digitalPinToPCMSK(pins[i]) |= bit (digitalPinToPCMSKbit(pins[i])); // Разрешаем PCINT для указанного пина
        PCIFR  |= bit (digitalPinToPCICRbit(pins[i]));  // Очищаем признак запроса прерывания для соответствующей группы пинов
        PCICR  |= bit (digitalPinToPCICRbit(pins[i]));  // Разрешаем PCINT для соответствующей группы пинов
        //pinMode(pins[i], INPUT);
    }

}

void loop() {
    delay(500);
    for (uint8_t i = 0; i < sizeof(pins); i++) {
        Serial.print(pins[i]);    
        Serial.print("(");    
        Serial.print(values[i]);    
        Serial.print(")");    
        Serial.print(" ");    
    }
    Serial.println();
}
