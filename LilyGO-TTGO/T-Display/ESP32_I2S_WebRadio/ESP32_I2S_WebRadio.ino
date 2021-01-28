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


#include <Arduino.h>
#include <WiFi.h>
#include <Audio.h>
#include <Button2.h>
#include <TFT_eSPI.h>
#include <Preferences.h>
#include <ESP32Encoder.h>
//#include <NTPClient.h>
#include <esp_sntp.h>

#include "FontsRus\CourierCyr8.h"
#include "FontsRus\FreeMono8.h"

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
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);

//#define StateRadioTab   0
//#define StateTimeTab    1
//#define StateWeatherTab 2

String ssid         = "";  // SSID WI-FI
String password     = "";

int currentStation  = 0;
int currentVolume   = 5;

int scrollX         = 0;
int scrollWidth     = 0;
long scrollTime     = 0;
#define scrollY     100
#define scrollStep  4
#define scrollDelay 25

#define MaxStringLenght 127
char target[MaxStringLenght + 1] = "";

typedef struct _radioItem {
  const char *name;
  const char *url;
} RadioItem;

const RadioItem listStation[] PROGMEM = {
    {.name = "Наше радио",                          .url = "nashe1.hostingradio.ru/nashe-128.mp3" },
    {.name = "Наше радио",                          .url = "nashe1.hostingradio.ru/nashe20-128.mp3" },
    {.name = "Дорожное радио",                      .url = "dorognoe.hostingradio.ru:8000/radio" },
//    {.name = "Авто радио",                          .url = "ic2.101.ru:8000/v3_1" },
    {.name = "Европа плюс",                         .url = "ep128.streamr.ru/" },
//    {.name = "101.ru - Евро хиты",                  .url = "ic3.101.ru:8000/c16_13" },
    {.name = "Радио Рекорд - Супердискотека 90-х",  .url = "air.radiorecord.ru:8102/sd90_128" },
    {.name = "Вести FM {Saint Petersburg}",         .url = "icecast.vgtrk.cdnvideo.ru/vestifm_mp3_192kbps" },
    {.name = "Радио Маяк Москва {Mayak}",           .url = "icecast.vgtrk.cdnvideo.ru:8000/mayakfm" },
    {.name = "101.ru - Retro",                      .url = "retroserver.streamr.ru:8043/retro128" },
    {.name = "Radio Eurodance",                     .url = "stream2.laut.fm/eurodance" },
//    {.name = "101.ru - Русский Рок",                .url = "ic3.101.ru:8000/c1_2" },
//    {.name = "Abacus.fm - Mozart Piano",            .url = "listen.abacus.fm/mozartpiano.m3u" },
//    {.name = "Classic FM",                          .url = "ice-sov.musicradio.com/ClassicFMMP3" },
    {.name = "Klassik Radio - Pure Bach",           .url = "stream.klassikradio.de/purebach/mp3-128/radiosure/" },
//  {.name = "NRK Klassisk",                        .url = "lyd.nrk.no/nrk_radio_klassisk_mp3_h" },
//    {.name = "101.ru - Tech House",                 .url = "ic3.101.ru:8000/c18_5?setst=-1&tok=10750927noz69Grzhi/DPKrPfpYleLanrbg7jaVx0dPaV9MOQIW8AqUSV0N7kQ==" },
    {.name = "Radio Caprice - Techno",              .url = "79.120.77.11:9073/" },
//    {.name = "101.ru - StarPro",                    .url = "ic3.101.ru:8000/c18_15" },
    {.name = "Bells - Хорошее радио",               .url = "radio.horoshee.fm:8000/mp3" },
};

#define StationCount (sizeof(listStation)/sizeof(listStation[0]))

void setup() {
  Serial.begin(115200);
  
  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  
  displaySystemInfo(tft);
  displaySystemInfo(Serial);  

  tft.printf("Wi-Fi SSID: %s, connecting", ssid.c_str());
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
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
  
  prefs.begin("WebRadio");
  currentVolume = prefs.getInt("volume", 5);
  currentStation = prefs.getInt("station", 0);
  
  audio.setPinout(I2S_BCK, I2S_LCK, I2S_DIN);
  
  btn1.setPressedHandler(nextStation);
  btn2.setPressedHandler(prevStation);
  
//  timeClient.setTimeOffset(prefs.getInt("utcOffset", 10800));
//  timeClient.begin();
//  timeClient.forceUpdate();
//  Serial.println(timeClient.getFormattedTime());


  yield();
  
  delay(1000);
  get_time();
  setVolume();

  //fontDemo(&CourierCyr8pt8b);
  //fontDemo(&FreeMono8pt8b);
  tft.setFreeFont(&CourierCyr8pt8b);

  setStation();
}

void setup_sntp() {
  setenv("TZ", "UTC-3", 1);// Set timezone to Moscow
  tzset();

  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, "pool.ntp.org");
  sntp_init();
}

