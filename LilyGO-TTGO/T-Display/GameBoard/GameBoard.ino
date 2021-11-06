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

//Button2 buttonA(BUTTON_A);
//Button2 buttonB(BUTTON_B);
//Button2 buttonC(BUTTON_CENTER);
//Button2 buttonU(BUTTON_UP);
//Button2 buttonD(BUTTON_DOWN);
//Button2 buttonL(BUTTON_LEFT);
//Button2 buttonR(BUTTON_RIGHT);
long _lastBtnTime = 0;


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
  //buttonU.setTapHandler(clickButtonU);
  //buttonD.setTapHandler(clickButtonD);
  //buttonL.setTapHandler(clickButtonL);
  //buttonR.setTapHandler(clickButtonR);
  //buttonA.setTapHandler(clickButtonA);
  //buttonB.setTapHandler(clickButtonB);
  //buttonC.setTapHandler(clickButtonC);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_CENTER, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  game->init();
}

void  loop() {
  //buttonU.loop();
  //buttonD.loop();
  //buttonL.loop();
  //buttonR.loop();
  //buttonA.loop();
  //buttonB.loop();
  //buttonC.loop();

  if (millis() - _lastBtnTime > 120) {
    _lastBtnTime = millis();
    if (digitalRead(BUTTON_UP) == LOW) {
      if (game != NULL) game->clickButtonU();
    }
    if (digitalRead(BUTTON_DOWN) == LOW) {
      if (game != NULL) game->clickButtonD();
    }
    if (digitalRead(BUTTON_LEFT) == LOW) {
      if (game != NULL) game->clickButtonL();
    }
    if (digitalRead(BUTTON_RIGHT) == LOW) {
      if (game != NULL) game->clickButtonR();
    }
    if (digitalRead(BUTTON_A) == LOW) {
      if (game != NULL) game->clickButtonA();
    }
    if (digitalRead(BUTTON_B) == LOW) {
      if (game != NULL) game->clickButtonB();
    }
    if (digitalRead(BUTTON_CENTER) == LOW) {
      if (game != NULL) game->clickButtonC();
    }
  }
  
  if (game != NULL) {
    if (game->loop()) return;
    game->init();
  }
}
/*
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
*/
