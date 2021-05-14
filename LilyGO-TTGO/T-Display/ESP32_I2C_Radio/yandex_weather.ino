extern TFT_eSPI tft;

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

int32_t posX;

unsigned short imageData[8192];

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
    f.read((uint8_t*)imageData, len);
    f.close();
    tft.pushImage(x, y, size, size, imageData);
  }
}

uint16_t ColorToRGB565(const uint8_t r, const uint8_t g, const uint8_t b) {
  return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}

void updateWeather() {
  http.begin("https://export.yandex.ru/bar/reginfo.xml?region=213");
  int httpCode = http.GET();
  if (httpCode > 0) {
    debug_printf("\r\n[HTTP] GET, code: %d\r\n", httpCode);
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

      //weatherTemperature.concat(F("°"));
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
      //Serial.println(payload);
      Serial.print(F("Трафик:"));
      Serial.println(trafficLevel);
      Serial.print(F("Погода:"));
      Serial.println(weatherDescription);
      Serial.print(F("Url:"));
      Serial.println(weatherUrlIcon);
      Serial.print(F("Скорость ветра:"));
      Serial.println(weatherWindSpeed);
      Serial.print(F("Ветер:"));
      Serial.println(weatherWindType);
      Serial.print(F("Влажность:"));
      Serial.println(weatherDampness);
      Serial.print(F("Давление:"));
      Serial.println(weatherPressure);
      Serial.print(F("Температура:"));
      Serial.println(weatherTemperature);
      Serial.print(F("file icon:"));
      Serial.println(iconFileName);
      Serial.print(F("file wind:"));
      Serial.println(windFileName);
      Serial.println();
#endif
    }
  } else {
    debug_printf("\r\n[HTTP] GET, error: %d\r\n", httpCode);
  }
  http.end();

  tft.fillScreen(0x4C7D); //ColorToRGB565(0x4D, 0x8D, 0xEE)

  if (iconFileName.length()) drawImageFile(iconFileName.c_str(), 107, 0, iconSize);
  drawImageFile(windFileName.c_str(), 192, 8, 32);
  
  //weatherDescription = F("облачно с прояснениями, необльшой дождь");
  tft.loadFont(FONT_CALIBRI_32);
  tft.setTextColor(TFT_WHITE);
  posX = tft.textWidth(weatherDescription);
  posX = (posX < 240) ? (240 - posX) >> 1 : 0;
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
