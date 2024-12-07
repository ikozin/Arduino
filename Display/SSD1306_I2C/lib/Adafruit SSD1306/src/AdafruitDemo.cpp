#include <AdafruitDemo.h>

AdafruitDemoLib::AdafruitDemoLib():
    display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
}

// SSD1306_NO_SPLASH
void AdafruitDemoLib::setup() {
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  
    display.clearDisplay(); // Clear the buffer
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Hello World!");
    display.display();
}

void AdafruitDemoLib::loop() {
}
