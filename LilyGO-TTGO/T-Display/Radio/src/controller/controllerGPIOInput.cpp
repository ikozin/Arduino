#include "controller/controllerGPIOInput.h"

// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html

ControllerGPIOInput::ControllerGPIOInput(const char* name, gpio_num_t pin, gpio_int_type_t int_type, gpio_pull_mode_t pull_mode) :
                        Controller(name) {
    _pin = pin;
    _int_type = int_type;
    _pull_mode = pull_mode;
}

// GPIO_INTR_DISABLE - отключено
// GPIO_INTR_POSEDGE - по изменению с 0 до 1
// GPIO_INTR_NEGEDGE - по изменению с 1 на 0
// GPIO_INTR_ANYEDGE - по любому изменению
// GPIO_INTR_LOW_LEVEL - по низкому уровню
// GPIO_INTR_HIGH_LEVEL - по высокому уровню
// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html

InitResponse_t ControllerGPIOInput::OnInit() {
    // gpio_install_isr_service(0);
    gpio_reset_pin(_pin);
    gpio_pad_select_gpio(_pin);
    gpio_set_direction(_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(_pin, _pull_mode); 
    gpio_set_intr_type(_pin, _int_type);
    gpio_intr_enable(_pin);
    gpio_isr_handler_add(_pin, gpio_isr_handler, this);
    return OnInitResultStop;
}

void IRAM_ATTR ControllerGPIOInput::gpio_isr_handler(void* parameter) {
    ControllerGPIOInput* controller = static_cast<ControllerGPIOInput*>(parameter);
    controller->_state = gpio_get_level(controller->_pin);
    for (int i = 0; i < EventListMax && controller->_eventList[i] != nullptr; i++) {
        xSemaphoreGiveFromISR(controller->_eventList[i], nullptr);
    }
}
