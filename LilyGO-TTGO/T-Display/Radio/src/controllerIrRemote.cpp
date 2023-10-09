#include "controllerIrRemote.h"
#include "IrRemote_CarMP3.h"

#define IR_INPUT_PIN        13
//#define DO_NOT_USE_FEEDBACK_LED
//#include "TinyIRReceiver.hpp"

//ControllerIrRemote ctrlIrRemote;
//volatile uint16_t   ir_cmd;
//volatile bool       ir_repeat;

ControllerIrRemote::ControllerIrRemote() : Controller("CtrlIrRemote") {
    _radio = NULL;
}

ControllerIrRemote& ControllerIrRemote::attachControllerRadio(ControllerRadio* radio) {
    _radio = radio;
    return *this;
}

void ControllerIrRemote::OnHandle() {
    LOGN("ControllerIrRemote::OnHandle")
    //initPCIInterruptForTinyReceiver(); 

    for (;;) {
        
        vTaskDelay( 100 / portTICK_PERIOD_MS );

        //xSemaphoreTake(_updateEvent, portMAX_DELAY);
        //LOGN("ControllerIrRemote::OnHandle")
        //LOGN("ControllerIrRemote, CMD=0x%04X R=%d\r\n", xPortGetCoreID(), ir_cmd, ir_repeat)
        // if (!ir_repeat) {
        //     switch (ir_cmd) {
        //         case CARMP3_CH_MINUS:
        //             if (_radio != NULL) _radio->changeChannel(-1);
        //             break;
        //         case CARMP3_CH_PLUS:
        //             if (_radio != NULL) _radio->changeChannel(1);
        //             break;
        //         case CARMP3_VOL_MINUS:
        //             if (_radio != NULL) _radio->changeVolume(-1);
        //             break;
        //         case CARMP3_VOL_PLUS:
        //             if (_radio != NULL) _radio->changeVolume(1);
        //             break;
        //         case CARMP3_PREV:
        //             setDisplayPagePrev();
        //             break;
        //         case CARMP3_NEXT:
        //             setDisplayPageNext();
        //             break;
        //         case CARMP3_EQ:
        //             if (_radio != NULL) _radio->toggleMute();
        //             break;
        //         case CARMP3_1:
        //             setDisplayPage(0);
        //             break;
        //         case CARMP3_2:
        //             setDisplayPage(1);
        //             break;
        //         case CARMP3_3:
        //             setDisplayPage(2);
        //             break;
        //         case CARMP3_4:
        //             setDisplayPage(4);
        //             break;
        //         case CARMP3_5:
        //             setDisplayPage(5);
        //             break;
        //         case CARMP3_6:
        //             setDisplayPage(6);
        //             break;
        //         case CARMP3_7:
        //             setDisplayPage(7);
        //             break;
        //         case CARMP3_8:
        //             setDisplayPage(8);
        //             break;
        //         case CARMP3_9:
        //             setDisplayPage(9);
        //             break;
        //         default:
        //             break;
        //     }
        // }
    }
}

// IRAM_ATTR void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
//     ir_cmd = aCommand;
//     ir_repeat = isRepeat;
//     xSemaphoreGive(ctrlIrRemote.GetEvent());
// }
