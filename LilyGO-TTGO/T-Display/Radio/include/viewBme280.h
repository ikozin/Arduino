#pragma once

#include "view.h"
#include "controllerBme280.h"
#include "controllerRadSens.h"
class ViewBME280 : public View {
    public:
        ViewBME280(const char* name, View** currentView, ControllerBme280* bme280);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerBme280* _bme280;
};
