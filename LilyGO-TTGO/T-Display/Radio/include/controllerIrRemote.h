#pragma once

#include "controller.h"
#include "controllerRadio.h"
#include "infrared_tools/ir_timings.h"
#include "infrared_tools/ir_tools.h"
#include "driver/rmt.h"

class ControllerIrRemote : public ControllerT<ControllerRadio> {
    public:
        ControllerIrRemote(const char* name, gpio_num_t pin, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual void OnDone() override;
        virtual bool OnIteration() override;
    private:
        gpio_num_t _pin;
        RingbufHandle_t _rb;
        ir_parser_t * _ir_parser;
        uint32_t _addr;
        uint32_t _cmd;
        bool _repeat;
    public:
        uint32_t GetAddress() const { return _addr; }
        uint32_t GetCommand() const { return _cmd; }
        bool IsRepeat() const { return _repeat; }
};

//extern ControllerIrRemote ctrlIrRemote;
