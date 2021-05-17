//https://github.com/me-no-dev/ESPAsyncWebServer#body-data-handling

String processorIndex(const String& var) {
  if (var == "VOLUME")
    return String(currentVolume);
  if (var == "STATION") {
    String text = String();
    text.reserve(4096);
    text.concat(F("\r\n"));
    for (int i = 0; i < listSize; i++) {
      text.concat(F("<option "));
      if (currentIndex == i) text.concat(F("selected "));
      text.concat(F("value=\""));
      text.concat(i);
      text.concat(F("\">"));
      text.concat(radioList[i].name);
      text.concat(F("</option>\r\n"));
    }
    return text;
  }
  if (var == "MUTE") {
    String text = String();
    if (isMute) {
      text.concat(F(" checked"));
    }
    return text;    
  }
  if (var == "W_TEMP") {
    return weatherTemperature;
  }
  if (var == "W_ICON") {
    return weatherUrlIcon;
  }
  if (var == "W_TYPE") {
    return weatherDescription;
  }
  if (var == "W_WIND") {
    return weatherWindType;
  }
  if (var == "W_WIND_SPEED") {
    return weatherWindSpeed;
  }
  if (var == "W_DAMPNESS") {
    return weatherDampness;
  }
  if (var == "W_PRESSURE") {
    return weatherPressure;
  }
  return String();
}

void page404(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void pageIndexGet(AsyncWebServerRequest *request) {
  debug_printf("GET: Index\r\n");
  request->send(SPIFFS, "/index.html", String(), false, processorIndex);
}

void pageIndexPost(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("POST: Index\r\n");
  //List all parameters
  int params = request->params();
  for(int i=0;i<params;i++){
    AsyncWebParameter* p = request->getParam(i);
    if(p->isFile()){ //p->isPost() is also true
      debug_printf("FILE[%s]: %s, size: %u\r\n", p->name().c_str(), p->value().c_str(), p->size());
    } else if(p->isPost()){
      debug_printf("POST[%s]: %s\r\n", p->name().c_str(), p->value().c_str());
    } else {
      debug_printf("GET[%s]: %s\r\n", p->name().c_str(), p->value().c_str());
    }
  }
  debug_printf("\r\n");
#endif

  bool value = request->hasParam("mute", true);
  if (isMute != value) {
    handleMute(value);      
  }
  if (request->hasParam("station", true)) {
    uint8_t index = request->getParam("station", true)->value().toInt();
    if (index < listSize && currentIndex != index) {
      handleSetRadio(index);
    }
  }
  if (request->hasParam("volume", true)) {
    uint8_t volume = request->getParam("volume", true)->value().toInt();
    if (volume <= 15 && currentVolume != volume) {
      handleSetVolume(volume);
    }
  }
  request->redirect("/");
}
