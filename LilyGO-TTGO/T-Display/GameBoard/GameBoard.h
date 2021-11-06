#ifndef _GameBoard_H_
#define _GameBoard_H_

#include <Button2.h>
#include <TFT_eSPI.h>

#define LED1          32
#define LED2          33

#define BUTTON_A      26
#define BUTTON_B      27
#define BUTTON_CENTER 2
#define BUTTON_UP     15
#define BUTTON_DOWN   12
#define BUTTON_LEFT   17
#define BUTTON_RIGHT  13

#if defined(DEBUG_CONSOLE)
#define debug_printf(...)   Serial.printf(__VA_ARGS__)
#else
#define debug_printf(...)
#endif

#endif
