#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include "view/view.h"

class Navigator
{
    public:
        Navigator(Preferences* prefs, View** views, int16_t size) {
            _index = 0;
            _prefs = prefs;
            _views = views;
            _size = size;
        }
    private:
        int16_t _index;
        Preferences* _prefs;
        View** _views;
        int16_t _size;
    public:
        void setDisplayPage(int16_t page) {
            int max =  _size - 1;
            if (page < 0) {
                page = max;
            }
            if (page > max) {
                page = 0;
            }
            if (_index == page) return;
            _index = page;
            _prefs->putInt("page", _index);
            View* currentView = _views[_index];
            xSemaphoreGive(currentView->GetEvent());
        }

        void setDisplayPagePrev(void) {
            setDisplayPage(_index - 1);
        }
        void setDisplayPageNext(void) {
            setDisplayPage(_index + 1);
        }
};