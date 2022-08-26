#ifndef _CONTROLLERRADIO_H_
#define _CONTROLLERRADIO_H_

#include "controller.h"
#include "rda5807m.h"
#include <Preferences.h>

#define VOLUME_MAX      15

class ControllerRadio : public Controller {
    public:
        ControllerRadio(const char* name, Preferences* prefs);

        bool getMute() const { return _isMute; }
        void toggleMute();

        uint16_t getRadio() const { return _currentIndex; }
        void changeChannel(int direction);

        uint16_t getVolume() const { return _currentVolume; }
        void changeVolume(int direction);

        uint8_t GetRssi() { return _radio.GetRssi(); }
    protected:
        virtual void OnHandle();
    private:
        Preferences* _prefs;
        Rda5807M _radio;
        uint16_t _currentVolume;    // 0..VOLUME_MAX
        uint16_t _currentIndex;
        bool _isMute; 
    private:
        void setMute(bool mute);
        void setVolume(uint16_t value);
        void setRadio(uint16_t index);
};

#endif  //_CONTROLLERRADIO_H_