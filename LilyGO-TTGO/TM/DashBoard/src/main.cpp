#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <esp_sntp.h>
#include <Audio.h>

#include "display.h"
#include "controller\controller.h"
#include "controller\controllerTimeSNTP.h"
#include "controller\controllerBme280.h"
#include "controller\controllerRadio.h"

#include "view\view.h"
#include "view\viewTimeDigit.h"

#if !defined(ESP32)
    #error Select ESP32 DEV Board
#endif

static const uint8_t LED_BUILTIN = 22;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN  // allow testing #ifdef LED_BUILTIN
// static const uint8_t SDA = 21;
// static const uint8_t SCL = 22;

LGFX tft;

Preferences prefs = Preferences();
Audio audio;

volatile int station         = 0;
volatile int volume          = 20;
volatile bool isMute         = false;

String ssid         = ""; // SSID WI-FI
String pswd         = "";

int16_t viewIndex  = -1;
View* currentView = nullptr;

ViewSettig viewSettig(&tft, &currentView);

SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

ControllerTimeSNTP ctrlTime = ControllerTimeSNTP("ControllerTimeSNTP", &prefs);
ViewTimeDigit viewTime = ViewTimeDigit("ViewTimeDigit", &viewSettig, &ctrlTime);

ControllerBme280 ctrlBme280 = ControllerBme280("ControllerBme280");


View* viewList[] = {
    &viewTime,
};

void setDisplayPage(int16_t page) {
    int max =  sizeof(viewList)/sizeof(viewList[0]) - 1;
    if (page < 0) {
        page = max;
    }
    if (page > max) {
        page = 0;
    }
    if (viewIndex == page) return;
    viewIndex = page;
    prefs.putInt("page", viewIndex);
    currentView = viewList[viewIndex];
    xSemaphoreGive(currentView->GetEvent());
}

 void setup() {
    Serial.begin(115200);
    LOG("Start\r\n");

    prefs.begin("Main");

    tft.init();
    tft.setRotation(1);
    tft.clear(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // boardInfo(tft);

    if (SPIFFS.begin(true)) {
        tft.printf("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
        LOG("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
    }
    else {
        //SPIFFS.format();
        tft.printf("SPIFFS Error\r\n");
        LOG("SPIFFS Error\r\n");
    }

    // prefs.putString("ssid", "...");
    // prefs.putString("pswd", "...");
    // prefs.putInt("tz", 10800);
    prefs.putBool("mute", false);
    prefs.putInt("volume", 20);


    ssid = prefs.getString("ssid", ssid);
    pswd = prefs.getString("pswd", pswd);

    tft.printf("Wi-Fi SSID: %s\r\n", ssid.c_str());
    LOG("Wi-Fi SSID: %s\r\n", ssid.c_str());
    
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.channel();
    WiFi.begin(ssid.c_str(), pswd.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        tft.printf(".");
        LOG(".");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    tft.printf("\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
    LOG("\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
    configTime(prefs.getInt("tz", 10800), 0, "ntp1.vniiftri.ru", "ntp2.vniiftri.ru");

    do vTaskDelay(pdMS_TO_TICKS(1000));
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED);
    // while (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(1000)) != ESP_OK);

    char text[64];
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);

    strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", timeinfo);
    tft.printf("%s\r\n", text);
    LOG("%s\r\n", text);

    LOG("Controller - Start\r\n");
    ctrlTime.Start(xMutex);
    ctrlBme280.Start(xMutex);

    LOG("View - Start\r\n");
    tft.clear(TFT_BLACK);

    viewTime.Start(8192);

    audio.setPinout(I2S_BCK, I2S_LCK, I2S_DIN);
    audio.connecttohost("https://nashe1.hostingradio.ru/nashe-128.mp3");
    audio.setVolume(volume); // 0...21

    // tft.fillScreen(TFT_PURPLE);
    // tft.setTextColor(TFT_WHITE, TFT_PURPLE);

    setDisplayPage(prefs.getInt("page", 0));
}

void loop() {
    audio.loop();
    // char text[64];
    // time_t now = time(nullptr);
    // struct tm* timeinfo = localtime(&now);
    // strftime(text, sizeof(text), "%H:%M ", timeinfo);
    // tft.setTextDatum(MC_DATUM);
    // tft.drawString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1, 7);
    vTaskDelay(pdMS_TO_TICKS(100));
}

void audio_showstreamtitle(const char *info) {
    LOG("streamtitle %s\r\n", info);
    // setScroll(info);
}
