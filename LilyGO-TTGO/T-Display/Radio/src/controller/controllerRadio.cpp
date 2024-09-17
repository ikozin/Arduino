#include "controller/controllerRadio.h"
#include "main.h"

ControllerRadio::ControllerRadio(const char* name, Preferences* prefs, RadioStorage* storage):
                    Controller(name) {
    _prefs = prefs;
    _storage = storage;
    _currentVolume = 0;
    _currentIndex  = 0;
    _isMute = false;
}

InitResponse_t ControllerRadio::OnInit() {
    _radio.Init();
    setRadioIndex(_prefs->getInt("station", 35));
    setVolume(_prefs->getInt("volume", 2));
    setMute(_prefs->getBool("mute", false));
    return OnInitResultStop;
}

void ControllerRadio::toggleMute() {
    setMute(!_isMute);
}

void ControllerRadio::changeChannel(int direction) {
    if (direction > 0) {
        if (_currentIndex < _storage->length() - 1) {
            setRadioIndex(_currentIndex + 1);
        }
    }
    if (direction < 0) {
        if (_currentIndex > 0) {
            setRadioIndex(_currentIndex - 1);
        }
    }
}

void ControllerRadio::changeVolume(int direction) {
    if (direction > 0) {
        if (_currentVolume < VOLUME_MAX) {
            setVolume(_currentVolume + 1);
        }
    }
    if (direction < 0) {
        if (_currentVolume > 0) {
            setVolume(_currentVolume - 1);
        }
    }
}


void ControllerRadio::setMute(bool mute) {
    _isMute = mute;
    _radio.SetMute(_isMute);
    _prefs->putBool("mute", _isMute);  
    FireUpdateEvent();
}

void ControllerRadio::setRadioIndex(uint16_t index) {
    if (index >= _storage->length()) index = 0;
    if (_currentIndex == index) return;
    _currentIndex = index;
    auto rec = _storage->getItem(_currentIndex);
    uint16_t band = rec->band;
    _radio.SetChannel(band);
    _prefs->putInt("station", _currentIndex);  
    FireUpdateEvent();
}

void ControllerRadio::setVolume(uint16_t value) {
    if (value > VOLUME_MAX) value = VOLUME_MAX;
    if (_currentVolume == value) return; 
    _currentVolume = value;
    _radio.SetVolume(_currentVolume);
    _prefs->putInt("volume", _currentVolume);
    FireUpdateEvent();
}
