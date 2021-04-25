HTTPClient _http;

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
        int index = payload.indexOf("<weather_code>");
        index += strlen("<weather_code>");
        Serial.println(payload.substring(index, payload.indexOf("</", index)).c_str());
        //
      }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %d\r\n", httpCode);
  }
  _http.end();
  Serial.printf("\r\n");  
*/
}
