//https://tsibrov.blogspot.com/2019/11/rda5807m-part1.html
//https://tsibrov.blogspot.com/2020/01/rda5807m-part2-rds.html

/*
                            T-Display
                       ┌─────────┐
                       ┤GND         3V3├ 
                       ┤GND         SVP├ 
     RDA5807           ┤21           37├  Encoder
     RDA5807           ┤22           38├  Encoder
                       ┤17     (39) SVN├  Encoder Button
                       ┤2            32├ 
                       ┤15           33├
 IR Remore Control     ┤13           25├
                       ┤12           26├
                       ┤GND          27├
                       ┤GND         GND├
                       ┤3V3          5V├
                       └─────────┘


*/

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
#include <Pangodream_18650_CL.h>
#include "IrRemote_CarMP3.h"
#include "alarm.h"

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

#if !defined(ST7789_DRIVER) || TFT_WIDTH != 135 || TFT_HEIGHT != 240
  #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup25_TTGO_T_Display.h"
#endif

#define IR_INPUT_PIN        13
#define DO_NOT_USE_FEEDBACK_LED
#include "TinyIRReceiver.cpp.h"

String trafficLevel        = String();
String weatherDescription  = String();
String weatherUrlIcon      = String();
String weatherWindSpeed    = String();
String weatherWindType     = String();
String weatherDampness     = String();
String weatherPressure     = String();
String weatherTemperature  = String();
String iconFileName        = String();
String windFileName        = String();

extern void page404(AsyncWebServerRequest*);
extern void pageIndexGet(AsyncWebServerRequest*);
extern void pageIndexPost(AsyncWebServerRequest*);
extern void pageAlarmGet(AsyncWebServerRequest*);
extern void pageAlarmPost(AsyncWebServerRequest*);
extern void pageSetAlarmGet(AsyncWebServerRequest*);
extern void pageSetAlarmPost(AsyncWebServerRequest*);
extern void pageSearchGet(AsyncWebServerRequest*);
extern void pageSearchPost(AsyncWebServerRequest*);
extern void pageRadioListGet(AsyncWebServerRequest*);
extern void pageUploadPost(AsyncWebServerRequest*);
extern void handleUpload(AsyncWebServerRequest*, String, size_t, uint8_t*, size_t, bool);

extern void displayWeather();

#define DEBUG_CONSOLE

#if defined(DEBUG_CONSOLE)
#define debug_printf(...)   Serial.printf(__VA_ARGS__)
#else
#define debug_printf(...)
#define listDir(...)
#endif

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 135x240

AsyncWebServer server(80);

Preferences prefs;
String ssid         = ""; // SSID WI-FI
String pswd         = "";

volatile uint16_t  ir_cmd;
volatile bool     ir_repeat;
volatile SemaphoreHandle_t ir_event;
TaskHandle_t      receiverTask;

TaskHandle_t weatherTask;

volatile SemaphoreHandle_t displayWeatherEvent;
volatile SemaphoreHandle_t displayRadioEvent;
volatile SemaphoreHandle_t displayDeviceEvent;
TaskHandle_t displayWeatherTask;
TaskHandle_t displayRadioTask;
TaskHandle_t displayDeviceTask;

#define DISPLAY_WEATHER 1
#define DISPLAY_RADIO   2
#define DISPLAY_DEVICE  3

int16_t currentPage  = 0;

alarm_t settings[5] = { {.value = 0xFFFFFFFF170000FF},  {.value = 0},  {.value = 0},  {.value = 0}, {.value = 0} };
#define MaxSettingsCount  (sizeof(settings) / sizeof(settings[0]))
uint16_t settingsCount = 1;

ESP32Encoder encoder;
#define ENCODER_BTN_L 39
Button2 btnEncoder(ENCODER_BTN_L);

#define MIN_USB_VOL   4.9
#define PIN_ADC_POWER 14
#define PIN_ADC_IN    34
#define CONV_FACTOR   1.8
#define READS         20
Pangodream_18650_CL BL(PIN_ADC_IN, CONV_FACTOR, READS);
TaskHandle_t batteryTask;

#define VOLUME_MAX      15
uint16_t currentVolume = 0;    // 0..15
uint16_t currentIndex  = 0;
bool    isMute = false;

const char* fileRadio = "/radiolist.dat";

#define RADIO_MAX   64

typedef struct _radioItem {
  uint16_t band;
  char name[78];
} RadioItem_t;

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

void (*currentHandle)(int);

