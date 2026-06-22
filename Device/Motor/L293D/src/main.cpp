#include <Arduino.h>
#include <AFMotor.h>
/*
Adafruit Motor Shield L293D
https://роботехника18.рф/подключение-мотор-шилд-к-ардуино/

┌────────────────────────────────────────────────────────────────┐
│ ┌───┬───┬───┐                                                  │
│ │ - │ + │ S │                                                  │
│ └───┴───┴───┘                                                  │
│ ┌───┬───┬───┐                                                  │
│ │ - │ + │ S │                                                  │
│ └───┴───┴───┘                                                  │
│                                                     ┌───┐      │
│                                                     │   ├   M4 │
│     ┌───┐                                           ├───┤      │
│ M1  ┤   │                                           │   ├   M4 │
│     ├───┤                                           ├───┤      │
│ M1  ┤   │                                           │   ├  GND │
│     ├───┤                                           ├───┤      │
│ GND ┤   │                                           │   ├   M3 │
│     ├───┤                                           ├───┤      │
│ M2  ┤   │                                           │   ├   M3 │
│     ├───┤                                           └───┘      │
│ M2  ┤   │                                                      │
│     └───┘  6-12V                                               │
│          ┌───┬───┐                                             │
│          │ + │ - │                                             │
│          └─┬─┴─┬─┘                                             │
│                                                                │
└────────────────────────────────────────────────────────────────┘

*/

AF_DCMotor motor1(1);
AF_DCMotor motor2(3);

void setup() {
    Serial.begin(115200);
    Serial.println("Motor test!");
    // turn on motor
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
}

void loop() {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    for (uint8_t i = 0; i < 255; i++) {
        motor1.setSpeed(i);  
        motor2.setSpeed(i);  
        delay(10);
    }
     for (uint8_t i = 255; i != 0; i--) {
        motor1.setSpeed(i);  
        motor2.setSpeed(i);  
        delay(10);
    }
  
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    for (uint8_t i = 0; i < 255; i++) {
        motor1.setSpeed(i);  
        motor2.setSpeed(i);  
        delay(10);
    }
    for (uint8_t i = 255; i != 0; i--) {
        motor1.setSpeed(i);
        motor2.setSpeed(i);
        delay(10);
    }

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(1000);
}
