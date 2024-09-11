#include "controller/controllerMHZ19.h"

ControllerMHZ19::ControllerMHZ19(const char* name, gpio_num_t rx, gpio_num_t tx):
                    Controller(name), _serial(1), _mhz19() {
    _updateTimeInSec = 60;
    _rx = rx;
    _tx = tx;
    _temperature = 0;
    _ppm = 0;
}

InitResponse_t ControllerMHZ19::OnInit() {
#ifdef MHZ19_FAKE
    _ppm = 600;
    _temperature = 25;
    return OnInitResultStart;
#else
    _serial.begin(9600, SERIAL_8N1, _rx, _tx);
    _mhz19.begin(_serial);
    _mhz19.autoCalibration();
    return OnInitResultStartDelaySec(60);
#endif
}

IterationCode_t ControllerMHZ19::OnIteration() {
#ifdef MHZ19_FAKE
    _ppm += esp_random() > (UINT32_MAX >> 1) ? 10: -10;
    _temperature += esp_random() > (UINT32_MAX >> 1) ? 0.5: -0.5;
#else
    _ppm = _mhz19.getCO2();
    _temperature = _mhz19.getTemperature();
#endif
    // LOGN("%s::getCO2, %d", _name, getCO2())
    // LOGN("%s::getTemperature, %f", _name, getTemperature())

    return IterationCode_t::Ok;
}
