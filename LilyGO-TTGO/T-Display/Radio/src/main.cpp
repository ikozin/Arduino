#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <Preferences.h>
#include <FS.h>
#include <SPIFFS.h>
#include <HTTPClient.h>
#include <Button2.h>
#include <TFT_eSPI.h>
#include <ESP32Encoder.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "main.h"

#include "view.h"
#include "viewRadio.h"
#include "viewDevice.h"
#include "viewWeather.h"

#include "controller.h"
#include "controllerRadio.h"
#include "controllerDevice.h"
#include "controllerWeather.h"

//#include "IrRemote_CarMP3.h"
//#include "alarm.h"


#if !defined(ESP32)
  #error Select ESP32 DEV Board (ttgo-lora32-v1)
#endif

#if !defined(USER_SETUP_ID) || USER_SETUP_ID != 25
  #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup25_TTGO_T_Display.h"
#endif

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 135x240

Preferences prefs = Preferences();
AsyncWebServer server = AsyncWebServer(80);

#define ENCODER_PIN_A   37
#define ENCODER_PIN_B   38
ESP32Encoder encoder = ESP32Encoder();
#define ENCODER_BTN     39
Button2 btnEncoder = Button2();

String ssid         = ""; // SSID WI-FI
String pswd         = "";

const char* fileRadio = "/radiolist.dat";

RadioItem_t radioList[RADIO_MAX] = {
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
  { 1021, "Радио Монте-Карло" },
  { 1025, "Comedy FM" },
  { 1030, "Радио Шансон" },
  { 1034, "Радио Маяк" },
  { 1037, "Радио Максимум" },
  { 1042, "Радио Энергия FM" },
  { 1047, "Радио 7 На Семи Холмах" },
  { 1050, "Радио Книга" },
  { 1053, "Capital FM" },
  { 1057, "Русское Радио" },
  { 1062, "Радио Европа Плюс" },
  { 1066, "Love радио" },
  { 1070, "звук IZ.RU" },
  { 1074, "Радио Хит FM" },
  { 1078, "Радио Новая Милицейская Волна" },
};
uint16_t listSize = 51;

ControllerRadio ctrlRadio = ControllerRadio("CtrlRadio", &prefs);
ControllerWeather ctrlWeather = ControllerWeather("CtrlWeather");
ControllerDevice ctrlDevice = ControllerDevice("CtrlDevice");

int16_t viewIndex  = -1;
View* currentView = NULL;
ViewRadio viewRadio = ViewRadio("ViewRadio", &tft, &currentView, &ctrlRadio);
ViewWeather viewWeather = ViewWeather("ViewWeather", &tft, &currentView, &ctrlWeather);
ViewDevice viewDevice = ViewDevice("ViewDevice", &tft, &currentView, &ctrlDevice);

View* viewList[] = {
  &viewRadio,
  &viewWeather,
  &viewDevice,
};

void (ControllerRadio::*currentHandle)(int);

void btnEncoderClick(Button2& b);
void btnEncoderDoubleClick(Button2& b);
void btnEncoderLongClick(Button2& b);

void setDisplayPage(int16_t page);

// void listDir(const char* dirname);

uint16_t fileData[8192];

