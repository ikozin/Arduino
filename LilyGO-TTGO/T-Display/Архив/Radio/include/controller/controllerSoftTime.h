#pragma once

#include "controller/controllerTime.h"

class ControllerSoftTime : public ControllerTime {
    public:
        ControllerSoftTime(const char* name, Preferences* prefs);
    protected:
        virtual InitResponse_t OnInit() override;
};
