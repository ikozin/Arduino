#include <typeinfo>
#include "view/view.h"

View::View(const char* name, View** currentView, SemaphoreHandle_t updateEvent) {
    _name = name;
    _currentView = currentView;
    _updateEvent = (updateEvent == nullptr) ? xSemaphoreCreateBinary() : updateEvent;
}

void View::Start(TFT_eSprite* sprite, Controller* ctrl, uint16_t stackDepth) {
    assert(sprite);
    _sprite = sprite;
    if (ctrl) {
        ctrl->AddUpdateEvent(GetEvent());
    }
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
    vTaskDelete(page->_task);
}
