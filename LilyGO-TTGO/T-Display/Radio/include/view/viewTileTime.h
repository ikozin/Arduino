#pragma once

#include "view/view.h"
#include "controller/controllerTime.h"

class ViewTileTime : public ViewT {
    public:
        ViewTileTime(const char* name, ViewSettig* setting, ControllerTime* ctrl, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual void OnDrawHandle() override;
    private:
        uint16_t getDateColor(DateTime& date);
    private:
        static char* dayOfWeeks[];
        static char* months[];
};
