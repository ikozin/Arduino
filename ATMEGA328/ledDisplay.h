#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <Arduino.h>
#define LED_DISPLAY_LENGTH  4
#define DISPLAY_SPACE       10
#define DISPLAY_CELCIUS     11
#define DISPLAY_HUMIDITY    12
#define DISPLAY_MINUS       13

namespace LED_DISPLAY
{
    //dp G F E D C B A
    const byte _digits[14] =
    {
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
      B01100011,    // Celcius
      B01110110,    // Humidity
      B01000000     // Minus
    };
    const byte _digitPin[LED_DISPLAY_LENGTH] = { A0, A1, A2, A3 };
    
    extern byte _curIndex;
    extern byte _dataValue[LED_DISPLAY_LENGTH];

    void begin();
    void print(byte v1, byte v2, byte v3, byte v4);
    void setTemperature(uint16_t value);
    void setHumidity(uint16_t value);
    void setTime(uint16_t value);
    void _refresh();
};

#endif
