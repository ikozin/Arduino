extern char trafficLevel[];
extern char weatherType[];
extern char weatherIcon[];
extern char weatherWindSpeed[];
extern char weatherWindType[];
extern char weatherDampness[];
extern char weatherPressure[];
extern char weatherTemperature[];

const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML><html lang="ru">
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8">
<meta http-equiv="Refresh" content="3660">
<title>ESP32 TTGO T-Display</title>
</head>
<body>
<div><form method="post"><fieldset>
  <label for="station">Станция: </label>
  <select id="station" name="station">
%STATION%  </select>
  <label for="volume">Громкость: </label>
  <input type="range" id="volume" name="volume" min="0" max="15" value="%VOLUME%"/>
  <input type="submit" />
</fieldset></form></div>
<div>
<div>%W_TEMP%</div>
<div><img src="%W_ICON%"/></div>
<div>%W_TYPE%</div>
<div>%W_WIND%</div>
<div>%W_WIND_SPEED%</div>
</div>
</body>)rawliteral";

String processorIndex(const String& var) {
  if (var == "VOLUME")
    return String(currentVolume);
  if (var == "STATION") {
    String text = String();
    text.reserve(4096);
    for (int i = 0; i < listSize; i++) {
      text.concat("<option ");
      if (currentIndex == i) text.concat("selected ");
      text.concat("value=\"");
      text.concat(i);
      text.concat("\">");
      text.concat(radioList[i].name);
      text.concat("</option>\r\n");
    }
    return text;
  }
  if (var == "W_TEMP") {
    return String(weatherTemperature);
  }
  if (var == "W_ICON") {
    return String(weatherIcon);
  }
  if (var == "W_TYPE") {
    return String(weatherType);
  }
  if (var == "W_WIND") {
    return String(weatherWindType);
  }
  if (var == "W_WIND_SPEED") {
    return String(weatherWindSpeed);
  }
  return String();
}

void page404(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void pageIndexGet(AsyncWebServerRequest *request) {
  //AsyncResponseStream *response = request->beginResponseStream("text/plain");
  //listDir("/", response);
  //request->send(response);
  //request->send(200, "text/plain", "Hello, world");
  request->send_P(200, "text/html", index_html, processorIndex);
}

void pageIndexPost(AsyncWebServerRequest *request) {
  if (request->hasParam("station", true)) {
    uint8_t index = request->getParam("station", true)->value().toInt();
    if (index < listSize && currentIndex != index) {
      currentIndex = index;
      radioSetRadio(currentIndex);
    }
  }
  if (request->hasParam("volume", true)) {
    uint8_t volume = request->getParam("volume", true)->value().toInt();
    if (volume <= 15 && currentVolume != volume) {
      currentVolume = volume;
      radioSetVolume(currentVolume);
    }
  }
  request->send_P(200, "text/html", index_html, processorIndex);
}
