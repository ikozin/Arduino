#include "controller/controllerBme280.h"
#include <Wire.h>

ControllerBme280::ControllerBme280(const char* name):
                    Controller(name) {
    _updateTimeInSec = 60;
    _data = { .Temperature = 0, .Humidity = 0, .Pressure = 0 };
    _value = 0;
}

InitResponse_t ControllerBme280::OnInit() {
#ifdef BME280_FAKE
    LOGN("FAKE START (%s)", _name);
    _data = {
        .Temperature = 30,
        .Humidity = 10,
        .Pressure = 790
    };
    for (int i = 0; i < Size() * Slice(); i++) {
        _value = (float)(random() % 40); 
        AddValue(_value);
    }
    LOGN("FAKE END (%s)", _name);
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
    _data.Temperature += esp_random() > (UINT32_MAX >> 1) ? 0.5: -0.5;
    _data.Humidity += esp_random() > (UINT32_MAX >> 1) ? 0.5: -0.5;
    _data.Pressure += esp_random() > (UINT32_MAX >> 1) ? 1.5: -1.5;
    LOGN("FAKE NEW (%s)", _name);
#else
    _data = {
        .Temperature = _bme.readTemperature(),
        .Humidity = _bme.readHumidity(),
        .Pressure = (float)(_bme.readPressure() / 1000.0F * 7.50062)
    };
#endif
    _value = _data.Temperature;
    AddValue(_value);
    return IterationCode_t::Ok;
}
