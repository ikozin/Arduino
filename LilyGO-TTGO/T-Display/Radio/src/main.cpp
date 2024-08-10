#include <Arduino.h>
//#include <WiFi.h>
#include <Preferences.h>
#include <SPIFFS.h>
#include <Button2.h>
#include <TFT_eSPI.h>
#include <ESP32Encoder.h>
#include <AsyncMqttClient.h>
//#include <ESPAsyncWebServer.h>
#include "main.h"
#include "setting.h"


#include "view.h"
#include "viewTime.h"
#include "viewRadio.h"
#include "viewBme280.h"
#include "viewRadsMHZ19.h"
#include "viewWeather.h"

#include "radioStorage.h"

#include "controller.h"
#include "controllerAlarmClock.h"
#include "controllerBuzzer.h"
#include "controllerBme280.h"
#include "controllerRadSens.h"
#include "controllerMHZ19.h"
#include "controllerIrRemote.h"
#include "controllerTime.h"
#include "controllerRadio.h"
#include "controllerWeather.h"
#include "controllerSoftReset.h"

#include <..\..\tools\sdk\esp32\include\lwip\include\apps\esp_sntp.h>

//#include "IrRemote_CarMP3.h"
//#include "alarm.h"

#if !defined(ESP32)
  #error Select ESP32 DEV Board (ttgo-lora32-v1)
#endif

#if !defined(USER_SETUP_ID) || USER_SETUP_ID != 25
  #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup25_TTGO_T_Display.h"
#endif

#define RADIO_ENABLE
// #define WEATHER_ENABLE
// #define BME280_ENABLE
// #define MHZ19_RADSENS_ENABLE
#define BUZZER_ENABLE
// #define TIME_ENABLE
// #define IR_ENABLE
// #define WIFI_ENABLE
// #define MQTT_ENABLE

#if defined(WEATHER_ENABLE)
    #define WIFI_ENABLE
#endif
#ifdef IR_ENABLE
    #define RADIO_ENABLE
#endif
#ifdef MQTT_ENABLE
    #define WIFI_ENABLE
#endif

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // 135x240
TFT_eSprite sprite = TFT_eSprite(&tft);

Preferences prefs = Preferences();
//AsyncWebServer server = AsyncWebServer(80);

#define ENCODER_PIN_A   37
#define ENCODER_PIN_B   38
ESP32Encoder encoder = ESP32Encoder();
#define ENCODER_BTN     39
Button2 btnEncoder = Button2();

String ssid         = ""; // SSID WI-FI
String pswd         = "";

int16_t viewIndex  = -1;
View* currentView = nullptr;

SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

RadioStorage ctrlRadioStorage;

#ifdef IR_ENABLE
#define IR_PIN  GPIO_NUM_13
ControllerIrRemote ctrlIrRemote("CtrlIrRemote", IR_PIN);
#endif

#ifdef BUZZER_ENABLE
#define BUZZER_PIN  GPIO_NUM_17
ControllerBuzzer ctrlBuzzer("CtrlBuzzer", BUZZER_PIN);
#endif

#ifdef RADIO_ENABLE
ControllerRadio ctrlRadio = ControllerRadio("CtrlRadio", &prefs, &ctrlRadioStorage);
ViewRadio viewRadio = ViewRadio("ViewRadio", &currentView, &ctrlRadio);
#endif

#ifdef WEATHER_ENABLE
ControllerWeather ctrlWeather = ControllerWeather("CtrlWeather");
ViewWeather viewWeather = ViewWeather("ViewWeather", &currentView, &ctrlWeather);
#endif

#ifdef BME280_ENABLE
ControllerBme280 ctrlBme280 = ControllerBme280("CtrlBme280");
ViewBME280 viewBme280 = ViewBME280("ViewBME280", &currentView, &ctrlBme280);
#endif

#ifdef MHZ19_RADSENS_ENABLE

#define UART_RX_PIN  GPIO_NUM_17
#define UART_TX_PIN  GPIO_NUM_27

