#pragma once

#include "view.h"
#include "controllerTime.h"

class ViewTime : public View {
    public:
        ViewTime(const char* name, View** currentView, ControllerTime* device);
    protected:
        virtual void OnHandle() override;
    private:
        uint16_t getDateColor(DateTime& date);
    private:
        ControllerTime* _device;
};
