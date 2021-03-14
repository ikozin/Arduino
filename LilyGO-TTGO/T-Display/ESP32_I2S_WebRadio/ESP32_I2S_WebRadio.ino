/*
                            T-Display
                       ┌─────────┐
                       ┤GND         3V3├ 
                       ┤GND         SVP├ 
                       ┤21           37├ Encoder Volume
                       ┤22           38├ Encoder Volume
Encoder Radio Button   ┤17          SVN├ Encoder Volume Button
                       ┤2            32├ 
Encoder Radio          ┤15           33├ I2S XMT
Encoder Radio          ┤13           25├ I2S DIN
*IR Remore Control*    ┤12           26├ I2S LCK
                       ┤GND          27├ I2S BCK
                       ┤GND         GND├ 
                       ┤3V3          5V├ 
                       └─────────┘

При подключению к COM порту устройства помеченные ** необходимо отключить, иначе не сможет загрузиться 

Схема подлючения I2S

(Standard I2S interface) BCLK->BCK, I2SO->DIN, and LRCLK(WS)->LCK

     ESP32         PCM5102A
    ┌───┐     ┌───┬───┐             ┌────┬──────────────--─────────────────────────────┐
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
    └───┘     └───┴───┘             └────┴───────────────---───────────────────────────┘

+5V   from ESP32   -> VCC
GND   from ESP32   -> GND, FLT, DMP, FMT, SCL
+3.3V from PCM5102 -> XMT


  ESP32          PCM5102A
┌───┐     ┌───┬───┐                │     │     │     │     │
│     │     │ FLT │ GND │      ┌─────┴───┴───┴───┴───┴──────-──┐
│     │     │ DEMP│ GND │      │        FLT   DEMP   XSMT   FMT    3V3            │
│     │     │ XSMT│ 3V3 │      ┤ BCK                                              │
│     │     │ FMT │ GND │      ┤ DIN                                              │
│     │     │ 3V3 │ 3V3 │      ┤ LCK                 PCM5102A                     │
│     │     ├───┼───┤      ┤ GND                                              │
│     │     │ SCK │ GND │      ┤ VIN                                              │
│ 27  ├───┤ BCK │     │      │                                                  │
│ 25  ├───┤ DIN │     │      └───────────────────────┬───┬─-─┘
│ 26  ├───┤ LCK │     │                                             │     │
│ GND ├───┤ GND │ GND │                                             └───┘
│ +5V ├───┤ VIN │     │
└───┘     └───┴───┘



НАСТРОЙКИ ПЛАТЫ
Плата: ESP32 Dev Module
Partition Scheme: Huge APP (3MB No OTA/1MB SPIFFS)


Формат raw файла
 --------- --------- --------- --------- --------- --------- -----------------------
|ForeColor|BackColor|  Pos X  |  Pos Y  |  Width  |  Height | Image bytes in rgb565 |
 --------- --------- --------- --------- --------- --------- -----------------------
| 2 byte  | 2 byte  | 2 byte  | 2 byte  | 2 byte  | 2 byte  | N bytes ...           |
 --------- --------- --------- --------- --------- --------- -----------------------

Интересная задача про многозадачность
https://habr.com/ru/post/479156/
код
https://github.com/abashind/home_auto_2019
*/

#include <Arduino.h>
#include <WiFi.h>
#include <Audio.h>
#include <Button2.h>
#include <TFT_eSPI.h>
#include <Preferences.h>
#include <ESP32Encoder.h>
#include <FS.h>
#include <SPIFFS.h>
#include <esp_adc_cal.h>
int vref = 1100;
#define ADC_EN              14  //ADC_EN is the ADC detection enable port
#define ADC_PIN             34

#define IR_INPUT_PIN      13 //12
#define DO_NOT_USE_FEEDBACK_LED
#include "TinyIRReceiver.cpp.h"

#include "WebRadio.h"


#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

