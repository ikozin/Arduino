#pragma once

#include "controller/controllerTime.h"

class ControllerTimeWeb : public ControllerTime {
    public:
        ControllerTimeWeb(const char* name, Preferences* prefs);
    protected:
        virtual bool OnInit() override;
        virtual bool OnUpdate() override;
    public:
        void SyncTime();
};
