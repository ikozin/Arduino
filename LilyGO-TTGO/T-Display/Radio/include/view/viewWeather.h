#include "view/view.h"
#include "controller/controllerWeather.h"

class ViewWeather : public ViewT {
    public:
        ViewWeather(const char* name, ViewSettig* setting, ControllerWeather* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, setting, ctrl, 0, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
    private:
        void drawImageFile(const char* fileName, const int32_t x, const int32_t y, const int32_t size);
        void drawTextBlock(int32_t left, int32_t top, int32_t width, const String &text);
};
