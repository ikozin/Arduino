#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <LittleFS.h>

#include <Button2.h>
#include <ESP32Encoder.h>

#include "display.h"
#include "logging.h"

#include "controller/storageAlarm.h"
#include "controller/storageRadio.h"

#include "controller/controller.h"
#include "controller/controllerAlarm.h"
#include "controller/controllerBme280.h"
#include "controller/controllerBuzzer.h"
#include "controller/controllerEnviroment.h"
#include "controller/controllerGPIOInput.h"
#include "controller/controllerGPIOInput_SoftReset.h"
#include "controller/controllerIrRemote.h"
#include "controller/controllerIrRemote_CarMp3.h"
#include "controller/controllerNavigator.h"
#include "controller/controllerRadSens.h"
#include "controller/controllerRadio.h"
#include "controller/controllerTimeDS3231.h"
#include "controller/controllerTimeWeb.h"

#include "view/view.h"
#include "view/viewTime.h"
#include "view/viewBme280.h"
#include "view/viewRadSens.h"
#include "view/viewRadio.h"

#if !defined(ESP32)
    #error Select ESP32 DEV Board (lilygo-t-display)
#endif

// https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html
/*
    ------------------------
    | 17 |           |     |
    |  2 |           |     |
    | 15 |           |     |
    | 13 |  IRemote  | +5V |    MP1094
    | 12 |           |     |
    | 25 |           | +5V |
    | 26 |           | +5V |
    | 27 |  Buzzer   |     |
    ------------------------
    | 33 |  Reset    |     |
    ------------------------

    -----------------------------------
    |SDA|SCL|GND|+3V|         |GND|+5V|
    | X | X | X | X | DS3231  | - | - |
    | X | X | X | X | RadSens | - | - |
    | X | X | X | X | BME280  | - | - |
    | X | X | X | X | RDA5807 | - | - |
    -----------------------------------
*/

#define BUZZER_ENABLE
#define IR_ENABLE
#define RADIO_ENABLE
#define BME280_ENABLE
#define RADSENS_ENABLE
#define TIME_ENABLE
#define RESET_ENABLE
#define WIFI_ENABLE

#ifdef IR_ENABLE
    #define RADIO_ENABLE
#endif

TFT_eSPI    tft(TFT_WIDTH, TFT_HEIGHT); // 135x240;
TFT_eSprite sprite(&tft);
Preferences prefs = Preferences();
//AsyncWebServer server = AsyncWebServer(80);

#define ENCODER_PIN_A   GPIO_NUM_38
#define ENCODER_PIN_B   GPIO_NUM_36
ESP32Encoder encoder = ESP32Encoder();

#define ENCODER_BTN     GPIO_NUM_32
Button2 btnEncoder = Button2();
void btnEncoderClick(Button2& b);
void btnEncoderDoubleClick(Button2& b);
void btnEncoderLongClick(Button2& b);

#ifdef WIFI_ENABLE
String ssid     = "";
String pswd     = "";
IPAddress host(192, 168, 2, 11);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns1(85, 21, 192, 5);
IPAddress dns2(213, 234, 192, 7);
#endif


ControllerEnviroment    ctrlEnviroment("CtrlEnvironment");

StorageAlarm            storeAlarm;
ControllerAlarm         ctrlAlarm("CtrlAlarm", &storeAlarm);

#ifdef BUZZER_ENABLE
#define BUZZER_PIN      GPIO_NUM_27
ControllerBuzzer        ctrlBuzzer("ctrlBuzzer", BUZZER_PIN);
#endif

#ifdef TIME_ENABLE
#ifdef WIFI_ENABLE
ControllerTimeWeb       ctrlTime("CtrlTimeWeb", &prefs);
#else
ControllerTimeDS3231    ctrlTime("CtrlTimeDS3231", &prefs);
#endif
ViewTime                viewTime("ViewTime", &ctrlEnviroment, &sprite, &ctrlTime);
#endif

#ifdef RADIO_ENABLE
StorageRadio            storageRadio;
ControllerRadio         ctrlRadio("CtrlRadio", &prefs, &storageRadio);
ViewRadio               viewRadio("ViewRadio", &ctrlEnviroment, &sprite, &ctrlRadio);
bool (ControllerRadio::*currentHandle)(int) = &ControllerRadio::changeVolume;
#endif

