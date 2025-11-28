#pragma once

#include "controller/controller.h"
#include "controller/controllerIrRemote.h"
/*
    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    ┃ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┃
Code┃ ┃     69     ┃ ┃     70     ┃ ┃     71     ┃ ┃
Name┃ ┃    "CH-"   ┃ ┃    "CH"    ┃ ┃    "CH+"   ┃ ┃
    ┃ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┃
    ┃ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┃
Code┃ ┃     68     ┃ ┃     64     ┃ ┃     67     ┃ ┃
Name┃ ┃   "PREV"   ┃ ┃   "NEXT"   ┃ ┃"PLAY/PAUSE"┃ ┃
    ┃ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┃
    ┃ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┃
Code┃ ┃      7     ┃ ┃     21     ┃ ┃      9     ┃ ┃
Name┃ ┃   "VOL-"   ┃ ┃   "VOL+"   ┃ ┃    "EQ"    ┃ ┃
    ┃ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┃
    ┃ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┃
Code┃ ┃     22     ┃ ┃     25     ┃ ┃     13     ┃ ┃
Name┃ ┃     "0"    ┃ ┃   "100+"   ┃ ┃   "200+"   ┃ ┃
    ┃ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┃
    ┃ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┃
Code┃ ┃     12     ┃ ┃     24     ┃ ┃     94     ┃ ┃
Name┃ ┃     "1"    ┃ ┃     "2"    ┃ ┃     "3"    ┃ ┃
    ┃ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┃
    ┃ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┃
Code┃ ┃      8     ┃ ┃     28     ┃ ┃     90     ┃ ┃
Name┃ ┃     "4"    ┃ ┃     "5"    ┃ ┃     "6"    ┃ ┃
    ┃ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┃
    ┃ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓ ┃
Code┃ ┃     66     ┃ ┃     82     ┃ ┃     74     ┃ ┃
Name┃ ┃     "7"    ┃ ┃     "8"    ┃ ┃     "9"    ┃ ┃
    ┃ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛ ┃
    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

class ControllerIrRemote_CarMp3 : public ControllerIrRemote {
    public:
        ControllerIrRemote_CarMp3(const char* name, gpio_num_t pin) : ControllerIrRemote(name, pin) {
        };
    protected:
        virtual bool OnCommand() override {
            if (_navigator == nullptr || _radio == nullptr) return false;
            LOGN("%s, %d", _name, _value.Command);
            if (!_value.IsRepeat) {
                if (_value.Command == 68) _radio->changeChannel(-1);
                if (_value.Command == 64) _radio->changeChannel(+1);
                if (_value.Command ==  7) _radio->changeVolume(-1);
                if (_value.Command == 21) _radio->changeVolume(+1);
                if (_value.Command == 67) _radio->toggleMute();
                if (_value.Command == 69) _navigator->setDisplayPagePrev();
                if (_value.Command == 71) _navigator->setDisplayPageNext();

                if (_value.Command == 22) _navigator->setDisplayPage(0);
                if (_value.Command == 12) _navigator->setDisplayPage(1);
                if (_value.Command == 24) _navigator->setDisplayPage(2);
                if (_value.Command == 94) _navigator->setDisplayPage(3);
                if (_value.Command ==  8) _navigator->setDisplayPage(4);
                if (_value.Command == 28) _navigator->setDisplayPage(5);
                if (_value.Command == 90) _navigator->setDisplayPage(6);
                if (_value.Command == 66) _navigator->setDisplayPage(7);
                if (_value.Command == 82) _navigator->setDisplayPage(8);
                if (_value.Command == 74) _navigator->setDisplayPage(9);
            }
            return true;
        }
};
