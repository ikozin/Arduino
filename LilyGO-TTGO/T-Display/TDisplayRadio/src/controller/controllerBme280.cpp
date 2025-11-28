#include "controller/controllerBme280.h"

ControllerBme280::ControllerBme280(const char* name):
                    ControllerValue(name, 60000) {
    _value = { .Temperature = 0, .Humidity = 0, .Pressure = 0 };
}

bool ControllerBme280::OnInit() {
    if (!_bme.begin(BME280_PORT, &Wire)) return false;
    _bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF);
    return true;
}

bool ControllerBme280::OnUpdate() {
    _value.Temperature = _bme.readTemperature();
    _value.Humidity = _bme.readHumidity();
    _value.Pressure = (float)(_bme.readPressure() / 1000.0F * 7.50062);
    return true;
}
