#include <Arduino.h>

#ifndef ESP32
    #error ESP32
#endif

/*

HC-SR501


Параметры
╔════════════════╦═════════╗
║ Протокол       ║  GPIO   ║
╠════════════════╬═════════╣
║ Питание        ║ 3V3, 5V ║
╚════════════════╩═════════╝

Распиновка
╔══════╦═════════╦═════╗    ╔═════════╦══════╦═════╗
║ DATA ║   VCC   ║ GND ║    ║   VCC   ║ DATA ║ GND ║
╠══════╬═════════╬═════╣    ╠═════════╬══════╬═════╣
║ GPIO ║ 3V3, 5V ║ GND ║    ║ 3V3, 5V ║ GPIO ║ GND ║
╚══════╩═════════╩═════╝    ╚═════════╩══════╩═════╝

https://wiki.dfrobot.com/Digital_Infrared_motion_sensor__SKU_SEN0018_

*/

gpio_num_t led_pin  = (gpio_num_t)LED_BUILTIN;
gpio_num_t pir_pin  = (gpio_num_t)32;

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
