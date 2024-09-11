#pragma once

#include "view/view.h"
#include "controller/controllerDS3231.h"

class ViewDS3231 : public ViewT {
    public:
        ViewDS3231(const char* name, ViewSettig* setting, ControllerDS3231* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, setting, ctrl, 0, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
    private:
        uint16_t getDateColor(DateTime& date);
    private:
        static char* dayOfWeeks[];
        static char* months[];
};
