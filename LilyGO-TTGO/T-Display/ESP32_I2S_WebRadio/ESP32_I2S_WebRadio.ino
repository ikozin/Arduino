/*
    ┌─────────┐
    ┤GND         3V3├ 
    ┤GND         SVP├ 
    ┤21           37├ 
    ┤22           38├ 
    ┤17          SVN├ 
    ┤2            32├ 
    ┤15           33├ 
    ┤13           25├ I2S
    ┤12           26├ I2S
    ┤GND          27├ I2S
    ┤GND         GND├ 
    ┤3V3          5V├ 
    └─────────┘



Схема подлючения

(Standard I2S interface) BCLK->BCK, I2SO->DIN, and LRCLK(WS)->LCK

     ESP32         PCM5102A
    ┌───┐     ┌───┬───┐             ┌────┬───────────────────────────────────────────┐
    │ +5V ├───┤ VCC │     │           ─┤  VCC  │                                                                        │
    │     │     │ 3.3V│ 3.3V│           ─┤  3.3V │ PCM5102A                                                               ├─┐
    │ GND ├───┤ GND │ GND │           ─┤  GND  │                                                                        │  │
    │     │     │ FLT │ GND │           ─┤  FLT  │ Filter select : Normal latency (Low) / Low latency (High)              ├─┘
    │     │     │ DMP │ GND │           ─┤  DMP  │ De-emphasis control for 44.1kHz sampling rate(1): Off (Low) / On (High)│
    │     │     │ SCL │ GND │           ─┤  SCL  │ System clock input                                                     │
    │ 27  ├───┤ BCK │     │           ─┤  BCK  │ Audio data bit clock input                                             │
    │ 25  ├───┤ DIN │     │           ─┤  DIN  │ Audio data input                                                       │
    │ 26  ├───┤ LCK │     │           ─┤  LCK  │ Audio data word clock input                                            │
    │     │     │ FMT │ GND │           ─┤  FMT  │ Audio format selection : I2S (Low) / Left justified (High)             │
    │     │     │ XMT │ 3.3V│           ─┤  XMT  │ Soft mute control : Soft mute (Low) / soft un-mute (High)              │
    └───┘     └───┴───┘             └────┴───────────────────────────────────────────┘

+5V   from ESP32   -> VCC
GND   from ESP32   -> GND, FLT, DMP, FMT, SCL
+3.3V from PCM5102 -> XMT


  ESP32          PCM5102A
┌───┐     ┌───┬───┐                │     │     │     │     │
│     │     │ FLT │ GND │      ┌─────┴───┴───┴───┴───┴────────┐
│     │     │ DEMP│ GND │      │        FLT   DEMP   XSMT   FMT    3V3            │
│     │     │ XSMT│ 3V3 │      ┤ BCK                                              │
│     │     │ FMT │ GND │      ┤ DIN                                              │
│     │     │ 3V3 │ 3V3 │      ┤ LCK                 PCM5102A                     │
│     │     ├───┼───┤      ┤ GND                                              │
│     │     │ SCK │ GND │      ┤ VIN                                              │
│ 27  ├───┤ BCK │     │      │                                                  │
│ 25  ├───┤ DIN │     │      └───────────────────────┬───┬──┘
│ 26  ├───┤ LCK │     │                                              │     │
│ GND ├───┤ GND │ GND │                                              └───┘
│ +5V ├───┤ VIN │     │
└───┘     └───┴───┘



НАСТРОЙКИ ПЛАТЫ
Плата: ESP32 Dev Module
Partition Scheme: Huge APP (3MB No OTA/1MB SPIFFS)
*/

#include <WiFi.h>
#include <Audio.h>
#include <Button2.h>
#include <TFT_eSPI.h>
#include <Preferences.h>
#include <ESP32Encoder.h>
#include <esp_sntp.h>
#include "WebRadio.h"

#define I2S_DIN       25    // DIN
#define I2S_BCK       27    // BCK
#define I2S_LCK       26    // LCK

#define BUTTON_1      35
#define BUTTON_2      0

#define TFT_BL        4   // Display backlight control pin

TFT_eSPI tft = TFT_eSPI(135, 240);
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
Audio audio;
Preferences prefs;
ESP32Encoder encoderL;
ESP32Encoder encoderR;

int currentPage     = RADIO_PAGE;

void (*loopPage)()  = NULL;


String ssid         = ""; // SSID WI-FI
String pswd         = "";

int station         = 0;
int volume          = 5;


typedef struct _radioItem {
  const char *name;
  const char *name2;  
  const char *url;
} RadioItem;

const RadioItem listStation[] PROGMEM = {
    {.name = "Наше радио",      .name2 = "",              .url = "nashe1.hostingradio.ru/nashe-128.mp3" },
    {.name = "Наше радио",      .name2 = "",              .url = "nashe1.hostingradio.ru/nashe20-128.mp3" },
    {.name = "Дорожное",        .name2 = "радио",         .url = "dorognoe.hostingradio.ru:8000/radio" },
    {.name = "Европа плюс",     .name2 = "",              .url = "ep128.streamr.ru/" },
    {.name = "Радио Рекорд",    .name2 = "Супердискотека",  .url = "air.radiorecord.ru:8102/sd90_128" },
    {.name = "Вести FM",        .name2 = "Petersburg",    .url = "icecast.vgtrk.cdnvideo.ru/vestifm_mp3_192kbps" },
    {.name = "Радио Маяк",      .name2 = "Москва",        .url = "icecast.vgtrk.cdnvideo.ru:8000/mayakfm" },
    {.name = "101.ru",          .name2 = "Retro",         .url = "retroserver.streamr.ru:8043/retro128" },
    {.name = "Radio",           .name2 = "Eurodance",     .url = "stream2.laut.fm/eurodance" },
    {.name = "Klassik Radio",   .name2 = "Pure Bach",     .url = "stream.klassikradio.de/purebach/mp3-128/radiosure/" },
    {.name = "Radio Caprice",   .name2 = "Techno",        .url = "79.120.77.11:9073/" },
    {.name = "Bells",           .name2 = "Хорошее радио", .url = "radio.horoshee.fm:8000/mp3" },
};

