#pragma once

#include <Arduino.h>
#include <Audio.h>
#include "logging.h"

// https://github.com/schreibfaul1/ESP32-audioI2S
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#queue-api
// https://github.com/schreibfaul1/ESP32-audioI2S/blob/master/examples/separate_audiotask/separate_audiotask.ino

#define I2S_DIN         (19)    // DIN
#define I2S_BCK         (26)    // BCK
#define I2S_LCK         (25)    // LBCK

#define CMD_SET_URL     (1)
#define CMD_SET_VOLUME  (2)

typedef struct AudioCommand{
    uint16_t        cmd;
    union {
        uint16_t    volume;
        const char* url;
    };
} AudioCommand_t;

class ControllerAudio {
    public:
        ControllerAudio() {
            _queue = xQueueCreate(4, sizeof(AudioCommand_t));
         }
        void Start();
        void SetVolume(uint16_t volume);
        void SetChannel(const char* url);
    private:
        Audio _audio;
        QueueHandle_t _queue;
    private:
        static void Handler(void* parameter);
};
