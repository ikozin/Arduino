#include "colors.h"
#include "display.h"

uint32_t palette_day[] {
    TFT_BLACK,
    TFT_WHITE,
    TFT_RED,
    TFT_GREEN,
    TFT_BLUE,
    TFT_YELLOW,
    TFT_MAGENTA
}; 

uint32_t palette_night[] {
    TFT_BLACK,
    0x79EF,
    0x7800,
    0x03E0,
    0x000F,
    0x79E0,
    0x780F
};

uint32_t *palette = palette_day;
