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
    isValid = false;
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
        LOGN("ControllerWeather::OnHandle")
        if (!WiFi.isConnected()) {
            isValid = false;
            LOGN("ControllerWeather::isValid, %d", isValid);
            continue;   
        }
        httpClient.begin("https://export.yandex.ru/bar/reginfo.xml?region=213");
        int httpCode = httpClient.GET();
        isValid = httpCode == HTTP_CODE_OK;
        if (isValid) {
            String payload = httpClient.getString();
            isValid = !payload.isEmpty();
            if (isValid) {
                parseWeatherInfo(payload);
                LOGN("ControllerWeather::weatherDescription, %s", weatherDescription.c_str());
                LOGN("ControllerWeather::weatherTemperature, %s", weatherTemperature.c_str());
                LOGN("ControllerWeather::weatherPressure, %s", weatherPressure.c_str());
                LOGN("ControllerWeather::weatherDampness, %s", weatherDampness.c_str());
                LOGN("ControllerWeather::weatherWindSpeed, %s", weatherWindSpeed.c_str());
                LOGN("ControllerWeather::weatherWindType, %s", weatherWindType.c_str());
                LOGN("ControllerWeather::trafficLevel, %s", trafficLevel.c_str());
                LOGN("ControllerWeather::weatherUrlIcon, %s", weatherUrlIcon.c_str());
                LOGN("ControllerWeather::iconFileName, %s", iconFileName.c_str());
                LOGN("ControllerWeather::windFileName, %s", windFileName.c_str());
            }
        }
        httpClient.end();
        LOGN("ControllerWeather::isValid, %d", isValid);
        xSemaphoreGive(_updateEvent);
        vTaskDelay(isValid ? UPDATE_WEATHER_TIME: 5000);
    }
}

uint16_t ControllerWeather::ColorToRGB565(const uint8_t r, const uint8_t g, const uint8_t b) {
  return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}

void ControllerWeather::parseWeatherInfo(String& payload) {
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

    if (!windFileName.isEmpty()) {
        windFileName = "/" + windFileName;
    }
    
    iconFileName = "/icon";
    if (!weatherUrlIcon.isEmpty()) {
        iconFileName += strrchr(weatherUrlIcon.c_str(), '/');
    }

    float windSpeed = weatherWindSpeed.toFloat();
    if (windSpeed > 3.0 && windSpeed < 10.0)
        windFileName.concat(F("2"));
    else if (windSpeed >= 10)
        windFileName.concat(F("3"));
    windFileName.concat(F(".png"));
    windFileName = "/icon" + windFileName;
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
