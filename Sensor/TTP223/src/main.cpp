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

#define BTN_PIN1    1
#define BTN_PIN2    3
#define BTN_PIN3    5
#define LED_PIN     48
// #define LED_PIN     LED_BUILTIN


#define LIB_USE_GPIO
// #define LIB_EncButton
// #define LIB_Button2

#ifdef LIB_USE_GPIO

gpio_num_t led_pin  = (gpio_num_t)LED_PIN;

int state = HIGH;

void IRAM_ATTR gpio_isr_handler(void* parameter) {
    gpio_set_level(led_pin, state);
    state = !state;
}

void setupPinHandler(gpio_num_t pin) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pin, GPIO_FLOATING); 
    gpio_set_intr_type(pin, GPIO_INTR_ANYEDGE);
    gpio_intr_enable(pin);
    gpio_isr_handler_add(pin, gpio_isr_handler, nullptr);
}

void setup() {
    gpio_install_isr_service(0);
#ifdef BTN_PIN1
    setupPinHandler((gpio_num_t)BTN_PIN1);
#endif
#ifdef BTN_PIN2
    setupPinHandler((gpio_num_t)BTN_PIN2);
#endif
#ifdef BTN_PIN3
    setupPinHandler((gpio_num_t)BTN_PIN3);
#endif

    gpio_reset_pin(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
}

void loop(void) {
}

#endif

#ifdef LIB_EncButton

#include "EncButton.h"

#ifdef BTN_PIN1
Button btn1(BTN_PIN1, INPUT_PULLDOWN, HIGH);
#endif
#ifdef BTN_PIN2
Button btn2(BTN_PIN2, INPUT_PULLDOWN, HIGH);
#endif
#ifdef BTN_PIN3
Button btn3(BTN_PIN3, INPUT_PULLDOWN, HIGH);
#endif

void showInfo(Button& btn) {
    Serial.print("pin = ");
    Serial.print(btn.getPin());
    Serial.print(", callback: ");
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
void cb() {
    // здесь EB_self - указатель на сам объект
#ifdef BTN_PIN1
    showInfo(btn1);
#endif
#ifdef BTN_PIN2
    showInfo(btn2);
#endif
#ifdef BTN_PIN3
    showInfo(btn3);
#endif
}

void setup() {
    Serial.begin(115200);

#ifdef BTN_PIN1
    btn1.attach(cb);
#endif
#ifdef BTN_PIN2
    btn2.attach(cb);
#endif
#ifdef BTN_PIN3
    btn3.attach(cb);
#endif

    Serial.println("Start");
}

void loop() {
#ifdef BTN_PIN1
    btn1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
#endif
#ifdef BTN_PIN2
    btn2.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
#endif
#ifdef BTN_PIN3
    btn3.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
#endif
}

#endif

#ifdef LIB_Button2

#include "Button2.h"

#ifdef BTN_PIN1
Button2 btn1 = Button2(BTN_PIN1, INPUT_PULLDOWN, false);
#endif
#ifdef BTN_PIN2
Button2 btn2 = Button2(BTN_PIN2, INPUT_PULLDOWN, false);
#endif
#ifdef BTN_PIN3
Button2 btn3 = Button2(BTN_PIN3, INPUT_PULLDOWN, false);
#endif
void btnEncoderClick(Button2& b);
void btnEncoderDoubleClick(Button2& b);
void btnEncoderLongClick(Button2& b);


void setup() {
    Serial.begin(115200);
    
#ifdef BTN_PIN1
    btn1.setClickHandler(btnEncoderClick);
    btn1.setDoubleClickHandler(btnEncoderDoubleClick);
    btn1.setLongClickTime(1000);
    btn1.setLongClickHandler(btnEncoderLongClick);  
#endif

#ifdef BTN_PIN2
    btn2.setClickHandler(btnEncoderClick);
    btn2.setDoubleClickHandler(btnEncoderDoubleClick);
    btn2.setLongClickTime(1000);
    btn2.setLongClickHandler(btnEncoderLongClick);  
#endif

#ifdef BTN_PIN3
    btn3.setClickHandler(btnEncoderClick);
    btn3.setDoubleClickHandler(btnEncoderDoubleClick);
    btn3.setLongClickTime(1000);
    btn3.setLongClickHandler(btnEncoderLongClick);  
#endif

    Serial.println("Start");
}


void loop() {
#ifdef BTN_PIN1
    btn1.loop();
#endif
#ifdef BTN_PIN2
    btn2.loop();
#endif
#ifdef BTN_PIN3
    btn3.loop();
#endif
}

void btnEncoderClick(Button2& b) {
    Serial.print("pin = ");
    Serial.print(b.getPin());
    Serial.println(",Click");
}

void btnEncoderDoubleClick(Button2& b) {
    Serial.print("pin = ");
    Serial.print(b.getPin());
    Serial.println(",DoubleClick");
}

void btnEncoderLongClick(Button2& b) {
    Serial.print("pin = ");
    Serial.print(b.getPin());
    Serial.println(",LongClick");
}

#endif
