#include <Wire.h>
#include "controllerDevice.h"


ControllerDevice::ControllerDevice(const char* name) : Controller(name) {
    _temperature = 0;
    _humidity = 0;
    _pressure = 0;
}

void ControllerDevice::OnHandle() {
    if (! _bme.begin(BME280_PORT, &Wire)) {
        // Serial.printf("bme280 error\r\n");
        vTaskDelete(_task);
        return;
    }

    _bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF);
    
    for (;;) {
        _temperature = _bme.readTemperature();
        // Serial.printf("Temperature: %f C\r\n", _temperature);
        _humidity = _bme.readHumidity();
        // Serial.printf("Humidity: %f %%\r\n", _humidity);
        _pressure = _bme.readPressure() / 1000.0F * 7.50062;
        // Serial.printf("Pressure: %f мм рт. ст.\r\n", _pressure);

        xSemaphoreGive(_updateEvent);
        vTaskDelay(UPDATE_DEVICE_TIME);
    }
}
