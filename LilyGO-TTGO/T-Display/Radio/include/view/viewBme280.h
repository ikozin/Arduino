#pragma once

#include "view/view.h"
#include "controller/controllerBme280.h"
#include "controller/controllerRadSens.h"
class ViewBME280 : public View {
    public:
        ViewBME280(const char* name, View** currentView, ControllerBme280* bme280);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerBme280* _bme280;
};
