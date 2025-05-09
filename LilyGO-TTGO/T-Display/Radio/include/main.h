#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include "controller/radioStorage.h"

// Для генерации шрифта использовать Create_font.pde (Processing)
// TFT_eSPI\Tools\Create_Smooth_Font\Create_font\Create_font.pde
// Директория Tools
#define FONT_TEXT_32    "font/Open Sans Regular32"
#define FONT_DIGIT_56   "font/Open Sans Regular56"

extern uint16_t fileData[4096];

extern Preferences prefs;
extern RadioStorage ctrlRadioStorage;

void setDisplayPage(int16_t page);
void setDisplayPageNext(void);
void setDisplayPagePrev(void);

void logTime();

// #define ENCODER_FAKE
// #define BME280_FAKE
// #define RADSENS_FAKE
