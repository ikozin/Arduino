#pragma once
#include <Arduino.h>

#define COLOR_BLACK     (palette[0])
#define COLOR_WHITE     (palette[1])
#define COLOR_RED       (palette[2])
#define COLOR_GREEN     (palette[3])
#define COLOR_BLUE      (palette[4])
#define COLOR_YELLOW    (palette[5])
#define COLOR_MAGENTA   (palette[6])

extern uint32_t palette_day[]; 
extern uint32_t palette_night[];
extern uint32_t *palette;
