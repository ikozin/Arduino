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

#include "controller/radioStorage.h"
#include "controller/controller.h"
#include "controller/controllerAlarmClock.h"
#include "controller/controllerBuzzer.h"
#include "controller/controllerBme280.h"
#include "controller/controllerRadSens.h"
#include "controller/controllerMHZ19.h"
#include "controller/controllerIrRemote.h"
#include "controller/controllerDS3231.h"
#include "controller/controllerSoftTime.h"
#include "controller/controllerRadio.h"
#include "controller/controllerWeather.h"
#include "controller/controllerSoftReset.h"
#include "controller/controllerPIR.h"

#include "component/component.h"
#include "component/componentSoftReset.h"
#include "component/componentPIR.h"
#include "component/componentIrRemote.h"

#include "view/view.h"
#include "view/viewDS3231.h"
#include "view/viewSoftTime.h"
#include "view/viewTileTime.h"
#include "view/viewRadio.h"
#include "view/viewBme280.h"
#include "view/viewRadsMHZ19.h"
#include "view/viewWeather.h"


#include <..\..\tools\sdk\esp32\include\lwip\include\apps\esp_sntp.h>

//#include "IrRemote_CarMP3.h"
//#include "alarm.h"

#if !defined(ESP32)
  #error Select ESP32 DEV Board (ttgo-lora32-v1)
#endif

#if !defined(USER_SETUP_ID) || USER_SETUP_ID != 25
  #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup25_TTGO_T_Display.h"
#endif

/*
    ------------------------
    | 17 |  PIR      | +5V |
    |  2 |           |     |
    | 15 |           |     |
    | 13 |  IRemote  | +5V |    MP1094
    | 12 |           |     |
    | 32 |           |     |
    | 33 |  Reset    |  -  |
    | 25 |  MHZ19    | +5V |
    | 26 |  MHZ19    | +5V |
    | 27 |  Buzzer   |  -  |
    ------------------------

    -----------------------------------
    |SDA|SCL|GND|+3V|         |GND|+5V|
    | X | X | X | X | DS3231  | - | - |
    | X | X | X | X | RadSens | - | - |
    | X | X | X | X | BME280  | - | - |
    | X | X | X | X | RDA5807 | - | - |
    -----------------------------------
*/

#define ENCODER_ENABLE
#define RADIO_ENABLE
// #define WEATHER_ENABLE
#define BME280_ENABLE
#define RADSENS_ENABLE
// #define PIR_ENABLE
// #define MHZ19_ENABLE
// #define RESET_ENABLE
#define BUZZER_ENABLE
#define TIME_ENABLE
#define IR_ENABLE
#define WIFI_ENABLE
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

#ifdef ENCODER_ENABLE
#if !defined(ENCODER_FAKE)
#define ENCODER_PIN_A   GPIO_NUM_38
#define ENCODER_PIN_B   GPIO_NUM_36
ESP32Encoder encoder = ESP32Encoder();
#define ENCODER_BTN     GPIO_NUM_32
Button2 btnEncoder = Button2();
#endif
#endif

String ssid         = ""; // SSID WI-FI
String pswd         = "";

int16_t viewIndex  = -1;
View* currentView = nullptr;

ViewSettig viewSettig(&tft, &sprite, &currentView);


SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

RadioStorage ctrlRadioStorage;

#ifdef IR_ENABLE
#define IR_PIN          GPIO_NUM_13
ControllerIrRemote ctrlIrRemote("CtrlIrRemote", IR_PIN);
#endif

#ifdef BUZZER_ENABLE
#define BUZZER_PIN      GPIO_NUM_27
ControllerBuzzer ctrlBuzzer("CtrlBuzzer", BUZZER_PIN);
#endif

#ifdef RADIO_ENABLE
ControllerRadio ctrlRadio = ControllerRadio("CtrlRadio", &prefs, &ctrlRadioStorage);
ViewRadio viewRadio = ViewRadio("ViewRadio", &viewSettig, &ctrlRadio);
#endif

#ifdef WEATHER_ENABLE
ControllerWeather ctrlWeather = ControllerWeather("CtrlWeather");
ViewWeather viewWeather = ViewWeather("ViewWeather", &viewSettig, &ctrlWeather);
#endif

