#include "controllerMHZ19.h"

ControllerMHZ19::ControllerMHZ19(const char* name, gpio_num_t rx, gpio_num_t tx, SemaphoreHandle_t updateEvent):
                    Controller(name, updateEvent), _serial(1), _mhz19() {
    _updateTimeInSec = 10;
    _rx = rx;
    _tx = tx;
    _temperature = 0;
    _ppm = 0;
}

InitResponse_t ControllerMHZ19::OnInit() {
    _serial.begin(9600, SERIAL_8N1, _rx, _tx);
    _mhz19.begin(_serial);
    _mhz19.autoCalibration();
    _mhz19.setRange(2000);
    DelayInMin(20);
    _mhz19.zeroSpan(2000);
    return OnInitResultStartDelaySec(60);
}

bool ControllerMHZ19::OnIteration() {
    _ppm = _mhz19.getCO2();
    _temperature = _mhz19.getTemperature();
    LOGN("%s::getCO2, %d", _name, getCO2())
    LOGN("%s::getTemperature, %f", _name, getTemperature())

    return true;
}
