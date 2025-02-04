#include "controller/controllerRadio.h"
#include <Wire.h>

ControllerRadio::ControllerRadio(const char* name, Preferences* prefs, Audio* audio):
                    Controller(name) {
    _prefs = prefs;
    _audio = audio;
    _currentVolume = 0;
    _isMute = false;
}

InitResponse_t ControllerRadio::OnInit() {
    if (_audio->setPinout(I2S_BCK, I2S_LCK, I2S_DIN)) {
        SetMute(_prefs->getBool("mute", false));
        SetVolume(_prefs->getInt("volume", 2));
        _audio->connecttohost("https://nashe1.hostingradio.ru/nashe-128.mp3");
        return OnInitResultStop;
    }
    return OnInitResultERROR;
}

void ControllerRadio::ToggleMute() {
    SetMute(!_isMute);
}

void ControllerRadio::SetMute(bool mute) {
    _isMute = mute;
    _audio->setVolume(_isMute ? 0 : _currentVolume);
    _prefs->putBool("mute", _isMute);
    FireUpdateEvent();
}

void ControllerRadio::ChangeVolume(int direction) {
    if (direction > 0) {
        if (_currentVolume < VOLUME_MAX) {
            SetVolume(_currentVolume + 1);
        }
    }
    if (direction < 0) {
        if (_currentVolume > 0) {
            SetVolume(_currentVolume - 1);
        }
    }
}

void ControllerRadio::SetVolume(uint16_t value) {
    if (value > VOLUME_MAX) value = VOLUME_MAX;
    if (_currentVolume == value) return; 
    _currentVolume = value;
    _prefs->putInt("volume", _currentVolume);
    if (!_isMute) {
        _audio->setVolume(_currentVolume);
    }
    FireUpdateEvent();
}
