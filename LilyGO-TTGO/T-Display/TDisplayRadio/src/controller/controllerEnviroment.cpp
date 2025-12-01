#include "controller/controllerEnviroment.h"

uint32_t ControllerEnviroment::palette_day[] {
    TFT_BLACK,
    TFT_WHITE,
    TFT_RED,
    TFT_GREEN,
    TFT_BLUE,
    TFT_YELLOW,
    TFT_MAGENTA
}; 

uint32_t ControllerEnviroment::palette_night[] {
    TFT_BLACK,
    0x79EF,
    0x7800,
    0x03E0,
    0x000F,
    0x79E0,
    0x780F
};

Images_t ControllerEnviroment::images_day { .temp = "/temp_52x106_day.png", .hum = "/hum_42x59_day.png", .rads = "/rads_85_day.png" }; 
Images_t ControllerEnviroment::images_night { .temp = "/temp_52x106_night.png", .hum = "/hum_42x59_day.night", .rads = "/rads_85_night.png" };

bool ControllerEnviroment::OnInit() {
    setEnviromentDay();
    return true;
}

bool ControllerEnviroment::OnUpdate() {
    return true;
}
