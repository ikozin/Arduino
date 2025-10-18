#include "controllerAudio.h"

// https://github.com/schreibfaul1/ESP32-audioI2S
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#queue-api
// https://github.com/schreibfaul1/ESP32-audioI2S/blob/master/examples/separate_audiotask/separate_audiotask.ino

void ControllerAudio::start() {
    xTaskCreatePinnedToCore(Handler, "audio", 4096, this, 2 | portPRIVILEGE_BIT, NULL, 1);
}

void ControllerAudio::setStation(const char* text) {
    _station = text;
    xEventGroupSetBits(_xEventGroup, BIT_STATION);
}

void ControllerAudio::setTitle(const char* text) {
    _title = text;
    xEventGroupSetBits(_xEventGroup, BIT_TRACK);
}


void ControllerAudio::setMute(bool mute) {
    LOG("ControllerAudio::setMute %d\r\n", mute);
    AudioCommand_t msg = { .cmd = CMD_SET_MUTE, .mute = mute };
    xQueueSend(_queue, &msg, portMAX_DELAY);
}

void ControllerAudio::toggleMute() {
    LOG("ControllerAudio::toggleMute\r\n");
    AudioCommand_t msg = { .cmd = CMD_SET_MUTE, .mute = !_mute };
    xQueueSend(_queue, &msg, portMAX_DELAY);
}

void ControllerAudio::setVolume(uint16_t volume) {
    LOG("ControllerAudio::SetVolume %d\r\n", volume);
    if (volume > VOLUME_MAX) return;
    AudioCommand_t msg = { .cmd = CMD_SET_VOLUME, .volume = volume };
    xQueueSend(_queue, &msg, portMAX_DELAY);
}

void ControllerAudio::changeVolume(int step) {
    int volume = _volume + step;
    if (volume < 0) volume = 0;
    if (volume > VOLUME_MAX) volume = VOLUME_MAX;
    setVolume(volume);
}

void ControllerAudio::setChannel(const char* url) {
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
                    xEventGroupSetBits(controller->_xEventGroup, BIT_STATION);
                    break;
                case CMD_SET_VOLUME:
                    controller->_volume = msg.volume;
                    if (!controller->_mute) {
                        controller->_audio.setVolume(msg.volume);
                    }
                    xEventGroupSetBits(controller->_xEventGroup, BIT_VOLUME);
                    break;
                case CMD_SET_MUTE:
                    controller->_mute = msg.mute;
                    controller->_audio.setVolume(controller->_mute ? 0: controller->_volume);
                    xEventGroupSetBits(controller->_xEventGroup, BIT_MUTE);
                    break;
              
                default:
                    break;
            }
        }        
    }
    vTaskDelete(NULL);
}
