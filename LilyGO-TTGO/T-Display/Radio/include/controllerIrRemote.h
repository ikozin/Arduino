#pragma once

#include "controller.h"
#include "controllerRadio.h"

class ControllerIrRemote : public Controller {
    public:
        ControllerIrRemote();
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        ControllerRadio* _radio;
    public:
        ControllerIrRemote& attachControllerRadio(ControllerRadio* radio);
};

//extern ControllerIrRemote ctrlIrRemote;
