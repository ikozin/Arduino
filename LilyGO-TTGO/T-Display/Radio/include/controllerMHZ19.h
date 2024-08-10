#pragma once

#include <HardwareSerial.h>
#include <MHZ19.h> 
#include "controller.h"

class ControllerMHZ19 : public Controller {
    public:
        ControllerMHZ19(const char* name, gpio_num_t rx, gpio_num_t tx, SemaphoreHandle_t updateEvent = nullptr);
    public:
        float getTemperature() const { return _temperature; }
        int getCO2() const { return _ppm; }
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        gpio_num_t  _rx;
        gpio_num_t  _tx;

        HardwareSerial _serial;
        MHZ19   _mhz19;
        float _temperature;
        int _ppm;
};
