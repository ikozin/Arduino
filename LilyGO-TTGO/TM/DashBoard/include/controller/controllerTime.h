#pragma once

#include "controller/controller.h"
#include <RTClib.h>

class ControllerTime : public Controller {
    public:
        ControllerTime(const char* name, Preferences* prefs) : Controller(name) {
            _updateTimeInSec = 1;
            _prefs = prefs;
        }
    public:
        DateTime getDateTime() const { return _currentTime; }
    protected:
        virtual IterationCode_t OnIteration() override { return IterationCode_t::Stop; }
    protected:
        DateTime _currentTime;
        Preferences* _prefs;
};
