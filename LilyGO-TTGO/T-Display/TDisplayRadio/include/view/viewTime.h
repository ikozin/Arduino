#pragma once

#include "view/view.h"
#include "controller/controllerTime.h"

class ViewTime : public ViewT<ControllerTime> {
    public:
        ViewTime(const char* name, TFT_eSprite* tft, ControllerTime* controller) : 
            ViewT(name, tft, controller) {
        }
    private:
        uint16_t getDateColor(TimeData& date);
    public:
        virtual void OnUpdate() override;
    private:
        char    _time[32];
        char    _date[32];
    private:
        static char*    _dayOfWeeks[];
        static char*    _months[];
};