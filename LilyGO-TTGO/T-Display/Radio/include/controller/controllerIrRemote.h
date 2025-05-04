#pragma once

#include "controller/controller.h"
#include "controller/controllerRadio.h"

#define IR_RECEIVE_PIN          GPIO_NUM_13
#define DECODE_NEC
#define SEND_PWM_BY_TIMER
#define NO_LED_FEEDBACK_CODE	
#define MARK_EXCESS_MICROS    20    // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.
#define USE_CALLBACK_FOR_TINY_RECEIVER

typedef struct _IrData_ {
    uint8_t Address;
    uint8_t Command;
    bool IsRepeat;
} IrData;

class ControllerIrRemote : public ControllerT<ControllerRadio>, public ISensor<IrData> {
    friend IRAM_ATTR void handleReceivedTinyIRData(void* parameter);
    public:
        ControllerIrRemote(const char* name, gpio_num_t pin);
    private:
        gpio_num_t  _pin;
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override { return IterationCode_t::Stop; }
};
