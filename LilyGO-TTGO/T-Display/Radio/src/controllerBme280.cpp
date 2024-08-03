#include <Wire.h>
#include "controllerBme280.h"

ControllerBme280::ControllerBme280(const char* name, SemaphoreHandle_t updateEvent):
                    Controller(name, updateEvent) {
    _updateTimeInSec = 60;
    
    _temperature = 0;
    _humidity = 0;
    _pressure = 0;
}

InitResponse_t ControllerBme280::OnInit() {
    if ( _bme.begin(BME280_PORT, &Wire)) {
        _bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X1, // temperature
                        Adafruit_BME280::SAMPLING_X1, // pressure
                        Adafruit_BME280::SAMPLING_X1, // humidity
                        Adafruit_BME280::FILTER_OFF);
        return OnInitResultOK;
    }
    return OnInitResultERROR;
}

bool ControllerBme280::OnIteration() {
    LOGN("ControllerBme280::OnIteration")

    _temperature = _bme.readTemperature();
    _humidity = _bme.readHumidity();
    _pressure = _bme.readPressure() / 1000.0F * 7.50062;

    LOGN("ControllerBme280::getTemperature, %f", getTemperature())
    LOGN("ControllerBme280::getHumidity, %f", getHumidity())
    LOGN("ControllerBme280::getPressure, %f", getPressure())

    return true;
}
