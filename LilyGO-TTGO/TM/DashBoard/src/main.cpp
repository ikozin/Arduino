#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <IPAddress.h>
#include <esp_sntp.h>
#include <ArduinoJson.h>
#include "controllerAudio.h"
#include "main.h"
#include "display.h"

#include "fonts/ShareTechMonoRegular32.h"
#include "fonts/DSEG7Classic_Regular52pt7b.h"

#if !defined(ESP32)
    #error Select ESP32 DEV Board
#endif

#define COLOR_BLACK_DAY     0x00000000
#define COLOR_RED_DAY       0x00FF0000
#define COLOR_GREEN_DAY     0x0000FF00
#define COLOR_BLUE_DAY      0x000000FF
#define COLOR_WHITE_DAY     (COLOR_RED_DAY | COLOR_GREEN_DAY | COLOR_BLUE_DAY)
#define COLOR_YELLOW_DAY    (COLOR_RED_DAY | COLOR_GREEN_DAY)

#define COLOR_BLACK_NIGHT   0x00000000
#define COLOR_RED_NIGHT     0x003F0000
#define COLOR_GREEN_NIGHT   0x00003F00
#define COLOR_BLUE_NIGHT    0x0000003F
#define COLOR_WHITE_NIGHT   (COLOR_RED_NIGHT | COLOR_GREEN_NIGHT | COLOR_BLUE_NIGHT)
#define COLOR_YELLOW_NIGHT  (COLOR_RED_NIGHT | COLOR_GREEN_NIGHT)

uint32_t palette_day[]      { COLOR_BLACK_DAY,   COLOR_WHITE_DAY,   COLOR_RED_DAY,   COLOR_GREEN_DAY,   COLOR_BLUE_DAY,   COLOR_YELLOW_DAY }; 
uint32_t palette_night[]    { COLOR_BLACK_NIGHT, COLOR_WHITE_NIGHT, COLOR_RED_NIGHT, COLOR_GREEN_NIGHT, COLOR_BLUE_NIGHT, COLOR_YELLOW_NIGHT };

uint32_t *palette = palette_night;

#define COLOR_BLACK     (palette[0])
#define COLOR_WHITE     (palette[1])
#define COLOR_RED       (palette[2])
#define COLOR_GREEN     (palette[3])
#define COLOR_BLUE      (palette[4])
#define COLOR_YELLOW    (palette[5])

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

LGFX tft;
Preferences prefs = Preferences();
ControllerAudio ctrlAudo(xEventGroup); 

