#ifndef _VIEWTIME_H_
#define _VIEWTIME_H_

#include "view.h"

class ViewTime : public View {
    public:
        ViewTime(const char* name, View** currentView);
    protected:
        virtual void OnHandle();
};

#endif  //_VIEWTIME_H_