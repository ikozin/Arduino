#include "controller/controllerGPIOInput.h"

// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html

ControllerGPIOInput::ControllerGPIOInput(const char* name, gpio_num_t pin, uint8_t int_type, uint8_t pull_mode) :
                        Controller(name) {
    _pin = pin;
    _int_type = int_type;
    _pull_mode = pull_mode;
    _value = 0;
}

// GPIO_INTR_DISABLE - отключено
// GPIO_INTR_POSEDGE - по изменению с 0 до 1
// GPIO_INTR_NEGEDGE - по изменению с 1 на 0
// GPIO_INTR_ANYEDGE - по любому изменению
// GPIO_INTR_LOW_LEVEL - по низкому уровню
// GPIO_INTR_HIGH_LEVEL - по высокому уровню
// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html

InitResponse_t ControllerGPIOInput::OnInit() {
    pinMode(_pin, _pull_mode);
    attachInterruptArg(_pin, isr_handler, this, _int_type);
    return OnInitResultStop;
}

void ControllerGPIOInput::isr_handler(void* parameter) {
    ControllerGPIOInput* controller = static_cast<ControllerGPIOInput*>(parameter);
    controller->_value = digitalRead(controller->_pin);
    for (int i = 0; i < EventListMax && controller->_eventList[i] != nullptr; i++) {
        xSemaphoreGiveFromISR(controller->_eventList[i], nullptr);
    }
}
