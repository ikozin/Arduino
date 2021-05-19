//https://github.com/me-no-dev/ESPAsyncWebServer#body-data-handling

#if defined(DEBUG_CONSOLE)
void logRequest(AsyncWebServerRequest *request) {
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
}
#endif

void page404(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String checkedString = String(" checked");
/*
void pageSetAlarmGet(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("GET: SetAlarm\r\n");
  logRequest(request);
#endif
  if (!request->hasParam("index"))  return page404(request);
  uint16_t index = request->getParam("index")->value().toInt();
  if (index >= settingsCount) return page404(request);
  alarm_t setting = settings[index];
  
  File f = SPIFFS.open("/setalarm.html");
  if (!f) return page404(request);
  size_t total = f.read((uint8_t*)fileData, sizeof(fileData));
  f.close();
  if (total == sizeof(fileData))  return page404(request);
  ((uint8_t*)fileData)[total] = '\0';

  String page = String();
  page.reserve(8192);
  page = (char*)fileData;
  page.replace("%index%", String(index));
  sprintf((char *)fileData, "%02d:%02d", setting.Hour, setting.Minute);
  String time = (char *)fileData;
  page.replace("%time%", time);
  page.replace("%day7%", setting.Sunday     ? checkedString: emptyString);
  page.replace("%day6%", setting.Saturday   ? checkedString: emptyString);
  page.replace("%day5%", setting.Friday     ? checkedString: emptyString);
  page.replace("%day4%", setting.Thursday   ? checkedString: emptyString);
  page.replace("%day3%", setting.Wednesday  ? checkedString: emptyString);
  page.replace("%day2%", setting.Tuesday    ? checkedString: emptyString);
  page.replace("%day1%", setting.Monday     ? checkedString: emptyString);
  
  request->send(200, "text/html", page);
}

void pageSetAlarmPost(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("Post: SetAlarm\r\n");
  logRequest(request);
#endif
  if (!request->hasParam("index", true))  return page404(request);
  uint16_t index = request->getParam("index", true)->value().toInt();
  if (index >= settingsCount)  return page404(request);

  alarm_t& setting = settings[index];

  if (request->hasParam("time", true)) {
    String text = request->getParam("time", true)->value();
    setting.Hour = text.toInt();
    char* p;
    for (p = text.begin(); *p != ':'; p++);
    setting.Minute = atol(++p);
    if (setting.Minute > 59) setting.Minute = 0;
    if (setting.Hour > 23)   setting.Hour = 8;    
  }
  else {
    setting.Minute = 0;
    setting.Hour = 8;
  }
  setting.Sunday     = request->hasParam("day7", true);
  setting.Saturday   = request->hasParam("day6", true);
  setting.Friday     = request->hasParam("day5", true);
  setting.Thursday   = request->hasParam("day4", true);
  setting.Wednesday  = request->hasParam("day3", true);
  setting.Tuesday    = request->hasParam("day2", true);
  setting.Monday     = request->hasParam("day1", true);

  request->redirect("/");
}
*/
