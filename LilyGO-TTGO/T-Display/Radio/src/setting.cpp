#include "setting.h"
#include "main.h"
#include "controllerAlarmClock.h"

#define SSID "ESP32-Radio"
#define PASSPHRASE  "12345678"

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void notEnoughMemory(AsyncWebServerRequest* request) {
  request->send(507, "text/plain", "Not enough memory");
}

String processorSetting(const String& var) {
    if (var == "SSID")
        return prefs.getString("ssid", "");
    if (var == "PSWD")
        return prefs.getString("pswd", "");
    if (var == "MQTT")
        return prefs.getString("mqtt", "");
    if (var == "TZ")
        return String(prefs.getInt("tz", 10800));
    if (var == "VOLUME")
        return String(prefs.getInt("volume", 2));
    if (var == "MUTE" && prefs.getBool("mute", false))
        return String("checked"); 
    if (var == "STATION") {
        int station = prefs.getInt("station", 0);
        String text = String();
        if (text.reserve(4096)) {
            for (int i = 0; i < ctrlRadioStorage.length(); i++) {
                text.concat("<option ");
                if (station == i) text.concat("selected ");
                text.concat("value='");
                text.concat(i);
                text.concat("'>");
                text.concat(ctrlRadioStorage.getItem(i)->name);
                text.concat("</option>\r\n");
            }
            return text;
        }
    }
    return String();
}

void handlerGetSetting(AsyncWebServerRequest *request) {
    Serial.println("handlerGetSetting");
    request->send(SPIFFS, "/html/setting.html", "text/html", false, processorSetting);
}

void handlerPostSetting(AsyncWebServerRequest *request) {
    Serial.println("handlerPostSetting");

    if (request->hasParam("ssid", true)) {
        Serial.print("ssid=");
        Serial.println(request->getParam("ssid", true)->value());
        prefs.putString("ssid", request->getParam("ssid", true)->value());
    }
    if (request->hasParam("pswd", true)) {
        Serial.print("pswd=");
        Serial.println(request->getParam("pswd", true)->value());
        prefs.putString("pswd", request->getParam("pswd", true)->value());
    }
    if (request->hasParam("mqtt", true)) {
        Serial.print("mqtt=");
        Serial.println(request->getParam("mqtt", true)->value());
        prefs.putString("mqtt", request->getParam("mqtt", true)->value());
    }
    if (request->hasParam("tz", true)) {
        Serial.print("tz=");
        Serial.println(request->getParam("tz", true)->value().toInt());
        prefs.putInt("tz", request->getParam("tz", true)->value().toInt());
    }
    if (request->hasParam("station", true)) {
        Serial.print("station=");
        Serial.println(request->getParam("station", true)->value().toInt());
        prefs.putInt("station", request->getParam("station", true)->value().toInt());
    }
    if (request->hasParam("volume", true)) {
        Serial.print("volume=");
        Serial.println(request->getParam("volume", true)->value().toInt());
        prefs.putInt("volume", request->getParam("volume", true)->value().toInt());
    }
    Serial.print("mute=");
    Serial.println(request->hasParam("mute", true));
    prefs.putBool("mute", request->hasParam("mute", true));

    request->redirect("/");
}

void handleGetRadioFile(AsyncWebServerRequest *request) {
    Serial.println("handleGetRadioFile");
    request->send(SPIFFS, FS_RADIOLIST_FILE, String(), true);
}

void handleGetAlarmFile(AsyncWebServerRequest *request) {
    Serial.println("handleGetAlarmFile");
    request->send(SPIFFS, FS_ALARMLIST_FILE, String(), true);
}

void handlePostUpload(AsyncWebServerRequest *request) {
    Serial.println("handlePostUpload");
    request->send(200);
}

void handleUploadRadioFile(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if(!index){
        ctrlRadioStorage.clear();
        Serial.printf("UploadStart: %s\n", filename.c_str());
        request->_tempFile = SPIFFS.open(FS_RADIOLIST_FILE, FILE_WRITE, true);
    }
    for(size_t i=0; i<len; i++){
        Serial.write(data[i]);
    }
    request->_tempFile.write(data, len);
    if(final){
        Serial.printf("\nUploadEnd: %s, %u B\n", filename.c_str(), index+len);
        request->_tempFile.close();
        ctrlRadioStorage.load();
    }
}

void handleUploadAlarmFile(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if(!index){
        ctrlRadioStorage.clear();
        Serial.printf("UploadStart: %s\n", filename.c_str());
        request->_tempFile = SPIFFS.open(FS_ALARMLIST_FILE, FILE_WRITE, true);
    }
    for(size_t i=0; i<len; i++){
        Serial.write(data[i]);
    }
    request->_tempFile.write(data, len);
    if(final){
        Serial.printf("\nUploadEnd: %s, %u B\n", filename.c_str(), index+len);
        request->_tempFile.close();
        ctrlRadioStorage.load();
    }
}

void setSettings(Preferences& prefs, TFT_eSPI& tft, AsyncWebServer& server) {
    WiFi.softAP(SSID, PASSPHRASE);
    IPAddress IP = WiFi.softAPIP();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(SSID, TFT_HEIGHT >> 1, (TFT_WIDTH >> 1) - 40);
    tft.drawString(IP.toString(), TFT_HEIGHT >> 1, (TFT_WIDTH >> 1));
    tft.drawString(PASSPHRASE, TFT_HEIGHT >> 1, (TFT_WIDTH >> 1) + 40);

    server.serveStatic("/bootstrap.css", SPIFFS, "/html/bootstrap.css");
    server.on("/", HTTP_GET, handlerGetSetting);
    server.on("/", HTTP_POST, handlerPostSetting);
    server.on("/upload_radio", HTTP_POST, handlePostUpload, handleUploadRadioFile);
    server.on("/upload_alarm", HTTP_POST, handlePostUpload, handleUploadAlarmFile);
   
    server.on(FS_RADIOLIST_FILE, HTTP_GET, handleGetRadioFile);
    server.on(FS_ALARMLIST_FILE, HTTP_GET, handleGetAlarmFile);
    

    server.onNotFound(notFound);
    server.begin();
    yield();

    while (true) {
        delay(1000);
        yield();
    }       
}
