#include <Arduino.h>

// #define DISP1637_CLK_DELAY 100   // задержка интерфейса в мкс
#include <GyverSegment.h>

#define DIO_PIN 17
#define CLK_PIN 16

Disp1637_6 oled(DIO_PIN, CLK_PIN);

void setup() {
    Serial.begin(115200);
    oled.power(true);
    oled.clear();
    oled.brightness(7);
}

void loop() {
    oled.showClock(23, 59);
    oled.update();
    delay(1000);
    oled.print("abcdef");
    oled.update();
    delay(1000);
    oled.showClock(0, 0);
    oled.update();
    delay(1000);
    oled.print("ABCDEF");
    oled.update();
    delay(1000);
}
