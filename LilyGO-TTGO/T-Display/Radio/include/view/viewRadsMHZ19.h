#pragma once

#include "view/view.h"
#include "controller/controllerRadSens.h"
#include "controller/controllerMHZ19.h"

class ViewRadsMHZ19 : public View {
    public:
        ViewRadsMHZ19(const char* name, ViewSettig* setting, ControllerRadSens* radSens, ControllerMHZ19* mhz19, SemaphoreHandle_t updateEvent = nullptr);
        virtual void Start(uint16_t stackDepth = 2048) override;
    protected:
        virtual void OnDrawHandle() override;
    private:
        ControllerRadSens*  _radSens;
        ControllerMHZ19*    _mhz19;
};