// Для генерации шрифта использовать Create_font.pde (Processing)
// TFT_eSPI\Tools\Create_Smooth_Font\Create_font\Create_font.pde
// Директория Tools
#define FONT_CALIBRI_32  "font/Calibri32"
#define FONT_CALIBRI_56  "font/Calibri56"
#define FONT_SEGOE_32    "font/Segoe UI Symbol32"
/*
Скетч использует 1070250 байт (81%) памяти устройства. Всего доступно 1310720 байт.
Глобальные переменные используют 64304 байт (21%) динамической памяти, оставляя 230608 байт для локальных переменных. Максимум: 294912 байт.
*/
uint16_t fileData[8192];

void setup() {
#if defined(DEBUG_CONSOLE)
  Serial.begin(115200);
  debug_printf("\r\n");
  debug_printf("\r\n");
  debug_printf("Model: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
  debug_printf("SDK: %s\r\n", ESP.getSdkVersion());
  debug_printf("Flash: %d\r\n", ESP.getFlashChipSize());
  debug_printf("NVS Free Entries: %d\r\n", prefs.freeEntries());
  debug_printf("Current Core = %d\r\n", xPortGetCoreID());
#endif

  pinMode(PIN_ADC_POWER, OUTPUT);
  digitalWrite(PIN_ADC_POWER, HIGH);

  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  if (SPIFFS.begin(true)) {
    listDir("/", &Serial);
    debug_printf("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
  }
  else {
    SPIFFS.format();
    tft.printf("SPIFFS Formatting\r\n");
    debug_printf("SPIFFS Formatting\r\n");
  }
  //SPIFFS.format();

  File f = SPIFFS.open(fileRadio);
  if (f) {
    f.read((uint8_t*)radioList, sizeof(radioList));
    f.close();
    for (listSize = 0; listSize < RADIO_MAX; listSize++) {
      if (radioList[listSize].band == 0) break;
    }
  } else {
    debug_printf("Error loading %s\r\n", fileRadio);
  }

  prefs.begin("WebRadio");
  //prefs.putString("ssid", "");
  //prefs.putString("pswd", "");
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
  
  displayWeatherEvent = xSemaphoreCreateBinary();
  displayRadioEvent = xSemaphoreCreateBinary();
  displayDeviceEvent = xSemaphoreCreateBinary();
  xTaskCreatePinnedToCore(displayWeatherHandler, "DisplayWeather", 4096, NULL, 1, &displayWeatherTask, 0);
  xTaskCreatePinnedToCore(displayRadioHandler, "DisplayRadio", 4096, NULL, 1, &displayRadioTask, 0);
  xTaskCreatePinnedToCore(displayDeviceHandler, "DisplayDevice", 4096, NULL, 1, &displayDeviceTask, 0);

  configTime(prefs.getInt("tz", 10800), 0, "pool.ntp.org");

  currentHandle = handleVolume;
  
  encoder.attachSingleEdge(37, 38);
  btnEncoder.setClickHandler(btnEncoderClick);
  btnEncoder.setDoubleClickHandler(btnEncoderDoubleClick);
  btnEncoder.setLongClickTime(500);
  btnEncoder.setLongClickHandler(btnEncoderLongClick);
  
  radioInit();
  handleSetRadio(prefs.getInt("station", 35));
  handleSetVolume(prefs.getInt("volume", 2));
  handleMute(prefs.getBool("mute", false));

  delay(1000);  // Ожидаем установку времени по NTP
 
  logTime(tft);
#if defined(DEBUG_CONSOLE)
  logTime(Serial);
#endif
  setDisplayPage(prefs.getInt("page", DISPLAY_WEATHER));

  ir_event = xSemaphoreCreateBinary();
  initPCIInterruptForTinyReceiver(); 
  xTaskCreatePinnedToCore(receiverHandler, "IrReceiverTask", 2048, NULL, 1, &receiverTask, 0);
 
  trafficLevel.reserve(8);
  weatherDescription.reserve(128);
  weatherUrlIcon.reserve(128);
  weatherWindSpeed.reserve(16);
  weatherWindType.reserve(64);
  weatherDampness.reserve(16);
  weatherPressure.reserve(16);
  weatherTemperature.reserve(16);
  xTaskCreatePinnedToCore(weatherHandler, "WeatherTask", 4096, NULL, 1, &weatherTask, 0);

  xTaskCreatePinnedToCore(batteryHandler, "BatteryTask", 4096, NULL, 1, &batteryTask, 1);

  debug_printf("WebServer\r\n");
  server.on("/", HTTP_GET, pageIndexGet);
  server.on("/", HTTP_POST, pageIndexPost);
  server.on("/index.html", HTTP_GET, pageIndexGet);
  server.on("/index.html", HTTP_POST, pageIndexPost);

  server.on("/alarm.html", HTTP_GET, pageAlarmGet);
  server.on("/alarm.html", HTTP_POST, pageAlarmPost);

  server.on("/setalarm.html", HTTP_GET, pageSetAlarmGet);
  server.on("/setalarm.html", HTTP_POST, pageSetAlarmPost);

  server.on("/rda5807m.html", HTTP_GET, pageSearchGet);
  server.on("/rda5807m.html", HTTP_POST, pageSearchPost);
  server.on("/upload", HTTP_POST, pageUploadPost, handleUpload);
  server.on(fileRadio, HTTP_GET, pageRadioListGet);
    
  //server.serveStatic(fileRadio, SPIFFS, fileRadio);
  //server.onFileUpload(handleUpload);

  server.onNotFound(page404);
  server.begin();

  setTimers(settingsCount);
 
#if defined(DEBUG_CONSOLE)
  //vTaskGetRunTimeStats();
#endif
}

void loop() {
  btnEncoder.loop();
  int dir = encoder.getCount();
  encoder.setCount(0);    
  currentHandle(dir);
  if(WiFi.status() != WL_CONNECTED) {
    debug_printf("\r\n---RECONNNECT---\r\n");
    server.end();
    WiFi.disconnect();
    WiFi.reconnect();
    while (WiFi.status() != WL_CONNECTED) {
      tft.printf(".");
      debug_printf(".");
      delay(500);
      yield();
    }
    server.begin();
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

void btnEncoderDoubleClick(Button2& b) {
  setDisplayPage(currentPage + 1);
}

void btnEncoderLongClick(Button2& b) {
  handleMute(!isMute);
}

void handleMute(bool mute) {
  if (mute == isMute) return;
  isMute = mute;
  radioSetMute(isMute);
  prefs.putBool("mute", isMute);  
  xSemaphoreGive(displayRadioEvent);
}

void handleSetRadio(uint16_t index) {
  if (index >= listSize) index = 0;
  if (currentIndex == index) return;
  currentIndex = index;
  RadioItem_t rec = radioList[currentIndex];
  uint16_t band = rec.band;
  debug_printf("%d:%s\r\n", band, rec.name);
  radioSetChannel(band);
  prefs.putInt("station", currentIndex);  
  xSemaphoreGive(displayRadioEvent);
}

void handleChannel(int direction) {
  if (direction > 0) {
    if (currentIndex < listSize - 1) {
      handleSetRadio(currentIndex + 1);
    }
  }
  if (direction < 0) {
    if (currentIndex > 0) {
      handleSetRadio(currentIndex - 1);
    }
  }
}

void handleSetVolume(uint16_t value) {
  if (value > VOLUME_MAX) value = VOLUME_MAX;
  if (currentVolume == value) return; 
  currentVolume = value;
  radioSetVolume(currentVolume);
  prefs.putInt("volume", currentVolume);
  xSemaphoreGive(displayRadioEvent);
}

void handleVolume(int direction) {
  if (direction > 0) {
    if (currentVolume < VOLUME_MAX) {
      handleSetVolume(currentVolume + 1);
    }
  }
  if (direction < 0) {
    if (currentVolume > 0) {
      handleSetVolume(currentVolume - 1);
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

void setDisplayPage(int16_t page) {
  if (page != DISPLAY_WEATHER && page != DISPLAY_RADIO && page != DISPLAY_DEVICE)
    page = DISPLAY_WEATHER;
  if (currentPage == page) return;
  currentPage = page;
  prefs.putInt("page", currentPage);
  switch (currentPage) {
    case DISPLAY_WEATHER:
      xSemaphoreGive(displayWeatherEvent);
      break;
    case DISPLAY_RADIO:
      xSemaphoreGive(displayRadioEvent);
      break;
    case DISPLAY_DEVICE:
      xSemaphoreGive(displayDeviceEvent);
      break;
    default:
      tft.fillScreen(TFT_RED);
  }
}

void batteryHandler(void* parameter) {
  for (;;) {
    if (BL.getBatteryVolts() >= MIN_USB_VOL) {
      //debug_printf("BatteryHandler Core = %d, Battery Charging\r\n", xPortGetCoreID());
    } else {
      int batteryLevel = BL.getBatteryChargeLevel();
      debug_printf("BatteryHandler Core = %d, Battary Level = %d\r\n", xPortGetCoreID(), batteryLevel);
    } 
    vTaskDelay(10000 / portTICK_RATE_MS);
  }
}

void displayWeatherHandler(void* parameter) {
  for (;;) {
    xSemaphoreTake(displayWeatherEvent, portMAX_DELAY);
    debug_printf("DisplayWeatherHandler Core = %d\r\n", xPortGetCoreID());
    if (currentPage == DISPLAY_WEATHER) displayWeather();
  }
}

void displayRadioHandler(void * parameter) {
  for (;;) {
    xSemaphoreTake(displayRadioEvent, portMAX_DELAY);
    debug_printf("DisplayRadioHandler Core = %d\r\n", xPortGetCoreID());
    if (currentPage == DISPLAY_RADIO) displayRadio();
  }
}

void displayVolume() {
  debug_printf("Volume = %d\r\n", currentVolume );
  const char* text;
  if (currentVolume < 1)       return;
  else if (currentVolume < 3)  text = "▁";
  else if (currentVolume < 5)  text = "▂";
  else if (currentVolume < 7)  text = "▃";
  else if (currentVolume < 9)  text = "▄";
  else if (currentVolume < 11) text = "▅";
  else if (currentVolume < 13) text = "▆";
  else if (currentVolume < 15) text = "▇";
  else                         text = "█";
  tft.setTextDatum(MC_DATUM);
  tft.drawString(text, 149, 21);
}

void displayMute() {
  const char* text;
  if (isMute) text = "";
  else        text = "";
  tft.setTextDatum(MC_DATUM);
  tft.drawString(text, 185, 24);
}

void displayLevel() {
  const char* text;
  uint8_t rssi = radioGetRssi();
  debug_printf("RSSI = %d\r\n", rssi);
  if (rssi < 20)      text = "";
  else if (rssi < 30) text = "";
  else if (rssi < 50) text = "";
  else if (rssi < 60) text = "";
  else                text = "";
  tft.setTextDatum(MC_DATUM);
  tft.drawString(text, 221, 24);
}

void displayFreq() {
  String freq;
  freq.reserve(16);

  RadioItem_t rec = radioList[currentIndex];
  uint16_t band = rec.band;
  freq.concat((uint16_t)(band / 10));
  freq.concat('.');
  freq.concat((uint16_t)(band % 10));
  tft.setTextDatum(MC_DATUM);
  tft.drawString(freq, 63, 26);
}

void displayRadio() {
  debug_printf("DisplayRadio Core = %d\r\n", xPortGetCoreID());

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_MAGENTA);

  tft.loadFont(FONT_SEGOE_32);
  debug_printf("▁ %d\r\n", tft.textWidth("▁"));
  debug_printf("▂ %d\r\n", tft.textWidth("▂"));
  debug_printf("▃ %d\r\n", tft.textWidth("▃"));
  debug_printf("▄ %d\r\n", tft.textWidth("▄"));
  debug_printf("▅ %d\r\n", tft.textWidth("▅"));
  debug_printf("▆ %d\r\n", tft.textWidth("▆"));
  debug_printf("▇ %d\r\n", tft.textWidth("▇"));
  debug_printf("█ %d\r\n", tft.textWidth("█"));
  debug_printf(" %d\r\n", tft.textWidth(""));
  debug_printf(" %d\r\n", tft.textWidth(""));
  debug_printf(" %d\r\n", tft.textWidth(""));
  debug_printf(" %d\r\n", tft.textWidth(""));
  debug_printf(" %d\r\n", tft.textWidth(""));
  debug_printf(" %d\r\n", tft.textWidth(""));
  debug_printf(" %d\r\n", tft.textWidth(""));
  debug_printf("Height = %d\r\n", tft.fontHeight());
  displayVolume();
  displayMute();
  displayLevel();
  tft.unloadFont();
  
  tft.loadFont(FONT_CALIBRI_56);
  displayFreq();
  tft.unloadFont();

  tft.loadFont(FONT_CALIBRI_32);
  
  RadioItem_t rec = radioList[currentIndex];
  String text = rec.name;
  if (tft.textWidth(text) >=  239) {
    tft.setTextDatum(TL_DATUM);
    tft.drawString(text, 0, 70);
  }
  else {
    tft.setTextDatum(TC_DATUM);
    tft.drawString(text, 119, 70);
  }
  tft.unloadFont();
}

void displayDeviceHandler(void* parameter) {
  for (;;) {
    xSemaphoreTake(displayDeviceEvent, portMAX_DELAY);
    debug_printf("DisplayDeviceHandler Core = %d\r\n", xPortGetCoreID());
    if (currentPage == DISPLAY_DEVICE) displayDevice();
  }
}

void displayDevice() {
  debug_printf("DisplayDevice Core = %d\r\n", xPortGetCoreID());
  tft.fillScreen(TFT_BLUE);
}

IRAM_ATTR void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  ir_cmd = aCommand;
  ir_repeat = isRepeat;
  xSemaphoreGive(ir_event);
}

void receiverHandler(void * parameter) {
  for (;;) {
    xSemaphoreTake(ir_event, portMAX_DELAY);
    debug_printf("\r\nIR Receiver Core = %d, CMD=0x%04X R=%d\n\r\n", xPortGetCoreID(), ir_cmd, ir_repeat);
    if (!ir_repeat) {
      switch (ir_cmd) {
        case CARMP3_CH_MINUS:
          handleChannel(-1);
          break;
        case CARMP3_CH_PLUS:
          handleChannel(1);
          break;
        case CARMP3_VOL_MINUS:
          handleVolume(-1);
          break;
        case CARMP3_VOL_PLUS:
          handleVolume(1);
          break;
        case CARMP3_EQ:
          handleMute(!isMute);
          break;
        case CARMP3_1:
          setDisplayPage(DISPLAY_WEATHER);
          break;
        case CARMP3_2:
          setDisplayPage(DISPLAY_RADIO);
          break;
        case CARMP3_3:
          setDisplayPage(DISPLAY_DEVICE);
          break;
        default:
          break;
      }
    }
  }
}

#if defined(DEBUG_CONSOLE)
void listDir(const char* dirname, Print* p) {
  p->printf("Listing directory: %s\r\n", dirname);

  File root = SPIFFS.open(dirname);
  if(!root) {
    p->printf("- failed to open directory\r\n");
    return;
  }
  if(!root.isDirectory()) {
    p->printf(" - not a directory\r\n");
    return;
  }

  File file = root.openNextFile();
  while(file) {
    if(file.isDirectory()) {
      p->printf("  DIR : %s\r\n", file.name());
      listDir(file.name(), p);
    } else {
      p->printf("  FILE: %s\tSIZE: %d\r\n", file.name(), file.size());
    }
    file = root.openNextFile();
  }
}

void vTaskGetRunTimeStats() {
  TaskStatus_t* pxTaskStatusArray;
  volatile UBaseType_t uxArraySize, x;
  uint32_t ulTotalRunTime, ulStatsAsPercentage;
  // Take a snapshot of the number of tasks in case it changes while this
  // function is executing.
  uxArraySize = uxTaskGetNumberOfTasks();
  // Allocate a TaskStatus_t structure for each task.  An array could be
  // allocated statically at compile time.
  pxTaskStatusArray = (TaskStatus_t *)pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));
  if (pxTaskStatusArray != NULL) {
    // Generate raw status information about each task.
    uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);
    // For percentage calculations.
    ulTotalRunTime /= 100UL;
    // Avoid divide by zero errors.
    if (ulTotalRunTime > 0) {
      // For each populated position in the pxTaskStatusArray array,
      // format the raw data as human readable ASCII data
      for (x = 0; x < uxArraySize; x++)
      {
        // What percentage of the total run time has the task used?
        // This will always be rounded down to the nearest integer.
        // ulTotalRunTimeDiv100 has already been divided by 100.
        ulStatsAsPercentage = pxTaskStatusArray[x].ulRunTimeCounter / ulTotalRunTime;
        if (ulStatsAsPercentage > 0UL) {
          debug_printf("%s\t\t%u\t\t%u%%\r\n", pxTaskStatusArray[x].pcTaskName, pxTaskStatusArray[x].ulRunTimeCounter, ulStatsAsPercentage);
        }
        else {
          // If the percentage is zero here then the task has
          // consumed less than 1% of the total run time.
          debug_printf("%s\t\t%u\t\t<1%%\r\n", pxTaskStatusArray[x].pcTaskName, pxTaskStatusArray[x].ulRunTimeCounter);
        }
      }
    }
    // The array is no longer needed, free the memory it consumes.
    vPortFree(pxTaskStatusArray);
  }
}

#endif
