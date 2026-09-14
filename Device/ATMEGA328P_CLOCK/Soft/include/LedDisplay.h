#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <Arduino.h>

#define LED_DISPLAY_LENGTH  4
#define DISPLAY_SPACE       10
#define DISPLAY_CELCIUS     11
#define DISPLAY_HUMIDITY    12
#define DISPLAY_MINUS       13

class LedSegmentDisplay {
    private:
        //dp G F E D C B A
        const uint8_t _digits[14] = {
            B00111111,    // 0
            B00000110,    // 1
            B01011011,    // 2
            B01001111,    // 3
            B01100110,    // 4
            B01101101,    // 5
            B01111101,    // 6
            B00000111,    // 7
            B01111111,    // 8
            B01101111,    // 9
            B00000000,    // SPACE
            B01100011,    // C
            B01110110,    // H
            B01000000     // -
        };
        
        const uint8_t _digitPin[LED_DISPLAY_LENGTH] = { A0, A1, A2, A3 };

    public:
        void begin(void);
        void setTemperature(uint16_t value);
        void setHumidity(uint16_t value);
        void setTime(uint16_t value);
        void display(void);
    private:
        uint8_t _curIndex;
        uint8_t _dataValue[LED_DISPLAY_LENGTH];
};

#endif