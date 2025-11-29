#include "controller/controllerSoftTime.h"
#include "main.h"

ControllerSoftTime::ControllerSoftTime(const char* name, Preferences* prefs):
                    ControllerTime(name, prefs) {
}

InitResponse_t ControllerSoftTime::OnInit() {
    _value = { .year = 2000, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 0 };
    return OnInitResultStart;
}
