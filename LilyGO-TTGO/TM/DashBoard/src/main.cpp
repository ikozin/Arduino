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
#include "fonts/ShareTechMonoRegular32.h"


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

volatile uint16_t   station = 0;
volatile uint16_t   volume  = 20;
volatile bool       isMute  = false;

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
    tft.setTextWrap(false, false);

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

void loop() {

    uint32_t x = 290;
    uint32_t y = 100;
    uint32_t width = 24;
    drawVolume(x, y, width, VOLUME_MAX);

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    strftime(text, sizeof(text), "%H:%M", timeinfo);
    
    tft.setTextFont(7);
    tft.setTextPadding(48);
    tft.setTextDatum(CC_DATUM);
    tft.drawString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1);

    // uint16_t w = 300;
    // uint16_t h = 100;
    // tft.setTextColor(TFT_WHITE, TFT_BLUE);
    // w = tft.textWidth(text);
    // h = tft.fontHeight() + 8;
    // tft.fillRect((TFT_HEIGHT - w) >> 1, (TFT_WIDTH - h) >> 1, w, h, TFT_MAGENTA);
    // tft.setTextPadding(80);

    tft.loadFont(ShareTechMonoRegular32);

    uint16_t widthBox = 320;
    String title = ctrlAudo.getTitle();
    title.concat("    ");
    int16_t widthText = tft.textWidth(title);
    int16_t size = widthText;
    Serial.printf("%s,%d,%d\r\n", title.c_str(), title.length(), size);
    do {
        title.concat(title);
        size += widthText;
    } while (widthBox > size);
    Serial.printf("%s,%d,%d\r\n", title.c_str(), title.length(), size);
    tft.setTextDatum(ML_DATUM);

    int16_t start = widthText;
    for (int16_t n = 0; n < 8; n++) {
        for (int16_t i = start; i >= -widthText; i-=8) {
            tft.drawString(title, i, 20);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        start = 0;
    }

    tft.unloadFont();
    vTaskDelay(pdMS_TO_TICKS(1000));
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
// void audio_showstation(const char *info){
//     LOG("station %s\r\n", info);
// }
void audio_showstreamtitle(const char *info){
    if (strlen(info) == 0) return;
    ctrlAudo.setTitle(info);
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
