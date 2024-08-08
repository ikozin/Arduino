#pragma once

#include "view.h"
#include "controllerRadSens.h"
#include "controllerMHZ19.h"

class ViewRadsMHZ19 : public View {
    public:
        ViewRadsMHZ19(const char* name, View** currentView, ControllerRadSens* radSens);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerRadSens* _radSens;
};
