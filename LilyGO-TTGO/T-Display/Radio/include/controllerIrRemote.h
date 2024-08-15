#pragma once

#include "controller.h"
#include "controllerRadio.h"
#include "driver/rmt.h"
#include "ir_tools.h"


class ControllerIrRemote : public ControllerT<ControllerRadio> {
    public:
        ControllerIrRemote(const char* name, gpio_num_t pin, rmt_channel_t channel = RMT_CHANNEL_0, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override;
        virtual void OnDone() override;
    private:
        gpio_num_t      _pin;
        rmt_channel_t   _channel;
        uint32_t        _addr;
        uint32_t        _cmd;
        bool            _repeat;
        ir_parser_t*    _ir_parser;
        RingbufHandle_t _rb;
    public:
        uint32_t GetAddress() const { return _addr; }
        uint32_t GetCommand() const { return _cmd; }
        bool IsRepeat() const { return _repeat; }
};