SemaphoreHandle_t updateEvent = xSemaphoreCreateBinary(); 
ControllerRadSens ctrlRadSens = ControllerRadSens("CtrlRadSens", updateEvent);
ControllerMHZ19 ctrlMHZ19 = ControllerMHZ19("CtrlMHZ19", UART_RX_PIN, UART_TX_PIN, updateEvent);
ViewRadsMHZ19 viewRadsMHZ19 = ViewRadsMHZ19("ViewRadsMHZ19", &currentView, &ctrlRadSens);
#endif

#ifdef TIME_ENABLE
ControllerTime ctrlTime = ControllerTime("CtrlTime", &prefs);
ViewTime viewTime = ViewTime("ViewTime", &currentView, &ctrlTime);
#endif

#define RESET_PIN   GPIO_NUM_33
ControllerSoftReset ctrlReset = ControllerSoftReset("CtrlSoftReset", RESET_PIN);

View* viewList[] = {
#ifdef TIME_ENABLE
    &viewTime,
#endif
#ifdef RADIO_ENABLE
    &viewRadio,
#endif
#ifdef WEATHER_ENABLE
    &viewWeather,
#endif
#ifdef BME280_ENABLE
    &viewBme280,
#endif
#ifdef MHZ19_RADSENS_ENABLE
    &viewRadsMHZ19,
#endif
};

#ifdef RADIO_ENABLE
void (ControllerRadio::*currentHandle)(int);
#endif


void btnEncoderClick(Button2& b);
void btnEncoderDoubleClick(Button2& b);
void btnEncoderLongClick(Button2& b);

// void listDir(const char* dirname);

uint16_t fileData[4096];

#ifdef WIFI_ENABLE

#ifdef MQTT_ENABLE
AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
#endif

TimerHandle_t wifiReconnectTimer;
AsyncWebServer server(80);

void connectToWifi() {
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid.c_str(), pswd.c_str());
}

#ifdef MQTT_ENABLE
void connectToMqtt() {
    Serial.println("Connecting to MQTT...");
    mqttClient.connect();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
    Serial.println("Disconnected from MQTT.");
    if (WiFi.isConnected()) {
        xTimerStart(mqttReconnectTimer, 0);
    }
}
#endif

void WiFiEvent(WiFiEvent_t event) {
    // Serial.printf("[WiFi-event] event: %d\n", event);
    switch(event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.println("\r\nWiFi connected");
            Serial.print("IP address:");
            Serial.println(WiFi.localIP());
            configTime(prefs.getInt("tz", 10800), 0, "ntp2.vniiftri.ru");
#ifdef MQTT_ENABLE
            connectToMqtt();
#endif
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("\r\nWiFi lost connection");
#ifdef MQTT_ENABLE
            xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
#endif
            xTimerStart(wifiReconnectTimer, 0);
            break;
    }
}
#endif

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
    Serial.begin(115200);

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
        LOG("Total: %d, Free: %d\r\n", SPIFFS.totalBytes(), SPIFFS.totalBytes() - SPIFFS.usedBytes());
        //listDir("/");
    }
    else {
        //SPIFFS.format();
        tft.printf("SPIFFS Error\r\n");
        LOG("SPIFFS Error\r\n");
    }

#ifdef RADIO_ENABLE
    if (!ctrlRadioStorage.load()) {
        tft.printf("Error loading RadioStorage");
        LOG("Error loading RadioStorage");
    }
#endif

    encoder.attachSingleEdge(ENCODER_PIN_A, ENCODER_PIN_B);
    btnEncoder.begin(ENCODER_BTN);
    if (btnEncoder.isPressedRaw()) {
#ifdef WIFI_ENABLE
        setSettings(prefs, tft, server);
#endif
    }

    // prefs.putString("ssid", "...");
    // prefs.putString("pswd", "...");
    // prefs.putInt("tz", 10800);
    // prefs.putInt("station", 32);
    // prefs.putInt("volume", 2);
    // prefs.putBool("mute", true);
    // prefs.putInt("page", 0);
    // prefs.putString("mqtt_broker", "192.168.1.50");
    // prefs.putString("mqtt_user", "...");
    // prefs.putString("mqtt_password", "...");

    ssid = prefs.getString("ssid", ssid);
    pswd = prefs.getString("pswd", pswd);

    tft.printf("Wi-Fi SSID: %s ", ssid.c_str());
    LOGN("Wi-Fi SSID: %s ", ssid.c_str())

