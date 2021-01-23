/*
Схема подлючения

(Standard I2S interface) BCLK->BCK, I2SO->DIN, and LRCLK(WS)->LCK

     ESP32         PCM5102A
    ┌───┐     ┌───┬───┐             ┌────┬──────┐
    │ +5V ├───┤ VCC │     │           ─┤  VCC  │          │
    │     │     │ 3.3V│ 3.3V│           ─┤  3.3V │          ├─┐
    │ GND ├───┤ GND │ GND │           ─┤  GND  │ PCM5102A │  │
    │     │     │ FLT │ GND │           ─┤  FLT  │          ├─┘
    │     │     │ DMP │ GND │           ─┤  DMP  │          │
    │     │     │ SCL │ GND │           ─┤  SCL  │          │
    │ 27  ├───┤ BCK │     │           ─┤  BCK  │          │
    │ 25  ├───┤ DIN │     │           ─┤  DIN  │          │
    │ 26  ├───┤ LCK │     │           ─┤  LCK  │          │
    │     │     │ FMT │ GND │           ─┤  FMT  │          │
    │     │     │ XMT │ 3.3V│           ─┤  XMT  │          │
    └───┘     └───┴───┘             └────┴──────┘

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

#define I2S_DOUT      25    // DIN connection
#define I2S_BCLK      27    // Bit clock
#define I2S_LRC       26    // Left Right Clock

#define BUTTON_1      35
#define BUTTON_2      0

TFT_eSPI tft = TFT_eSPI(135, 240);
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
Audio audio;

String ssid         = "";  // SSID WI-FI
String password     = "";
int currentStation = 0;

typedef struct _radioItem
{
  char *name;
  char *url;
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
    {.name = "Bells - Хорошее радио",               .url = "radio.horoshee.fm:8000/mp3" },
};

#define StationCount (sizeof(listStation)/sizeof(listStation[0]))

void setup()
{
  Serial.begin(115200);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  //tft.setTextSize(2);
  tft.drawCentreString("WebRadio", 67, 80, 2);
/*
  Serial.print("width  ");
  Serial.println(tft.width());
  Serial.print("height  ");
  Serial.println(tft.height());
  Serial.print("StationCount  ");
  Serial.println(StationCount);
*/
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
   tft.drawCentreString(".  ", 67, 120, 2);
   delay(500);
   tft.drawCentreString(" . ", 67, 120, 2);
   delay(500);
   tft.drawCentreString("  .", 67, 120, 2);
   delay(500);
  }
  tft.fillScreen(TFT_BLACK);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(5); // 0...21
  setRadioStation();
  
  btn1.setPressedHandler(nextRadioStation);
  btn2.setPressedHandler(prevRadioStation);
}

void setRadioStation()
{
  Serial.print("CurrentStation  ");
  Serial.println(currentStation);
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString(listStation[currentStation].name, 67, 80, 2);
  audio.connecttohost(listStation[currentStation].url);
}

void nextRadioStation(Button2 & b)
{
  currentStation++;
  if (currentStation == StationCount) currentStation = 0;
  setRadioStation();
}

void prevRadioStation(Button2 & b)
{
  currentStation--;
  if (currentStation < 0) currentStation = StationCount - 1;
  setRadioStation();
}

void loop()
{
  audio.loop();
  btn1.loop();
  btn2.loop();
}

// optional
void audio_info(const char *info)
{
  Serial.print("info        ");
  Serial.println(info);
}
void audio_id3data(const char *info)
{
  Serial.print("id3data     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info)
{
  Serial.print("eof_mp3     ");
  Serial.println(info);
}
void audio_showstation(const char *info)
{
  Serial.print("station     ");
  Serial.println(info);
}
void audio_showstreaminfo(const char *info)
{
  Serial.print("streaminfo  ");
  Serial.println(info);
}
void audio_showstreamtitle(const char *info)
{
  Serial.print("streamtitle ");
  Serial.println(info);
}
void audio_bitrate(const char *info)
{
  Serial.print("bitrate     ");
  Serial.println(info);
}
void audio_commercial(const char *info)
{
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info)
{
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info)
{
  Serial.print("lasthost    ");
  Serial.println(info);
}
void audio_eof_speech(const char *info)
{
  Serial.print("eof_speech  ");
  Serial.println(info);
}
