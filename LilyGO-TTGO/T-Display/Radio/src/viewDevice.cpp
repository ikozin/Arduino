#include "viewDevice.h"

ViewDevice::ViewDevice(const char* name, TFT_eSPI* tft, View** currentView, ControllerDevice* device) : View(name, tft, currentView) {
  assert(device);
  _device = device;
}

void ViewDevice::OnHandle() {
  // Serial.printf("%s\r\n", _name);
  char text[32];
  _tft->fillScreen(TFT_BLUE);
  //_tft->setTextColor(TFT_MAGENTA);
  _tft->setTextColor(TFT_WHITE);
  _tft->loadFont(FONT_CALIBRI_32);
  _tft->setTextDatum(TC_DATUM);
  
  sprintf(text, "%+.1f °", _device->getTemperature());
  _tft->drawString(text, 60, 20);
  // Serial.printf("%s\r\n", text);
  sprintf(text, "%.0f %%", _device->getHumidity());
  _tft->drawString(text, 180, 20);
  // Serial.printf("%s\r\n", text);
  sprintf(text, "%.0f мм. рт. ст.", _device->getPressure());
  _tft->drawString(text, 120, 80);
  // Serial.printf("%s\r\n", text);
}
