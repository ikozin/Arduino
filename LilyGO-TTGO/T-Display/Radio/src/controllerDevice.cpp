#include <Wire.h>
#include "controllerDevice.h"

ControllerDevice::ControllerDevice(const char* name) : Controller(name), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _temperature = 0;
    _humidity = 0;
    _pressure = 0;

    _dynamicValue = 0; 
    _staticValue = 0;
    _impulseValue = 0;
}

void ControllerDevice::OnHandle() {
    if (! _bme.begin(BME280_PORT, &Wire)) {
        // Serial.printf("bme280 error\r\n");
        return;
    }
    if (!_radSens.init()) {
        // Serial.printf("RadSens error\r\n");
        return;
    }

    _bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF);
    
    for (;;) {
        _temperature = _bme.readTemperature();
        _humidity = _bme.readHumidity();
        _pressure = _bme.readPressure() / 1000.0F * 7.50062;

        _dynamicValue = _radSens.getRadIntensyDynamic(); 
        _staticValue = _radSens.getRadIntensyStatic();
        _impulseValue = _radSens.getNumberOfPulses();

        xSemaphoreGive(_updateEvent);
        vTaskDelay(UPDATE_DEVICE_TIME);
    }
}
