#pragma once

#include "controller/controller.h"
#include "controller/controllerBuzzer.h"
#include <Preferences.h>
#include "display.h"
#include "view/view.h"

class ControllerNavigator : public Controller {
    public:
        ControllerNavigator(const char* name, TFT_eSPI* tft, TFT_eSprite* sprite,
            Preferences* prefs, View** views, int16_t size, uint64_t swipeTime);
    protected:
        virtual bool OnInit() override;
        virtual bool OnUpdate() override;
    protected:
        ControllerBuzzer* _buzzer;
    public:
        void Attach(ControllerBuzzer* buzzer) {
            _buzzer = buzzer;
        }
    private:
        TFT_eSPI* _tft;
        TFT_eSprite* _sprite;
        int16_t _index;
        Preferences* _prefs;
        View** _views;
        int16_t _size;
        bool _force;
        uint64_t _swipeTime;
        uint64_t _lastSwipe;
    public:
        View* getView() const { return _views[_index]; }
        bool setDisplayPagePrev(void) { return setDisplayPage(_index - 1); }
        bool setDisplayPageNext(void) { return setDisplayPage(_index + 1); }
        bool setDisplayPage(int16_t page);
        void UpdateView();
};