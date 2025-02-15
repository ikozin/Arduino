#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <esp_sntp.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>

#include "controllerAudio.h"
#include "logging.h"

#include "fonts/Segment772.h"
#include "fonts/Bahnschrift36.h"


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

// #define I2S_DIN         19    // DIN
// #define I2S_BCK         26    // BCK
// #define I2S_LCK         25    // LBCK

#define VOLUME_MAX      21

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
Preferences prefs = Preferences();
ControllerAudio ctrlAudo; 

// volatile int station         = 0;
// volatile int volume          = 20;
// volatile bool isMute         = false;

String ssid         = ""; // SSID WI-FI
String pswd         = "";
JsonDocument doc;
JsonArray stationList;
const char * name;
const char * url;

char text[64];

void fatalError(const char * msg) {
    tft.printf(msg);
    LOG(msg);
    vTaskDelay(pdMS_TO_TICKS(5000));
    esp_restart();
}


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
        fatalError("SPIFFS Error\r\n");
    }

    File file = SPIFFS.open("/setting.json");
    if (file) {
        // Deserialize the JSON document
        DeserializationError error = deserializeJson(doc, file);
        file.close();
        if (error) {
            fatalError("Error deserialize setting.json\r\n");
        }
    }
    stationList = doc.as<JsonArray>();
    tft.printf("Radio list: %d\r\n", stationList.size());
    LOG("Radio list: %d\r\n", stationList.size());

    

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

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);

    strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", timeinfo);
    tft.printf("%s\r\n", text);
    LOG("%s\r\n", text);

    JsonObject station = stationList[1].as<JsonObject>();;
    name = station["name"].as<const char*>();
    url = station["url"].as<const char*>();

    ctrlAudo.Start();
    ctrlAudo.SetVolume(21);
    ctrlAudo.SetChannel(url);

    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(CC_DATUM);

}

const uint VR_MIDL_VOL_VAL  (VOLUME_MAX / 3);
const uint VR_MAX_VOL_VAL   (VR_MIDL_VOL_VAL + VR_MIDL_VOL_VAL);
const uint VR_BAR_HEIGHT    (6);

void drawVolume(uint32_t x, uint32_t y, uint32_t width, uint16_t volume) {
    tft.fillRect(x, y, width, (VOLUME_MAX * VR_BAR_HEIGHT) + 6, TFT_BLACK);
    tft.drawRoundRect(x, y, width, (VOLUME_MAX * VR_BAR_HEIGHT) + 6, 4, TFT_WHITE);
    for(uint16_t i = 1; i <= volume; i++) {
        uint32_t color = TFT_GREEN; //0x3526;
        if (i > VR_MIDL_VOL_VAL)  color = TFT_YELLOW;
        if (i > VR_MAX_VOL_VAL) color = TFT_RED;
        tft.fillRect(x + 4, y + (VOLUME_MAX * VR_BAR_HEIGHT) + 4 - (i * VR_BAR_HEIGHT), width - 8, 3, color);
    }
}

uint16_t volume = 0;
void loop() {

    uint32_t x = 290;
    uint32_t y = 100;
    uint32_t width = 24;
    drawVolume(x, y, width, VOLUME_MAX);

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    strftime(text, sizeof(text), "%H:%M", timeinfo);
    
    // uint16_t w = 300;
    // uint16_t h = 100;
    // tft.setTextColor(TFT_WHITE, TFT_BLUE);
    // w = tft.textWidth(text);
    // h = tft.fontHeight() + 8;
    // tft.fillRect((TFT_HEIGHT - w) >> 1, (TFT_WIDTH - h) >> 1, w, h, TFT_MAGENTA);
    // tft.setTextPadding(80);

    stationList.begin();
    for (size_t i = 0; i < stationList.size(); i++) {
        
        JsonObject station = stationList[i].as<JsonObject>();;
        name = station["name"].as<const char*>();
        url = station["url"].as<const char*>();

        tft.setTextFont(7);
        tft.setTextWrap(false, false);
        tft.setTextPadding(48);
        tft.drawString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1);
    
        tft.loadFont(Bahnschrift36);
        tft.drawString(name, TFT_HEIGHT >> 1, 50);
        tft.unloadFont();
            
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    // vTaskDelay(pdMS_TO_TICKS(1000));
}