#ifdef BME280_ENABLE
ControllerBme280        ctrlBme280("CtrlBme280");
ViewBme280              viewBme280("ViewBme280", &ctrlEnviroment, &sprite, &ctrlBme280);
#endif

#ifdef RADSENS_ENABLE
ControllerRadSens       ctrlRadSens("CtrlRadSens");
ViewRadSens             viewRadSens("ViewRadSens", &ctrlEnviroment, &sprite, &ctrlRadSens);
#endif

#ifdef IR_ENABLE
#define IR_PIN          GPIO_NUM_13
ControllerIrRemote_CarMp3 ctrlIrRemote("ctrlIrRemote", IR_PIN);
#endif

#ifdef RESET_ENABLE
#define RESET_PIN       GPIO_NUM_33
ControllerGPIOInput_SoftReset   ctrlReset("ctrlReset", RESET_PIN);
#endif

IView* viewList[] = {
#ifdef TIME_ENABLE
    &viewTime,
#endif
#ifdef RADIO_ENABLE
    &viewRadio,
#endif
#ifdef BME280_ENABLE
    &viewBme280,
#endif
#if defined(RADSENS_ENABLE)
    &viewRadSens,
#endif
};

ControllerNavigator ctrlNavigator("ctrlNavigator", &tft, &sprite,
    &prefs, viewList, sizeof(viewList)/sizeof(viewList[0]), 10000);

Controller* ctrlList[] = {
#ifdef TIME_ENABLE
    &ctrlTime,
#endif
#ifdef RADIO_ENABLE
    &ctrlRadio,
#endif
#ifdef BME280_ENABLE
    &ctrlBme280,
#endif
#ifdef RADSENS_ENABLE
    &ctrlRadSens,
#endif
#ifdef IR_ENABLE
    &ctrlIrRemote,
#endif
#ifdef RESET_ENABLE
    &ctrlReset,
#endif
#ifdef BUZZER_ENABLE
    &ctrlBuzzer,
#endif
    &ctrlAlarm,
    &ctrlNavigator,
    &ctrlEnviroment,
};


void boardInfo(Print* printer) {
    printer->println();
    printer->println();
    printer->print("Model: ");
    printer->print(ESP.getChipModel());
    printer->print(", Rev: ");
    printer->print(ESP.getChipRevision());
    printer->print(", Core: ");
    printer->print(ESP.getChipCores());
    printer->println();
    printer->print("SDK: ");
    printer->print(ESP.getSdkVersion());
    printer->println();
    printer->print("Flash: ");
    printer->print(ESP.getFlashChipSize());
    printer->println();
    printer->print("NVS Free Entries: ");
    printer->print(prefs.freeEntries());
    printer->println();
    printer->print("Current Core = ");
    printer->print(xPortGetCoreID());
    printer->println();
}

void fatalError(const char * msg) {
    tft.println(msg);
    LOGN(msg);
    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP.restart();
}

#ifdef WIFI_ENABLE
TimerHandle_t wifiReconnectTimer;

void connectToWifi() {
    // LOGN("Connecting to Wi-Fi...");
    WiFi.begin(ssid.c_str(), pswd.c_str());
}

void WiFiEvent(WiFiEvent_t event) {
    // LOGN("[WiFi-event] event: %d", (int)event);
    switch(event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOGN("\r\nWiFi connected\r\nIP address:%s", WiFi.localIP().toString().c_str());
#ifdef TIME_ENABLE
            ctrlTime.SyncTime();
#endif
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOGN("\r\nWiFi lost connection");
            xTimerStart(wifiReconnectTimer, 0);
            break;
    }
}
#endif

void setup() {
    Serial.begin(115200);
    LOGN("Start");

    prefs.begin("Main");

    gpio_install_isr_service((int)ARDUINO_ISR_FLAG);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);

    boardInfo(&tft);

    if (LittleFS.begin(false)) {
        tft.print("Total: ");
        tft.print(LittleFS.totalBytes());
        tft.print(", Free: ");
        tft.print(LittleFS.totalBytes() - LittleFS.usedBytes());
        tft.println();
        LOGN("Total: %d, Free: %d", LittleFS.totalBytes(), LittleFS.totalBytes() - LittleFS.usedBytes());
    }
    else {
        fatalError("SPIFFS Error");
    }

    encoder.attachSingleEdge(ENCODER_PIN_A, ENCODER_PIN_B);
    btnEncoder.begin(ENCODER_BTN);
//     if (btnEncoder.isPressedRaw()) {
//         setSettings(prefs, tft, server);
//     } 

