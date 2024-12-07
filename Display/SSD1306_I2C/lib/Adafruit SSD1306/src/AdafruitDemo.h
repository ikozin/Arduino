#pragma once

#define SSD1306_NO_SPLASH

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class AdafruitDemoLib {
    public:
        AdafruitDemoLib();
    protected:
        const int SCREEN_WIDTH = 128;
        const int SCREEN_HEIGHT = 64;
        const int SCREEN_ADDRESS = 0x3C;
        const int OLED_RESET = -1;
    public:
        void setup(void);
        void loop(void);
    private:
        Adafruit_SSD1306 display;
};