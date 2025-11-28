#include "controller/controllerGPIOInput.h"

// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html

ControllerGPIOInput::ControllerGPIOInput(const char* name, gpio_num_t pin, uint8_t int_type, uint8_t pull_mode) :
    ControllerValue(name, 0) {
    _pin = pin;
    _int_type = int_type;
    _pull_mode = pull_mode;
    _value = 0;
    _xMutex = xSemaphoreCreateBinary();
}

// GPIO_INTR_DISABLE - отключено
// GPIO_INTR_POSEDGE - по изменению с 0 до 1
// GPIO_INTR_NEGEDGE - по изменению с 1 на 0
// GPIO_INTR_ANYEDGE - по любому изменению
// GPIO_INTR_LOW_LEVEL - по низкому уровню
// GPIO_INTR_HIGH_LEVEL - по высокому уровню
// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html

bool ControllerGPIOInput::OnInit() {
    pinMode(_pin, _pull_mode);
    attachInterruptArg(_pin, isr_handler, this, _int_type);
    return true;
}

bool ControllerGPIOInput::OnUpdate() {
    bool result = xSemaphoreTake(_xMutex, 0);
    if (!result) return false;
    return OnCommand();
}

void ControllerGPIOInput::isr_handler(void* parameter) {
    ControllerGPIOInput* controller = static_cast<ControllerGPIOInput*>(parameter);
    controller->_value = digitalRead(controller->_pin);
    xSemaphoreGiveFromISR(controller->_xMutex, nullptr);
}
