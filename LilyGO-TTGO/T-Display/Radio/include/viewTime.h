#ifndef _VIEWTIME_H_
#define _VIEWTIME_H_

#include "view.h"
#include "controllerTime.h"

class ViewTime : public View {
    public:
        ViewTime(const char* name, View** currentView, ControllerTime* device);
    protected:
        virtual void OnHandle();
    private:
        uint16_t getDateColor(DateTime& date);
    private:
        ControllerTime* _device;
};

#endif  //_VIEWTIME_H_