#ifdef BME280_ENABLE
ControllerBme280 ctrlBme280 = ControllerBme280("CtrlBme280");
ViewBME280 viewBme280 = ViewBME280("ViewBME280", &viewSettig, &ctrlBme280);
#endif

#ifdef RADSENS_ENABLE
ControllerRadSens ctrlRadSens = ControllerRadSens("CtrlRadSens");
#endif

#ifdef MHZ19_ENABLE
#define UART_RX_PIN     GPIO_NUM_26
#define UART_TX_PIN     GPIO_NUM_25
ControllerMHZ19 ctrlMHZ19 = ControllerMHZ19("CtrlMHZ19", UART_RX_PIN, UART_TX_PIN);
#endif

#if defined(RADSENS_ENABLE) || defined(MHZ19_ENABLE)

#ifdef RADSENS_ENABLE
ControllerRadSens* radSens = &ctrlRadSens;
#else
ControllerRadSens* radSens = nullptr;
#endif
#ifdef MHZ19_ENABLE
ControllerMHZ19* mhz19 = &ctrlMHZ19;
#else
ControllerMHZ19* mhz19 = nullptr;
#endif

ViewRadsMHZ19 viewRadsMHZ19 = ViewRadsMHZ19("ViewRadsMHZ19", &viewSettig, radSens, mhz19);
#endif


#ifdef TIME_ENABLE
ControllerDS3231 ctrlTime = ControllerDS3231("CtrlDS3231", &prefs);
ViewDS3231 viewTime = ViewDS3231("ViewDS3231", &viewSettig, &ctrlTime);
// ViewTileTime viewTime = ViewTileTime("ViewTileTime", &viewSettig, &ctrlTime);
// ControllerSoftTime ctrlTime = ControllerSoftTime("CtrlSoftTime", &prefs);
// ViewSoftTime viewTime = ViewSoftTime("ViewSoftTime", &viewSettig, &ctrlTime);
#endif

#ifdef RESET_ENABLE
#define RESET_PIN       GPIO_NUM_33
ControllerSoftReset ctrlReset = ControllerSoftReset("CtrlSoftReset", RESET_PIN);
ComponentSoftReset cmpReset = ComponentSoftReset("cmpReset", &ctrlReset);
#endif

#ifdef PIR_ENABLE
#define PIR_PIN         GPIO_NUM_17
ControllerPIR crtlPIR = ControllerPIR("crtlPIR", PIR_PIN);
ComponentPIR cmpPIR = ComponentPIR("cmpPIR", &crtlPIR);
#endif

#if defined(IR_ENABLE) & defined(RADIO_ENABLE)
ComponentIrRemote cmpIrRemote = ComponentIrRemote("cmpIrRemote", &ctrlIrRemote, &ctrlRadio); 
#endif


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
#if defined(RADSENS_ENABLE) || defined(MHZ19_ENABLE)
    &viewRadsMHZ19,
#endif
};

#ifdef RADIO_ENABLE
void (ControllerRadio::*currentHandle)(int);
#endif

#ifdef ENCODER_ENABLE
void btnEncoderClick(Button2& b);
void btnEncoderDoubleClick(Button2& b);
void btnEncoderLongClick(Button2& b);
#endif
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
    // Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid.c_str(), pswd.c_str());
}

#ifdef MQTT_ENABLE
void connectToMqtt() {
    // Serial.println("Connecting to MQTT...");
    mqttClient.connect();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
    // Serial.println("Disconnected from MQTT.");
    if (WiFi.isConnected()) {
        xTimerStart(mqttReconnectTimer, 0);
    }
}
#endif

