#include "controllerIrRemote.h"
#include "IrRemote_CarMP3.h"

#define IR_INPUT_PIN        13
#define DO_NOT_USE_FEEDBACK_LED
#include "TinyIRReceiver.hpp"

ControllerIrRemote ctrlIrRemote;
volatile uint16_t  ir_cmd;
volatile bool     ir_repeat;

ControllerIrRemote::ControllerIrRemote() : Controller("CtrlIrRemote") {
    _radio = NULL;
}

void ControllerIrRemote::attachControllerRadio(ControllerRadio* radio) {
    _radio = radio;
}

void ControllerIrRemote::OnHandle() {
    initPCIInterruptForTinyReceiver(); 
    for (;;) {
        xSemaphoreTake(_updateEvent, portMAX_DELAY);
        Serial.printf("\r\nIR Receiver Core = %d, CMD=0x%04X R=%d\n\r\n", xPortGetCoreID(), ir_cmd, ir_repeat);
        if (!ir_repeat) {
            switch (ir_cmd) {
                case CARMP3_CH_MINUS:
                    if (_radio != NULL) _radio->changeChannel(-1);
                    break;
                case CARMP3_CH_PLUS:
                    if (_radio != NULL) _radio->changeChannel(1);
                    break;
                case CARMP3_VOL_MINUS:
                    if (_radio != NULL) _radio->changeVolume(-1);
                    break;
                case CARMP3_VOL_PLUS:
                    if (_radio != NULL) _radio->changeVolume(1);
                    break;
                case CARMP3_EQ:
                    if (_radio != NULL) _radio->toggleMute();
                    break;
                // case CARMP3_1:
                //     setDisplayPage(DISPLAY_WEATHER);
                //     break;
                // case CARMP3_2:
                //     setDisplayPage(DISPLAY_RADIO);
                //     break;
                // case CARMP3_3:
                //     setDisplayPage(DISPLAY_DEVICE);
                //     break;
                default:
                    break;
            }
        }
    }
}

IRAM_ATTR void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
    ir_cmd = aCommand;
    ir_repeat = isRepeat;
    xSemaphoreGive(ctrlIrRemote.GetEvent());
}
