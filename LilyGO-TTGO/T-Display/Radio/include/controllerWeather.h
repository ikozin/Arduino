#pragma once

#include "controller.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

class ControllerWeather : public Controller {
    public:
        ControllerWeather(const char* name);
    public:
        bool  isValid;
        String weatherDescription;
        String weatherUrlIcon;
        String weatherWindSpeed;
        String weatherWindType;
        String weatherHumidity;
        String weatherPressure;
        String weatherTemperature;
        String iconFileName;
        String windFileName;
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        StaticJsonDocument<2048> _doc;
        uint16_t ColorToRGB565(const uint8_t r, const uint8_t g, const uint8_t b);
        bool parseWeatherInfo(HTTPClient& client, String& payload);
};
