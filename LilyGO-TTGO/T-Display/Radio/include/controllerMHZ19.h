#pragma once

#include <HardwareSerial.h>
#include <MHZ19.h> 
#include "controller.h"

#define UART_RX_PIN  (13)
#define UART_TX_PIN  (15)

class ControllerMHZ19 : public Controller {
    public:
        ControllerMHZ19(const char* name);
    public:
        float getTemperature() const { return _temperature; }
        int getCO2() const { return _ppm; }
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        HardwareSerial _serial;
        MHZ19   _mhz19;
        float _temperature;
        int _ppm;
};
