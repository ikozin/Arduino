#pragma once

#include "view/view.h"
#include "controller/controllerRadSens.h"
#include "controller/controllerMHZ19.h"

class ViewRadsMHZ19 : public View {
    public:
        ViewRadsMHZ19(const char* name, View** currentView, ControllerRadSens* radSens, ControllerMHZ19* mhz19);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerRadSens*  _radSens;
        ControllerMHZ19*    _mhz19;
};
