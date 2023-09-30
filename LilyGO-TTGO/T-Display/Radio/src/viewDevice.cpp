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
    _sprite->setTextDatum(CC_DATUM);
    //_sprite->drawFastHLine(0, TFT_WIDTH >> 1, TFT_HEIGHT, TFT_WHITE);
    //_sprite->drawFastVLine(TFT_HEIGHT >> 1, 0, TFT_WIDTH, TFT_WHITE);

    uint16_t y2 = TFT_WIDTH >> 1;
    uint16_t y4 = TFT_WIDTH >> 2;
    uint16_t x2 = TFT_HEIGHT >> 1;
    uint16_t x4 = TFT_HEIGHT >> 2;

    _sprite->drawFloat(_device->getTemperature(), 0, x4, y4, 7);
    _sprite->drawFloat(_device->getHumidity(), 0, x4 + x2, y4, 7);
    
    _sprite->drawFloat(_device->getPressure(), 0, x4, y4 + y2, 7);

    _sprite->drawFloat(rad, 0, x4 + x2, y4 + y2, 7);
}
