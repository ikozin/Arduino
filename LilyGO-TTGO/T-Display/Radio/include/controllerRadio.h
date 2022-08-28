#ifndef _CONTROLLERRADIO_H_
#define _CONTROLLERRADIO_H_

#include <Preferences.h>
#include "controller.h"
#include "controllerRadioStorage.h"
#include "rda5807m.h"

#define VOLUME_MAX      15

class ControllerRadio : public Controller {
    public:
        ControllerRadio(const char* name, Preferences* prefs, ControllerRadioStorage* storage);
        
        ControllerRadioStorage* getStorage() const { return _storage; }

        bool getMute() const { return _isMute; }
        void toggleMute();
        void setMute(bool mute);

        uint16_t getRadioIndex() const { return _currentIndex; }
        void setRadioIndex(uint16_t index);

        void changeChannel(int direction);

        uint16_t getVolume() const { return _currentVolume; }
        void changeVolume(int direction);
        void setVolume(uint16_t value);

        uint8_t GetRssi() { return _radio.GetRssi(); }
    protected:
        virtual void OnHandle();
    private:
        Preferences* _prefs;
        ControllerRadioStorage* _storage;
        Rda5807M _radio;
        uint16_t _currentVolume;    // 0..VOLUME_MAX
        uint16_t _currentIndex;
        bool _isMute; 
};

#endif  //_CONTROLLERRADIO_H_