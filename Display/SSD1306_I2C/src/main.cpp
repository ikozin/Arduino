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
AdafruitDemoLib demo;
#endif
#ifdef Gyver_Lib
GyverDemoLib demo;
#endif

void setup() {
    demo.setup();
}

void loop() {
    demo.loop();
}
