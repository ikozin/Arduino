//https://tsibrov.blogspot.com/2019/11/rda5807m-part1.html
//https://tsibrov.blogspot.com/2020/01/rda5807m-part2-rds.html

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

//ARDUINO_AVR_MINI
//ARDUINO_AVR_NANO
//ARDUINO_AVR_UNO

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

//#define DEBUG_CONSOLE

#if defined(DEBUG_CONSOLE)
#define debug_printf(...)   Serial.printf(__VA_ARGS__)
#else
#define debug_printf(...)
#define listDir(...)
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

//Для генерации шрифта использовать Create_font.pde (Processing)
// TFT_eSPI\Tools\Create_Smooth_Font\Create_font\Create_font.pde
#define FONT_CALIBRI_32  "Calibri32"// unicodeBlocks = 0x0400, 0x0452, | specificUnicodes =  0x002B, 0x002C, 0x002D, 0x002E, 
#define FONT_CALIBRI_56  "Calibri56"// unicodeBlocks =                 | specificUnicodes =  0x00B0, 0x002B, 0x002D, 0x002E, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039,

void setup() {
#if defined(DEBUG_CONSOLE)
  Serial.begin(115200);
  debug_printf("\r\n");
  debug_printf("\r\n");
#endif

  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  if (SPIFFS.begin(true)) {
      listDir("/");
  }
  else {
      SPIFFS.format();
      tft.printf("SPIFFS Formatting\r\n");
      debug_printf("SPIFFS Formatting\r\n");
  }
  //SPIFFS.format();

  prefs.begin("WebRadio");
  ssid = prefs.getString("ssid", ssid);
  pswd = prefs.getString("pswd", pswd);

  tft.printf("Wi-Fi SSID: %s ", ssid.c_str());
  debug_printf("Wi-Fi SSID: %s ", ssid.c_str());

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pswd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    tft.printf(".");
    debug_printf(".");
    delay(500);
    yield();
  }
  tft.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
  debug_printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
  
  configTime(prefs.getInt("tz", 10800), 0, "pool.ntp.org");

  currentHandle = handleVolume;
  
  encoder.attachSingleEdge(37, 38);
  btnEncoder.setClickHandler(btnEncoderClick);
  btnEncoder.setLongClickTime(500);
  btnEncoder.setLongClickHandler(btnEncoderLongClick);

  radioInit();
  radioSetRadio(currentIndex);
  radioSetVolume(currentVolume);
  //radioSetMute(!radioGetMute());
  
  delay(1000);  // Ожидаем установку времени по NTP
 
  logTime(tft);
#if defined(DEBUG_CONSOLE)
  logTime(Serial);
#endif
  updateWeather();
}

void loop() {
  btnEncoder.loop();
  int dir = encoder.getCount();
  encoder.setCount(0);    
  currentHandle(dir);

  long curTime = millis();
  if (curTime - lastTime > 20 * 60000) {
    lastTime = curTime;
    updateWeather();
  }  
}

void btnEncoderClick(Button2& b) {
  if (currentHandle == handleChannel) {
      debug_printf("Volume Control\r\n");
      currentHandle = handleVolume;
  }
  else {
      debug_printf("Channel Control\r\n");
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

#if defined(DEBUG_CONSOLE)
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
#endif
