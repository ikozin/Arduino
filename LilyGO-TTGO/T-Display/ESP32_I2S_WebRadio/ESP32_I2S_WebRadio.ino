/*
Схема подлючения

(Standard I2S interface) BCLK->BCK, I2SO->DIN, and LRCLK(WS)->LCK

     ESP32         PCM5102A
    ┌───┐     ┌───────┐
    │ +5V ├───┤ VCC │     │
    │     │     │ 3.3V│ 3.3V│
    │ GND ├───┤ GND │ GND │
    │     │     │ FLT │ GND │
    │     │     │ DMP │ GND │
    │     │     │ SCL │ GND │
    │ 27  ├───┤ BCK │     │
    │ 25  ├───┤ DIN │     │
    │ 26  ├───┤ LCK │     │
    │     │     │ FMT │ GND │
    │     │     │ XMT │ 3.3V│
    └───┘     └───┴───┘

+5V   from ESP32   -> VCC
GND   from ESP32   -> GND, FLT, DMP, FMT, SCL
+3.3V from PCM5102 -> XMT

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

#define BUTTON_1            35
#define BUTTON_2            0

TFT_eSPI tft = TFT_eSPI(135, 240);
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
Audio audio;

String ssid         = "";  // SSID WI-FI
String password     = "";
int currentStation = 0;

// объявляем массив строк c радиостанциями
const char *listStation[]  = {
  "http://nashe1.hostingradio.ru/nashe-128.mp3",
  //"https://epdop.hostingradio.ru:8033/europaplus32.mp3",   // 0
  //"https://ic7.101.ru:8000/a100",                          // 1
  "https://emgspb.hostingradio.ru/retrofmspb64.mp3",       // 2
  "https://icecast-vgtrk.cdnvideo.ru/vestifm_mp3_64kbps",  // 3
  "https://rusradio.hostingradio.ru/rusradio96.aacp",      // 4
};
#define StationCount (sizeof(listStation)/sizeof(listStation[0]))

/*
{.Name = "Nashe radio",                         .URL = "nashe1.hostingradio.ru/nashe-128.mp3" }
{.Name = "Nashe radio2",                        .URL = "nashe1.hostingradio.ru/nashe20-128.mp3" }
{.Name = "Dorozhnoe radio",                     .URL = "dorognoe.hostingradio.ru:8000/radio" }
{.Name = "Auto radio",                          .URL = "ic2.101.ru:8000/v3_1" }
{.Name = "Evropa plyus",                        .URL = "ep128.streamr.ru/" }
{.Name = "101.ru - Euro Hits",                  .URL = "ic3.101.ru:8000/c16_13" }
{.Name = "Radio Svoboda",                       .URL = "rfe-channel-04.akacast.akamaistream.net/7/885/229654/v1/ibb.akacast.akamaistream.net/rfe_channel_04.mp3" }
{.Name = "Radio Rekord - Superdiskoteka 90-h",  .URL = "air.radiorecord.ru:8102/sd90_128" }
{.Name = "Vesti FM {Saint Petersburg}",         .URL = "icecast.vgtrk.cdnvideo.ru/vestifm_mp3_192kbps" }
{.Name = "Радио Маяк Москва {Mayak}",           .URL = "icecast.vgtrk.cdnvideo.ru:8000/mayakfm" }
{.Name = "101.ru - Retro",                      .URL = "retroserver.streamr.ru:8043/retro128" }
{.Name = "Radio Eurodance",                     .URL = "stream2.laut.fm/eurodance" }
{.Name = "101.ru - Русский Рок",                .URL = "ic3.101.ru:8000/c1_2" }
{.Name = "Abacus.fm - Mozart Piano",            .URL = "listen.abacus.fm/mozartpiano.m3u" }
{.Name = "Classic FM",                          .URL = "ice-sov.musicradio.com/ClassicFMMP3" }
{.Name = "Klassik Radio - Pure Bach",           .URL = "stream.klassikradio.de/purebach/mp3-128/radiosure/" }
{.Name = "NRK Klassisk",                        .URL = "lyd.nrk.no/nrk_radio_klassisk_mp3_h" }
{.Name = "101.ru - Tech House",                 .URL = "ic3.101.ru:8000/c18_5?setst=-1&tok=10750927noz69Grzhi/DPKrPfpYleLanrbg7jaVx0dPaV9MOQIW8AqUSV0N7kQ==" }
{.Name = "Radio Caprice - Techno",              .URL = "79.120.77.11:9073/" }
{.Name = "101.ru - StarPro",                    .URL = "ic3.101.ru:8000/c18_15" }
{.Name = "Bells - Хорошее радио",               .URL = "radio.horoshee.fm:8000/mp3" }

*/

void setup()
{
  Serial.begin(115200);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.drawCentreString("WebRadio", 67, 80, 2);

  Serial.print("width  ");
  Serial.println(tft.width());
  Serial.print("height  ");
  Serial.println(tft.height());
  Serial.print("StationCount  ");
  Serial.println(StationCount);

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
  audio.connecttohost(listStation[currentStation]);
  
  btn1.setPressedHandler(nextRadioStation);
  btn2.setPressedHandler(prevRadioStation);
}

void nextRadioStation(Button2 & b)
{
  currentStation++;
  if (currentStation == StationCount) currentStation = 0;
  Serial.print("CurrentStation  ");
  Serial.println(currentStation);
  audio.connecttohost(listStation[currentStation]);
}

void prevRadioStation(Button2 & b)
{
  currentStation--;
  if (currentStation < 0) currentStation = StationCount - 1;
  Serial.print("CurrentStation  ");
  Serial.println(currentStation);
  audio.connecttohost(listStation[currentStation]);
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
