
String alert_ttt = String(R"rawliteral(<li class='list-group-item'>
        <form method='post'>
          <div class='row'>
            <div class='col-auto'>
              <input type='time' class='form-control' name='time' value='%time%'>
            </div>            
            <div class='col-auto'>
              <div class='form-check'>
                <input class='form-check-input' type='checkbox' name='day1'%day1%/>
                <label class='form-check-label' for='day1'>Понедельник</label>
              </div>            
              <div class='form-check'>
                <input class='form-check-input' type='checkbox' name='day2'%day2%/>
                <label class='form-check-label' for='day2'>Вторник</label>
              </div>            
              <div class='form-check'>
                <input class='form-check-input' type='checkbox' name='day3'%day3%/>
                <label class='form-check-label' for='day3'>Среда</label>
              </div>            
              <div class='form-check'>
                <input class='form-check-input' type='checkbox' name='day4'%day4%/>
                <label class='form-check-label' for='day4'>Четверг</label>
              </div>            
              <div class='form-check'>
                <input class='form-check-input' type='checkbox' name='day5'%day5%/>
                <label class='form-check-label' for='day5'>Пятница</label>
              </div>            
              <div class="form-check">
                <input class='form-check-input' type='checkbox' name='day6'%day6%/>
                <label class='form-check-label' for='day6'>Суббота</label>
              </div>            
              <div class='form-check'>
                <input class='form-check-input' type='checkbox' name='day7'%day7%/>
                <label class='form-check-label' for='day7'>Восресение</label>
              </div>            
            </div>            
            <div class='col-auto'>
              <button type='submit' class='btn btn-primary' name='edit' value='%index%'>Изменить</button>
              <button type='submit' class='btn btn-primary' name='del' value='%index%'>Удалить</button>
            </div>
          </div>
        </form>
      </li>)rawliteral");



String alert_html = String(R"rawliteral(
<!DOCTYPE HTML>
<html lang='ru'>
<head>
  <meta http-equiv='content-type' content='text/html; charset=utf-8'>
  <meta name='viewport' content='width=device-width, initial-scale=1'>
  <title>ESP32 TTGO T-Display</title>
  <link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css'/>
  <style>
  </style>
</head>
<body>
  <br/>
  <div class='container'>
    <div class='row'>
      <form method="post">
          <button type='submit' class='btn btn-primary' name='add'>Добавить новый</button>
      </form>
    </div>
    <br/>
    <ul class='list-group'>
    %list%
    </ul>
    <br/>
  </div>
</body>
</html>
)rawliteral");


String processorAlarm(const String& var) {
  if (var == "list") {
    String text = String();
    for (int i = 0; i < settingsCount; i++) {
      text.concat("\r\n<li class=\"list-group-item\">");
      text.concat("\r\n<button type=\"submit\" class=\"btn btn-primary\" name=\"edit\" value=\"");
      text.concat(i);
      text.concat("\">Изменить</button>");
      text.concat("\r\n<button type=\"submit\" class=\"btn btn-primary\" name=\"del\" value=\"");
      text.concat(i);
      text.concat("\">Удалить</button>");
      text.concat("\r\n</li>");      
    }
    text.concat("\r\n");      
    return text;
  }
  return emptyString;
}

void pageAlarmGet(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("GET: Alarm\r\n");
  logRequest(request);
#endif

  String alert = String(alert_ttt);
  String list = String();
  String page = String(alert_html);
  alert.reserve(2048);
  list.reserve(16384);
  page.reserve(16384);
  for (int i = 0; i < settingsCount; i++) {
    alarm_t setting = settings[i];
    String alert = String(alert_ttt);
    
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

    list.concat(alert);
  }
  page.replace("%list%", list);
  //debug_printf(alert_html.c_str());
  //request->send(SPIFFS, "/alarm.html", emptyString, false, processorAlarm);
  request->send(200, "text/html", page);
}

void parseTime(alarm_t& setting, AsyncWebServerRequest *request) {
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

void pageAlarmPost(AsyncWebServerRequest *request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("Post: Alarm\r\n");
  logRequest(request);
#endif
  if (request->hasParam("add", true)) {
    if (settingsCount >= MaxSettingsCount) return request->redirect("/");

    // Вставляем в начало
    for (uint16_t i = MaxSettingsCount - 1; i > 0; i--) settings[i].value = settings[i - 1].value;
    settings[0].value = 0x0800007F;
    settingsCount++;
    return request->redirect("/alarm.html");
  }
  if (request->hasParam("del", true)) {
    uint16_t index = request->getParam("del", true)->value().toInt();
    if (settingsCount == 0 || index >= settingsCount)  return request->redirect("/");

    for (uint16_t i = index; i < MaxSettingsCount - 1; i++) settings[i].value = settings[i + 1].value;
    settings[MaxSettingsCount - 1].value = 0;
    settingsCount--;
    return request->redirect("/alarm.html");
  }
  if (request->hasParam("edit", true)) {
    uint16_t index = request->getParam("edit", true)->value().toInt();
    if (index >= settingsCount)  return request->redirect("/alarm.html");

    alarm_t& setting = settings[index];
    parseTime(setting, request);
    setting.Sunday     = request->hasParam("day7", true);
    setting.Saturday   = request->hasParam("day6", true);
    setting.Friday     = request->hasParam("day5", true);
    setting.Thursday   = request->hasParam("day4", true);
    setting.Wednesday  = request->hasParam("day3", true);
    setting.Tuesday    = request->hasParam("day2", true);
    setting.Monday     = request->hasParam("day1", true);

    return request->redirect("/alarm.html");
  }
  return request->redirect("/");
}