void WiFiEvent(WiFiEvent_t event) {
    // Serial.printf("[WiFi-event] event: %d\n", event);
    switch(event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            // Serial.println("\r\nWiFi connected");
            // Serial.print("IP address:");
            // Serial.println(WiFi.localIP());
            configTime(prefs.getInt("tz", 10800), 0, "ntp1.vniiftri.ru", "ntp2.vniiftri.ru");
#ifdef MQTT_ENABLE
            connectToMqtt();
#endif
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            // Serial.println("\r\nWiFi lost connection");
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

#ifdef ENCODER_ENABLE
#if !defined(ENCODER_FAKE)
    encoder.attachSingleEdge(ENCODER_PIN_A, ENCODER_PIN_B);
    btnEncoder.begin(ENCODER_BTN);
    if (btnEncoder.isPressedRaw()) {
#ifdef WIFI_ENABLE
        setSettings(prefs, tft, server);
#endif
    }
#endif
#endif
 
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
    ctrlTime.Start(xMutex);
#endif
#ifdef RADIO_ENABLE
    ctrlRadio.Start();
    ctrlAlarmClock.attachController(&ctrlRadio);
    ctrlAlarmClock.Start(2048);
#endif
#ifdef WEATHER_ENABLE
    ctrlWeather.Start(8192);
#endif
#ifdef BME280_ENABLE
    ctrlBme280.Start(xMutex);
#endif
#ifdef BUZZER_ENABLE
    ctrlBuzzer.Start();
#endif

#ifdef RADSENS_ENABLE
    ctrlRadSens.Start(xMutex);
#endif
#ifdef MHZ19_ENABLE
    ctrlMHZ19.Start();
#endif
#ifdef IR_ENABLE
    ctrlIrRemote.attachController(&ctrlRadio);
    ctrlIrRemote.Start();
#endif
#ifdef PIR_ENABLE
    crtlPIR.Start();
#endif
#ifdef RESET_ENABLE
    ctrlReset.Start();
#endif

    LOGN("Component - Start")
#if defined(IR_ENABLE)
    cmpIrRemote.Start(&ctrlIrRemote);
#endif
#ifdef PIR_ENABLE
    cmpPIR.Start(&crtlPIR);
#endif
#ifdef RESET_ENABLE
    cmpReset.Start(&ctrlReset);
#endif

    LOGN("View - Start")
    sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);
#ifdef TIME_ENABLE
    viewTime.Start(2048);
#endif
#ifdef RADIO_ENABLE
    viewRadio.Start();
#endif
#ifdef WEATHER_ENABLE
    viewWeather.Start(8192);
#endif
#ifdef BME280_ENABLE
    viewBme280.Start(2048);
#endif
#if defined(RADSENS_ENABLE) || defined(MHZ19_ENABLE)
    viewRadsMHZ19.Start(2048);
#endif
#ifdef RADIO_ENABLE
    currentHandle = &ControllerRadio::changeVolume;
#endif
#ifdef ENCODER_ENABLE
#if !defined(ENCODER_FAKE)
    btnEncoder.setClickHandler(btnEncoderClick);
    btnEncoder.setDoubleClickHandler(btnEncoderDoubleClick);
    btnEncoder.setLongClickTime(500);
    btnEncoder.setLongClickHandler(btnEncoderLongClick);  
#else
    pinMode(GPIO_NUM_35,  INPUT);
#endif
#endif

    setDisplayPage(prefs.getInt("page", 0));
}

void loop() {
#ifdef ENCODER_ENABLE
#if !defined(ENCODER_FAKE)
    btnEncoder.loop();
    int dir = encoder.getCount();
    encoder.setCount(0);
#else
    if (digitalRead(GPIO_NUM_35) == LOW) {
        setDisplayPageNext();
        delay(200);
    }
#endif
#else
    int dir =0;
#endif
#ifdef RADIO_ENABLE
    (&ctrlRadio->*currentHandle)(dir);
#endif
}

