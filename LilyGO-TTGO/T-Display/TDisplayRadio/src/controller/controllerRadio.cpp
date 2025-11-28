#include "controller/controllerRadio.h"

ControllerRadio::ControllerRadio(const char* name, Preferences* prefs, StorageRadio* storage):
                    Controller(name, portMAX_DELAY) {
    _prefs = prefs;
    _storage = storage;
    _currentVolume = 0;
    _currentIndex  = 0;
    _isMute = false;
}

bool ControllerRadio::OnInit() {
    if (!_storage->load()) {
        return false;
    }
    _radio.Init();
    setRadioIndex(_prefs->getInt("station", 35));
    setVolume(_prefs->getInt("volume", 2));
    setMute(_prefs->getBool("mute", false));
    return true;
}

bool ControllerRadio::toggleMute() {
    setMute(!_isMute);
    return true;
}

bool ControllerRadio::changeChannel(int direction) {
    if (direction > 0) {
        if (_currentIndex < _storage->length() - 1) {
            return setRadioIndex(_currentIndex + 1);
        }
    }
    if (direction < 0) {
        if (_currentIndex > 0) {
            return setRadioIndex(_currentIndex - 1);
        }
    }
    return false;
}

bool ControllerRadio::changeVolume(int direction) {
    if (direction > 0) {
        if (_currentVolume < VOLUME_MAX) {
            return setVolume(_currentVolume + 1);
        }
    }
    if (direction < 0) {
        if (_currentVolume > 0) {
            return setVolume(_currentVolume - 1);
        }
    }
    return false;
}


void ControllerRadio::setMute(bool mute) {
    _isMute = mute;
    _radio.SetMute(_isMute);
    _prefs->putBool("mute", _isMute);  
    setEvent();
}

bool ControllerRadio::setRadioIndex(uint16_t index) {
    if (index >= _storage->length()) index = 0;
    if (_currentIndex == index) return false;
    _currentIndex = index;
    auto rec = _storage->getItem(_currentIndex);
    uint16_t band = rec->band;
    _radio.SetChannel(band);
    _prefs->putInt("station", _currentIndex);  
    setEvent();
    return true;
}

bool ControllerRadio::setVolume(uint16_t value) {
    if (value > VOLUME_MAX) value = VOLUME_MAX;
    if (_currentVolume == value) return false; 
    _currentVolume = value;
    _radio.SetVolume(_currentVolume);
    _prefs->putInt("volume", _currentVolume);
    setEvent();
    return true;
}
