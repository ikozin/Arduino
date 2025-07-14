#include <Arduino.h>

#include <GyverDemo.h>
#include <AdafruitDemo.h>

/*

Параметры
╔═════════════╦════════╗
║ Экран       ║ 128x64 ║
╠═════════════╬════════╣
║ Протокол    ║ I2C    ║
╠═════════════╬════════╣
║ Адрес (I2C) ║ 0x3C   ║
╠═════════════╬════════╣
║ Питание     ║ +5V    ║
╚═════════════╩════════╝

Распиновка
╔═════╦═════╦═════╦═════╗
║ GND ║ VCC ║ SCL ║ SDA ║
╠═════╬═════╬═════╬═════╣
║ GND ║ +5V ║ SCL ║ SDA ║
╚═════╩═════╩═════╩═════╝

*/

// #define Adafruit_Lib
#define Gyver_Lib

#ifdef Adafruit_Lib
// AdafruitDemoLib<128, 32> demo;
AdafruitDemoLib<128, 64> demo;
#endif
#ifdef Gyver_Lib
// GyverDemoLib<SSD1306_128x32> demo;
GyverDemoLib<SSD1306_128x64> demo;
#endif

void setup() {
    demo.setup();
}

void loop() {
    demo.loop();
}
