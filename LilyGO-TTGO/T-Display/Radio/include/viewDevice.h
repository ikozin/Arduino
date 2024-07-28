#pragma once

#include "view.h"
#include "controllerBme280.h"
#include "controllerRadSens.h"
class ViewDevice : public View {
    public:
        ViewDevice(const char* name, View** currentView, ControllerBme280* bme280, ControllerRadSens* radSens);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerBme280* _bme280;
        ControllerRadSens* _radSens;
};
