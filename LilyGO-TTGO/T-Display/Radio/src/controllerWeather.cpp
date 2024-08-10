#include "controllerWeather.h"
#include "main.h"
#include <FS.h>
#include <SPIFFS.h>

String payload;
HTTPClient httpClient;

//#define WEATHER_STUB

#if defined(WEATHER_STUB)
    const String weather_stub = "{\"location\":{\"name\":\"Moscow\",\"region\":\"Moscow City\",\"country\":\"Russia\",\"lat\":55.75,\"lon\":37.62,\"tz_id\":\"Europe/Moscow\",\"localtime_epoch\":1709628576,\"localtime\":\"2024-03-05 11:49\"},\"current\":{\"last_updated_epoch\":1709628300,\"last_updated\":\"2024-03-05 11:45\",\"temp_c\":-1.0,\"temp_f\":30.2,\"is_day\":1,\"condition\":{\"text\":\"переменная облачность\",\"icon\":\"//cdn.weatherapi.com/weather/64x64/day/326.png\",\"code\":1213},\"wind_mph\":11.9,\"wind_kph\":19.1,\"wind_degree\":50,\"wind_dir\":\"NE\",\"pressure_mb\":1022.0,\"pressure_in\":30.18,\"precip_mm\":0.07,\"precip_in\":0.0,\"humidity\":86,\"cloud\":75,\"feelslike_c\":-5.9,\"feelslike_f\":21.3,\"vis_km\":9.0,\"vis_miles\":5.0,\"uv\":1.0,\"gust_mph\":13.6,\"gust_kph\":21.9}}";
#endif

ControllerWeather::ControllerWeather(const char* name):
                    Controller(name, nullptr), _doc() {
    _updateTimeInSec = 20 * 60;
    
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

InitResponse_t ControllerWeather::OnInit() {
    return OnInitResultStart;
}

bool ControllerWeather::OnIteration() {
    if (!WiFi.isConnected()) {
        isValid = false;
        LOGN("%s::isValid, %d", _name, isValid);
        return true;   
    }
#if !defined(WEATHER_STUB)
    httpClient.begin("https://api.weatherapi.com/v1/current.json?q=Moscow,RU&units=metric&lang=ru&key=b0b2880fa2ae4b8594e115610231806");
    isValid = httpClient.GET() == HTTP_CODE_OK;
    if (isValid) {
        payload = httpClient.getString();
        isValid = !payload.isEmpty();
    }
    httpClient.setReuse(true);
#endif
#if defined(WEATHER_STUB)
    isValid = true;
    payload = weather_stub;
#endif
    if (isValid) {
        isValid = parseWeatherInfo(httpClient, payload);
    }

    LOGN("%::isValid, %d", _name, isValid);
    return true;
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
    // //cdn.weatherapi.com/weather/64x64/night/311.png
    // //cdn.weatherapi.com/weather/64x64/day/311.png
    if (!weatherUrlIcon.isEmpty()) {
        weatherUrlIcon = "https:" + weatherUrlIcon;
        int pos = weatherUrlIcon.lastIndexOf('/');
        if (pos != 1) {
            if (weatherUrlIcon.indexOf("night") != -1) {
                iconFileName = "/icon/night" + weatherUrlIcon.substring(pos);
            } else if (weatherUrlIcon.indexOf("day") != -1) {
                iconFileName = "/icon/day" + weatherUrlIcon.substring(pos);
            } else {
                iconFileName.clear();
            }
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
    LOGN("%s::weatherDescription, %s", _name, weatherDescription.c_str());
    LOGN("%s::weatherTemperature, %s", _name, weatherTemperature.c_str());
    LOGN("%s::weatherPressure, %s", _name, weatherPressure.c_str());
    LOGN("%s::weatherHumidity, %s", _name, weatherHumidity.c_str());
    LOGN("%s::weatherWindSpeed, %s", _name, weatherWindSpeed.c_str());
    LOGN("%s::weatherWindType, %s", _name, weatherWindType.c_str());
    LOGN("%s::weatherUrlIcon, %s", _name, weatherUrlIcon.c_str());
    LOGN("%s::iconFileName, %s", _name, iconFileName.c_str());
    LOGN("%s::windFileName, %s", _name, windFileName.c_str());

    return true;
}
