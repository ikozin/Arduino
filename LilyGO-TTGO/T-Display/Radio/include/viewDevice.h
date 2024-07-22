#pragma once

#include "view.h"
#include "controllerDevice.h"
class ViewDevice : public View {
    public:
        ViewDevice(const char* name, View** currentView, ControllerDevice* device);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerDevice* _device;
};
