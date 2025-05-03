#include "controller/controllerIrRemote.h"
#include "TinyIRReceiver.hpp"

// 
//  ┌──────────────────────────────┐
//  │ ┌──────┐  ┌──────┐  ┌──────┐ │
//  │ │"PWR" │  │"RET" │  │"MOD" │ │
//  │ │  69  │  │  70  │  │  71  │ │
//  │ └──────┘  └──────┘  └──────┘ │
//  │ ┌──────┐  ┌──────┐  ┌──────┐ │
//  │ │"TIME"│  │"SEL" │  │ "EQ" │ │
//  │ │  68  │  │  64  │  │  67  │ │
//  │ └──────┘  └──────┘  └──────┘ │
//  │ ┌──────┐  ┌──────┐  ┌──────┐ │
//  │ │"PREV"│  │"NEXT"│  │"PLAY"│ │
//  │ │   7  │  │  21  │  │   9  │ │
//  │ └──────┘  └──────┘  └──────┘ │
//  │ ┌──────┐  ┌──────┐  ┌──────┐ │
//  │ │"VOL-"│  │"VOL+"│  │ "0"  │ │
//  │ │  22  │  │  25  │  │  13  │ │
//  │ └──────┘  └──────┘  └──────┘ │
//  │ ┌──────┐  ┌──────┐  ┌──────┐ │
//  │ │ "1"  │  │ "2"  │  │ "3"  │ │
//  │ │  12  │  │  24  │  │  94  │ │
//  │ └──────┘  └──────┘  └──────┘ │
//  │ ┌──────┐  ┌──────┐  ┌──────┐ │
//  │ │ "4"  │  │ "5"  │  │ "6"  │ │
//  │ │   8  │  │  28  │  │  90  │ │
//  │ └──────┘  └──────┘  └──────┘ │
//  │ ┌──────┐  ┌──────┐  ┌──────┐ │
//  │ │ "7"  │  │ "8"  │  │ "9"  │ │
//  │ │  66  │  │  82  │  │  74  │ │
//  │ └──────┘  └──────┘  └──────┘ │
//  └──────────────────────────────┘

ControllerIrRemote::ControllerIrRemote(const char* name, gpio_num_t pin) :
                        ControllerT(name) {
    _pin = pin;
}

InitResponse_t ControllerIrRemote::OnInit() {
    return (initPCIInterruptForTinyReceiver(this)) ? OnInitResultStop : OnInitResultERROR;
}

uint8_t ControllerIrRemote::GetAddress() {
     return TinyIRReceiverData.Address;
}
uint8_t ControllerIrRemote::GetCommand() {
    return TinyIRReceiverData.Command;
}
bool ControllerIrRemote::IsRepeat() {
    return TinyIRReceiverData.Flags & IRDATA_FLAGS_IS_REPEAT;
}

IRAM_ATTR void handleReceivedTinyIRData(void* parameter) {
    ControllerIrRemote* controller = static_cast<ControllerIrRemote*>(parameter);
    for (int i = 0; i < EventListMax && controller->_eventList[i] != nullptr; i++) {
        xSemaphoreGiveFromISR(controller->_eventList[i], nullptr);
    }
}

