#include "controller/controllerBme280.h"
#include <Wire.h>

ControllerBme280::ControllerBme280(const char* name):
                    Controller(name) {
    _updateTimeInSec = 60;
    _value = { .Temperature = 0, .Humidity = 0, .Pressure = 0 };
}

InitResponse_t ControllerBme280::OnInit() {
#ifdef BME280_FAKE
    _value.Temperature = 30;
    _value.Humidity = 10;
    _value.Pressure = 790;
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
    _value.Temperature += esp_random() > (UINT32_MAX >> 1) ? 0.5: -0.5;
    _value.Humidity += esp_random() > (UINT32_MAX >> 1) ? 0.5: -0.5;
    _value.Pressure += esp_random() > (UINT32_MAX >> 1) ? 1.5: -1.5;
#else
    _value.Temperature = _bme.readTemperature();
    _value.Humidity = _bme.readHumidity();
    _value.Pressure = (float)(_bme.readPressure() / 1000.0F * 7.50062);
#endif
    return IterationCode_t::Ok;
}
