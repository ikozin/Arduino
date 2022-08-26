#ifndef _CONTROLLERWEATHER_H_
#define _CONTROLLERWEATHER_H_

#include "controller.h"
#include <HTTPClient.h>

#define UPDATE_WEATHER_TIME (20 * 60000 / portTICK_RATE_MS)

class ControllerWeather : public Controller {
    public:
        ControllerWeather(const char* name);
    public:
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
        virtual void OnHandle();
    private:
        char* getMatch(const char* text, const char* pattern, String& value, const char first, const char last);
};


#endif  //_CONTROLLERWEATHER_H_