void get_time()
{
  time_t now;
  char strftime_buf[64];
  struct tm timeinfo;
  time(&now);
  localtime_r(&now, &timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  Serial.printf("%s\r\n", strftime_buf);
}

void setStation() {
  clearScroll();
  Serial.printf("station: %d\r\n", currentStation);
  prefs.putInt("station", currentStation);
  audio.connecttohost(listStation[currentStation].url);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  const char* pname = utf8rus2(listStation[currentStation].name);
  int width = tft.textWidth(pname);
  tft.drawString(pname, (TFT_HEIGHT - width) >> 2, 20);
}

void nextStation(Button2& b) {
  currentStation++;
  if (currentStation == StationCount) currentStation = 0;
  setStation();
}

void prevStation(Button2& b) {
  currentStation--;
  if (currentStation < 0) currentStation = StationCount - 1;
  setStation();
}

void setVolume() {
  Serial.printf("volume: %d\r\n", currentVolume);
  prefs.putInt("volume", currentVolume);
  audio.setVolume(currentVolume); // 0...21
}

void upVolume() {
  currentVolume++;
  if (currentVolume > 21) currentVolume = 21;
  setVolume();
}

void downVolume() {
  currentVolume--;
  if (currentVolume < 0) currentVolume = 0;
  setVolume();
}

void clearScroll() {
  scrollWidth = 0;
  scrollX = TFT_HEIGHT;
  int height = tft.fontHeight() >> 2;
  tft.fillRect(0, scrollY - height, scrollX, scrollY + height, TFT_BLACK);
}

void setScroll(const char * ptext) {
  clearScroll();
  utf8rus2(ptext);
  scrollX = TFT_HEIGHT;
  scrollWidth = tft.textWidth(target);
  if (scrollWidth < TFT_HEIGHT) {
    tft.drawString(target, (TFT_HEIGHT - scrollWidth) >> 2, scrollY);
    scrollWidth = 0;
  }
  strcat(target, "  ");
}

void nextScroll() {
  if (scrollWidth == 0) return;
  long time = millis();
  if (time - scrollTime >= scrollDelay) {
    tft.drawString(target, scrollX, scrollY);
    scrollX -= scrollStep;
    if (scrollX < -scrollWidth) scrollX = TFT_HEIGHT;  
    //Serial.println(time - scrollTime);
    scrollTime = time;
  }
}

void setRadioTab() {

}

void loopRadioTab() {
  nextScroll();
}

void loop() {
  audio.loop();
  btn1.loop();
  btn2.loop();
  loopRadioTab();
  //timeClient.update();  
}

void displaySystemInfo(Print& prn) {
  prn.printf("\r\nModel: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
  uint64_t chipid = ESP.getEfuseMac();
  prn.printf("ChipId: %04X%08X\r\n", (uint32_t)(chipid >> 32), (uint32_t)(chipid & 0xFFFFFFFF));
  prn.printf("Flash: %d\r\n", ESP.getFlashChipSize());
  prn.printf("SDK: %s\r\n", ESP.getSdkVersion());
}

void fontDemo(const GFXfont* pfont) {
  tft.setFreeFont(pfont);
  tft.setTextSize(1);
 
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.setCursor(0, 20);
  tft.printf("0123456789");
  tft.setCursor(0, 40);

  tft.print((char)149);
  tft.print((char)181);
  delay(12000);
}


char *utf8rus2(const char *source) {
  int i,j,k;
  unsigned char n;
  char m[2] = { '0', '\0' };
  strcpy(target, "");
  k = strlen(source);
  i = j = 0;
  while (i < k) {
    n = source[i++];
    if (n >= 127) {
      switch (n) {
        case 208:{
          n = source[i++];
          if (n == 129) { n = 149; break; } // перекодируем букву Ё->Е
          break;
        }
        case 209: {
          n = source[i++];
          if (n == 145) { n = 181; break; } // перекодируем букву ё->е
          break;
        }
        case 239: {
          n = source[i++];
          n = source[i++];
          continue;
        }
      }
    }

    m[0] = n; strcat(target, m);
    if (++j >= MaxStringLenght) break;
  }
  return target;
}

/////////////////////////////////////////////////////////////////////////////////
// optional
/*
void audio_info(const char *info) {
  Serial.printf("info        %s\r\n", info);
}
void audio_id3data(const char *info) {
  Serial.printf("id3data     %s\r\n", info);
}
void audio_eof_mp3(const char *info) {
  Serial.printf("eof_mp3     %s\r\n", info);
}
void audio_showstation(const char *info) {
  Serial.printf("station     %s\r\n", info);
}
*/
void audio_showstreamtitle(const char *info) {

  Serial.printf("streamtitle %s\r\n", info);
/*
  for (int i = 0; i < strlen(info); i++)
    Serial.printf("%d, ", (int)info[i]);
  Serial.printf("\r\n");    
*/
  setScroll(info);
}
/*
void audio_bitrate(const char *info) {
  Serial.printf("bitrate     %s\r\n", info);
}
void audio_commercial(const char *info) {
  Serial.printf("commercial  %s\r\n", info);
}
void audio_icyurl(const char *info) {
  Serial.printf("icyurl      %s\r\n", info);
}
void audio_lasthost(const char *info) {
  Serial.printf("lasthost    %s\r\n", info);
}
void audio_eof_speech(const char *info) {
  Serial.printf("eof_speech  %s\r\n", info);
}
*/
