#ifndef _VIEWWEATHER_H_
#define _VIEWWEATHER_H_

#include "view.h"
#include "controllerWeather.h"

class ViewWeather : public View {
    public:
        ViewWeather(const char* name, View** currentView, ControllerWeather* weather);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerWeather* _weather;
    private:
        void drawImageFile(const char* fileName, const int32_t x, const int32_t y, const int32_t size);
        void drawTextBlock(int32_t left, int32_t top, int32_t width, const String &text);
};

#endif  //_VIEWWEATHER_H_