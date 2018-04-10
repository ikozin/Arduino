#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <Arduino.h>
#define LED_DISPLAY_LENGTH 4

namespace LED_DISPLAY
{
    const byte _digits[11] =
    {
      B00111111,    //dp G F E D C B A
      B00000110,    //dp G F E D C B A
      B01011011,    //dp G F E D C B A
      B01001111,    //dp G F E D C B A
      B01100110,    //dp G F E D C B A
      B01101101,    //dp G F E D C B A
      B01111101,    //dp G F E D C B A
      B00000111,    //dp G F E D C B A
      B01111111,    //dp G F E D C B A
      B01101111,    //dp G F E D C B A
      B00000000     //dp G F E D C B A
    };
    const byte _digitPin[LED_DISPLAY_LENGTH] = { A0, A1, A2, A3 };
    
    extern byte _curIndex;
    extern byte _dataValue[LED_DISPLAY_LENGTH];

    void begin();
    void print(byte v1, byte v2, byte v3, byte v4);
		void _refresh();
};

#endif
