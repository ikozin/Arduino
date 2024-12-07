#include <GyverDemo.h>

void GyverDemoLib::setup() {
    oled.init();
    Wire.setClock(800000L);

    oled.clear();   // очистить дисплей (или буфер)
    oled.update();  // обновить. Только для режима с буфером! OLED_BUFFER

    oled.home();            // курсор в 0,0
    oled.print("Hello World!");   // печатай что угодно: числа, строки, float, как Serial!
    oled.update();
}

void GyverDemoLib::loop() {
}
