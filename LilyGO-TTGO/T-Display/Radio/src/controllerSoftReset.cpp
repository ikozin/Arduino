#include "controllerSoftReset.h"

ControllerSoftReset::ControllerSoftReset(gpio_num_t pin) :
                        Controller("ControllerSoftReset", NULL) {
    // _updateTimeInSec = 1;
    _pin = pin;
}


// GPIO_INTR_DISABLE - отключено
// GPIO_INTR_POSEDGE - по изменению с 0 до 1
// GPIO_INTR_NEGEDGE - по изменению с 1 на 0
// GPIO_INTR_ANYEDGE - по любому изменению
// GPIO_INTR_LOW_LEVEL - по низкому уровню
// GPIO_INTR_HIGH_LEVEL - по высокому уровню

InitResponse_t ControllerSoftReset::OnInit() {
    gpio_install_isr_service(0);
    gpio_reset_pin(_pin);
    gpio_pad_select_gpio(_pin);
    gpio_set_direction(_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(_pin, GPIO_PULLUP_ONLY); 
    gpio_set_intr_type(_pin, GPIO_INTR_NEGEDGE);
    gpio_intr_enable(_pin);
    gpio_isr_handler_add(_pin, gpio_isr_handler, this);
    return OnInitResultStart;
}

// bool ControllerSoftReset::OnIteration() {
//     LOGN("ControllerSoftReset::OnIteration")
//     int result = gpio_get_level(_pin);
//     LOGN("ControllerSoftReset::result, %d", result);
//     return false;
// }

void ControllerSoftReset::OnHandle() {
    xSemaphoreTake(_updateEvent, portMAX_DELAY);
    LOGN("%s::RESET", _name);
    esp_restart();
}

void IRAM_ATTR ControllerSoftReset::gpio_isr_handler(void* parameter) {
    ControllerSoftReset* controller = static_cast<ControllerSoftReset*>(parameter);
    xSemaphoreGiveFromISR(controller->_updateEvent, NULL);
}
