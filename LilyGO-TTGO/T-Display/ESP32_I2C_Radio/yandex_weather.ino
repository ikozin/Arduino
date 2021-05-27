
extern TFT_eSPI tft;

#define UPDATE_WEATHER_TIME (20 * 60000 / portTICK_RATE_MS)
//#define UPDATE_WEATHER_TIME (60000 / portTICK_RATE_MS)

HTTPClient http;
const int32_t iconSize = 64;

char _trafficPattern[]     = "<info|<traffic|<region|<level";
char _typePattern[]        = "<weather|<day_part|<weather_type";
char _iconPattern[]        = "<image-v3";
char _windSpeedPattern[]   = "<wind_speed";
char _windTypePattern[]    = "<wind_direction";
char _dampnessPattern[]    = "<dampness";
char _pressurePattern[]    = "<pressure";
char _temperaturePattern[] = "<temperature";
char _windPattern[]        = "<info|<weather|<day_part|<wind_direction|id=";

// Возврат: указатель на последний обработанный символ, мелкая оптимизация,
// чтобы каждый раз не начинать с начала,
// в связи с этим ВАЖЕН ПОРЯДОК ПОИСКА ЗНАЧЕНИЙ.
char* getMatch(const char* text, const char* pattern, String& value, const char first, const char last) {
  if (text == NULL ) return NULL;
  char* delimeter = strchr(pattern, '|');
  if (delimeter == NULL) {
    char* begin = strstr(text, pattern);
    if (begin == NULL) return NULL;
    begin += strlen(pattern);
    while (*begin++ != first);
    char* end = strchr(begin, last);
    *end = '\0';
    value = begin;
    *end = last;
    return end + 1;
  }
  *delimeter = '\0';
  char* begin = strstr(text, pattern);
  if (begin == NULL) {
    *delimeter = '|';
    return NULL;
  }
  begin += strlen(pattern);
  *delimeter++ = '|';
  return getMatch(begin, delimeter, value, first, last);
}

void drawImageFile(const char* fileName, const int32_t x, const int32_t y, const int32_t size) {
  File f = SPIFFS.open(fileName);
  if (f) {
    size_t len = f.size();
    if (len <= sizeof(fileData)) {
      f.read((uint8_t*)fileData, len);
      tft.pushImage(x, y, size, size, fileData);
    }
    f.close();
  }
}
/*
uint16_t ColorToRGB565(const uint8_t r, const uint8_t g, const uint8_t b) {
  return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}
*/
void weatherHandler(void* parameter) {
  for (;;) {
    debug_printf("\r\nYandex Weather Core = %d\r\n", xPortGetCoreID());
    http.begin("https://export.yandex.ru/bar/reginfo.xml?region=213");
    int httpCode = http.GET();
    if (httpCode > 0) {
      debug_printf("[HTTP] GET, code: %d\r\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        char* pstr = payload.begin();
        pstr = getMatch(pstr, _trafficPattern, trafficLevel, '>', '<');
        pstr = getMatch(pstr, _typePattern, weatherDescription, '>', '<');
        pstr = getMatch(pstr, _iconPattern, weatherUrlIcon, '>', '<');
        pstr = getMatch(pstr, _windSpeedPattern, weatherWindSpeed, '>', '<');
        pstr = getMatch(pstr, _windTypePattern, weatherWindType, '>', '<');
        pstr = getMatch(pstr, _dampnessPattern, weatherDampness, '>', '<');
        pstr = getMatch(pstr, _pressurePattern, weatherPressure, '>', '<');
        pstr = getMatch(pstr, _temperaturePattern, weatherTemperature, '>', '<');
        getMatch(payload.begin(), _windPattern, windFileName, '"', '"');
  
        if (!windFileName.isEmpty())
          windFileName = "/" + windFileName;
        iconFileName = strrchr(weatherUrlIcon.c_str(), '/');
  
        float windSpeed = weatherWindSpeed.toFloat();
        if (windSpeed > 3.0 && windSpeed < 10.0)
          windFileName.concat(F("2"));
        else if (windSpeed >= 10)
          windFileName.concat(F("3"));
        windFileName.concat(F(".png"));
        
#if defined(DEBUG_CONSOLE)
        debug_printf("Yandex Weather Core = %d\r\n", xPortGetCoreID());
        //Serial.println(payload);
        debug_printf("Трафик:        %s\r\n" ,trafficLevel.c_str());
        debug_printf("Погода:        %s\r\n" ,weatherDescription.c_str());
        debug_printf("Url:           %s\r\n" ,weatherUrlIcon.c_str());
        debug_printf("Скорость ветра:%s\r\n" ,weatherWindSpeed.c_str());
        debug_printf("Ветер:         %s\r\n" ,weatherWindType.c_str());
        debug_printf("Влажность:     %s\r\n" ,weatherDampness.c_str());
        debug_printf("Давление:      %s\r\n" ,weatherPressure.c_str());
        debug_printf("Температура:   %s\r\n" ,weatherTemperature.c_str());
        debug_printf("file icon:     %s\r\n" ,iconFileName.c_str());
        debug_printf("file wind:     %s\r\n" ,windFileName.c_str());
        debug_printf("\r\n");
#endif
      }
    } else {
      debug_printf("\r\n[HTTP] GET, error: %d\r\n", httpCode);
    }
    http.end();
    xSemaphoreGive(displayWeatherEvent);
    vTaskDelay(UPDATE_WEATHER_TIME);
  }
}

void displayWeather() {
  debug_printf("DisplayWeather Core = %d\r\n", xPortGetCoreID());
  tft.fillScreen(0x4C7D); //ColorToRGB565(0x4D, 0x8D, 0xEE)
  tft.setTextDatum(TL_DATUM);

  drawImageFile(iconFileName.c_str(), 107, 0, iconSize);
  drawImageFile(windFileName.c_str(), 192, 8, 32);
  
  //weatherDescription = F("облачно с прояснениями, необльшой дождь");
  tft.loadFont(FONT_CALIBRI_32);
  tft.setTextColor(TFT_WHITE);
  int32_t posX = tft.textWidth(weatherDescription);
  posX = (posX < 240) ? (240 - posX) >> 1 : 0;
  tft.setTextDatum(TL_DATUM);
  tft.drawString(weatherDescription, posX + 2, 64);
  tft.unloadFont();

  // Для шрифта Colibri56
  // Ширина: для срок от -40° до +40° максимальная = 101
  // Высота: 48
  tft.loadFont(FONT_CALIBRI_56);
  tft.setTextColor(TFT_WHITE);
  posX = ((int32_t)101 - tft.textWidth(weatherTemperature)) >> 1;
  tft.drawString(weatherTemperature, posX + 2, 10);
  tft.unloadFont();
}
