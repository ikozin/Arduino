#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <LittleFS.h>

#include <Button2.h>
#include <ESP32Encoder.h>

#include "display.h"
#include "colors.h"
#include "logging.h"

#include "controller/storageAlarm.h"
#include "controller/storageRadio.h"

#include "controller/controller.h"
#include "controller/controllerAlarm.h"
#include "controller/controllerBme280.h"
#include "controller/controllerBuzzer.h"
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
ViewTime                viewTime("ViewTime", &sprite, &ctrlTime);
#endif

#ifdef RADIO_ENABLE
StorageRadio            storageRadio;
ControllerRadio         ctrlRadio("CtrlRadio", &prefs, &storageRadio);
ViewRadio               viewRadio("ViewRadio", &sprite, &ctrlRadio);
bool (ControllerRadio::*currentHandle)(int) = &ControllerRadio::changeVolume;
#endif

#ifdef BME280_ENABLE
ControllerBme280        ctrlBme280("CtrlBme280");
ViewBme280              viewBme280("ViewBme280", &sprite, &ctrlBme280);
#endif

#ifdef RADSENS_ENABLE
ControllerRadSens       ctrlRadSens("CtrlRadSens");
ViewRadSens             viewRadSens("ViewRadSens", &sprite, &ctrlRadSens);
#endif

#ifdef IR_ENABLE
#define IR_PIN          GPIO_NUM_13
ControllerIrRemote_CarMp3 ctrlIrRemote("ctrlIrRemote", IR_PIN);
#endif

#ifdef RESET_ENABLE
#define RESET_PIN       GPIO_NUM_33
ControllerGPIOInput_SoftReset   ctrlReset("ctrlReset", RESET_PIN);
#endif

View* viewList[] = {
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
    tft.fillScreen(COLOR_BLACK);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK);
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
    for (int i = 0; i < sizeof(ctrlList)/sizeof(ctrlList[0]); i++) {
        Controller* ctrl = ctrlList[i];
        if (!ctrl->Initialize()) fatalError(ctrl->GetName());
    }
    ctrlAlarm.Attach(&ctrlRadio, &ctrlBuzzer);
#ifdef IR_ENABLE
    ctrlIrRemote.Attach(&ctrlNavigator, &ctrlRadio);
#endif
    //ctrlNavigator.Attach(&ctrlBuzzer);
    btnEncoder.setClickHandler(btnEncoderClick);
    btnEncoder.setDoubleClickHandler(btnEncoderDoubleClick);
    btnEncoder.setLongClickTime(1000);
    btnEncoder.setLongClickHandler(btnEncoderLongClick);  

    uint64_t time = UINT64_MAX;
    for (int i = 0; i < sizeof(ctrlList)/sizeof(ctrlList[0]); i++) {
        ctrlList[i]->Update(time);
    }
    ctrlBuzzer.Play();
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

/*
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
    navigator.setDisplayPageNext();
}
*/