#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <Preferences.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

Preferences prefs;
String ssid         = ""; // SSID WI-FI
String pswd         = "";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.printf("\r\n");
  Serial.printf("\r\n");
  
  delay(3000);
  
  prefs.begin("WebRadio");
  ssid = prefs.getString("ssid", ssid);
  pswd = prefs.getString("pswd", pswd);

  if(SPIFFS.begin(true)) {
    listDir("/", &Serial);
  }
  else {
    SPIFFS.format();
    Serial.printf("SPIFFS Formatting\r\n");
  }

  Serial.printf("Wi-Fi SSID: %s ", ssid.c_str());
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pswd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(500);
    yield();
  }
  Serial.printf("\r\nconnected!\r\nip: %s\r\n", WiFi.localIP().toString().c_str());

  configTime(prefs.getInt("tz", 10800), 0, "pool.ntp.org");

  server.on("/", HTTP_GET, pageIndex);
  server.onNotFound(page404);
  server.begin();  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void page404(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void pageIndex(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("text/plain");
  listDir("/", response);
  request->send(response);
  //request->send(200, "text/plain", "Hello, world");
}

void listDir(const char* dirname, Print* stream) {
  stream->printf("Listing directory: %s\r\n", dirname);

  File root = SPIFFS.open(dirname);
  if(!root) {
    stream->printf("- failed to open directory\r\n");
    return;
  }
  if(!root.isDirectory()) {
    stream->printf(" - not a directory\r\n");
    return;
  }

  File file = root.openNextFile();
  while(file) {
    if(file.isDirectory()) {
      stream->printf("  DIR : %s\r\n", file.name());
      listDir(file.name(), stream);
    } else {
      stream->printf("  FILE: %s\tSIZE: %d\r\n", file.name(), file.size());
    }
    file = root.openNextFile();
  }
}
