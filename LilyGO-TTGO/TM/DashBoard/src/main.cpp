#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
// #include <..\..\tools\sdk\esp32\include\lwip\include\apps\esp_sntp.h>
#include <esp_sntp.h>

#include <TFT_eSPI.h>
#include <Audio.h>

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif
#if !defined(USER_SETUP_ID) || USER_SETUP_ID != 23
  #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup23_TTGO_TM.h"
#endif

static const uint8_t LED_BUILTIN = 22;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN  // allow testing #ifdef LED_BUILTIN
// static const uint8_t SDA = 21;
// static const uint8_t SCL = 22;

#define I2S_DIN       19    // DIN
#define I2S_BCK       26    // BCK
#define I2S_LCK       25    // LBCK

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 240x320
TFT_eSprite sprite = TFT_eSprite(&tft);

Preferences prefs = Preferences();
Audio audio;

volatile int station         = 0;
volatile int volume          = 20;
volatile bool isMute         = false;

String ssid         = ""; // SSID WI-FI
String pswd         = "";

void setup() {
    Serial.begin(115200);
    Serial.printf("Start\r\n");

    prefs.begin("Main");

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // boardInfo(tft);

    if (SPIFFS.begin(true)) {
        tft.printf("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
        Serial.printf("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
    }
    else {
        //SPIFFS.format();
        tft.printf("SPIFFS Error\r\n");
        Serial.printf("SPIFFS Error\r\n");
    }

    // prefs.putString("ssid", "...");
    // prefs.putString("pswd", "...");
    // prefs.putInt("tz", 10800);

    ssid = prefs.getString("ssid", ssid);
    pswd = prefs.getString("pswd", pswd);

    tft.printf("Wi-Fi SSID: %s\r\n", ssid.c_str());
    Serial.printf("Wi-Fi SSID: %s\r\n", ssid.c_str());
    
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.channel();
    WiFi.begin(ssid.c_str(), pswd.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        tft.printf(".");
        Serial.printf(".");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
    tft.printf("\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
    Serial.printf("\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
    configTime(prefs.getInt("tz", 10800), 0, "ntp1.vniiftri.ru", "ntp2.vniiftri.ru");

    do vTaskDelay(1000 / portTICK_RATE_MS);
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED);

    char text[64];
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    strftime(text, sizeof(text), "%c", &timeinfo);
    //strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", &timeinfo);
    tft.printf("%s\r\n", text);
    Serial.printf("%s\r\n", text);

    audio.setPinout(I2S_BCK, I2S_LCK, I2S_DIN);
    audio.connecttohost("https://nashe1.hostingradio.ru/nashe-128.mp3");
    audio.setVolume(volume); // 0...21

    tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE, TFT_PURPLE);
}

void loop() {
    audio.loop();
    char text[64];
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    strftime(text, sizeof(text), "%H:%M ", &timeinfo);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1, 7);
}

void audio_showstreamtitle(const char *info) {
    Serial.printf("streamtitle %s\r\n", info);
    // setScroll(info);
}
