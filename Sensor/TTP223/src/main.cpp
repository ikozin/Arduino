#include <Arduino.h>

/*

TTP223

Параметры
╔════════════════╦═════════╗
║ Протокол       ║ GPIO    ║
╠════════════════╬═════════╣
║ Питание        ║ 3V3, 5V ║
╚════════════════╩═════════╝

Распиновка
╔═════╦═════╦═════╗
║ GND ║ I/O ║ VCC ║
╠═════╬═════╬═════╣
║ GND ║GPIO ║ 3V3 ║
╚═════╩═════╩═════╝

Перемычки
╔═════╦══════════════╦══════════════╗
║     ║     A=0      ║     A=1      ║
╠═════╬══════════════╬══════════════╣
║ B=0 ║ I/O = HIGH   ║ I/O = LOW    ║
║     ║ Без фиксации ║ Без фиксации ║
╠═════╬══════════════╬══════════════╣
║ B=1 ║ I/O = HIGH   ║ I/O = LOW    ║
║     ║ С фиксацией  ║ С фиксацией  ║
╚═════╩══════════════╩══════════════╝

https://kit.alexgyver.ru/tutorials/ttp223/
https://kit.alexgyver.ru/tutorials/button/

*/

// #define USE_GPIO

#ifdef USE_GPIO
gpio_num_t led_pin  = (gpio_num_t)LED_BUILTIN;
gpio_num_t btn_pin  = (gpio_num_t)32;

void IRAM_ATTR gpio_isr_handler(void* parameter) {
    int state = gpio_get_level(btn_pin);
    gpio_set_level(led_pin, state);
}

void setup() {
    gpio_install_isr_service(0);
    gpio_reset_pin(btn_pin);
    gpio_pad_select_gpio(btn_pin);
    gpio_set_direction(btn_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(btn_pin, GPIO_FLOATING); 
    gpio_set_intr_type(btn_pin, GPIO_INTR_ANYEDGE);
    gpio_intr_enable(btn_pin);
    gpio_isr_handler_add(btn_pin, gpio_isr_handler, nullptr);

    gpio_reset_pin(led_pin);
    gpio_pad_select_gpio(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
}

void loop(void) {
}

#else

#include "EncButton.h"

#define BTN_PIN 32
Button btn(BTN_PIN, INPUT_PULLDOWN, HIGH);

void cb() {
    // здесь EB_self - указатель на сам объект

    Serial.print("callback: ");
    switch (btn.action()) {
        case EB_PRESS:
            Serial.println("press");
            break;
        case EB_HOLD:
            Serial.println("hold");
            break;
        case EB_STEP:
            Serial.println("step");
            break;
        case EB_RELEASE:
            Serial.print("release. steps: ");
            Serial.print(btn.getSteps());
            Serial.print(", press for: ");
            Serial.print(btn.pressFor());
            Serial.print(", hold for: ");
            Serial.print(btn.holdFor());
            Serial.print(", step for: ");
            Serial.println(btn.stepFor());
            break;
        case EB_CLICK:
            Serial.println("click");
            break;
        case EB_CLICKS:
            Serial.print("clicks ");
            Serial.println(btn.getClicks());
            break;
        case EB_REL_HOLD:
            Serial.println("release hold");
            break;
        case EB_REL_HOLD_C:
            Serial.print("release hold clicks ");
            Serial.println(btn.getClicks());
            break;
        case EB_REL_STEP:
            Serial.println("release step");
            break;
        case EB_REL_STEP_C:
            Serial.print("release step clicks ");
            Serial.println(btn.getClicks());
            break;
        default:
            Serial.println();
    }
}

void setup() {
    Serial.begin(115200);

    btn.attach(cb);

    Serial.println("Start");
}

void loop() {
    btn.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
}
#endif