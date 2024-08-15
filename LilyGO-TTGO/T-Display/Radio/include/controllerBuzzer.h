#pragma once

#include "controller.h"
#include "driver/rmt.h"

class ControllerBuzzer : public Controller {
    public:
        ControllerBuzzer(const char* name, gpio_num_t pin, rmt_channel_t channel = RMT_CHANNEL_1, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override;
    private:
        rmt_channel_t       _channel;
        uint32_t            _volume;
        SemaphoreHandle_t   _startEvent;

        const char *        _song;
        byte                _duration;
        byte                _octava;
        long                _wholeNote;
    private:
        void noTone();
        void tone(int frq, int duration);
    public:
        void Play(const char* song);
        void Stop();
};
