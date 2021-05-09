extern TFT_eSPI tft;

HTTPClient _http;
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

char trafficLevel[8]       = {'\0'};
char weatherType[128]      = {'\0'};
char weatherIcon[128]      = {'\0'};
char weatherWindSpeed[16]  = {'\0'};
char weatherWindType[64]   = {'\0'};
char weatherDampness[16]   = {'\0'};
char weatherPressure[16]   = {'\0'};
char weatherTemperature[16]= {'\0'};
char* fileName = NULL;
char windFileName[32]      = {'\0'};
int32_t posX;

unsigned short imageData[8192];

void updateWeather() {
  _http.begin("https://export.yandex.ru/bar/reginfo.xml?region=213");
  int httpCode = _http.GET();
  if (httpCode > 0) {
      debug_printf("\r\n[HTTP] GET, code: %d\r\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = _http.getString();
        char* pstr = payload.begin();
        pstr = getMatch(pstr, _trafficPattern, trafficLevel, sizeof(trafficLevel)-1, '>', '<');
        pstr = getMatch(pstr, _typePattern, weatherType, sizeof(weatherType)-1, '>', '<');
        pstr = getMatch(pstr, _iconPattern, weatherIcon, sizeof(weatherIcon)-1, '>', '<');
        pstr = getMatch(pstr, _windSpeedPattern, weatherWindSpeed, sizeof(weatherWindSpeed)-1, '>', '<');
        pstr = getMatch(pstr, _windTypePattern, weatherWindType, sizeof(weatherWindType)-1, '>', '<');
        pstr = getMatch(pstr, _dampnessPattern, weatherDampness, sizeof(weatherDampness)-1, '>', '<');
        pstr = getMatch(pstr, _pressurePattern, weatherPressure, sizeof(weatherPressure)-1, '>', '<');
        pstr = getMatch(pstr, _temperaturePattern, weatherTemperature, sizeof(weatherTemperature)-1, '>', '<');
        fileName = strrchr(weatherIcon, '/');
        strcat(weatherTemperature, "°");
        strcpy(windFileName, "/");
        getMatch(payload.begin(), _windPattern, windFileName + 1, sizeof(windFileName)-2, '"', '"');
        double windSpeed = atof(weatherWindSpeed);
        if (windSpeed > 3.0 && windSpeed < 10.0)
          strcat(windFileName, "2");
        else if (windSpeed >= 10)
          strcat(windFileName, "3");
        strcat(windFileName, ".png");
        
#if defined(DEBUG_CONSOLE)
        //Serial.println(payload);
        Serial.println(trafficLevel);
        Serial.println(weatherType);
        Serial.println(weatherIcon);
        Serial.println(weatherWindSpeed);
        Serial.println(weatherWindType);
        Serial.println(weatherDampness);
        Serial.println(weatherPressure);
        Serial.println(weatherTemperature);
        Serial.println(fileName);
        Serial.println(windFileName);
        Serial.println();
#endif

      }
  } else {
    debug_printf("\r\n[HTTP] GET, error: %d\r\n", httpCode);
  }
  _http.end();

  tft.fillScreen(0x4C7D); //ColorToRGB565(0x4D, 0x8D, 0xEE)

  if (fileName != NULL) drawImageFile(fileName, 107, 0, iconSize);
  drawImageFile(windFileName, 192, 8, 32);
  
  //strcpy(weatherType, "облачно с прояснениями, необльшой дождь");
  tft.loadFont(FONT_CALIBRI_32);
  tft.setTextColor(TFT_WHITE);
  posX = tft.textWidth(weatherType);
  posX = (posX < 240) ? (240 - posX) >> 1 : 0;
  tft.drawString(weatherType, posX + 2, 64);
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

// Возврат: указатель на последний обработанный символ, мелкая оптимизация,
// чтобы каждый раз не начинать с начала,
// в связи с этим ВАЖЕН ПОРЯДОК ПОИСКА ЗНАЧЕНИЙ.
char* getMatch(char* text, char* pattern, char* value, size_t size, char first, char last) {
  if (text == NULL ) return NULL;
  char* delimeter = strchr(pattern, '|');
  if (delimeter == NULL) {
    char* begin = strstr(text, pattern);
    if (begin == NULL) return NULL;
    begin += strlen(pattern);
    while (*begin++ != first);
    char* end = strchr(begin, last);
    *end = '\0';
    strncpy (value, begin, size);
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
  return getMatch(begin, delimeter, value, size, first, last);
}

void drawImageFile(const char* fileName, int32_t x, int32_t y, int32_t size) {
    File f = SPIFFS.open(fileName);
    if (f) {
        size_t len = f.size();
        f.read((uint8_t*)imageData, len);
        f.close();
        tft.pushImage(x, y, size, size, imageData);
    }
}

uint16_t ColorToRGB565(uint8_t r, uint8_t g, uint8_t b)
{
  return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}
