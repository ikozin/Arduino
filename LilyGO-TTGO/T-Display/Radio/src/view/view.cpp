#include <typeinfo>
#include "view/view.h"

View::View(const char* name, View** currentView) {
    _name = name;
    _currentView = currentView;
}

void View::Start(TFT_eSprite* sprite, SemaphoreHandle_t updateEvent, uint16_t stackDepth) {
    assert(sprite);
    assert(updateEvent);
    _sprite = sprite;
    _updateEvent = updateEvent;
    xTaskCreate(ViewHandler, this->_name, stackDepth, this, 100, &this->_task);
}

void View::ViewHandler(void* parameter) {
    assert(parameter);
    View* page = static_cast<View*>(parameter);
    for (;;) {
        xSemaphoreTake(page->_updateEvent, portMAX_DELAY);
        // Serial.printf("Update Event %s\r\n", page->_name);
        if (*page->_currentView == page) {
            page->OnHandle();
            page->_sprite->pushSprite(0, 0);
        }
    }
}
