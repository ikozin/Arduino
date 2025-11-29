#include <view/toolPng.h>

PNG ToolPng::_png;
uint16_t ToolPng::_lineBuffer[];
int16_t ToolPng::_xpos = 0;
int16_t ToolPng::_ypos = 0;
TFT_eSprite* ToolPng::_tft = nullptr;

int ToolPng::pngDraw(PNGDRAW *pDraw) {
    if (_tft == nullptr) return false;
    _png.getLineAsRGB565(pDraw, _lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
    _tft->pushImage(_xpos, _ypos + pDraw->y, pDraw->iWidth, 1, _lineBuffer);
    return true;
}

bool ToolPng::Draw(TFT_eSprite* tft, uint8_t * image, size_t size, int16_t x) {
    _tft = tft;
    int16_t rc = _png.openFLASH(image, size, pngDraw);
    if (rc == PNG_SUCCESS) {
        _xpos = x;
        _ypos = (TFT_WIDTH - _png.getHeight()) >> 1;
        rc = _png.decode(NULL, 0);
        // png.close(); // not needed for memory->memory decode
        return true;
    }
    return false;
}

bool ToolPng::Draw(TFT_eSprite* tft, uint8_t * image, size_t size, int16_t x, int16_t y) {
    _tft = tft;
    int16_t rc = _png.openFLASH(image, size, pngDraw);
    if (rc == PNG_SUCCESS) {
        _xpos = x;
        _ypos = y;
        rc = _png.decode(NULL, 0);
        // png.close(); // not needed for memory->memory decode
        return true;
    }
    return false;
}
