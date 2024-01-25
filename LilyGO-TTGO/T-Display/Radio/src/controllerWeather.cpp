#include "controllerWeather.h"
#include "main.h"
#include <FS.h>
#include <SPIFFS.h>

String payload;
HTTPClient httpClient;

ControllerWeather::ControllerWeather(const char* name) : Controller(name), _doc() {
    isValid = false;
    weatherDescription.reserve(128);
    weatherUrlIcon.reserve(128);
    weatherWindSpeed.reserve(16);
    weatherWindType.reserve(64);
    weatherHumidity.reserve(16);
    weatherPressure.reserve(16);
    weatherTemperature.reserve(16);
    payload.reserve(8192);
}

void ControllerWeather::OnHandle() {
    for (;;) {
        LOGN("ControllerWeather::OnHandle")
        if (!WiFi.isConnected()) {
            isValid = false;
            LOGN("ControllerWeather::isValid, %d", isValid);
            continue;   
        }
        httpClient.begin("https://api.weatherapi.com/v1/current.json?q=Moscow,RU&units=metric&lang=ru&key=b0b2880fa2ae4b8594e115610231806");
        isValid = httpClient.GET() == HTTP_CODE_OK;
        if (isValid) {
            payload = httpClient.getString();
            isValid = !payload.isEmpty();
        }
        httpClient.setReuse(true);
        if (isValid) {
            isValid = parseWeatherInfo(httpClient, payload);
        }

        LOGN("ControllerWeather::isValid, %d", isValid);
        xSemaphoreGive(_updateEvent);
        vTaskDelay(isValid ? UPDATE_WEATHER_TIME: 10000);
    }
}

uint16_t ControllerWeather::ColorToRGB565(const uint8_t r, const uint8_t g, const uint8_t b) {
  return (uint16_t)(((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3));
}

bool ControllerWeather::parseWeatherInfo(HTTPClient& client, String& payload) {
    char* pstr = payload.begin();
    DeserializationError error = deserializeJson(_doc, pstr);
    if (error) {
        LOGN("Failed to read json, using default configuration");
        return false;
    }
    iconFileName.clear();
    weatherDescription = _doc["current"]["condition"]["text"].as<String>();
    weatherTemperature = _doc["current"]["temp_c"].as<String>();
    weatherHumidity = _doc["current"]["humidity"].as<String>();
    weatherPressure = String(_doc["current"]["pressure_mb"].as<float>() * 0.750062, 1);
    weatherWindSpeed = _doc["current"]["wind_mph"].as<String>();
    weatherWindType =_doc["current"]["wind_dir"].as<String>();
    weatherUrlIcon = _doc["current"]["condition"]["icon"].as<String>();

    if (!weatherTemperature.isEmpty()) {
        weatherTemperature += "°";
        if (isdigit(weatherTemperature[0])) {
            weatherTemperature = "+" + weatherTemperature;
        }
    }
    if (!weatherUrlIcon.isEmpty()) {
        weatherUrlIcon = "https:" + weatherUrlIcon;
        int pos = weatherUrlIcon.lastIndexOf('/');
        if (pos != 1) {
            iconFileName = "/icon" + weatherUrlIcon.substring(pos);
        }
        if (!SPIFFS.exists(iconFileName)) {
            if (client.begin(weatherUrlIcon)) {
                int code = client.GET();
                if (code == HTTP_CODE_OK) {
                    File f = SPIFFS.open(iconFileName, "w");
                    if (f) {
                        client.writeToStream(&f);
                        f.close();
                    }
                }
                client.end();
            }
        }
    }    
    LOGN("ControllerWeather::weatherDescription, %s", weatherDescription.c_str());
    LOGN("ControllerWeather::weatherTemperature, %s", weatherTemperature.c_str());
    LOGN("ControllerWeather::weatherPressure, %s", weatherPressure.c_str());
    LOGN("ControllerWeather::weatherHumidity, %s", weatherHumidity.c_str());
    LOGN("ControllerWeather::weatherWindSpeed, %s", weatherWindSpeed.c_str());
    LOGN("ControllerWeather::weatherWindType, %s", weatherWindType.c_str());
    LOGN("ControllerWeather::weatherUrlIcon, %s", weatherUrlIcon.c_str());
    LOGN("ControllerWeather::iconFileName, %s", iconFileName.c_str());
    LOGN("ControllerWeather::windFileName, %s", windFileName.c_str());

    return true;
}
