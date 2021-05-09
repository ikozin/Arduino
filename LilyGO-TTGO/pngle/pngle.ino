//https://github.com/kikuchan/pngle
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <Preferences.h>
#include <FS.h>
#include <SPIFFS.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>
#include "miniz.h"
#include "pngle.h"

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 135x240

Preferences prefs;
String ssid         = ""; // SSID WI-FI
String pswd         = "";

void setup() {
  Serial.begin(115200);
  Serial.printf("\r\n");
  Serial.printf("\r\n");

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  if(SPIFFS.begin(true)) {
    listDir("/");
  }
  else {
    SPIFFS.format();
    Serial.printf("SPIFFS Formatting\r\n");
  }
  //SPIFFS.format();

  prefs.begin("WebRadio");
  ssid = prefs.getString("ssid", ssid);
  pswd = prefs.getString("pswd", pswd);

  tft.printf("Wi-Fi SSID: %s ", ssid.c_str());
  Serial.printf("Wi-Fi SSID: %s ", ssid.c_str());

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pswd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    tft.printf(".");
    Serial.printf(".");
    delay(500);
    yield();
  }
  tft.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
  Serial.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());

  configTime(prefs.getInt("tz", 10800), 0, "pool.ntp.org");

}

uint8_t buf[1024];
int remain = 0;
int len;
//https://export.yandex.ru/bar/reginfo.xml?region=213
HTTPClient http;
void loop() {
  http.begin("https://yastatic.net/weather/i/icons/funky/png/light/64/bkn_-ra_d.png");
  int httpCode = http.GET();
  Serial.printf("%d\r\n", httpCode);
  if (httpCode > 0) {
    tft.fillScreen(0x4C7D);

    WiFiClient *stream = http.getStreamPtr();
    pngle_t *pngle = pngle_new();
    pngle_set_draw_callback(pngle, on_draw);
    while (http.connected()) {
      size_t size = stream->available();
      if (!size) {
        delay(1);
        continue;
      }
      if (size > sizeof(buf) - remain) {
        size = sizeof(buf) - remain;
      }
      int len = stream->readBytes(buf + remain, size);
      int fed = pngle_feed(pngle, buf, remain + len);
      if (fed < 0) {
        Serial.printf("ERROR: %s\r\n", pngle_error(pngle));
        break;
      }
      remain = remain + len - fed;
      if (remain > 0) {
        memmove(buf, buf + fed, remain);
      }
    }    
    pngle_destroy(pngle);
  }
  http.end();
  delay(60000);
}

void listDir(const char* dirname) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = SPIFFS.open(dirname);
  if(!root) {
    Serial.printf("- failed to open directory\r\n");
    return;
  }
  if(!root.isDirectory()) {
    Serial.printf(" - not a directory\r\n");
    return;
  }

  File file = root.openNextFile();
  while(file) {
    if(file.isDirectory()) {
      Serial.printf("  DIR : %s\r\n", file.name());
      listDir(file.name());
    } else {
      Serial.printf("  FILE: %s\tSIZE: %d\r\n", file.name(), file.size());
    }
    file = root.openNextFile();
  }
}

void on_draw(pngle_t *pngle, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t rgba[4]) {
  uint8_t r = rgba[0]; // 0 - 255
  uint8_t g = rgba[1]; // 0 - 255
  uint8_t b = rgba[2]; // 0 - 255
  uint8_t a = rgba[3]; // 0: fully transparent, 255: fully opaque
  uint16_t color = a? tft.color565(r, g, b): 0x4C7D;
  //tft.drawPixel(x, y, tft.color565(r, g, b));
  tft.drawPixel(x, y, color);
  //Serial.printf("put pixel at (%d, %d) with color #%02x%02x%02x\r\n", x, y, r, g, b);
}

uint16_t ColorToRGB565(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}
