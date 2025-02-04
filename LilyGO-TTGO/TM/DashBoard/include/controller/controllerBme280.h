#pragma once

#include "controller/controller.h"
#include <Adafruit_BME280.h>

#define BME280_PORT 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

class ControllerBme280 : public Controller {
    public:
        ControllerBme280(const char* name);
    public:
        float getTemperature() const { return _temperature; }
        float getHumidity() const { return _humidity; }
        float getPressure() const { return _pressure; }
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override;
    private:
        Adafruit_BME280 _bme;   // I2C
        float _temperature;
        float _humidity;
        float _pressure;
};