#define StationCount (sizeof(listStation)/sizeof(listStation[0]))

void setup() {
  Serial.begin(115200);
  
  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h

  prefs.begin("WebRadio");
  
  ssid = prefs.getString("ssid", ssid);
  pswd = prefs.getString("pswd", pswd);
  //prefs.putString("ssid", ssid);
  //prefs.putString("pswd", pswd);
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  
  displaySystemInfo(tft);
  displaySystemInfo(Serial);  

  tft.printf("Wi-Fi SSID: %s, connecting", ssid.c_str());
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pswd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    tft.printf(".");
    delay(500);
    tft.printf(".");
    delay(500);
    tft.printf(".");
    delay(500);
    yield();
  }
  tft.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());

  setup_sntp();
  
  currentPage = prefs.getInt("page", TIME_PAGE);
  volume    = prefs.getInt("volume", volume);
  station   = prefs.getInt("station", station);
  
  stationY  = prefs.getInt("stationY", stationY);
  station2Y = prefs.getInt("station2Y", station2Y);
  scrollY   = prefs.getInt("scrollY", scrollY);

  timeX     = prefs.getInt("timeX", timeX);
  timeY     = prefs.getInt("timeY", timeY);
  dowY      = prefs.getInt("dowY", dowY);
  calendarY = prefs.getInt("calendarY", calendarY);
  
  audio.setPinout(I2S_BCK, I2S_LCK, I2S_DIN);
  
  btn1.setClickHandler(nextStation);
  btn2.setClickHandler(prevStation);

  btn1.setLongClickHandler(nextPage);
  btn2.setLongClickHandler(prevPage);
  
  delay(1000);

  logTime(tft);
  logTime(Serial);
  
  setVolume();
  setStation();

  switch (currentPage) {
    case RADIO_PAGE:
      setRadioPage();
      break;
    case TIME_PAGE:
      setTimePage();
      break;
  }
}

void setup_sntp() {
  setenv("TZ", "UTC-3", 1);// Set timezone to Moscow
  tzset();

  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, "pool.ntp.org");
  sntp_init();
}

void logTime(Print& prn)
{
  time_t now;
  char strftime_buf[64];
  struct tm timeinfo;
  time(&now);
  localtime_r(&now, &timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  prn.printf("%s\r\n", strftime_buf);
}

void nextPage(Button2& b) {
  switch (currentPage) {
    case RADIO_PAGE:
      setTimePage();
      break;
    case TIME_PAGE:
      setRadioPage();
      break;
  }
  prefs.putInt("page", currentPage);
}

void prevPage(Button2& b) {
  switch (currentPage) {
    case TIME_PAGE:
      setRadioPage();
      break;
    case RADIO_PAGE:
      setTimePage();
      break;
  }
  prefs.putInt("page", currentPage);
}

void setRadioPage() {
  loopPage = NULL;
  currentPage = RADIO_PAGE;
  displayRadioPage();
  loopPage = loopRadioPage;
}

void setTimePage() {
  loopPage = NULL;
  currentPage = TIME_PAGE;
  displayTimePage();
  loopPage = loopTimePage;
}

void nextStation(Button2& b) {
  station++;
  if (station == StationCount) station = 0;
  setStation();
}

void prevStation(Button2& b) {
  station--;
  if (station < 0) station = StationCount - 1;
  setStation();
}

void setStation() {
  Serial.printf("station: %d\r\n", station);
  prefs.putInt("station", station);
  audio.connecttohost(listStation[station].url);
  displayStation();
}

void upVolume() {
  volume++;
  if (volume > 21) volume = 21;
  setVolume();
}

void downVolume() {
  volume--;
  if (volume < 0) volume = 0;
  setVolume();
}

void setVolume() {
  Serial.printf("volume: %d\r\n", volume);
  prefs.putInt("volume", volume);
  audio.setVolume(volume); // 0...21
}

void loop() {
  audio.loop();
  btn1.loop();
  btn2.loop();
  if (loopPage) loopPage();
}

void displaySystemInfo(Print& prn) {
  prn.printf("\r\nModel: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
  uint64_t chipid = ESP.getEfuseMac();
  prn.printf("ChipId: %04X%08X\r\n", (uint32_t)(chipid >> 32), (uint32_t)(chipid & 0xFFFFFFFF));
  prn.printf("Flash: %d\r\n", ESP.getFlashChipSize());
  prn.printf("SDK: %s\r\n", ESP.getSdkVersion());
}

void audio_showstreamtitle(const char *info) {
  Serial.printf("streamtitle %s\r\n", info);
  setScroll(info);
}