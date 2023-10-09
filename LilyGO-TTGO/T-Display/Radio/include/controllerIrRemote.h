#ifndef _CONTROLLERIRREMOTE_H_
#define _CONTROLLERIRREMOTE_H_

#include "controller.h"
#include "controllerRadio.h"

class ControllerIrRemote : public Controller {
    public:
        ControllerIrRemote();
    protected:
        virtual void OnHandle();
    private:
        ControllerRadio* _radio;
    public:
        ControllerIrRemote& attachControllerRadio(ControllerRadio* radio);
};

//extern ControllerIrRemote ctrlIrRemote;

#endif  //_CONTROLLERIRREMOTE_H_