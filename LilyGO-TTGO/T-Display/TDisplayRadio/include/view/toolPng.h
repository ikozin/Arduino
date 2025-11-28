#pragma once

#include "display.h"
#include <pgmspace.h>
#include <PNGdec.h>
#include <FS.h>
#include <LittleFS.h>

#define MAX_PNG_IMAGE_WIDTH TFT_HEIGHT

class ToolPng {
    // public:
    //     ToolPng() {
    //         xpos = 0;
    //         ypos = 0;
    //         local_tft = nullptr;
    //     }
    public:
        static PNG _png; // PNG decoder instance
        static uint16_t _lineBuffer[MAX_PNG_IMAGE_WIDTH];
        static int16_t _xpos;
        static int16_t _ypos;
        static TFT_eSprite* _tft;
    protected:
        static int pngDraw(PNGDRAW *pDraw);
    public:
        static bool Draw(TFT_eSprite* tft, uint8_t * image, size_t size, int16_t x);
        static bool Draw(TFT_eSprite* tft, uint8_t * image, size_t size, int16_t x, int16_t y);
        static bool Draw(TFT_eSprite* tft, const char* fileName, int16_t x);
        static bool Draw(TFT_eSprite* tft, const char* fileName, int16_t x, int16_t y);
};

