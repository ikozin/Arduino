#include <Arduino.h>

#ifndef ESP32
    #error ESP32
#endif

/*

HLK-LD2420


Параметры
╔════════════════╦════════════╗
║ Протокол       ║ UART, GPIO ║
╠════════════════╬════════════╣
║ Скорость UART* ║ 115200     ║
╠════════════════╬════════════╣
║ Скорость UART* ║ 256000     ║
╠════════════════╬════════════╣
║ Питание        ║ +3V3       ║
╚════════════════╩════════════╝
* зависит от версии прошивки, для версии начиная с 1.5.3 скорость 115200, для старых 256000

Распиновка
╔═════╦═════╦═════╦═════╦═════╗
║ 3V3 ║ GND ║ OT1 ║ RX  ║ OT2 ║
╠═════╬═════╬═════╬═════╬═════╣
║ 3V3 ║ GND ║ RXD ║ TXD ║ OUT ║
╚═════╩═════╬═════╩═════╬═════╣
            ║   UART    ║GPIO ║
            ╚═══════════╩═════╝

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html

*/

gpio_num_t pir_pin  = (gpio_num_t)27;
gpio_num_t led_pin  = (gpio_num_t)25;

void IRAM_ATTR gpio_isr_handler(void* parameter) {
    int state = gpio_get_level(pir_pin);
    gpio_set_level(led_pin, state);
}

void setup() {
    gpio_install_isr_service(0);
    gpio_reset_pin(pir_pin);
    gpio_pad_select_gpio(pir_pin);
    gpio_set_direction(pir_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pir_pin, GPIO_FLOATING); 
    gpio_set_intr_type(pir_pin, GPIO_INTR_ANYEDGE);
    gpio_intr_enable(pir_pin);
    gpio_isr_handler_add(pir_pin, gpio_isr_handler, nullptr);

    gpio_reset_pin(led_pin);
    gpio_pad_select_gpio(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
}

void loop(void) {
}
