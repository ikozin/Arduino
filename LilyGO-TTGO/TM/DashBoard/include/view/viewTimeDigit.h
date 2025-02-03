#pragma once

#include "view/view.h"
#include "controller/controllerTime.h"

class ViewTimeDigit : public ViewT {
    public:
        ViewTimeDigit(const char* name, ViewSettig* setting, ControllerTime* ctrl, SemaphoreHandle_t updateEvent = nullptr):
            ViewT(name, setting, ctrl, 0, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
    private:
        uint16_t getDateColor(DateTime& date);
    private:
        static char* dayOfWeeks[];
        static char* months[];
};
