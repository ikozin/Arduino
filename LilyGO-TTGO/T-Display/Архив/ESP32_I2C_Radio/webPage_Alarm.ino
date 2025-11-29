
void pageAlarmGet(AsyncWebServerRequest* request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("GET: Alarm\r\n");
  logRequest(request);
#endif
  
  String templ = String();
  String alert = String();
  String list = String();
  String html = String();
  if (!templ.reserve(4096)) return page507(request);
  if (!alert.reserve(4096)) return page507(request);
  if (!list.reserve(16384)) return page507(request);
  if (!html.reserve(16384)) return page507(request);
  loadFile("/html/alarm.ttt", templ);
  loadFile("/html/alarm.html", html);
  if (templ.isEmpty()) return request->send(500, "text/plain", "File \"/alarm.ttt\" not found or too large");
  if (html.isEmpty()) return request->send(500, "text/plain", "File \"/alarm.html\" not found or too large");

  list = "\r\n";
  for (int i = 0; i < settingsCount; i++) {
    alert.concat(templ);

    alarm_t setting = settings[i];
    alert.replace("%index%", String(i));
    sprintf((char *)fileData, "%02d:%02d", setting.Hour, setting.Minute);
    String time = (char *)fileData;
    alert.replace("%time%", time);
    alert.replace("%day7%", setting.Sunday     ? checkedString: emptyString);
    alert.replace("%day6%", setting.Saturday   ? checkedString: emptyString);
    alert.replace("%day5%", setting.Friday     ? checkedString: emptyString);
    alert.replace("%day4%", setting.Thursday   ? checkedString: emptyString);
    alert.replace("%day3%", setting.Wednesday  ? checkedString: emptyString);
    alert.replace("%day2%", setting.Tuesday    ? checkedString: emptyString);
    alert.replace("%day1%", setting.Monday     ? checkedString: emptyString);
    alert.replace("%station%", (setting.Index == -1) ? "--- Не выбрано ---": radioList[setting.Index].name);
    alert.replace("%volume%", String(setting.Volume));
    alert.replace("%mute%", setting.IsMute     ? checkedString: emptyString);
    list.concat(alert);
    alert.clear();
  }
  html.replace("%list%", list);

  //debug_printf("templ capacity = %d\r\n", templ.capacity());  // WString.h - capacity сделать public
  //debug_printf("alert capacity = %d\r\n", alert.capacity());  // WString.h - capacity сделать public
  //debug_printf("list capacity = %d\r\n", list.capacity());    // WString.h - capacity сделать public
  //debug_printf("html capacity = %d\r\n", html.capacity());    // WString.h - capacity сделать public

  request->send(200, "text/html", html);
}

void parseTime(alarm_t& setting, AsyncWebServerRequest* request) {
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
}

void pageAlarmPost(AsyncWebServerRequest* request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("Post: Alarm\r\n");
  logRequest(request);
#endif

  // INSERT
  if (request->hasParam("add", true)) {
    if (settingsCount >= MaxSettingsCount) return page507(request);
    // Вставляем в начало
    for (uint16_t i = MaxSettingsCount - 1; i > 0; i--) settings[i].value = settings[i - 1].value;
    settings[0].value = 0xFFFFFFFF0800007F;
    settingsCount++;
    setTimers(settingsCount);
    return request->redirect("/setalarm.html?index=0");
  }

  // DELETE
  if (request->hasParam("del", true)) {
    uint16_t index = request->getParam("del", true)->value().toInt();
    if (settingsCount == 0 || index >= settingsCount)  return page400(request);
    // Сдвигаем на место удаленного
    for (uint16_t i = index; i < MaxSettingsCount - 1; i++) settings[i].value = settings[i + 1].value;
    settings[MaxSettingsCount - 1].value = 0;
    settingsCount--;
    setTimers(settingsCount);
    return request->redirect("/alarm.html");
  }
  return request->redirect("/");
}
