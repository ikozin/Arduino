#include "controllerWeather.h"
#include "main.h"

char _trafficPattern[]     = "<info|<traffic|<region|<level";
char _typePattern[]        = "<weather|<day_part|<weather_type";
char _iconPattern[]        = "<image-v3";
char _windSpeedPattern[]   = "<wind_speed";
char _windTypePattern[]    = "<wind_direction";
char _dampnessPattern[]    = "<dampness";
char _pressurePattern[]    = "<pressure";
char _temperaturePattern[] = "<temperature";
char _windPattern[]        = "<info|<weather|<day_part|<wind_direction|id=";


ControllerWeather::ControllerWeather(const char* name) : Controller(name) {
    trafficLevel.reserve(8);
    weatherDescription.reserve(128);
    weatherUrlIcon.reserve(128);
    weatherWindSpeed.reserve(16);
    weatherWindType.reserve(64);
    weatherDampness.reserve(16);
    weatherPressure.reserve(16);
    weatherTemperature.reserve(16);
}

void ControllerWeather::OnHandle() {
    HTTPClient httpClient;
    for (;;) {
        httpClient.begin("https://export.yandex.ru/bar/reginfo.xml?region=213");
        int httpCode = httpClient.GET();
        if (httpCode > 0) {
            // Serial.printf("[HTTP] GET, code: %d\r\n", httpCode);
            if (httpCode == HTTP_CODE_OK) {
                String payload = httpClient.getString();
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
                iconFileName = "/icon" + iconFileName;
  
                float windSpeed = weatherWindSpeed.toFloat();
                if (windSpeed > 3.0 && windSpeed < 10.0)
                    windFileName.concat(F("2"));
                else if (windSpeed >= 10)
                    windFileName.concat(F("3"));
                windFileName.concat(F(".png"));
                windFileName = "/icon" + windFileName;
        
                logTime();
                Serial.printf("Yandex Weather\r\n");
                Serial.printf("Core           %d\r\n", xPortGetCoreID());
                Serial.printf("Трафик:        %s\r\n" ,trafficLevel.c_str());
                Serial.printf("Погода:        %s\r\n" ,weatherDescription.c_str());
                Serial.printf("Url:           %s\r\n" ,weatherUrlIcon.c_str());
                Serial.printf("Скорость ветра:%s\r\n" ,weatherWindSpeed.c_str());
                Serial.printf("Ветер:         %s\r\n" ,weatherWindType.c_str());
                Serial.printf("Влажность:     %s\r\n" ,weatherDampness.c_str());
                Serial.printf("Давление:      %s\r\n" ,weatherPressure.c_str());
                Serial.printf("Температура:   %s\r\n" ,weatherTemperature.c_str());
                Serial.printf("file icon:     %s\r\n" ,iconFileName.c_str());
                Serial.printf("file wind:     %s\r\n" ,windFileName.c_str());
                Serial.printf("\r\n");
            }
        // } else {
        //     Serial.printf("\r\n[HTTP] GET, error: %d\r\n", httpCode);
        }
        httpClient.end();
        xSemaphoreGive(_updateEvent);
        vTaskDelay(UPDATE_WEATHER_TIME);
    }
}

uint16_t ControllerWeather::ColorToRGB565(const uint8_t r, const uint8_t g, const uint8_t b) {
  return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}

// Возврат: указатель на последний обработанный символ, мелкая оптимизация,
// чтобы каждый раз не начинать с начала,
// в связи с этим ВАЖЕН ПОРЯДОК ПОИСКА ЗНАЧЕНИЙ.
char* ControllerWeather::getMatch(const char* text, const char* pattern, String& value, const char first, const char last) {
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
