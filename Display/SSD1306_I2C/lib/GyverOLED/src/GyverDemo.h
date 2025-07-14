#pragma once

#include <Arduino.h>
#include <GyverOLED.h>

template <int _TYPE>
class GyverDemoLib {
    public:
        GyverDemoLib() : oled(0x3C) { };
    public:
        void setup(void){
            oled.init();
            Wire.setClock(800000L);
            oled.clear();   // очистить дисплей (или буфер)
            oled.update();  // обновить. Только для режима с буфером! OLED_BUFFER
            oled.home();            // курсор в 0,0
            oled.println("Hello World!");
            oled.println("Привет МИР!");
            oled.println("0123456789");
            oled.update();
        }

        void loop(void) const {};

    private:
        GyverOLED<_TYPE, OLED_BUFFER> oled;
};