#pragma once

#include "view/view.h"
#include "controller/controllerRadio.h"

class ViewRadio : public View {
    private:
        ControllerRadio* _radio;
    public:
        ViewRadio(const char* name, View** currentView, ControllerRadio* radio);
    protected:
        virtual void OnHandle() override;
};
