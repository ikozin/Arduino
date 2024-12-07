#include <Arduino.h>

#include <GyverDemo.h>
#include <AdafruitDemo.h>

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
