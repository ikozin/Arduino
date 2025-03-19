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
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#event-group-api

static const uint8_t LED_BUILTIN = 22;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN  // allow testing #ifdef LED_BUILTIN
// static const uint8_t SDA = 21;
// static const uint8_t SCL = 22;

// #define I2S_DIN         19    // DIN
// #define I2S_BCK         26    // BCK
// #define I2S_LCK         25    // LBCK

StaticEventGroup_t xEventGroupBuffer;
EventGroupHandle_t xEventGroup = xEventGroupCreateStatic(&xEventGroupBuffer);
//EventGroupHandle_t xEventGroup = xEventGroupCreate();

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
Preferences prefs = Preferences();
ControllerAudio ctrlAudo(xEventGroup); 


#define BIT_TIME    ( 1 << 0 )
#define BIT_STATION ( 1 << 1 )
#define BIT_TRACK   ( 1 << 2 )
#define BIT_VOLUME  ( 1 << 3 )

#define BIT_ALL     ( BIT_TIME | BIT_STATION | BIT_TRACK | BIT_VOLUME )

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

void IRAM_ATTR isr_handler_volume_up(void* parameter) {
    ControllerAudio* controller = static_cast<ControllerAudio*>(parameter);
    controller->changeVolume(1);

}

void IRAM_ATTR isr_handler_volume_down(void* parameter) {
    ControllerAudio* controller = static_cast<ControllerAudio*>(parameter);
    controller->changeVolume(-1);
}

void setPinHandler(gpio_num_t pin, gpio_int_type_t int_type, gpio_pull_mode_t pull_mode, gpio_isr_t handler) {
    gpio_install_isr_service(0);
    gpio_reset_pin(pin);
    gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pin, pull_mode); 
    gpio_set_intr_type(pin, int_type);
    gpio_intr_enable(pin);
    gpio_isr_handler_add(pin, handler, &ctrlAudo);
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

    ctrlAudo.start();
    ctrlAudo.setVolume(21);
    ctrlAudo.setChannel(url);

    setPinHandler((gpio_num_t)37, GPIO_INTR_NEGEDGE,GPIO_PULLUP_ONLY, isr_handler_volume_up);
    setPinHandler((gpio_num_t)38, GPIO_INTR_NEGEDGE,GPIO_PULLUP_ONLY, isr_handler_volume_down);

    tft.fillScreen(TFT_BLACK);
    tft.setTextWrap(false, false);

    xEventGroupSetBits(xEventGroup, BIT_TIME);
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
void drawTrack(int32_t x, int32_t y) {
    String title = ctrlAudo.getTitle();
    tft.loadFont(ShareTechMonoRegular32);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(title, x, y);
    tft.unloadFont();
}

void drawTime(int32_t x, int32_t y, struct tm* timeinfo) {
    // char text[16];
    strftime(text, sizeof(text), "%H:%M", timeinfo);
    tft.setTextFont(7);
    tft.setTextPadding(48);
    tft.setTextDatum(CC_DATUM);
    tft.drawString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1);
}

void loop() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    drawTime(TFT_HEIGHT >> 1, TFT_WIDTH >> 1, timeinfo);

    EventBits_t uxBits = xEventGroupWaitBits(xEventGroup, BIT_ALL, pdTRUE, pdFALSE, pdMS_TO_TICKS(500));
    if (uxBits) {
        // if (uxBits & BIT_TIME) {
        //     time_t now = time(nullptr);
        //     struct tm* timeinfo = localtime(&now);
        //     drawTime(TFT_HEIGHT >> 1, TFT_WIDTH >> 1, timeinfo);
        // }
        if (uxBits & BIT_STATION) {

        }
        if (uxBits & BIT_TRACK) {
            drawTrack(0, 20);
        }
        if (uxBits & BIT_VOLUME) {
            drawVolume(290, 100, 24, ctrlAudo.getVolume());
        }
        
    }
    // vTaskDelay(pdMS_TO_TICKS(1000));
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
