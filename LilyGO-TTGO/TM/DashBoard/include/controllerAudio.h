#pragma once

#include <Arduino.h>
#include <SPIFFS.h>

#include <Audio.h>
#include "main.h"


// https://github.com/schreibfaul1/ESP32-audioI2S
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#queue-api
// https://github.com/schreibfaul1/ESP32-audioI2S/blob/master/examples/separate_audiotask/separate_audiotask.ino

#define VOLUME_MAX      (21)

#define I2S_DIN         (19)    // DIN
#define I2S_BCK         (26)    // BCK
#define I2S_LCK         (25)    // LBCK

#define CMD_SET_URL     (1)
#define CMD_SET_VOLUME  (2)
#define CMD_SET_MUTE    (3)

typedef struct AudioCommand{
    uint16_t        cmd;
    union {
        uint16_t    volume;
        const char* url;
        bool        mute;
    };
} AudioCommand_t;

class ControllerAudio {
    public:
        ControllerAudio(EventGroupHandle_t xEventGroup) {
            _xEventGroup = xEventGroup;
            _queue = xQueueCreate(4, sizeof(AudioCommand_t));
            _station.reserve(64);
            _title.reserve(128);
            _mute = true;
            _volume = 0;
         }
        void start();
        void setChannel(const char* url);

        void setMute(bool mute);
        void toggleMute();
        const uint16_t getMute() const { return _mute; }
        
        void setVolume(uint16_t volume);
        void changeVolume(int step);
        const uint16_t getVolume() const { return _volume; }

        void setStation(const char* text);
        const char* getStation() const { return _station.c_str(); }

        void setTitle(const char* text);
        const char* getTitle() const { return _title.c_str(); }
    private:
        EventGroupHandle_t _xEventGroup;
        Audio _audio;
        QueueHandle_t _queue;
        String _station;
        String _title;
        uint16_t _volume;
        bool _mute;
    private:
        static void Handler(void* parameter);
};