#define DEBUG_CONSOLE
/*
Скетч использует 1184021 байт (90%) памяти устройства. Всего доступно 1310720 байт.
Глобальные переменные используют 102564 байт (31%) динамической памяти, оставляя 225116 байт для локальных переменных. Максимум: 327680 байт.

Скетч использует 1187501 байт (90%) памяти устройства. Всего доступно 1310720 байт.
Глобальные переменные используют 102636 байт (31%) динамической памяти, оставляя 225044 байт для локальных переменных. Максимум: 327680 байт.

*/
#if defined(DEBUG_CONSOLE)
#define debug_printf(...)   Serial.printf(__VA_ARGS__)
#else
#define debug_printf(...)
#define listDir(...)
#endif

#define I2S_DIN       25    // DIN
#define I2S_BCK       27    // BCK
#define I2S_LCK       26    // LCK

//#define BUTTON_1      35
//#define BUTTON_2      0


#define PIN_I2S_MUTE  32

#define TFT_BL        4   // Display backlight control pin

TFT_eSPI tft = TFT_eSPI(135, 240);

Audio audio;
Preferences prefs;

ESP32Encoder encoderL;
#define ENCODER_BTN_L 39

//ESP32Encoder encoderR;
#define ENCODER_BTN_R 17

//Button2 btnHard1(BUTTON_1);
//Button2 btnHard2(BUTTON_2);
Button2 btnEncoderL(ENCODER_BTN_L);
Button2 btnEncoderR(ENCODER_BTN_R);

int currentPage     = RADIO_PAGE;

void (*loopPage)()  = NULL;
void (*updatePage)()  = NULL;

String ssid         = ""; // SSID WI-FI
String pswd         = "";

volatile int station         = 0;
volatile int volume          = 5;
volatile bool isMute         = false;

SemaphoreHandle_t mutex;

volatile uint8_t  ir_cmd;
volatile bool     ir_repeat;
SemaphoreHandle_t ir_event;

typedef struct _radioItem {
  const char *name;
  const char *name2;  
  const char *file;
  const char *url;
} RadioItem;

const RadioItem listStation[] PROGMEM = {
    {.name = "Наше радио",      .name2 = "",                .file = "/nashe.raw",       .url = "https://nashe1.hostingradio.ru/nashe-128.mp3" },
    {.name = "Русское радио",   .name2 = "",                .file = "/rusradio.raw",    .url = "https://rusradio.hostingradio.ru/rusradio96.aacp" },
    {.name = "Авторадио",       .name2 = "",                .file = "/avto.raw",        .url = "https://pub0301.101.ru:8443/stream/air/aac/64/100" },
    {.name = "Вести FM",        .name2 = "",                .file = "/vestifm.raw",     .url = "https://icecast-vgtrk.cdnvideo.ru/vestifm_mp3_128kbps" },
    {.name = "Дорожное",        .name2 = "радио",           .file = "/dorognoe.raw",    .url = "https://dorognoe.hostingradio.ru/radio" },
    {.name = "Радио Рекорд",    .name2 = "",                .file = "/record.raw",      .url = "https://air2.radiorecord.ru:9002/rr_128" },
    {.name = "Радио DFM",       .name2 = "",                .file = "/dfm.raw",         .url = "https://dfm.hostingradio.ru/dfm96.aacp" },
};

#define StationCount (sizeof(listStation)/sizeof(listStation[0]))

void setup() {
#if defined(DEBUG_CONSOLE)  
  Serial.begin(115200);
  Serial.printf("\r\n");
  Serial.printf("\r\n");
#endif
  mutex = xSemaphoreCreateMutex();

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
#if defined(DEBUG_CONSOLE)
  displaySystemInfo(Serial);  
#endif
  if(SPIFFS.begin(true)) {
    listDir("/");
  }
  else {
    debug_printf("SPIFFS Mount Failed");
  }
    
  tft.printf("Wi-Fi SSID: %s, connecting", ssid.c_str());
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
  
  pinMode(PIN_I2S_MUTE, OUTPUT);
  audio.setPinout(I2S_BCK, I2S_LCK, I2S_DIN);
  
  btnEncoderL.setClickHandler(btnEncoderLClick);
  btnEncoderR.setClickHandler(btnEncoderRClick);
  btnEncoderL.setLongClickTime(500);
  btnEncoderL.setLongClickTime(500);
  btnEncoderL.setLongClickHandler(btnEncoderLongClick);
  btnEncoderR.setLongClickHandler(btnEncoderLongClick);

  //xTaskCreate(button_handler, "button_handler", 16384, NULL, 2, NULL);
  xTaskCreate(button_handler, "button_handler", 4096, NULL, 2, NULL);

  encoderL.attachSingleEdge(37, 38);
  //encoderR.attachSingleEdge(13, 15);

#if defined(DEBUG_CONSOLE)  
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);    //Check type of calibration value used to characterize ADC
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
      Serial.printf("eFuse Vref:%u mV\r\n", adc_chars.vref);
      vref = adc_chars.vref;
  } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
      Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\r\n", adc_chars.coeff_a, adc_chars.coeff_b);
  } else {
      Serial.printf("Default Vref: 1100mV\r\n");
  }
