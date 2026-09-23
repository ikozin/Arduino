#include <Arduino.h>
#include <GyverOLED.h>
#include <GyverIO.h>
#include <StringUtils.h>

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"
#include "viola.h"

#define DEMO_AUDIO

/*
ESP32 C3 SuperMini
       ┌───┬──────────┬───┐
GPIO5  ┤   │ ESP32-C3 │   ├ 5V
GPIO6  ┤   │          │   ├ GND
GPIO7  ┤   │          │   ├ 3V3
GPIO8  ┤SDA│          │   ├ GPIO4
GPIO9  ┤SCL│          │   ├ GPIO3
GPIO10 ┤   │          │   ├ GPIO2
GPIO20 ┤RX │          │   ├ GPIO1
GPIO21 ┤TX │          │   ├ GPIO0
       └───┴──────────┴───┘
*/

#ifdef DEMO_OLED
GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
const uint8_t bitmap_32x32[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xF0, 0x70, 0x70, 0x30, 0x30, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0x70, 0x30, 0x30, 0x20, 0x00, 0x00,
    0x00, 0x30, 0x78, 0xFC, 0x7F, 0x3F, 0x0F, 0x0F, 0x1F, 0x3C, 0x78, 0xF0, 0xE0, 0xC0, 0x80, 0x80, 0x80, 0x40, 0xE0, 0xF0, 0xF8, 0xFC, 0xFF, 0x7F, 0x33, 0x13, 0x1E, 0x1C, 0x1C, 0x0E, 0x07, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF9, 0xF7, 0xEF, 0x5F, 0x3F, 0x7F, 0xFE, 0xFD, 0xFB, 0xF1, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x1E, 0x33, 0x33, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00,
};
#endif


#ifdef DEMO_AUDIO

#define I2S_BCLK    5
#define I2S_DOUT    6
#define I2S_LRC     7
// https://github.com/makepkg/ESP32-C3-Internet-Radio/blob/main/platformio.ini
// esp32-c3 ESP8266Audio  path:**/platformio.ini
// https://github.com/pschatzmann/arduino-audio-tools/wiki/Working-with-PlatformIO
AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

#endif


void setup() {
    Serial.begin(115200);
    Serial.println("Start");

#ifdef DEMO_OLED
    Wire.setClock(800000L); // макс. 800'000
    oled.init(SDA, SCL);    // инициализация
    oled.clear();
    oled.rect(0, 0, oled._maxX, oled._maxY, OLED_STROKE);
    oled.drawBitmap((oled._maxX - 32) >> 1, (oled._maxY - 32) >> 1, bitmap_32x32, 32, 32);
    oled.update();
#endif

#ifdef DEMO_AUDIO
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM(viola, sizeof(viola));
    out = new AudioOutputI2S();
    out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    out->SetGain(0.5);
    wav = new AudioGeneratorWAV();
    wav->begin(file, out);
#endif
}

// Arduino loop - repeated processing: copy input stream to output stream
void loop() {
#ifdef DEMO_AUDIO
    if (wav->isRunning()) {
        if (!wav->loop()) {
            wav->stop();
        }
    } else {
        Serial.printf("WAV done\n");
        delay(1000);
    }
#endif
}
