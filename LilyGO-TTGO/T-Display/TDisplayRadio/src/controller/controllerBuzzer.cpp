#include "controller/controllerBuzzer.h"

ControllerBuzzer::ControllerBuzzer(const char* name, gpio_num_t pin) : Controller(name, 0) {
    _pin = pin;
    _song = nullptr;
    _index = 0;
    pinMode(_pin, OUTPUT);
}

bool ControllerBuzzer::OnInit() {
    return true;
}

bool ControllerBuzzer::OnUpdate() {
    bool result = rtttl::isPlaying();
    if (result) rtttl::play();
    return result;
}

void ControllerBuzzer::Play() {
    Stop();
    _song = songs[_index];
    rtttl::begin(_pin, _song);
    _index++;
    if (_index == MAX_SONG) _index = 0;
}

void ControllerBuzzer::Stop() {
    if (rtttl::isPlaying()) rtttl::stop();
    _song = nullptr;
}
