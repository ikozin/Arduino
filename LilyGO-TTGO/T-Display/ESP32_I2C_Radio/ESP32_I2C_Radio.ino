//https://tsibrov.blogspot.com/2019/11/rda5807m-part1.html
//https://tsibrov.blogspot.com/2020/01/rda5807m-part2-rds.html

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <ESP32Encoder.h>
#include <Button2.h>
#include <TFT_eSPI.h>
#include <Preferences.h>
#include <HTTPClient.h>

#include "tinyxml2.h"

#define DEBUG_CONSOLE

//ARDUINO_AVR_MINI
//ARDUINO_AVR_NANO
//ARDUINO_AVR_UNO

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 135x240

Preferences prefs;
String ssid         = ""; // SSID WI-FI
String pswd         = "";

long lastTime       = 0;
//void updateWeather();

ESP32Encoder encoder;
#define ENCODER_BTN_L 39
Button2 btnEncoder(ENCODER_BTN_L);

uint8_t currentVolume = 2;    // 0..15
uint8_t currentIndex = 35;

typedef struct _radioItem {
  uint16_t band;
  char name[62];
} RadioItem_t;

const RadioItem_t radioList[] PROGMEM = {
  {  875, "БИЗНЕС-FM" },
  {  879, "Like FM" },
  {  883, "Радио Ретро FM" },
  {  887, "Юмор FM" },
  {  891, "Радио Джаз" },
  {  895, "Радио Мегаполис FM" },
  {  899, "Страна FM" },
  {  903, "Авто Радио" },
  {  908, "Relax-FM" },
  {  912, "Радио Эхо Москвы" },
  {  916, "Радио Культура" },
  {  920, "Москва ФМ" },
  {  924, "Радио Дача" },
  {  928, "Радио Карнавал" },
  {  932, "STUDIO 21" },
  {  936, "Коммерсант ФМ" },
  {  940, "Восток FM" },
  {  944, "Весна FM" },
  {  948, "Говорит Москва" },
  {  952, "Рок ФМ" },
  {  956, "Радио Звезда-FM" },
  {  960, "Дорожное радио" },
  {  964, "Такси FM" },
  {  968, "Детское радио" },
  {  972, "Радио Комсомольская правда" },
  {  976, "Вести ФМ" },
  {  980, "Радио Шоколад" },
  {  984, "Новое Радио" },
  {  988, "Радио Романтика" },
  {  992, "Радио Орфей" },
  {  996, "Радио Русский Хит" },
  { 1001, "Радио Серебряный Дождь" },
  { 1005, "Жара FM" },
  { 1009, "Радио Вера" },
  { 1012, "Радио DFM" },
  { 1017, "Наше Радио" },
  { 1021, "Радио Монте-Карлo" },
  { 1025, "Comedy FM" },
  { 1030, "Радио Шансон" },
  { 1034, "Радио Маяк" },
  { 1037, "Радио Максимум" },
  { 1042, "Радио Энергия FM" },
  { 1047, "Радио 7 На Семи Хoлмах" },
  { 1050, "Радио Книга" },
  { 1053, "Capital FM" },
  { 1057, "Русское Радио" },
  { 1062, "Радио Европа Плюс" },
  { 1066, "Love радио" },
  { 1070, "звук IZ.RU" },
  { 1074, "Радио Хит FM" },
  { 1078, "Радио Новая Милицейская Волна" },
};

const int listSize = sizeof(radioList) / sizeof(RadioItem_t);

void (*currentHandle)(int);

void setup() {
#if defined(DEBUG_CONSOLE)
  Serial.begin(115200);
  Serial.printf("\r\n");
  Serial.printf("\r\n");
#endif
  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  prefs.begin("WebRadio");
  ssid = prefs.getString("ssid", ssid);
  pswd = prefs.getString("pswd", pswd);

  tft.printf("Wi-Fi SSID: %s ", ssid.c_str());
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pswd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    tft.printf(".");
    delay(500);
    yield();
  }
  tft.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());

  configTime(prefs.getInt("tz", 10800), 0, "pool.ntp.org");

  currentHandle = handleVolume;
  
  encoder.attachSingleEdge(37, 38);
  btnEncoder.setClickHandler(btnEncoderClick);
  btnEncoder.setLongClickTime(500);
  btnEncoder.setLongClickHandler(btnEncoderLongClick);

  radioInit();
  radioSetRadio(currentIndex);
  radioSetVolume(currentVolume);
  
  delay(1000);
  //yield();
  
  logTime(tft);
  logTime(Serial);
}

void loop() {
  btnEncoder.loop();
  int dir = encoder.getCount();
  encoder.setCount(0);    
  currentHandle(dir);

#if defined(DEBUG_CONSOLE)
  long t = millis();
  if (t - lastTime < 60000) return;
  lastTime = t;
  updateWeather();
#endif
  
}

void btnEncoderClick(Button2& b) {
  if (currentHandle == handleChannel) {
#if defined(DEBUG_CONSOLE)
      Serial.println(F("Volume Control"));
#endif
      currentHandle = handleVolume;
  }
  else {
#if defined(DEBUG_CONSOLE)
      Serial.println(F("Channel Control"));
#endif
      currentHandle = handleChannel;
  }
}

void btnEncoderLongClick(Button2& b) {
  radioSetMute(!radioGetMute());
}


void handleChannel(int dir) {
  if (dir > 0) {
    if (currentIndex < listSize - 1) {
      radioSetRadio(++currentIndex);
    }
  }
  if (dir < 0) {
    if (currentIndex > 0) {
      radioSetRadio(--currentIndex);
    }
  }
}

void handleVolume(int dir) {
  if (dir > 0) {
    if (currentVolume < 15) {
      radioSetVolume(++currentVolume);
    }
  }
  if (dir < 0) {
    if (currentVolume > 0) {
      radioSetVolume(--currentVolume);
    }
  }
}

void logTime(Print& prn) {
  char strftime_buf[64];
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  prn.printf("%s\r\n", strftime_buf);
}
