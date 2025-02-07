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

// void audio_info(const char *info){
//     LOG("info %s\r\n", info);
//     tft.printf("info %s\r\n", info);
// }
// void audio_id3data(const char *info){  //id3 metadata
//     LOG("id3data %s\r\n", info);
//     tft.printf("id3data %s\r\n", info);
// }
// void audio_eof_mp3(const char *info){  //end of file
//     LOG("eof_mp3 %s\r\n", info);
//     tft.printf("eof_mp3 %s\r\n", info);
// }

void audio_showstation(const char *info){
    LOG("station %s\r\n", info);
}
void audio_showstreamtitle(const char *info){
    LOG("title %s\r\n", info);
}
// void audio_bitrate(const char *info){
//     LOG("bitrate %s\r\n", info);
//     tft.printf("bitrate %s\r\n", info);
// }
// void audio_commercial(const char *info){  //duration in sec
//     LOG("commercial %s\r\n", info);
//     tft.printf("commercial %s\r\n", info);
// }
// void audio_icyurl(const char *info){  //homepage
//     LOG("icyurl %s\r\n", info);
//     tft.printf("icyurl %s\r\n", info);
// }
// void audio_lasthost(const char *info){  //stream URL played
//     LOG("lasthost %s\r\n", info);
//     tft.printf("lasthost %s\r\n", info);
// }
// void audio_eof_speech(const char *info){
//     LOG("eof_speech %s\r\n", info);
//     tft.printf("eof_speech %s\r\n", info);
// }