// #ifdef WIFI_ENABLE
//     prefs.putString("ssid", ssid);
//     prefs.putString("pswd", pswd);
//     prefs.putString("inet_host", "192.168.2.11");
//     prefs.putString("inet_gateway", "192.168.2.1");
//     prefs.putString("inet_subnet", "255.255.255.0");
//     prefs.putString("inet_dns1", "85.21.192.5");
//     prefs.putString("inet_dns2", "213.234.192.7");
// #endif
//     prefs.putInt("tz", 10800);
//     prefs.putInt("station", 32);
//     prefs.putInt("volume", 2);
//     prefs.putBool("mute", true);
//     prefs.putInt("page", 0);
//     prefs.putULong64("dayTime", MAKETIME(8, 0, 0));
//     prefs.putULong64("nightTime", MAKETIME(23, 0, 0));

#ifdef WIFI_ENABLE
    ssid = prefs.getString("ssid", ssid);
    pswd = prefs.getString("pswd", pswd);

    tft.print("Wi-Fi SSID: ");
    tft.print(ssid.c_str());
    tft.print(" ");
    LOG("Wi-Fi SSID: %s ", ssid.c_str());

    host.fromString(prefs.getString("inet_host"));
    gateway.fromString(prefs.getString("inet_gateway"));
    subnet.fromString(prefs.getString("inet_subnet"));
    dns1.fromString(prefs.getString("inet_dns1"));
    dns2.fromString(prefs.getString("inet_dns2"));

    WiFi.config(host, gateway, subnet, dns1, dns2);
      // WiFi.disconnect();
    WiFi.mode(WIFI_STA);

    wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));
    WiFi.onEvent(WiFiEvent);
    connectToWifi();
    while (WiFi.status() != WL_CONNECTED) {
        tft.print(".");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
    tft.print("\r\nconnected!\r\nip: ");
    tft.println(WiFi.localIP().toString().c_str());
    LOGN("\r\nconnected!\r\nip: ");
    LOGN(WiFi.localIP().toString().c_str());
#endif
// #ifdef DEBUG_CONSOLE
//     char text[64];
//     struct tm timeinfo;
//     getLocalTime(&timeinfo);
//     strftime(text, sizeof(text), "%c", &timeinfo);
//     //strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", &timeinfo);
//     Serial.println(text);
// #endif

ctrlAlarm.Attach(&ctrlRadio, &ctrlBuzzer);
    ctrlEnviroment.Attach(&ctrlNavigator,
        prefs.getULong64("dayTime", MAKETIME(8, 0, 0)),
        prefs.getULong64("nightTime", MAKETIME(23, 0, 0)));
#ifdef IR_ENABLE
    ctrlIrRemote.Attach(&ctrlNavigator, &ctrlRadio);
#endif
    for (int i = 0; i < sizeof(ctrlList)/sizeof(ctrlList[0]); i++) {
        Controller* ctrl = ctrlList[i];
        if (!ctrl->Initialize()) fatalError(ctrl->GetName());
    }

    btnEncoder.setClickHandler(btnEncoderClick);
    btnEncoder.setDoubleClickHandler(btnEncoderDoubleClick);
    btnEncoder.setLongClickTime(1000);
    btnEncoder.setLongClickHandler(btnEncoderLongClick);  

    uint64_t time = UINT64_MAX;
    for (int i = 0; i < sizeof(ctrlList)/sizeof(ctrlList[0]); i++) {
        ctrlList[i]->Update(time);
    }
}

void loop() {
    btnEncoder.loop();
    (&ctrlRadio->*currentHandle)(encoder.getCount());
    encoder.setCount(0);

    vTaskDelay(50 / portTICK_RATE_MS);
    uint64_t time = millis();
    for (int i = 0; i < sizeof(ctrlList)/sizeof(ctrlList[0]); i++) {
        ctrlList[i]->Update(time);
    }
}

void btnEncoderClick(Button2& b) {
    ctrlNavigator.setDisplayPageNext();
}

void btnEncoderDoubleClick(Button2& b) {
#ifdef RADIO_ENABLE
    currentHandle = (currentHandle == &ControllerRadio::changeChannel)
        ? &ControllerRadio::changeVolume
        : &ControllerRadio::changeChannel;
#endif
}

void btnEncoderLongClick(Button2& b) {
#ifdef RADIO_ENABLE
    ctrlRadio.toggleMute();
#endif
}
