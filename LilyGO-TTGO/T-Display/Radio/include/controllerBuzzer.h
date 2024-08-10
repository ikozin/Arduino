#pragma once

#include "controller.h"
#include "RTTTL.h"

class ControllerBuzzer : public Controller {
    public:
        ControllerBuzzer(const char* name, gpio_num_t pin, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        RTTTL   _rtttl;
    public:
        void Play(const char* song);
        void Stop();
};
