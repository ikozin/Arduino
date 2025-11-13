#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include "controller/radioStorage.h"

// Для генерации шрифта использовать Create_font.pde (Processing)
// TFT_eSPI\Tools\Create_Smooth_Font\Create_font\Create_font.pde
// Директория Tools

#define STACK_512_B  (512)

#define STACK_1_KB  (1024 * 1)
#define STACK_2_KB  (1024 * 2)
#define STACK_3_KB  (1024 * 3)
#define STACK_4_KB  (1024 * 4)
#define STACK_5_KB  (1024 * 5)
#define STACK_6_KB  (1024 * 6)
#define STACK_7_KB  (1024 * 7)
#define STACK_8_KB  (1024 * 8)

extern Preferences prefs;
extern RadioStorage ctrlRadioStorage;

void setDisplayPage(int16_t page);
void setDisplayPageNext(void);
void setDisplayPagePrev(void);

void logTime();

// #define ENCODER_FAKE
// #define BME280_FAKE
// #define RADSENS_FAKE
