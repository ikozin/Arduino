#pragma once

#include <Adafruit_BME280.h>
#include "controller.h"
#include <CG_RadSens.h>

#define BME280_PORT 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

class ControllerDevice : public Controller {
    public:
        ControllerDevice(const char* name);
    public:
        float getTemperature() const { return _temperature; }
        float getHumidity() const { return _humidity; }
        float getPressure() const { return _pressure; }

        float getDynamic() const { return _dynamicValue; }
        float getStatic() const { return _staticValue; }
        float getImpulse() const { return _impulseValue; }
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        Adafruit_BME280 _bme;   // I2C
        float _temperature;
        float _humidity;
        float _pressure;

        CG_RadSens _radSens;    // I2C
        float _dynamicValue; 
        float _staticValue;
        float _impulseValue;
};
