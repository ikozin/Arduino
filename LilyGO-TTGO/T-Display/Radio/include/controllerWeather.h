#ifndef _CONTROLLERWEATHER_H_
#define _CONTROLLERWEATHER_H_

#include "controller.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define UPDATE_WEATHER_TIME (20 * 60000 / portTICK_RATE_MS)

class ControllerWeather : public Controller {
    public:
        ControllerWeather(const char* name);
    public:
        bool  isValid;
        String trafficLevel;
        String weatherDescription;
        String weatherUrlIcon;
        String weatherWindSpeed;
        String weatherWindType;
        String weatherDampness;
        String weatherPressure;
        String weatherTemperature;
        String iconFileName;
        String windFileName;
    protected:
        virtual void OnHandle() override;
    private:
        StaticJsonDocument<2048> _doc;
        uint16_t ColorToRGB565(const uint8_t r, const uint8_t g, const uint8_t b);
        bool parseWeatherInfo(String& payload);
        char* getMatch(const char* text, const char* pattern, String& value, const char first, const char last);
};


#endif  //_CONTROLLERWEATHER_H_