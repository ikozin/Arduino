#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <esp_sntp.h>
#include <TFT_eSPI.h>
#include "controllerAudio.h"

#include "logging.h"

#if !defined(ESP32)
    #error Select ESP32 DEV Board
#endif

#if USER_SETUP_ID != 23
    #error Select USER_SETUP_ID 23
#endif
#if SPI_FREQUENCY != 80000000
    #error Set SPI_FREQUENCY = 80000000
#endif

// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#task-api
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html

static const uint8_t LED_BUILTIN = 22;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN  // allow testing #ifdef LED_BUILTIN
// static const uint8_t SDA = 21;
// static const uint8_t SCL = 22;

#define I2S_DIN         19    // DIN
#define I2S_BCK         26    // BCK
#define I2S_LCK         25    // LBCK

#define VOLUME_MAX      21

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
Preferences prefs = Preferences();
ControllerAudio ctrlAudo; 

// volatile int station         = 0;
// volatile int volume          = 20;
// volatile bool isMute         = false;

String ssid         = ""; // SSID WI-FI
String pswd         = "";

void setup() {
    Serial.begin(115200);
    LOG("Start\r\n");

    prefs.begin("Main");

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    
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
    // prefs.putBool("mute", false);
    // prefs.putInt("volume", 20);

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

    ctrlAudo.Start();
    ctrlAudo.SetVolume(21);
    ctrlAudo.SetChannel("https://nashe1.hostingradio.ru/nashe-128.mp3");
}

bool once = true; 
void loop() {
    if (once) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        ctrlAudo.SetVolume(10);
        vTaskDelay(pdMS_TO_TICKS(5000));
        ctrlAudo.SetVolume(15);
        vTaskDelay(pdMS_TO_TICKS(5000));
        ctrlAudo.SetVolume(20);
        once = false;
        return;
    }
    delay(1000);
}
