#pragma once
#include <Arduino.h>

static byte data[] = {
	B11111100,		// 0
	B01100000,		// 1
	B11011010,		// 2
	B11110010,		// 3
	B01100110,		// 4
	B10110110,		// 5
	B10111110,		// 6
	B11100000,		// 7
	B11111110,		// 8
	B11110110,		// 9
	B11101111,		// A
	B11111111,		// b
	B10011110,		// C
	B11111111,		// d
	B11111111,		// E
	B11111111,		// F
};

class TM1639AS {
    private:
        byte _dataPin;
        byte _clockPin;
        byte _strobePin;

        byte _maxDisplays;
        byte _digits;
    public:
        TM1639AS(byte dataPin, byte clockPin, byte strobePin);
    public:
        void begin(bool activateDisplay, byte intensity);
        void clearDisplay();
        void setSegments(byte* segments);
    private:
        void sendCommand(byte cmd);
        void send(byte data);
};