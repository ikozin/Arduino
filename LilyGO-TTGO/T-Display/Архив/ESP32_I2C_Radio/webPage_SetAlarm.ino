
String processorSetAlarm(const String& var) {
  return emptyString;
}

void pageSetAlarmGet(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("GET: SetAlarm\r\n");
  logRequest(request);
#endif
  if (!request->hasParam("index")) return page400(request);
  uint16_t index = request->getParam("index")->value().toInt();
  if (settingsCount == 0 || index >= settingsCount)  return page400(request);
  alarm_t setting = settings[index];

  String station = String();
  String html = String();
  if (!station.reserve(4096)) return page507(request);
  if (!html.reserve(8192)) return page507(request);
  loadFile("/html/setalarm.html", html);

  html.replace("%index%", String(index));
  sprintf((char *)fileData, "%02d:%02d", setting.Hour, setting.Minute);
  String time = (char *)fileData;
  html.replace("%time%", time);
  html.replace("%day7%", setting.Sunday     ? checkedString : emptyString);
  html.replace("%day6%", setting.Saturday   ? checkedString : emptyString);
  html.replace("%day5%", setting.Friday     ? checkedString : emptyString);
  html.replace("%day4%", setting.Thursday   ? checkedString : emptyString);
  html.replace("%day3%", setting.Wednesday  ? checkedString : emptyString);
  html.replace("%day2%", setting.Tuesday    ? checkedString : emptyString);
  html.replace("%day1%", setting.Monday     ? checkedString : emptyString);
  
  const char* selected = emptyString.c_str();
  if (setting.Index == -1) selected = selectedString.c_str();
  sprintf((char *)fileData, "\r\n<option%s value=\"%d\">%s</option>", selected, -1, "--- Не выбрано ---");
  station = (char *)fileData;
  for (int i = 0; i < listSize; i++) {
    selected = emptyString.c_str();
    if (setting.Index == i) selected = selectedString.c_str();
    sprintf((char *)fileData, "\r\n<option%s value=\"%d\">%s</option>", selected, i, radioList[i].name);
    station += (char *)fileData;
  }
  station += "\r\n";
  html.replace("%station%", station);
  html.replace("%volume%", String(setting.Volume));
  html.replace("%mute%", setting.IsMute ? checkedString : emptyString);

  //debug_printf("station capacity = %d\r\n", station.capacity());  // WString.h - capacity сделать public
  //debug_printf("html capacity = %d\r\n", html.capacity());        // WString.h - capacity сделать public

  request->send(200, "text/html", html);
}

void pageSetAlarmPost(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("Post: SetAlarm\r\n");
  logRequest(request);
#endif

  if (!request->hasParam("edit", true)) return page400(request);
  uint16_t index = request->getParam("edit", true)->value().toInt();
  if (index >= settingsCount)  return page400(request);

  alarm_t& setting = settings[index];
  parseTime(setting, request);
  setting.Sunday     = request->hasParam("day7", true);
  setting.Saturday   = request->hasParam("day6", true);
  setting.Friday     = request->hasParam("day5", true);
  setting.Thursday   = request->hasParam("day4", true);
  setting.Wednesday  = request->hasParam("day3", true);
  setting.Tuesday    = request->hasParam("day2", true);
  setting.Monday     = request->hasParam("day1", true);
  setting.IsMute     = request->hasParam("mute", true);
  setting.Volume = request->getParam("volume", true)->value().toInt();
  setting.Index = request->getParam("station", true)->value().toInt();
  if (!(setting.value & WEEK_MASK)) setting.value |= WEEK_MASK;

  debug_printf("alarm[%d]=0x%llX\r\n", index, setting.value);
  setTimers(settingsCount);
  return request->redirect("/alarm.html");
}