String ssid = ""; // SSID WI-FI
String pswd = "";
uint16_t    station = 0;
uint16_t    volume  = 2;
bool        isMute  = false;
uint16_t    timezone = 10800;
IPAddress   host = IPAddress(192, 168, 2, 30);
IPAddress   gateway = IPAddress(192, 168, 2, 1);
IPAddress   subnet = IPAddress(255, 255, 255, 0);
IPAddress   dns1 = IPAddress(85, 21, 192, 5);
IPAddress   dns2 = IPAddress(213, 234, 192, 7);

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
    //gpio_pad_select_gpio(pin);
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
    tft.fillScreen(COLOR_BLACK);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK);
    
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

    // prefs.putString("ssid", ssid);
    // prefs.putString("pswd", pswd);
    // prefs.putUInt("tz", timezone);
    // prefs.putUInt("volume", volume);
    // prefs.putBool("mute", isMute);
    // prefs.putString("host", host.toString());
    // prefs.putString("gateway", gateway.toString());
    // prefs.putString("subnet", subnet.toString());
    // prefs.putString("dns1", dns1.toString());
    // prefs.putString("dns2", dns2.toString());

    ssid = prefs.getString("ssid", ssid);
    pswd = prefs.getString("pswd", pswd);
    timezone = prefs.getUInt("tz", timezone);
    volume = prefs.getUInt("volume", volume);
    isMute = prefs.getBool("mute", isMute);
    host.fromString(prefs.getString("host", host.toString()));
    gateway.fromString(prefs.getString("gateway", gateway.toString()));
    subnet.fromString(prefs.getString("subnet", subnet.toString()));
    dns1.fromString(prefs.getString("dns1", dns1.toString()));
    dns2.fromString(prefs.getString("dns2", dns2.toString()));

    tft.printf("Wi-Fi SSID: %s\r\n", ssid.c_str());
    LOG("Wi-Fi SSID: %s\r\n", ssid.c_str());
    
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.config(host, gateway, subnet, dns1, dns2);

    WiFi.channel();
    WiFi.begin(ssid.c_str(), pswd.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        tft.printf(".");
        LOG(".");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    tft.printf("\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
    LOG("\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
    configTime(timezone, 0, "ntp1.vniiftri.ru", "ntp2.vniiftri.ru", "ntp3.vniiftri.ru");

    // do vTaskDelay(pdMS_TO_TICKS(1000));
    // while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED);

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);

    strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", timeinfo);
    tft.printf("%s\r\n", text);
    LOG("%s\r\n", text);

    JsonObject station = stationList[1].as<JsonObject>();;
    name = station["name"].as<const char*>();
    url = station["url"].as<const char*>();

    ctrlAudo.start();
    ctrlAudo.setMute(isMute);
    ctrlAudo.setVolume(volume);
    ctrlAudo.setChannel(url);

    setPinHandler((gpio_num_t)37, GPIO_INTR_NEGEDGE,GPIO_PULLUP_ONLY, isr_handler_volume_up);
    setPinHandler((gpio_num_t)38, GPIO_INTR_NEGEDGE,GPIO_PULLUP_ONLY, isr_handler_volume_down);

    tft.fillScreen(COLOR_BLACK);
    tft.setTextWrap(false, false);

    xEventGroupSetBits(xEventGroup, BIT_TIME);
}

const uint VR_MIDL_VOL_VAL  (VOLUME_MAX / 3);
const uint VR_MAX_VOL_VAL   (VR_MIDL_VOL_VAL + VR_MIDL_VOL_VAL);
const uint VR_BAR_HEIGHT    (6);

void drawVolume(uint32_t x, uint32_t y, uint32_t width, uint16_t volume) {
    tft.startWrite();
    tft.fillRect(x, y, width, (VOLUME_MAX * VR_BAR_HEIGHT) + 6, COLOR_BLACK);
    tft.drawRoundRect(x, y, width, (VOLUME_MAX * VR_BAR_HEIGHT) + 6, 4, COLOR_WHITE);
    for(uint16_t i = 1; i <= volume; i++) {
        uint32_t color = COLOR_GREEN;
        if (i > VR_MIDL_VOL_VAL)  color = COLOR_YELLOW;
        if (i > VR_MAX_VOL_VAL) color = COLOR_RED;
        tft.fillRect(x + 4, y + (VOLUME_MAX * VR_BAR_HEIGHT) + 4 - (i * VR_BAR_HEIGHT), width - 8, 3, color);
    }
    tft.endWrite();
}

void drawStation(int32_t x, int32_t y) {
    String station = ctrlAudo.getStation();
    tft.startWrite();
    tft.loadFont(Share_Tech_Mono_Regular32);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(station, x, y);
    tft.unloadFont();
    tft.endWrite();
}

String _title;
int32_t _x = TFT_HEIGHT;
int32_t _y = 20;
int32_t _width = 0;
void drawTrack() {
    tft.loadFont(Share_Tech_Mono_Regular32);
    tft.setTextDatum(ML_DATUM);
    _x = TFT_HEIGHT;
    _title = ctrlAudo.getTitle();
    _width = tft.textWidth(_title);

    if (_width < TFT_HEIGHT) {
        _x = (TFT_HEIGHT - _width) >> 1;
        _width = 0;
    } else {
        _title += "  ";
        _width += 16;
    }
    LOG("Start: %d, %d, %d\r\n", _x, _y, _width);
    tft.startWrite();
    tft.drawString(_title, _x, _y);
    tft.unloadFont();
    tft.endWrite();
}

void updateTrack() {
    if (_width == 0) return;
    _x-= 16;
    if (_x < -_width) _x = TFT_HEIGHT;
    LOG("update: %d\r\n", _x);
    tft.startWrite();
    tft.loadFont(Share_Tech_Mono_Regular32);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(_title, _x, _y);
    tft.unloadFont();
    tft.endWrite();
}

void drawTime(int32_t x, int32_t y, struct tm* timeinfo) {
    // char text[16];
    strftime(text, sizeof(text), "%H:%M", timeinfo);
    tft.startWrite();
    tft.loadFont(DSEG7Classic_Regular52pt7b);
    tft.setTextPadding(48);
    tft.setTextDatum(CC_DATUM);
    tft.drawString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1);
    tft.unloadFont();
    tft.endWrite();
}

void loop() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    drawTime(TFT_HEIGHT >> 1, TFT_WIDTH >> 1, timeinfo);

    EventBits_t uxBits = xEventGroupWaitBits(xEventGroup, BIT_ALL, pdTRUE, pdFALSE, pdMS_TO_TICKS(250));
    if (uxBits) {
        // if (uxBits & BIT_TIME) {
        //     time_t now = time(nullptr);
        //     struct tm* timeinfo = localtime(&now);
        //     drawTime(TFT_HEIGHT >> 1, TFT_WIDTH >> 1, timeinfo);
        // }
        if (uxBits & BIT_STATION) {
            drawStation(0, 200);
        }
        if (uxBits & BIT_TRACK) {
            drawTrack();
        }
        if (uxBits & BIT_VOLUME) {
            drawVolume(290, 100, 24, ctrlAudo.getVolume());
        }
        if (uxBits & BIT_MUTE) {

        }
    }
    updateTrack();
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

void audio_showstation(const char *info){
    if (strlen(info) == 0) return;
    ctrlAudo.setStation(info);
    LOG("station %s\r\n", info);

}

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
