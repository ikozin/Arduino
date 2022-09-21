#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>

// Для генерации шрифта использовать Create_font.pde (Processing)
// TFT_eSPI\Tools\Create_Smooth_Font\Create_font\Create_font.pde
// Директория Tools
#define FONT_CALIBRI_32  "font/Calibri32"
#define FONT_CALIBRI_56  "font/Calibri56"
#define FONT_SEGOE_32    "font/Segoe UI Symbol32"

extern uint16_t fileData[8192];

void setDisplayPage(int16_t page);

void logTime();

#endif  //_MAIN_H_