#endif
      
  delay(1000);

  ir_event = xSemaphoreCreateBinary();
  xTaskCreate(ir_remote_handler, "ir_remote_handler", 4096, NULL, 1, NULL);
  initPCIInterruptForTinyReceiver(); 
  
  logTime(tft);
  logTime(Serial);
  
  setStation();
  setVolume();
  setMute(isMute);

  switch (currentPage) {
    case RADIO_PAGE:
      setRadioPage();
      break;
    case TIME_PAGE:
      setTimePage();
      break;
    case WEATHER_PAGE:
      setWeatherPage();
      break;
    default:
      setRadioPage();
      break;
  }
}

void logTime(Print& prn) {
  char strftime_buf[64];
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  prn.printf("%s\r\n", strftime_buf);
}

void btnEncoderLongClick(Button2& b) {
  isMute = !isMute;
  setMute(isMute);
}

void btnEncoderLClick(Button2& b) {
  nextPage();
}

void btnEncoderRClick(Button2& b) {
  prevPage();
}

void nextPage() {
  switch (currentPage) {
    case RADIO_PAGE:
      setTimePage();
      break;
    case TIME_PAGE:
      setWeatherPage();
      break;
    case WEATHER_PAGE:
      setRadioPage();
      break;
  }
  prefs.putInt("page", currentPage);
}

void prevPage() {
  switch (currentPage) {
    case RADIO_PAGE:
      setWeatherPage();
      break;
    case TIME_PAGE:
      setRadioPage();
      break;
    case WEATHER_PAGE:
      setTimePage();
      break;
  }
  prefs.putInt("page", currentPage);
}

void setRadioPage() {
  if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
    debug_printf("RadioPage\r\n");
    loopPage = NULL;
    updatePage = NULL;
    currentPage = RADIO_PAGE;
    prefs.putInt("page", currentPage);
    updatePage = displayRadioPage;
    displayRadioPage();
    loopPage = loopRadioPage;
    xSemaphoreGive(mutex);
  }
}

void setTimePage() {
  if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
    debug_printf("TimePage\r\n");
    loopPage = NULL;
    updatePage = NULL;
    currentPage = TIME_PAGE;
    prefs.putInt("page", currentPage);
    updatePage = displayTimePage;
    displayTimePage();
    loopPage = loopTimePage;
    xSemaphoreGive(mutex);
  }
}

void setWeatherPage() {
  if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
    debug_printf("WeatherPage\r\n");
    loopPage = NULL;
    updatePage = NULL;
    currentPage = WEATHER_PAGE;
    prefs.putInt("page", currentPage);
    updatePage = displayWeatherPage;
    displayWeatherPage();
    loopPage = loopWeatherPage;
    xSemaphoreGive(mutex);
  }
}

void setMute(bool value) {
  xSemaphoreTake(mutex, portMAX_DELAY);

  debug_printf("Mute: %s\r\n", value ? "On": "Off");
  digitalWrite(PIN_I2S_MUTE, value ? LOW: HIGH);

  xSemaphoreGive(mutex);
}

void nextStation() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  station++;
  if (station == StationCount) station = 0;
  setStation();
  xSemaphoreGive(mutex);

  if (updatePage != NULL) updatePage();
}

