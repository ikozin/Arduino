#ifndef _CONTROLLERTIME_H_
#define _CONTROLLERTIME_H_

#include "controller.h"

class ControllerTime : public Controller {
    public:
        ControllerTime(const char* name);
    protected:
        virtual void OnHandle();
};

#endif  //_CONTROLLERTIME_H_