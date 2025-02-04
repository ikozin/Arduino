#pragma once

#include "controller/controller.h"
#include <Audio.h>

#define I2S_DIN         19    // DIN
#define I2S_BCK         26    // BCK
#define I2S_LCK         25    // LBCK

#define VOLUME_MAX      21

class ControllerRadio : public Controller {
    public:
        ControllerRadio(const char* name, Preferences* prefs, Audio* audio);
    public:
        bool GetMute() const { return _isMute; }
        void ToggleMute();
        void SetMute(bool mute);
        uint16_t GetVolume() const { return _currentVolume; }
        void ChangeVolume(int direction);
        void SetVolume(uint16_t value);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override { return IterationCode_t::Ok; };
    private:
        Preferences* _prefs;
        Audio* _audio;
        uint16_t _currentVolume;
        bool _isMute;
};
