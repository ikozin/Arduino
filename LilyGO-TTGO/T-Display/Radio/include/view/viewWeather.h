#include "view/view.h"
#include "controller/controllerWeather.h"

class ViewWeather : public ViewT<ControllerWeather> {
    public:
        ViewWeather(const char* name, View** currentView, ControllerWeather* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, currentView, ctrl, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
    private:
        void drawImageFile(const char* fileName, const int32_t x, const int32_t y, const int32_t size);
        void drawTextBlock(int32_t left, int32_t top, int32_t width, const String &text);
};
