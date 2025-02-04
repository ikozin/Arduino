#include "controller/controllerBme280.h"
#include <Wire.h>

ControllerBme280::ControllerBme280(const char* name):
                    Controller(name) {
    _updateTimeInSec = 60;
    
    _temperature = 0;
    _humidity = 0;
    _pressure = 0;
}

InitResponse_t ControllerBme280::OnInit() {
#ifdef BME280_FAKE
    _temperature = 25;
    _humidity = 30;
    _pressure = 670;
    return OnInitResultStart;
#else
    if ( _bme.begin(BME280_PORT, &Wire)) {
        _bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X1, // temperature
                        Adafruit_BME280::SAMPLING_X1, // pressure
                        Adafruit_BME280::SAMPLING_X1, // humidity
                        Adafruit_BME280::FILTER_OFF);
        return OnInitResultStart;
    }
    return OnInitResultERROR;
#endif
}

IterationCode_t ControllerBme280::OnIteration() {
#ifdef BME280_FAKE
    _temperature += esp_random() > (UINT32_MAX >> 1) ? 0.5: -0.5;
    _humidity += esp_random() > (UINT32_MAX >> 1) ? 0.5: -0.5;
    _pressure += esp_random() > (UINT32_MAX >> 1) ? 1.5: -1.5;
#else
    _temperature = _bme.readTemperature();
    _humidity = _bme.readHumidity();
    _pressure = _bme.readPressure() / 1000.0F * 7.50062;
#endif

    // LOGN("%s::getTemperature, %f", _name, getTemperature())
    // LOGN("%s::getHumidity, %f", _name, getHumidity())
    // LOGN("%s::getPressure, %f", _name, getPressure())

    return IterationCode_t::Ok;
}
