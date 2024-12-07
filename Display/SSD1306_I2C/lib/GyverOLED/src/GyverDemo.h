#pragma once

#include <Arduino.h>
#include <GyverOLED.h>


class GyverDemoLib {
    public:
        GyverDemoLib() { };
    protected:
        const int SCREEN_WIDTH = 128;
        const int SCREEN_HEIGHT = 64;
        const int SCREEN_ADDRESS = 0x3D;
        const int OLED_RESET = -1;
    public:
        void setup(void);
        void loop(void);
    private:
        GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
};