#pragma once

#include <Arduino.h>
#include <Audio.h>
#include "logging.h"

// https://github.com/schreibfaul1/ESP32-audioI2S
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#queue-api
// https://github.com/schreibfaul1/ESP32-audioI2S/blob/master/examples/separate_audiotask/separate_audiotask.ino

#define VOLUME_MAX      (21)

#define I2S_DIN         (19)    // DIN
#define I2S_BCK         (26)    // BCK
#define I2S_LCK         (25)    // LBCK

#define CMD_SET_URL     (1)
#define CMD_SET_VOLUME  (2)

#define BIT_TIME    ( 1 << 0 )
#define BIT_STATION ( 1 << 1 )
#define BIT_TRACK   ( 1 << 2 )
#define BIT_VOLUME  ( 1 << 3 )

typedef struct AudioCommand{
    uint16_t        cmd;
    union {
        uint16_t    volume;
        const char* url;
    };
} AudioCommand_t;

class ControllerAudio {
    public:
        ControllerAudio(EventGroupHandle_t xEventGroup) {
            _xEventGroup = xEventGroup;
            _queue = xQueueCreate(4, sizeof(AudioCommand_t));
            _title.reserve(128);
         }
        void start();
        void setChannel(const char* url);
        
        void setVolume(uint16_t volume);
        void changeVolume(int step);
        const uint16_t getVolume() const { return _volume; }

        void setTitle(const char* text);
        const char* getTitle() const { return _title.c_str(); }
    private:
        EventGroupHandle_t _xEventGroup;
        Audio _audio;
        QueueHandle_t _queue;
        String _title;
        uint16_t _volume;
    private:
        static void Handler(void* parameter);
};
