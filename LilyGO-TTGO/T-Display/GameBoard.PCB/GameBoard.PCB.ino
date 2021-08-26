#include <Arduino.h>
#include <Preferences.h>
#include <FS.h>
#include <SPIFFS.h>
#include <Button2.h>
#include <TFT_eSPI.h>

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

#if !defined(ST7789_DRIVER) || TFT_WIDTH != 135 || TFT_HEIGHT != 240
  #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup25_TTGO_T_Display.h"
#endif

#define LED1          32
#define LED2          33

#define BUTTON_A      26
#define BUTTON_B      27
#define BUTTON_CENTER 2
#define BUTTON_UP     15
#define BUTTON_DOWN   12
#define BUTTON_LEFT   17
#define BUTTON_RIGHT  13

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 135x240

Button2 buttonA(BUTTON_A);
Button2 buttonB(BUTTON_B);
Button2 buttonC(BUTTON_CENTER);
Button2 buttonU(BUTTON_UP);
Button2 buttonD(BUTTON_DOWN);
Button2 buttonL(BUTTON_LEFT);
Button2 buttonR(BUTTON_RIGHT);

void  setup() {
  Serial.begin(115200);
  Serial.println("\r\nStart...");

  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  if (!SPIFFS.begin(true)) {
    //SPIFFS.format();
    Serial.printf("SPIFFS Formatting\r\n");
  }

  buttonA.setTapHandler(clickButtonA);
  buttonB.setTapHandler(clickButtonB);
  buttonC.setTapHandler(clickButtonC);
  buttonU.setTapHandler(clickButtonU);
  buttonD.setTapHandler(clickButtonD);
  buttonL.setTapHandler(clickButtonL);
  buttonR.setTapHandler(clickButtonR);
}

void  loop() {
  buttonA.loop();
  buttonB.loop();
  buttonC.loop();
  buttonU.loop();
  buttonD.loop();
  buttonL.loop();
  buttonR.loop();
}

void clickButtonA(Button2& btn) {
  Serial.println("A");
}

void clickButtonB(Button2& btn) {
  Serial.println("B");
}

void clickButtonC(Button2& btn) {
  Serial.println("Center");
}

void clickButtonU(Button2& btn) {
  Serial.println("Up");
}

void clickButtonD(Button2& btn) {
  Serial.println("Down");
}

void clickButtonL(Button2& btn) {
  Serial.println("Left");
}

void clickButtonR(Button2& btn) {
  Serial.println("Right");
}
