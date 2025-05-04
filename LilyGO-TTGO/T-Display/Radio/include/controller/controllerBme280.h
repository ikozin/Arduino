#pragma once

#include "controller/controller.h"
#include <Adafruit_BME280.h>

#define BME280_PORT 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

typedef struct _Bme280Data_ {
    float Temperature;
    float Humidity;
    float Pressure;
} Bme280Data;

class ControllerBme280 : public Controller, public ISensor<Bme280Data> {
    public:
        ControllerBme280(const char* name);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override;
    private:
        Adafruit_BME280 _bme;   // I2C
};
