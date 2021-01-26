/*
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

#define I2S_DOUT      25    // DIN connection
#define I2S_BCLK      27    // Bit clock
#define I2S_LRC       26    // Left Right Clock

#define BUTTON_1      35
#define BUTTON_2      0

TFT_eSPI tft = TFT_eSPI(135, 240);
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
Audio audio;
Preferences prefs;

String ssid         = "";  // SSID WI-FI
String password     = "";
int currentStation  = 0;
int currentVolume   = 5;

typedef struct _radioItem
{
  const char *name;
  const char *url;
} RadioItem;

const RadioItem listStation[] PROGMEM = 
{
    {.name = ("NASHE RADIO"),                       .url = "nashe1.hostingradio.ru/nashe-128.mp3" },
    {.name = "Nashe radio2",                        .url = "nashe1.hostingradio.ru/nashe20-128.mp3" },
    {.name = "Dorozhnoe radio",                     .url = "dorognoe.hostingradio.ru:8000/radio" },
//    {.name = "Auto radio",                          .url = "ic2.101.ru:8000/v3_1" },
    {.name = "Evropa plyus",                        .url = "ep128.streamr.ru/" },
//    {.name = "101.ru - Euro Hits",                  .url = "ic3.101.ru:8000/c16_13" },
    {.name = "Radio Rekord - Superdiskoteka 90-h",  .url = "air.radiorecord.ru:8102/sd90_128" },
    {.name = "Vesti FM {Saint Petersburg}",         .url = "icecast.vgtrk.cdnvideo.ru/vestifm_mp3_192kbps" },
//--    {.name = "Радио Маяк Москва {Mayak}",           .url = "icecast.vgtrk.cdnvideo.ru:8000/mayakfm" },
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
//--    {.name = "Bells - Хорошее радио",               .url = "radio.horoshee.fm:8000/mp3" },
};

#define StationCount (sizeof(listStation)/sizeof(listStation[0]))

#define TFT_BL              4   // Display backlight control pin

void setup()
{
  Serial.begin(115200);
  
  pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setTextFont(2);
  tft.printf("\r\nstart WebRadio\r\n");
  displaySystemInfo(tft);
  displaySystemInfo(Serial);  
  tft.printf("Wi-Fi SSID: %s\r\n", ssid.c_str());
  tft.printf("connecting");

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    tft.printf(".");
    delay(500);
    tft.printf(".");
    delay(500);
    tft.printf(".");
    delay(500);
    yield();
  }
  tft.printf("\r\nconnected!\r\n");
  tft.printf("ip: %s\r\n", WiFi.localIP().toString().c_str());
  
  prefs.begin("WebRadio");
  currentVolume = prefs.getInt("volume", 5);
  currentStation = prefs.getInt("station", 0);
  
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  
  btn1.setPressedHandler(nextStation);
  btn2.setPressedHandler(prevStation);

  delay(1000);
  setVolume();
  setStation();
}

void setStation()
{
  Serial.printf("station: %d\r\n", currentStation);
  prefs.putInt("station", currentStation);
  audio.connecttohost(listStation[currentStation].url);
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString(listStation[currentStation].name, 67, 80, 2);
}

void nextStation(Button2& b)
{
  currentStation++;
  if (currentStation == StationCount) currentStation = 0;
  setStation();
}

void prevStation(Button2& b)
{
  currentStation--;
  if (currentStation < 0) currentStation = StationCount - 1;
  setStation();
}

void setVolume()
{
  Serial.printf("volume: %d\r\n", currentVolume);
  prefs.putInt("volume", currentVolume);
  audio.setVolume(currentVolume); // 0...21
}

void upVolume()
{
  currentVolume++;
  if (currentVolume > 21) currentVolume = 21;
  setVolume();
}

void downVolume()
{
  currentVolume--;
  if (currentVolume < 0) currentVolume = 0;
  setVolume();
}

void loop()
{
  audio.loop();
  btn1.loop();
  btn2.loop();
}

void displaySystemInfo(Print& prn)
{
  prn.printf("Model: %s\r\n", ESP.getChipModel());
  prn.printf("Rev: %d\r\n", ESP.getChipRevision());
  prn.printf("Core: %d\r\n", ESP.getChipCores());
  uint64_t chipid = ESP.getEfuseMac();
  prn.printf("ChipId: %04X%08X\r\n", (uint32_t)(chipid >> 32), (uint32_t)(chipid & 0xFFFFFFFF));
  prn.printf("Flash: %d\r\n", ESP.getFlashChipSize());
  prn.printf("SDK: %s\r\n", ESP.getSdkVersion());
}

/////////////////////////////////////////////////////////////////////////////////
// optional
void audio_info(const char *info)
{
  Serial.printf("info        %s\r\n", info);
}
void audio_id3data(const char *info)
{
  Serial.printf("id3data     %s\r\n", info);
}
void audio_eof_mp3(const char *info)
{
  Serial.printf("eof_mp3     %s\r\n", info);
}
void audio_showstation(const char *info)
{
  Serial.printf("station     %s\r\n", info);
}
void audio_showstreaminfo(const char *info)
{
  Serial.printf("streaminfo  %s\r\n", info);
}
void audio_showstreamtitle(const char *info)
{
  Serial.printf("streamtitle %s\r\n", info);
}
void audio_bitrate(const char *info)
{
  Serial.printf("bitrate     %s\r\n", info);
}
void audio_commercial(const char *info)
{
  Serial.printf("commercial  %s\r\n", info);
}
void audio_icyurl(const char *info)
{
  Serial.printf("icyurl      %s\r\n", info);
}
void audio_lasthost(const char *info)
{
  Serial.printf("lasthost    %s\r\n", info);
}
void audio_eof_speech(const char *info)
{
  Serial.printf("eof_speech  %s\r\n", info);
}
