#include "viewDevice.h"

ViewDevice::ViewDevice(const char* name, TFT_eSPI* tft, View** currentView, ControllerDevice* device) : View(name, tft, currentView) {
  assert(device);
  _device = device;
}

void ViewDevice::OnHandle() {
  // Serial.printf("%s\r\n", _name);
  _tft->fillScreen(TFT_BLUE);
  _tft->setCursor(0, 0);
  _tft->printf("Temperature: %f C\r\n", _device->getTemperature());
  _tft->printf("Humidity: %f %%\r\n", _device->getHumidity());
  _tft->printf("Pressure: %f hPa\r\n", _device->getPressure());
}
