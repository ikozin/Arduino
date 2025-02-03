#include <typeinfo>
#include "view/view.h"

View::View(const char* name, ViewSettig* setting, SemaphoreHandle_t updateEvent) {
    _name = name;
    _setting = setting;
    _updateEvent = (updateEvent == nullptr) ? xSemaphoreCreateBinary() : updateEvent;
}

void View::ViewHandler(void* parameter) {
    assert(parameter);
    View* view = static_cast<View*>(parameter);
    view->OnInit();
    for (;;) {
        xSemaphoreTake(view->_updateEvent, portMAX_DELAY);
        if (*view->getSetting()->getCurrentView() == view) {
            view->OnDrawHandle();
        }
    }
    vTaskDelete(view->_task);
}