void prevStation() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  station--;
  if (station < 0) station = StationCount - 1;
  setStation();
  xSemaphoreGive(mutex);

  if (updatePage != NULL) updatePage();
}

void setStation() {
  debug_printf("Station: %s %s\r\n", listStation[station].name, listStation[station].name2);
  prefs.putInt("station", station);
  audio.connecttohost(listStation[station].url);
}

void upVolume() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  volume++;
  if (volume > 21) volume = 21;
  setVolume();
  xSemaphoreGive(mutex);
}

void downVolume() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  volume--;
  if (volume < 0) volume = 0;
  setVolume();
  xSemaphoreGive(mutex);
}

void setVolume() {
  debug_printf("Volume: %d\r\n", volume);
  prefs.putInt("volume", volume);
  audio.setVolume(volume); // 0...21
}

void loop() {
  
  audio.loop();

  if (loopPage) loopPage();

  static uint64_t timeStamp = 0;
  if (millis() - timeStamp > 10000) {
      timeStamp = millis();
      uint16_t v = analogRead(ADC_PIN);
      float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
      String voltage = " Voltage :" + String(battery_voltage) + "V";

      char strftime_buf[64];
      struct tm timeinfo;
      getLocalTime(&timeinfo);
      strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
      Serial.print(strftime_buf);
      
      Serial.println(voltage);
  }
    
  if (encoderL.getCount() != 0) {
    if (encoderL.getCount() > 0) upVolume();
    if (encoderL.getCount() < 0) downVolume();
    encoderL.setCount(0);    
  }
/*
  if (encoderR.getCount() != 0) {
    if (encoderR.getCount() > 0) nextStation();
    if (encoderR.getCount() < 0) prevStation();
    encoderR.setCount(0);    
  }
*/
}

void audio_handler(void *pvParameters) {
    while (true) {
      audio.loop();
      vTaskDelay(500 / portTICK_RATE_MS);
    }
}

void button_handler(void *pvParameters) {
    while (true) {
      btnEncoderL.loop();
      btnEncoderR.loop();
      vTaskDelay(30 / portTICK_RATE_MS);
    }
}
/*
CarMP3
0x45  0x46  0x47
0x44  0x40  0x43
0x07  0x15  0x09
0x16  0x19  0x0D
0x0C  0x18  0x5E
0x08  0x1C  0x5A
0x42  0x52  0x4A

*/
void ir_remote_handler(void *pvParameters) {
    while (true) {
      xSemaphoreTake(ir_event, portMAX_DELAY);
      //debug_printf("C=0x%04X  R=%d\r\n", ir_cmd, ir_repeat);
      if (ir_repeat) continue;
      switch (ir_cmd) {
        case 0x45:
          prevStation();
          break;
        case 0x47:
          nextStation();
          break;
        case 0x07:
          downVolume();
          break;
        case 0x15:
          upVolume();
          break;
        case 0x09:
          isMute = !isMute;
          setMute(isMute);
          break;
        case 0x0C:
          setRadioPage();
          break;
        case 0x18:
          setTimePage();
          break;
        case 0x5E:
          setWeatherPage();
          break;
        default:
          break;
      }
    }
}

IRAM_ATTR void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  ir_cmd = aCommand;
  ir_repeat = isRepeat;
  xSemaphoreGive(ir_event);
}

void displaySystemInfo(Print& prn) {
  prn.printf("\r\nModel: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
  uint64_t chipid = ESP.getEfuseMac();
  prn.printf("ChipId: %04X%08X\r\n", (uint32_t)(chipid >> 32), (uint32_t)(chipid & 0xFFFFFFFF));
  prn.printf("Flash: %d\r\n", ESP.getFlashChipSize());
  prn.printf("SDK: %s\r\n", ESP.getSdkVersion());
  prn.printf("NVS Free Entries: %d\r\n", prefs.freeEntries());
}

#if defined(DEBUG_CONSOLE)
void listDir(const char * dirname) {
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

void audio_showstreamtitle(const char *info) {
  debug_printf("streamtitle %s\r\n", info);
  setScroll(info);
}
