#pragma once

#include "controller/controller.h"
#include "controller/StorageRadio.h"
#include "controller/rda5807m.h"

#define VOLUME_MAX      15

class ControllerRadio : public Controller {
    public:
        ControllerRadio(const char* name, Preferences* prefs, StorageRadio* storage);
        
        StorageRadio* getStorage() const { return _storage; }

        bool getMute() const { return _isMute; }
        bool toggleMute();
        void setMute(bool mute);

        uint16_t getRadioIndex() const { return _currentIndex; }
        bool setRadioIndex(uint16_t index);

        bool changeChannel(int direction);

        uint16_t getVolume() const { return _currentVolume; }
        bool changeVolume(int direction);
        bool setVolume(uint16_t value);

        uint8_t GetRssi() { return _radio.GetRssi(); }
    protected:
        virtual bool OnInit() override;
    private:
        Preferences* _prefs;
        StorageRadio* _storage;
        Rda5807M _radio;
        uint16_t _currentVolume;    // 0..VOLUME_MAX
        uint16_t _currentIndex;
        bool _isMute; 
};
