#include <typeinfo>
#include "view.h"

View::View(const char* name, TFT_eSPI* tft, View** currentView) {
    _name = name;
    _tft = tft;
    _currentView = currentView;
}

void View::Start(SemaphoreHandle_t updateEvent) {
  assert(updateEvent);
  _updateEvent = updateEvent;
  xTaskCreate(ViewHandler, this->_name, 4096, this, 1, &this->_task);
}

void View::ViewHandler(void* parameter) {
  assert(parameter);
  View* page = (View*) parameter;
  for (;;) {
    xSemaphoreTake(page->_updateEvent, portMAX_DELAY);
    // Serial.printf("Update Event %s\r\n", page->_name);
    if (*page->_currentView == page) page->OnHandle();
  }
}
