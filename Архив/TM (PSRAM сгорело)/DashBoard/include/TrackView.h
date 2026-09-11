#pragma once
#include "display.h"
#include "colors.h"
#include "logging.h"

class TrackView {
    private:
        int32_t         _x;
        int32_t         _y;
        int32_t         _height;
        int32_t         _width;
        int32_t         _step;
        LGFX*           _tft;
        const uint8_t*  _font;
        String          _track;
    public:
        TrackView(LGFX* tft, const uint8_t* font) {
            _tft = tft;
            _font = font;
            _tft->loadFont(_font);
            _height = _tft->fontHeight();
            _step = _tft->fontWidth();
            _tft->unloadFont();
            _track.reserve(64);
            _width = 0;
        };

        void begin(uint32_t x, uint32_t y, const char* track) {
            // LOG("track:%s, %d, %d\r\n", track, x, y);
            _x = TFT_HEIGHT;
            _y = y;
            _track = track;
            _tft->loadFont(_font);
            _tft->setTextDatum(ML_DATUM);
            _width = _tft->textWidth(_track.c_str());
            if (_width < TFT_HEIGHT) {
                _x = (TFT_HEIGHT - _width) >> 1;
                _width = 0;
            } else {
                _track += "  ";
                _width -= _step << 1;
            }
            // LOG("%s, %d, %d, %d, %d\r\n", _track.c_str(), _x, _y, _width, _height);
            _tft->startWrite();
            _tft->fillRect(0, _y - (_height >> 1), TFT_HEIGHT, _y + (_height >> 1), COLOR_BLACK);
            _tft->setTextColor(COLOR_WHITE, COLOR_BLACK);
            _tft->drawString(_track.c_str(), _x, _y);
            _tft->endWrite();
            _tft->unloadFont();
        }
        void update() {
            if (_width == 0) return;
            _tft->loadFont(_font);
            _tft->startWrite();
            _x-= _step;
            if (_x <= -_width) {
                _x = TFT_HEIGHT;
                _tft->fillRect(0, _y - (_height >> 1), _step, _y + (_height >> 1), COLOR_BLACK);
            }
            _tft->setTextDatum(ML_DATUM);
            _tft->startWrite();
            _tft->setTextColor(COLOR_WHITE, COLOR_BLACK);
            _tft->drawString(_track.c_str(), _x, _y);
            _tft->endWrite();
            _tft->unloadFont();
        }
};