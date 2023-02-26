#include "viewDevice.h"

ViewDevice::ViewDevice(const char* name, TFT_eSPI* tft, View** currentView, ControllerDevice* device) : View(name, tft, currentView) {
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
    _tft->fillScreen(backColor);
    //_tft->setTextColor(TFT_MAGENTA);
    _tft->setTextColor(TFT_WHITE);
    _tft->setTextDatum(BL_DATUM);
    //_tft->drawFastHLine(0, TFT_WIDTH >> 1, TFT_HEIGHT, TFT_WHITE);
    //_tft->drawFastVLine(TFT_HEIGHT >> 1, 0, TFT_WIDTH, TFT_WHITE);

    _tft->loadFont(FONT_DIGIT_56);
    sprintf(text, "%+.0f°", _device->getTemperature());
    _tft->drawString(text, 4, 64);
    _tft->unloadFont();

    _tft->loadFont(FONT_TEXT_32);

    sprintf(text, "%.0f %%", _device->getHumidity());
    _tft->drawString(text, 148, 64);

    sprintf(text, "%.0f мм", _device->getPressure());
    _tft->drawString(text, 8, 122);

    sprintf(text, "%.0f м/ч" , rad);
    _tft->drawString(text, 138, 122);
    _tft->unloadFont();
}
