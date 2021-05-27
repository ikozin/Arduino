
String processorSearch(const String& var) {
  if (var == "band") {
    return String(radioGetChannel()/ 10);
  }
  if (var == "seekth") {
    return String((int)radioGetSeekTh());
  }
  if (var == "softblend") {
    return String((int)radioGetSoftBlend());
  }
  return String();
}

void pageSearchGet(AsyncWebServerRequest* request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("GET: Search\r\n");
  logRequest(request);
#endif

  request->send(SPIFFS, "/rda5807m.html", emptyString, false, processorSearch);
}

void pageSearchPost(AsyncWebServerRequest* request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("Post: Search\r\n");
  logRequest(request);
#endif
  if (request->hasParam("seek", true)) {
    uint16_t seekth = request->getParam("seekth", true)->value().toInt();
    uint16_t softblend = request->getParam("softblend", true)->value().toInt();
    int value = request->getParam("seek", true)->value().toInt();
    radioSeek(seekth, softblend, value > 0);
  }
  if (request->hasParam("set", true)) {
    uint16_t band = request->getParam("band", true)->value().toFloat() * 10;
    radioSetChannel(band);
  }
  return request->redirect("/rda5807m.html");
}
