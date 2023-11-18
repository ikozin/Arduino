#include "Dip16_RU5_RU7.h"

//     ЗАПИСЬ
//
//      ___     ──┐                                         ┌ ── ── ── ── ── ┐
//      RAS       │ <-                            1.51   -> │   <- 2.46 ->   │
//                └─────────────────────────────────────────┘                └
//      ___     ─────────────────────────────┐               ┌ ── ── ── ── ── ── ── ── ── ── ── ── ── ──┐
//      CAS                                  │ <-   375n  -> │   <- 3.595 ->                            │
//                                           └───────────────┘                                          └
//      __      ─────────────┐                                ┌ ── ── ── ── ── ── ── ── ┐
//      WR                   │ <-                 1.135    -> │  <- 2.84 ->             │
//                           └────────────────────────────────┘                         └
//                                           │              │
//                                           │ <-   255n -> │
//                                           │              │

//     ЧТЕНИЕ
//
//      ___     ──┐                                      ┌ ── ── ── ── ── ─┐ 
//      RAS       │ <-                          1.005 -> │     <- 2.9 ->   │ 
//                └──────────────────────────────────────┘                 └─
//      ___     ────────────────────────────┐               ┌ ── ── ── ── ── ── ── ── ─┐
//      CAS                                 │ <-   440n  -> │  <- 3.47 ->              │
//                                          └───────────────┘                          └──
//                                          │            │
//                                          │ <- 315n -> │
//                                          │            │


int Dip16_RU5_RU7::check_devices(GyverDisplay& display) {
    int errorCount = 0;
    info(display);
    init();
    debug_println("----------");
    Serial.flush();

    noInterrupts();
    
    for (int i = 0; i < 8; i++) {
        PORTC &= ~RAS_PORT_C;   //RAS
        PORTC |= RAS_PORT_C;    //RAS
    }

    errorCount += checkByte(B00000000) ? B00000001 : 0;
    errorCount += checkByte(B01010101) ? B00000010 : 0;
    errorCount += checkByte(B10101010) ? B00000100 : 0;
    errorCount += checkByte(B00110011) ? B00001000 : 0;
    errorCount += checkByte(B11001100) ? B00010000 : 0;
    errorCount += checkByte(B00001111) ? B00100000 : 0;
    errorCount += checkByte(B11110000) ? B01000000 : 0;
    errorCount += checkByte(B01100110) ? B10000000 : 0;

    interrupts();

    if (errorCount > 0) {
        if (errorCount & B00000001) Serial.println("Error = B00000000");
        if (errorCount & B00000010) Serial.println("Error = B01010101");
        if (errorCount & B00000100) Serial.println("Error = B10101010");
        if (errorCount & B00001000) Serial.println("Error = B00110011");
        if (errorCount & B00010000) Serial.println("Error = B11001100");
        if (errorCount & B00100000) Serial.println("Error = B00001111");
        if (errorCount & B01000000) Serial.println("Error = B11110000");
        if (errorCount & B01100110) Serial.println("Error = B01100110");
    }
    debug_println("----------");
    done();
    return errorCount;
}


long inline Dip16_RU5_RU7::checkByte(uint8_t value) {
    long error = 0;
    for (int col = 0; col < _cols; col++) {
        for (int row = 0; row < _rows; row++) {
            uint8_t bit = value & 1;
            write(row, col, bit);
            value = (value >> 1) | (bit << 7);
        }
    }
    for (int col = 0; col < _cols; col++) {
        for (int row = 0; row < _rows; row++) {
            uint8_t bit = value & 1;
            if (read(row, col) != bit) {
                error ++;
            }
            value = (value >> 1) | (bit << 7);
        }
    }
    return error;
}


void inline Dip16_RU5_RU7::write(int row, int col, uint8_t value) {
    PORTA = portA[row];
    PORTC = portC[row];

    PORTC &= ~RAS_PORT_C;   //RAS
    __asm__("nop\n\t");     //62.5ns

    PORTA = portA[col];
    PORTC = portC[col] & ~RAS_PORT_C & ~WE_PORT_C ;  //WE
    PORTC = (value > 0) ? PORTC | DI_PORT_C: PORTC & ~DI_PORT_C; //DI

    PORTA &= ~CAS_PORT_A;   //CAS
    __asm__("nop\n\t");     //62.5ns
    __asm__("nop\n\t");     //62.5ns

    PORTC |= RAS_PORT_C;    //RAS
    PORTA |= CAS_PORT_A;    //CAS
    PORTC |= WE_PORT_C;     //WE
}


uint8_t inline Dip16_RU5_RU7::read(int row, int col) {
    PORTA = portA[row];
    PORTC = portC[row];

    PORTC &= ~RAS_PORT_C;   //RAS
    __asm__("nop\n\t");     //62.5ns

    PORTA = portA[col];
    PORTC = portC[col] & ~RAS_PORT_C;
    PORTA &= ~CAS_PORT_A;   //CAS
    __asm__("nop\n\t");     //62.5ns
    __asm__("nop\n\t");     //62.5ns     

    uint8_t value = (PINA & DO_PORT_A) ? HIGH: LOW;

    PORTC |= RAS_PORT_C;    //RAS
    PORTA |= CAS_PORT_A;    //CAS

    return value;
}


void inline Dip16_RU5_RU7::refresh(void) {
    for (int i = 0; i < _rows; i++) {
        PORTA = portA[i];
        PORTC = portC[i];

        PORTC &=  ~RAS_PORT_C;  //RAS
        __asm__("nop\n\t");     //62.5ns
        PORTC |=  RAS_PORT_C;   //RAS
    }
}
