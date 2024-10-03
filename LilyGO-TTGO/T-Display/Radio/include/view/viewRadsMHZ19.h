#pragma once

#include "view/view.h"
#include "controller/controllerRadSens.h"
#include "controller/controllerMHZ19.h"

typedef enum _Co2Level {
    Min = 0,
    Middle,
    Max,
} Co2Level;

class ViewRadsMHZ19 : public ViewT {
    public:
        ViewRadsMHZ19(const char* name, ViewSettig* setting, ControllerRadSens* radSens, ControllerMHZ19* mhz19, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual void OnDrawHandle() override;
    private:
        uint32_t            _co2_Min;
        uint32_t            _co2_Max;
        ControllerMHZ19*    _mhz19;
    private:
        Co2Level getCO2Level(float value) const {
            return (value <= _co2_Min) ? Co2Level::Min : ((value > _co2_Max) ? Co2Level::Max : Co2Level::Middle);
        };
};
