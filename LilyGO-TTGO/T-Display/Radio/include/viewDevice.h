#ifndef _VIEWDEVICE_H_
#define _VIEWDEVICE_H_

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

#endif  //_VIEWDEVICE_H_