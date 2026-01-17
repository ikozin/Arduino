#pragma once

#include "controller/controller.h"
#include <Preferences.h>
#include "display.h"
#include "view/iview.h"

class ControllerNavigator : public Controller {
    public:
        ControllerNavigator(const char* name, TFT_eSPI* tft, TFT_eSprite* sprite,
            Preferences* prefs, IView** views, int16_t size, uint64_t swipeTime);
    protected:
        virtual bool OnInit() override;
        virtual bool OnUpdate() override;
    private:
        TFT_eSPI* _tft;
        TFT_eSprite* _sprite;
        int16_t _index;
        Preferences* _prefs;
        IView** _views;
        int16_t _size;
        bool _force;
        uint64_t _swipeTime;
        uint64_t _lastSwipe;
    private:
        IView* getView() const { return _views[_index]; }
    public:
        void forceUpdate() { _force = true; };
        bool setDisplayPagePrev(void) { return setDisplayPage(_index - 1); }
        bool setDisplayPageNext(void) { return setDisplayPage(_index + 1); }
        bool setDisplayPage(int16_t page);
        void UpdateView();
};