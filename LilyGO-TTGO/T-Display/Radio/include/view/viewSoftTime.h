#pragma once

#include "view/view.h"
#include "controller/controllerTime.h"

class ViewSoftTime : public ViewT {
    public:
        ViewSoftTime(const char* name, ViewSettig* setting, ControllerTime* ctrl, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual void OnInit() override;
        virtual void OnDrawHandle() override;
    private:
        uint16_t getDateColor(TimeData& date);
    private:
        TFT_eSprite _textSprite;
        int16_t     _textX;
        static char* dayOfWeeks[];
        static char* months[];
};
