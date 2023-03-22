#ifndef _VIEWTIME_H_
#define _VIEWTIME_H_

#include "view.h"

class ViewTime : public View {
    public:
        ViewTime(const char* name, TFT_eSPI* tft, View** currentView);
    protected:
        virtual void OnHandle();
    private:
        TFT_eSprite sprite;
};

#endif  //_VIEWTIME_H_