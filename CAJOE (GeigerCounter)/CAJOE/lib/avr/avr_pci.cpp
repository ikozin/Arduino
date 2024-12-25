#include <avr_pci.h>

#if defined(__AVR__)

// https://tsibrov.blogspot.com/2019/06/arduino-interrupts-part2.html

uint8_t oldPINB = 0xFF;
uint8_t oldPINC = 0xFF;
uint8_t oldPIND = 0xFF;

typedef void (*isr_handler_t)(uint8_t);

isr_handler_t isrHandlerPB[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
isr_handler_t isrHandlerPC[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
isr_handler_t isrHandlerPD[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };


void pciSetup(byte pin, isr_handler_t func) {
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin)); // Разрешаем PCINT для указанного пина
    PCIFR  |= bit (digitalPinToPCICRbit(pin));  // Очищаем признак запроса прерывания для соответствующей группы пинов
    PCICR  |= bit (digitalPinToPCICRbit(pin));  // Разрешаем PCINT для соответствующей группы пинов

    uint8_t group = digitalPinToPCICRbit(pin);
    switch (group) {
        case 0: // PORTB
            isrHandlerPB[digitalPinToPCMSKbit(pin)] = func;
            break;
        case 1: // PORTC
            isrHandlerPC[digitalPinToPCMSKbit(pin)] = func;
            break;
        case 2: // PORTD
            isrHandlerPD[digitalPinToPCMSKbit(pin)] = func;
            break;
    }
}

// Обработчик запросов прерывания от пинов D8..D13
ISR (PCINT0_vect) {
    uint8_t value = PINB;
    uint8_t changedbits = value ^ oldPINB;
    oldPINB = value;

    if (isrHandlerPB[PB0] != nullptr && changedbits & (1 << PB0)) { // Изменился D8
        isrHandlerPB[PB0](value & (1 << PB0));
    }

    if (isrHandlerPB[PB1] != nullptr && changedbits & (1 << PB1)) { // Изменился D9
        isrHandlerPB[PB1](value & (1 << PB1));
    }

    if (isrHandlerPB[PB2] != nullptr && changedbits & (1 << PB2)) { // Изменился D10
        isrHandlerPB[PB2](value & (1 << PB2));
    }

    if (isrHandlerPB[PB3] != nullptr && changedbits & (1 << PB3)) { // Изменился D11
        isrHandlerPB[PB3](value & (1 << PB3));
    }

    if (isrHandlerPB[PB4] != nullptr && changedbits & (1 << PB4)) { // Изменился D12
        isrHandlerPB[PB4](value & (1 << PB4));
    }

    if (isrHandlerPB[PB5] != nullptr && changedbits & (1 << PB5)) { // Изменился D13
        isrHandlerPB[PB5](value & (1 << PB5));
    }
}

// Обработчик запросов прерывания от пинов A0..A5
ISR (PCINT1_vect) {
    uint8_t value = PINC;
    uint8_t changedbits = value ^ oldPINC;
    oldPINC = value;

    if (isrHandlerPC[PC0] != nullptr && changedbits & (1 << PC0)) { // Изменился A0
        isrHandlerPC[PC0](value & (1 << PC0));
    }

    if (isrHandlerPC[PC1] != nullptr && changedbits & (1 << PC1)) { // Изменился A1
        isrHandlerPC[PC1](value & (1 << PC1));
    }

    if (isrHandlerPC[PC2] != nullptr && changedbits & (1 << PC2)) { // Изменился A2
        isrHandlerPC[PC2](value & (1 << PC2));
    }

    if (isrHandlerPC[PC3] != nullptr && changedbits & (1 << PC3)) { // Изменился A3
        isrHandlerPC[PC3](value & (1 << PC3));
    }

    if (isrHandlerPC[PC4] != nullptr && changedbits & (1 << PC4)) { // Изменился A4
        isrHandlerPC[PC4](value & (1 << PC4));
    }

    if (isrHandlerPC[PC5] != nullptr && changedbits & (1 << PC5)) { // Изменился A5
        isrHandlerPC[PC5](value & (1 << PC5));
    }
}

// Обработчик запросов прерывания от пинов D0..D7
ISR (PCINT2_vect) {
    uint8_t value = PIND;
    uint8_t changedbits = value ^ oldPIND;
    oldPIND = value;

    if (isrHandlerPD[PD0] != nullptr && changedbits & (1 << PD0)) { // Изменился D0
        isrHandlerPD[PD0](value & (1 << PD0));
    }

    if (isrHandlerPD[PD1] != nullptr && changedbits & (1 << PD1)) { // Изменился D1
        isrHandlerPD[PD1](value & (1 << PD1));
    }

    if (isrHandlerPD[PD2] != nullptr && changedbits & (1 << PD2)) { // Изменился D2
        isrHandlerPD[PD2](value & (1 << PD2));
    }

    if (isrHandlerPD[PD3] != nullptr && changedbits & (1 << PD3)) { // Изменился D3
        isrHandlerPD[PD3](value & (1 << PD3));
    }

    if (isrHandlerPD[PD4] != nullptr && changedbits & (1 << PD4)) { // Изменился D4
        isrHandlerPD[PD4](value & (1 << PD4));
    }

    if (isrHandlerPD[PD5] != nullptr && changedbits & (1 << PD5)) { // Изменился D5
        isrHandlerPD[PD5](value & (1 << PD5));
    }

    if (isrHandlerPD[PD6] != nullptr && changedbits & (1 << PD6)) { // Изменился D6
        isrHandlerPD[PD6](value & (1 << PD6));
    }

    if (isrHandlerPD[PD7] != nullptr && changedbits & (1 << PD7)) { // Изменился D7
        isrHandlerPD[PD7](value & (1 << PD7));
    }
}

#endif