int index_song = 0;
const char* songs[] = {
"Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6",
"Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6",
"Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6",
"MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.",
"MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d",
"Pacman:d=4,o=5,b=112:32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32c6,32p,32c7,32p,32g6,32p,32e6,32p,32c7,32g6,16p,16e6,16p,32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32d#6,32e6,32f6,32p,32f6,32f#6,32g6,32p,32g6,32g#6,32a6,32p,32b.6",
"Terminator II:d=4,o=5,b=90:32d6,16e6,2f6,8e6,8c6,2f,16p,32d6,16e6,2f6,8e6,8c6,2a6,2g6",
"Toccata:d=4,o=5,b=160:16a4,16g4,1a4,16g4,16f4,16d4,16e4,2c#4,16p,d.4,2p,16a4,16g4,1a4,8e.4,8f.4,8c#.4,2d4",
"Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6",
"Tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a",
"AxelF:d=4,o=5,b=125:32p,8g,8p,16a#.,8p,16g,16p,16g,8c6,8g,8f,8g,8p,16d.6,8p,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g,p,ss,16f6,8d6,8c6,8a#,g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g",
"girl:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#",
"careaboutus:d=4,o=5,b=125:16f,16e,16f,16e,16f,16e,8d,16e,16d,16e,16d,16e,16d,16c,16d,d",
"Scatman:d=4,o=5,b=200:8b,16b,32p,8b,16b,32p,8b,2d6,16p,16c#.6,16p.,8d6,16p,16c#6,8b,16p,8f#,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8f#,2p,32p,2d6,16p,16c#6,8p,16d.6,16p.,16c#6,16a.,16p.,8e,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8b,16b,32p,8b,16b,32p,8b,2d6,16p,16c#.6,16p.,8d6,16p,16c#6,8b,16p,8f#,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8f#,2p,32p,2d6,16p,16c#6,8p,16d.6,16p.,16c#6,16a.,16p.,8e,2p.,16c#6,8p,16d.6,16p.,16c#6,16a,8p,8e,2p,32p,16f#.6,16p.,16b.,16p.",
"Smoke:d=4,o=5,b=112:c,d#,f.,c,d#,8f#,f,p,c,d#,f.,d#,c,2p,8p,c,d#,f.,c,d#,8f#,f,p,c,d#,f.,d#,c,p",
"countdown:d=4,o=5,b=125:p,8p,16b,16a,b,e,p,8p,16c6,16b,8c6,8b,a,p,8p,16c6,16b,c6,e,p,8p,16a,16g,8a,8g,8f#,8a,g.,16f#,16g,a.,16g,16a,8b,8a,8g,8f#,e,c6,2b.,16b,16c6,16b,16a,1b",
"VanessaMae:d=4,o=6,b=70:32c7,32b,16c7,32g,32p,32g,32p,32d#,32p,32d#,32p,32c,32p,32c,32p,32c7,32b,16c7,32g#,32p,32g#,32p,32f,32p,16f,32c,32p,32c,32p,32c7,32b,16c7,32g,32p,32g,32p,32d#,32p,32d#,32p,32c,32p,32c,32p,32g,32f,32d#,32d,32c,32d,32d#,32c,32d#,32f,16g,8p,16d7,32c7,32d7,32a#,32d7,32a,32d7,32g,32d7,32d7,32p,32d7,32p,32d7,32p,16d7,32c7,32d7,32a#,32d7,32a,32d7,32g,32d7,32d7,32p,32d7,32p,32d7,32p,32g,32f,32d#,32d,32c,32d,32d#,32c,32d#,32f,16c",
"Verve:d=4,o=5,b=180:e,g,e,f,d,2f,a#,f,2a#,a,f,2a,p,e,g,e,f,d,2f,a#,f,2a#,a,f,2a,p",
"Wannabe:d=4,o=5,b=125:16g,16g,16g,16g,8g,8a,8g,8e,8p,16c,16d,16c,8d,8d,8c,e,p,8g,8g,8g,8a,8g,8e,8p,c6,8c6,8b,8g,8a,16b,16a,g",
"Yaketysax:d=4,o=5,b=125:8d.,16e,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8a4,16a4,16a#4,16b4,16d,16e,16d,g,p,16d,16e,16d,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8d,16d,16d,16f#,16a,8f,d,p,16d,16e,16d,8g,16g,16g,8g,16g,16g,8g,8g,16e,8e.,8c,8c,8c,8c,16e,16g,16a,16g,16a#,8g,16a,16b,16a#,16b,16a,16b,8d6,16a,16b,16d6,8b,8g,8d,16e6,16b,16b,16d,8a,8g,g",
"StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6",
"StWars:d=4,o=5,b=180:8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6,p,8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6",
"Cantina:d=4,o=5,b=250:8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,a,8a,8g#,8a,g,8f#,8g,8f#,f.,8d.,16p,p.,8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,8a,8p,8g,8p,g.,8f#,8g,8p,8c6,a#,a,g",
"SWEnd:d=4,o=5,b=225:2c,1f,2g.,8g#,8a#,1g#,2c.,c,2f.,g,g#,c,8g#.,8c.,8c6,1a#.,2c,2f.,g,g#.,8f,c.6,8g#,1f6,2f,8g#.,8g.,8f,2c6,8c.6,8g#.,8f,2c,8c.,8c.,8c,2f,8f.,8f.,8f,2f",
};

void btnEncoderClick(Button2& b) {
#ifdef BUZZER_ENABLE
    ctrlBuzzer.Play(songs[index_song++]);
    if (index_song >= sizeof(songs)/sizeof(songs[0])) index_song = 0;
#endif
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
