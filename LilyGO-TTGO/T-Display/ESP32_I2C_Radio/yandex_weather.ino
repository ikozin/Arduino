HTTPClient _http;

char _type[] = "<info|<weather|<day_part|<weather_type";
char _windSpeed[] = "<info|<weather|<day_part|<wind_speed";
char _temperature[] = "<info|<weather|<day_part|<temperature";
char _icon[] = "<info|<weather|<day_part|<image-v3";
String value;

void updateWeather() {
/*
  Serial.printf("\r\n");
  _http.begin("https://export.yandex.ru/bar/reginfo.xml?region=213");
  int httpCode = _http.GET();
  if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\r\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        //_http.writeToStream(&Serial);
        String payload = _http.getString();
        Serial.println(payload);
        //value.reserve(128);
        getMatch(payload.begin(), _type, value);
        Serial.println(value.c_str());
        getMatch(payload.begin(), _windSpeed, value);
        Serial.println(value.c_str());
        getMatch(payload.begin(), _temperature, value);
        Serial.println(value.c_str());
        getMatch(payload.begin(), _icon, value);
        Serial.println(value.c_str());
        char * fileName = value.begin() + value.lastIndexOf('/');
        Serial.println(fileName);
       
        //
      }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %d\r\n", httpCode);
  }
  _http.end();
  Serial.printf("\r\n");  
*/
}

bool getMatch(char* text, char* pattern, String& value ) {
    //Serial.println(pattern);
    char* delimeter = strchr(pattern, '|');
    if (delimeter == NULL) {
        char* begin = strstr(text, pattern);
        if (begin == NULL) return false;
        begin += strlen(pattern);
        while (*begin++ != '>');
        char* end = strchr(begin, '<');
        *end = '\0';
        value = begin;
        *end = '<';
        return true;
    }
    *delimeter = '\0';
    char* begin = strstr(text, pattern);
    if (begin == NULL) {
      *delimeter = '|';
      return false;
    }
    begin += strlen(pattern);
    *delimeter++ = '|';
    return getMatch(begin, delimeter, value);
}
