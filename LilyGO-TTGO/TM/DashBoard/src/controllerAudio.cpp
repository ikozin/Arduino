#include "controllerAudio.h"

// https://github.com/schreibfaul1/ESP32-audioI2S
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#queue-api
// https://github.com/schreibfaul1/ESP32-audioI2S/blob/master/examples/separate_audiotask/separate_audiotask.ino

void ControllerAudio::Start() {
    xTaskCreatePinnedToCore(
        Handler,
        "audio",
        8192,
        this,
        2 | portPRIVILEGE_BIT,
        NULL,
        1
    );
}

void ControllerAudio::SetVolume(uint16_t volume) {
    LOG("ControllerAudio::SetVolume %d\r\n", volume);
    if (volume > 21) return;
    AudioCommand_t msg = { .cmd = CMD_SET_VOLUME, .volume = volume };
    xQueueSend(_queue, &msg, portMAX_DELAY);
}

void ControllerAudio::SetChannel(const char* url) {
    LOG("ControllerAudio::SetChannel %s\r\n", url);
    AudioCommand_t msg = { .cmd = CMD_SET_URL, .url = url };
    xQueueSend(_queue, &msg, portMAX_DELAY);
}

void ControllerAudio::Handler(void* parameter) {
    assert(parameter);
    ControllerAudio* controller = static_cast<ControllerAudio*>(parameter);
    controller->_audio.setPinout(I2S_BCK, I2S_LCK, I2S_DIN);

    AudioCommand_t msg;
    while (true) {
        controller->_audio.loop();
        if (xQueueReceive(controller->_queue, &msg, 1) == pdPASS) {
            switch (msg.cmd)
            {
                case CMD_SET_URL:
                    controller->_audio.connecttohost(msg.url);
                    break;
                case CMD_SET_VOLUME:
                    controller->_audio.setVolume(msg.volume);
                    break;
                
                default:
                    break;
            }
        }        
    }
    vTaskDelete(NULL);
}
