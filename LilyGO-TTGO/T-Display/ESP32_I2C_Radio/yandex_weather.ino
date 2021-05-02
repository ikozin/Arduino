extern TFT_eSPI tft;

HTTPClient _http;
const int32_t iconSize = 64;

char _typePattern[]        = "<info|<weather|<day_part|<weather_type";
char _iconPattern[]        = "<image-v3";
char _windSpeedPattern[]   = "<wind_speed";
char _windTypePattern[]    = "<wind_direction";
char _dampnessPattern[]    = "<dampness";
char _pressurePattern[]    = "<pressure";
char _temperaturePattern[] = "<temperature";

char weatherType[128]      = {'\0'};
char weatherIcon[128]      = {'\0'};
char weatherWindSpeed[16]  = {'\0'};
char weatherWindType[64]   = {'\0'};
char weatherDampness[16]   = {'\0'};
char weatherPressure[16]   = {'\0'};
char weatherTemperature[16]= {'\0'};
char* fileName = NULL;

unsigned short imageData[8192];

void updateWeather() {
  _http.begin("https://export.yandex.ru/bar/reginfo.xml?region=213");
  int httpCode = _http.GET();
  if (httpCode > 0) {
      //debug_printf("\r\n[HTTP] GET... code: %d\r\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = _http.getString();
        char* pstr = payload.begin();
        pstr = getMatch(pstr, _typePattern, weatherType, sizeof(weatherType)-1);
        pstr = getMatch(pstr, _iconPattern, weatherIcon, sizeof(weatherIcon)-1);
        pstr = getMatch(pstr, _windSpeedPattern, weatherWindSpeed, sizeof(weatherWindSpeed)-1);
        pstr = getMatch(pstr, _windTypePattern, weatherWindType, sizeof(weatherWindType)-1);
        pstr = getMatch(pstr, _dampnessPattern, weatherDampness, sizeof(weatherDampness)-1);
        pstr = getMatch(pstr, _pressurePattern, weatherPressure, sizeof(weatherPressure)-1);
        pstr = getMatch(pstr, _temperaturePattern, weatherTemperature, sizeof(weatherTemperature)-1);
        fileName = strrchr(weatherIcon, '/');

#if defined(DEBUG_CONSOLE)
        //Serial.println(payload);
        Serial.println(weatherType);
        Serial.println(weatherIcon);
        Serial.println(weatherWindSpeed);
        Serial.println(weatherWindType);
        Serial.println(weatherDampness);
        Serial.println(weatherPressure);
        Serial.println(weatherTemperature);
        Serial.println(fileName);
        Serial.println();
#endif

      }
  } else {
    debug_printf("\r\n[HTTP] GET... failed, error: %d\r\n", httpCode);
  }
  _http.end();

  tft.fillScreen(ColorToRGB565(0x4D, 0x8D, 0xEE));
  if (fileName != NULL) {
    File f = SPIFFS.open(fileName);
    if (f) {
      size_t len = f.size();
      f.read((uint8_t*)imageData, len);
      f.close();
      tft.pushImage(0, 0, iconSize, iconSize, imageData);
    }
  }
}

// Возврат: указатель на последний обработанный символ, мелкая оптимизация,
// чтобы каждый раз не начинать с начала,
// в связи с этим ВАЖЕН ПОРЯДОК ПОИСКА ЗНАЧЕНИЙ.
char* getMatch(char* text, char* pattern, char* value, size_t size) {
    if (text == NULL ) return NULL;
    char* delimeter = strchr(pattern, '|');
    if (delimeter == NULL) {
        char* begin = strstr(text, pattern);
        if (begin == NULL) return NULL;
        begin += strlen(pattern);
        while (*begin++ != '>');
        char* end = strchr(begin, '<');
        *end = '\0';
        strncpy (value, begin, size);
        *end = '<';
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
    return getMatch(begin, delimeter, value, size);
}

uint16_t ColorToRGB565(uint8_t r, uint8_t g, uint8_t b)
{
    return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}
