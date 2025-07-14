#pragma once

#define SSD1306_NO_SPLASH

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


template <int _WIDTH, int _HEIGHT>
class AdafruitDemoLib {
    public:
        AdafruitDemoLib() : display(_WIDTH, _HEIGHT, &Wire) {}
    public:
        void setup(void) {
            display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.println("Hello World!");
            display.println("Привет МИР!");
            display.println("0123456789");
            display.display();
        }
        void loop(void) const {};
    private:
        Adafruit_SSD1306 display;
};