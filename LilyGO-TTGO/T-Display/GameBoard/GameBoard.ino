#define DEBUG_CONSOLE

#include <Arduino.h>
#include <Preferences.h>
#include <FS.h>
#include <SPIFFS.h>
#include "GameBoard.h"
#include "TestBoard.h"
#include "GameSnake.h"
#include "GameTetris.h"

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

#if !defined(ST7789_DRIVER) || TFT_WIDTH != 135 || TFT_HEIGHT != 240
  #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup25_TTGO_T_Display.h"
#endif

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 135x240

Button2 buttonA(BUTTON_A);
Button2 buttonB(BUTTON_B);
Button2 buttonC(BUTTON_CENTER);
Button2 buttonU(BUTTON_UP);
Button2 buttonD(BUTTON_DOWN);
Button2 buttonL(BUTTON_LEFT);
Button2 buttonR(BUTTON_RIGHT);

TestBoard test(&tft);
Snake  snake(&tft);
Tetris  tetris(&tft);

Game*  game = &tetris;

void  setup() {
  Serial.begin(115200);
  Serial.println(F("\r\nStart..."));

  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  if (!SPIFFS.begin(true)) {
    //SPIFFS.format();
    Serial.println(F("SPIFFS Formatting\r\n"));
  }
  buttonU.setTapHandler(clickButtonU);
  buttonD.setTapHandler(clickButtonD);
  buttonL.setTapHandler(clickButtonL);
  buttonR.setTapHandler(clickButtonR);
  buttonA.setTapHandler(clickButtonA);
  buttonB.setTapHandler(clickButtonB);
  buttonC.setTapHandler(clickButtonC);
  game->init();
}

void  loop() {
  buttonU.loop();
  buttonD.loop();
  buttonL.loop();
  buttonR.loop();
  buttonA.loop();
  buttonB.loop();
  buttonC.loop();
  if (game != NULL) {
    if (game->loop()) return;
    game =  NULL;
  }
}

void clickButtonA(Button2& btn) {
  if (game != NULL) game->clickButtonA();
}

void clickButtonB(Button2& btn) {
  if (game != NULL) game->clickButtonB();
}

void clickButtonC(Button2& btn) {
  if (game != NULL) game->clickButtonC();
}

void clickButtonU(Button2& btn) {
  if (game != NULL) game->clickButtonU();
}

void clickButtonD(Button2& btn) {
  if (game != NULL) game->clickButtonD();
}

void clickButtonL(Button2& btn) {
  if (game != NULL) game->clickButtonL();
}

void clickButtonR(Button2& btn) {
  if (game != NULL) game->clickButtonR();
}
