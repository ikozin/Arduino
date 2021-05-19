
String processorIndex(const String& var) {
  if (var == "STATION") {
    String text = String();
    text.reserve(4096);
    text.concat("\r\n");
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
  if (var == "MUTE" && isMute)  return checkedString;
  if (var == "VOLUME")  return String(currentVolume);
  if (var == "W_TEMP")  return weatherTemperature;
  if (var == "W_ICON")  return weatherUrlIcon;
  if (var == "W_TYPE")  return weatherDescription;
  if (var == "W_WIND")  return weatherWindType;
  if (var == "W_WIND_SPEED")  return weatherWindSpeed;
  if (var == "W_DAMPNESS")  return weatherDampness;
  if (var == "W_PRESSURE")  return weatherPressure;

  return emptyString;
}

void pageIndexGet(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("GET: Index\r\n");
  logRequest(request);
#endif

  request->send(SPIFFS, "/index.html", emptyString, false, processorIndex);
}

void pageIndexPost(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("Post: Index\r\n");
  logRequest(request);
#endif

  handleMute(request->hasParam("mute", true));      
  if (request->hasParam("station", true)) handleSetRadio(request->getParam("station", true)->value().toInt());
  if (request->hasParam("volume", true))  handleSetVolume(request->getParam("volume", true)->value().toInt());

  request->redirect("/");
}
