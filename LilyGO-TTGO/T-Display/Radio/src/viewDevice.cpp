#include "viewDevice.h"

ViewDevice::ViewDevice(const char* name, View** currentView, ControllerDevice* device) : View(name, currentView) {
    assert(device);
    _device = device;
}

void ViewDevice::OnHandle() {
    LOGN("ViewDevice::OnHandle")
    char text[32];
    float rad = _device->getStatic();
    uint32_t backColor = TFT_DARKGREEN;
    if (rad > 30) {
        backColor = TFT_RED;
    } else if (rad > 20) {
        backColor = TFT_YELLOW;
    }
    _sprite->fillSprite(backColor);
    //_sprite->setTextColor(TFT_MAGENTA);
    _sprite->setTextColor(TFT_WHITE);
    _sprite->setTextDatum(BL_DATUM);
    //_sprite->drawFastHLine(0, TFT_WIDTH >> 1, TFT_HEIGHT, TFT_WHITE);
    //_sprite->drawFastVLine(TFT_HEIGHT >> 1, 0, TFT_WIDTH, TFT_WHITE);

    _sprite->loadFont(FONT_DIGIT_56);
    sprintf(text, "%+.0f°", _device->getTemperature());
    _sprite->drawString(text, 3, 64);
    //_sprite->unloadFont();

    //_sprite->loadFont(FONT_TEXT_32);

    sprintf(text, "%.0f", _device->getHumidity());
    int w = _sprite->drawString(text, 130, 64);
    
    _sprite->unloadFont();

    _sprite->loadFont(FONT_TEXT_32);
    _sprite->drawString("%", 130 + w, 64);

    sprintf(text, "%.0f мм", _device->getPressure());
    _sprite->drawString(text, 8, 122);

    sprintf(text, "%.0f м/ч" , rad);
    _sprite->drawString(text, 138, 122);
    _sprite->unloadFont();
}
