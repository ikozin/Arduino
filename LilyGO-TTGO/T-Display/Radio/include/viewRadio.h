#ifndef _VIEWRADIO_H_
#define _VIEWRADIO_H_

#include "view.h"
#include "controllerRadio.h"

class ViewRadio : public View {
    private:
        ControllerRadio* _radio;
    public:
        ViewRadio(const char* name, TFT_eSPI* tft, View** currentView, ControllerRadio* radio);
    protected:
        virtual void OnHandle();
    private:
        void displayVolume();
        void displayMute();
        void displayLevel();
        void displayFreq();
};

#endif  //_VIEWRADIO_H_