void setup() {
  Serial.begin(9600);
  while(!Serial);
  delay(5000);
  // Serial.printf("\r\n");
  // Serial.printf("\r\n");
  // Serial.printf("Model: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
  // Serial.printf("SDK: %s\r\n", ESP.getSdkVersion());
  // Serial.printf("Flash: %d\r\n", ESP.getFlashChipSize());
  // Serial.printf("NVS Free Entries: %d\r\n", prefs.freeEntries());
  // Serial.printf("Current Core = %d\r\n", xPortGetCoreID());

  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.printf("Model: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
  tft.printf("SDK: %s\r\n", ESP.getSdkVersion());
  tft.printf("Flash: %d\r\n", ESP.getFlashChipSize());
  tft.printf("NVS Free Entries: %d\r\n", prefs.freeEntries());
  tft.printf("Current Core = %d\r\n", xPortGetCoreID());

  if (SPIFFS.begin(true)) {
    tft.printf("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
    //listDir("/");
  }
  else {
    //SPIFFS.format();
    tft.printf("SPIFFS Error\r\n");
  }

  File f = SPIFFS.open(fileRadio);
  if (f) {
    f.read((uint8_t*)radioList, sizeof(radioList));
    f.close();
    for (listSize = 0; listSize < RADIO_MAX; listSize++) {
      if (radioList[listSize].band == 0) break;
    }
  } else {
    tft.printf("Error loading %s\r\n", fileRadio);
  }

  prefs.begin("Main");
  //prefs.putString("ssid", "i-net");
  //prefs.putString("pswd", "95ad8c6d7e9a0c56c40a389ec8a89fe8b4c7d9b60fa3bfd28fe9dcee2e7a");
  //prefs.putInt("tz", 10800);
  //prefs.putInt("station", 35);
  //prefs.putInt("volume", 2);
  //prefs.putBool("mute", false);
  //prefs.putInt("page", DISPLAY_RADIO);

  ssid = prefs.getString("ssid", ssid);
  pswd = prefs.getString("pswd", pswd);

  tft.printf("Wi-Fi SSID: %s ", ssid.c_str());

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pswd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    tft.printf(".");
    vTaskDelay(500 / portTICK_RATE_MS);
  }
  tft.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
  configTime(prefs.getInt("tz", 10800), 0, "pool.ntp.org");

  ctrlRadio.Start();
  ctrlWeather.Start();
  ctrlDevice.Start();

  viewRadio.Start(ctrlRadio.GetEvent());
  viewWeather.Start(ctrlWeather.GetEvent());
  viewDevice.Start(ctrlDevice.GetEvent());

  currentHandle = &ControllerRadio::changeVolume;

  encoder.attachSingleEdge(ENCODER_PIN_A, ENCODER_PIN_B);
  btnEncoder.begin(ENCODER_BTN);
  btnEncoder.setClickHandler(btnEncoderClick);
  btnEncoder.setDoubleClickHandler(btnEncoderDoubleClick);
  btnEncoder.setLongClickTime(500);
  btnEncoder.setLongClickHandler(btnEncoderLongClick);  

  setDisplayPage(prefs.getInt("page", 0));
}

void loop() {
  btnEncoder.loop();
  int dir = encoder.getCount();
  encoder.setCount(0);
  (&ctrlRadio->*currentHandle)(dir);
}

void btnEncoderClick(Button2& b) {
  if (currentHandle == &ControllerRadio::changeChannel) {
    currentHandle = &ControllerRadio::changeVolume;
  }
  else {
    currentHandle = &ControllerRadio::changeChannel;
  }
}

void btnEncoderDoubleClick(Button2& b) {
  setDisplayPage(viewIndex + 1);
}

void btnEncoderLongClick(Button2& b) {
  ctrlRadio.toggleMute();
}

void setDisplayPage(int16_t page) {
  int max =  sizeof(viewList)/sizeof(viewList[0]) - 1;
  if (page < 0 || page > max)
    page = 0;
  if (viewIndex == page) return;
  viewIndex = page;
  prefs.putInt("page", viewIndex);
  currentView = viewList[viewIndex];
  xSemaphoreGive(currentView->GetEvent());
}

void logTime() {
  char strftime_buf[64];
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  Serial.printf("%s\r\n", strftime_buf);
}

// void listDir(const char* dirname) {
//   Serial.printf("Listing directory: %s\r\n", dirname);

//   File root = SPIFFS.open(dirname);
//   if(!root) {
//     Serial.printf("- failed to open directory\r\n");
//     return;
//   }
//   if(!root.isDirectory()) {
//     Serial.printf(" - not a directory\r\n");
//     return;
//   }

//   File file = root.openNextFile();
//   while(file) {
//     if(file.isDirectory()) {
//       Serial.printf("  DIR : %s\r\n", file.name());
//       listDir(file.name());
//     } else {
//       Serial.printf("  FILE: %s\tSIZE: %d\r\n", file.name(), file.size());
//     }
//     file = root.openNextFile();
//   }
// }
