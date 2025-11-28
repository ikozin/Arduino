#include "controller/controllerNavigator.h"

ControllerNavigator::ControllerNavigator(const char* name, TFT_eSPI* tft, TFT_eSprite* sprite,
    Preferences* prefs, View** views, int16_t size, uint64_t swipeTime) :
    Controller(name, 0) {
    _tft = tft;
    _sprite = sprite;
    _index = 0;
    _prefs = prefs;
    _views = views;
    _size = size;
    _force = true;
    _swipeTime = swipeTime;
    _lastSwipe = 0;
    _buzzer = nullptr;
}

bool ControllerNavigator::OnInit() {
    _index = _prefs->getInt("page", 0);
    return true;
}

bool ControllerNavigator::OnUpdate() {
    uint64_t ticks = millis();
    if (ticks - _lastSwipe > _swipeTime) {
        setDisplayPageNext();
    }
    UpdateView();
    return false;
}

bool ControllerNavigator::setDisplayPage(int16_t page) {
    int max =  _size - 1;
    if (page < 0) {
        page = max;
    }
    if (page > max) {
        page = 0;
    }
    if (_index == page) return false;
    _index = page;
    _force = true;
    _prefs->putInt("page", _index);
    if (_buzzer != nullptr) _buzzer->Play();
    return true;
}

void ControllerNavigator::UpdateView() {
    getView()->Update(_force);
    _tft->startWrite();
    _sprite->pushSprite(0, 0);
    _tft->endWrite();
    if (_force) {
        _lastSwipe = millis();
        _force = false;
    }
}
