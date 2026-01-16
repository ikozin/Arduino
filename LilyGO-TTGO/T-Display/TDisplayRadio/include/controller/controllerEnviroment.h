#pragma once

#include "controller/controller.h"
#include "controller/controllerNavigator.h"
#include <Preferences.h>
#include "display.h"

#define COLOR_BLACK     (_env->getPalette()[0])
#define COLOR_WHITE     (_env->getPalette()[1])
#define COLOR_RED       (_env->getPalette()[2])
#define COLOR_GREEN     (_env->getPalette()[3])
#define COLOR_BLUE      (_env->getPalette()[4])
#define COLOR_YELLOW    (_env->getPalette()[5])
#define COLOR_MAGENTA   (_env->getPalette()[6])

#define MAKETIME(h, m, s)  (h * 3600U + m * 60U + s)

typedef struct _images_t_ {
    const char* temp;
    const char* hum;
    const char* rads;
} Images_t;

class ControllerEnviroment : public Controller {
    public:
        ControllerEnviroment(const char* name) : Controller(name, 1000) {
            _navigator = nullptr;
            _palette = nullptr;
            _images = nullptr;
            _dayStart = 8 * 3600;
            _dayFinish = 23 * 3600;
        }
    protected:
        virtual bool OnInit() override;
        virtual bool OnUpdate() override;
    private:
        ControllerNavigator* _navigator;
        uint32_t* _palette;
        Images_t* _images;
        uint64_t _dayStart;
        uint64_t _dayFinish;
    private:
        static uint32_t palette_day[]; 
        static uint32_t palette_night[];
        static Images_t images_day; 
        static Images_t images_night;
    public:
        void Attach(ControllerNavigator* navigator, uint64_t secStart, uint64_t secFinish) {
            _dayStart = secStart;
            _dayFinish = secFinish;
            _navigator = navigator;
        }
        void setEnviromentDay() {
            _palette = ControllerEnviroment::palette_day;
            _images = &ControllerEnviroment::images_day;
            if (_navigator != nullptr) _navigator->forceUpdate();
        }
        void setEnviromentHight() {
            _palette = ControllerEnviroment::palette_night;
            _images = &ControllerEnviroment::images_night;
            if (_navigator != nullptr) _navigator->forceUpdate();
        }
        uint32_t* getPalette() const { return _palette; }
        Images_t* getImage() const { return _images; }
    };