#pragma once

#include "view/view.h"
#include "controller/controllerTime.h"

class ViewTime : public ViewT<ControllerTime> {
    public:
        ViewTime(const char* name, View** currentView, ControllerTime* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, currentView, ctrl, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
    private:
        uint16_t getDateColor(DateTime& date);
};
