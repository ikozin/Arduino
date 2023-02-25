#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include <SPIFFS.h>
#include <Button2.h>
#include <TFT_eSPI.h>
#include <ESP32Encoder.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "main.h"
#include "setting.h"


#include "view.h"
#include "viewRadio.h"
#include "viewDevice.h"
#include "viewWeather.h"

#include "radioStorage.h"

#include "controller.h"
#include "controllerAlarmClock.h"
#include "controllerDevice.h"
#include "controllerIrRemote.h"
#include "controllerRadio.h"
#include "controllerWeather.h"

#include <..\..\tools\sdk\esp32\include\lwip\include\apps\esp_sntp.h>

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
//AsyncWebServer server = AsyncWebServer(80);

#define ENCODER_PIN_A   37
#define ENCODER_PIN_B   38
ESP32Encoder encoder = ESP32Encoder();
#define ENCODER_BTN     39
Button2 btnEncoder = Button2();

String ssid         = ""; // SSID WI-FI
String pswd         = "";

const char* fileRadio = "/radiolist.dat";

RadioStorage ctrlRadioStorage;
ControllerRadio ctrlRadio = ControllerRadio("CtrlRadio", &prefs, &ctrlRadioStorage);
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

// void listDir(const char* dirname);

uint16_t fileData[4096];

TimerHandle_t wifiReconnectTimer;
AsyncWebServer server(80);

void connectToWifi() {
    WiFi.begin(ssid.c_str(), pswd.c_str());
}

void WiFiEvent(WiFiEvent_t event) {
    switch(event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.println("\r\nWiFi connected");
            Serial.print("IP address:");
            Serial.println(WiFi.localIP());
            configTime(prefs.getInt("tz", 10800), 0, "ntp2.vniiftri.ru");
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("\r\nWiFi lost connection");
            xTimerStart(wifiReconnectTimer, 0);
            break;
    }
}


void boardInfo(Print& stream) {
    stream.printf("\r\n");
    stream.printf("\r\n");
    stream.printf("Model: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
    stream.printf("SDK: %s\r\n", ESP.getSdkVersion());
    stream.printf("Flash: %d\r\n", ESP.getFlashChipSize());
    stream.printf("NVS Free Entries: %d\r\n", prefs.freeEntries());
    stream.printf("Current Core = %d\r\n", xPortGetCoreID());
}

void setup() {
    Serial.begin(57600);

    boardInfo(Serial);

    // pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
    // digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h

    prefs.begin("Main");

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    boardInfo(tft);

    if (SPIFFS.begin(true)) {
        tft.printf("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
        //listDir("/");
    }
    else {
        //SPIFFS.format();
        tft.printf("SPIFFS Error\r\n");
    }

    if (!ctrlRadioStorage.load()) {
        tft.printf("Error loading %s\r\n", fileRadio);
    }

    encoder.attachSingleEdge(ENCODER_PIN_A, ENCODER_PIN_B);
    btnEncoder.begin(ENCODER_BTN);
    if (btnEncoder.isPressedRaw()) {
        setSettings(prefs, tft, server);
    }

    //prefs.putString("ssid", "...");
    //prefs.putString("pswd", "...");
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

    wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));
    WiFi.onEvent(WiFiEvent);


    do vTaskDelay(500 / portTICK_RATE_MS);
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED);

    ctrlRadio.Start();
    ctrlWeather.Start();
    ctrlDevice.Start();
    ctrlAlarmClock.attachControllerRadio(&ctrlRadio).Start();
    ctrlIrRemote.attachControllerRadio(&ctrlRadio).Start();


    viewRadio.Start(ctrlRadio.GetEvent());
    viewWeather.Start(ctrlWeather.GetEvent());
    viewDevice.Start(ctrlDevice.GetEvent());

    currentHandle = &ControllerRadio::changeVolume;

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
    setDisplayPageNext();
}

void btnEncoderLongClick(Button2& b) {
    ctrlRadio.toggleMute();
}

void setDisplayPagePrev(void) {
    setDisplayPage(viewIndex - 1);
}

void setDisplayPageNext(void) {
    setDisplayPage(viewIndex + 1);
}

void setDisplayPage(int16_t page) {
    int max =  sizeof(viewList)/sizeof(viewList[0]) - 1;
    if (page < 0) {
        page = max;
    }
    if (page > max) {
        page = 0;
    }
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
