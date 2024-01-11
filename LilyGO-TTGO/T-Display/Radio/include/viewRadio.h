#ifndef _VIEWRADIO_H_
#define _VIEWRADIO_H_

#include "view.h"
#include "controllerRadio.h"

class ViewRadio : public View {
    private:
        ControllerRadio* _radio;
    public:
        ViewRadio(const char* name, View** currentView, ControllerRadio* radio);
    protected:
        virtual void OnHandle() override;
};

#endif  //_VIEWRADIO_H_