#ifdef WIFI_ENABLE
    // WiFi.disconnect();
    WiFi.mode(WIFI_STA);
#ifdef MQTT_ENABLE
    // mqttClient.onConnect(onMqttConnect);
    mqttClient.onDisconnect(onMqttDisconnect);
    // mqttClient.onSubscribe(onMqttSubscribe);
    // mqttClient.onUnsubscribe(onMqttUnsubscribe);
    // mqttClient.onMessage(onMqttMessage);
    // mqttClient.onPublish(onMqttPublish);
    mqttClient.setServer(prefs.getString("mqtt_broker").c_str(), 1883);    
    mqttClient.setCredentials(prefs.getString("mqtt_user").c_str(), prefs.getString("mqtt_password").c_str());
    mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
#endif
    wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));
    WiFi.onEvent(WiFiEvent);
    connectToWifi();
    while (WiFi.status() != WL_CONNECTED) {
        tft.printf(".");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
    tft.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());
    LOG("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str())
    configTime(prefs.getInt("tz", 10800), 0, "ntp1.vniiftri.ru", "ntp2.vniiftri.ru");

    do vTaskDelay(1000 / portTICK_RATE_MS);
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED);
#endif

#ifdef DEBUG_CONSOLE
    char text[64];
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    strftime(text, sizeof(text), "%c", &timeinfo);
    //strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", &timeinfo);
    Serial.printf("%s\r\n", text);
#endif

    LOGN("Controller - Start")
#ifdef TIME_ENABLE
    ctrlTime.SetLockingHandler(xMutex);
    ctrlTime.Start();
#endif
#ifdef RADIO_ENABLE
    ctrlRadio.Start();
    ctrlAlarmClock.attachController(&ctrlRadio);
    ctrlAlarmClock.Start(4096);
#endif
#ifdef WEATHER_ENABLE
    ctrlWeather.Start(8192);
#endif
#ifdef BME280_ENABLE
    ctrlBme280.Start();
#endif
#ifdef BUZZER_ENABLE
    ctrlBuzzer.Start();
#endif

#ifdef MHZ19_RADSENS_ENABLE
    ctrlRadSens.SetLockingHandler(xMutex);
    ctrlRadSens.Start();
    ctrlMHZ19.SetLockingHandler(xMutex);
    ctrlMHZ19.Start();
#endif
#ifdef IR_ENABLE
    ctrlIrRemote.attachController(&ctrlRadio);
    ctrlIrRemote.Start();
#endif
    ctrlReset.Start();

    LOGN("View - Start")
    sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);
#ifdef TIME_ENABLE
    viewTime.Start(&sprite, ctrlTime.GetEvent());
#endif
#ifdef RADIO_ENABLE
    viewRadio.Start(&sprite, ctrlRadio.GetEvent());
#endif
#ifdef WEATHER_ENABLE
    viewWeather.Start(&sprite, ctrlWeather.GetEvent(), 8192);
#endif
#ifdef BME280_ENABLE
    viewBme280.Start(&sprite, ctrlBme280.GetEvent());
#endif
#ifdef MHZ19_RADSENS_ENABLE
    viewRadsMHZ19.Start(&sprite, ctrlRadSens.GetEvent());
#endif

#ifdef RADIO_ENABLE
    currentHandle = &ControllerRadio::changeVolume;
#endif
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
#ifdef RADIO_ENABLE
    (&ctrlRadio->*currentHandle)(dir);
#endif
}

void btnEncoderClick(Button2& b) {
    setDisplayPageNext();
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
