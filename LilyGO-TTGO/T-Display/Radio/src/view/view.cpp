#include <typeinfo>
#include "view/view.h"

View::View(const char* name, ViewSettig* setting, SemaphoreHandle_t updateEvent) {
    _name = name;
    _setting = setting;
    _updateEvent = (updateEvent == nullptr) ? xSemaphoreCreateBinary() : updateEvent;
}

void View::ViewHandler(void* parameter) {
    assert(parameter);
    View* page = static_cast<View*>(parameter);
    LOGN("%s::OnInit", page->_name);
    page->OnInit();
    for (;;) {
        xSemaphoreTake(page->_updateEvent, portMAX_DELAY);
        if (*page->getSetting()->getCurrentView() == page) {
            LOGN("%s::OnDrawHandle", page->_name);
            page->OnDrawHandle();
            page->getSetting()->getSprite()->pushSprite(0, 0);
        }
    }
    vTaskDelete(page->_task);
}
