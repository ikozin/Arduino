#include "controllerMHZ19.h"

ControllerMHZ19::ControllerMHZ19(const char* name):
                    Controller(name), _serial(1), _mhz19() {
    _updateTimeInSec = 10;

    _temperature = 0;
    _ppm = 0;
}

InitResponse_t ControllerMHZ19::OnInit() {
    _serial.begin(9600, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
    _mhz19.begin(_serial);
    _mhz19.autoCalibration(false);
    _mhz19.setRange(5000);
    return OnInitDelayInSec(600);
}

bool ControllerMHZ19::OnIteration() {
    LOGN("ControllerMHZ19::OnIteration")

    _ppm = _mhz19.getCO2();
    _temperature = _mhz19.getTemperature();

    LOGN("ControllerMHZ19::getCO2, %d", getCO2())
    LOGN("ControllerMHZ19::getTemperature, %f", getTemperature())

    return true;
}