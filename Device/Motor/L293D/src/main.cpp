#include <Arduino.h>

#define L293D
//#define AF_SHIELD_V1

//#define MOTOR_DC
//#define MOTOR_SERVO

#ifdef L293D

#include <GyverMotor2.h>
/*
┌────────────────────────────────────────────────────┐
│                                                    │     
│                                          ┌───┐     │
│                                          │ * ├ VCC │
│ ┌─────┐                                  ├───┤     │              L293N
│ ┤  A- │                                  │ * ├ GND │
│ ├─────┤                                  ├───┤     │           ┌*───────┐
│ ┤  A+ │                                  │ * ├ IN1 │       EN1 ┤ 1   16 ├ VCC
│ ├─────┤                                  ├───┤     │       IN1 ┤ 2   15 ├ IN4
│ ┤  B- │                                  │ * ├ IN2 │       A-  ┤ 3   14 ├ B+
│ ├─────┤                                  ├───┤     │       GNG ┤ 4   13 ├ GND
│ ┤  B+ │                                  │ * ├ IN3 │       GND ┤ 5   12 ├ GND
│ ├─────┤                                  ├───┤     │       A+  ┤ 6   11 ├ B-
│ ┤ GND │                                  │ * ├ IN4 │       IN2 ┤ 7   10 ├ IN3
│ ├─────┤                                  ├───┤     │       VIN ┤ 8    9 ├ EN2
│ ┤ VIN │                                  │ * ├ EN1 │           └────────┘
│ └─────┘                                  ├───┤     │
│                                          │ * ├ EN2 │
│                                          └───┘     │
│                ┌───┬───┬───┬───┬───┬───┐           │
│                └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘           │
└────────────────────────────────────────────────────┘
*/

void setup() {
    Serial.begin(115200);
    Serial.println("Motor TEST");

    pinMode(3, OUTPUT); // EN1 (PWM)
    pinMode(2, OUTPUT); // IN1
    pinMode(4, OUTPUT); // IN2

    pinMode(6, OUTPUT);  // EN2
    pinMode(7, OUTPUT); // EN3
    pinMode(8, OUTPUT); // IN4
}

void loop() {
#ifdef MOTOR_DC
    Serial.println("DC FORWARD");
    
    motor.run(FORWARD);
    for (uint8_t i = 0; i < 255; i++) {
        motor.setSpeed(i);  
        delay(10);
    }
    for (uint8_t i = 255; i != 0; i--) {
        motor.setSpeed(i);  
        delay(10);
    }
  
    Serial.println("DC BACKWARD");
    motor.run(BACKWARD);
    for (uint8_t i = 0; i < 255; i++) {
        motor.setSpeed(i);  
        delay(10);
    }
    for (uint8_t i = 255; i != 0; i--) {
        motor.setSpeed(i);
        delay(10);
    }

    Serial.println("DC RELEASE");
    motor.run(RELEASE);
    delay(1000);
#endif
}
#endif

#ifdef AF_SHIELD_V1

#include <AFMotor.h>
#include <Servo.h>
/*
Adafruit Motor Shield L293D
https://роботехника18.рф/подключение-мотор-шилд-к-ардуино/

Arduino Uno не тянет сдиговый регистр
┌────────────────────────────────────────────────────────────────┐
│ ┌───┬───┬───┐                                                  │
│ │ - │ + │ S │ (D10)                                            │
│ └───┴───┴───┘                                                  │
│ ┌───┬───┬───┐                                                  │
│ │ - │ + │ S │ (D9)                                             │
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

#ifdef MOTOR_DC
AF_DCMotor motor(4);
#endif

#ifdef MOTOR_SERVO
#define SERVO_PIN   10  // or 9
Servo servo;
#endif

void setup() {
    Serial.begin(115200);
    Serial.println("Motor TEST");

#ifdef MOTOR_DC
    // turn on motor
    motor.setSpeed(20);
    motor.run(FORWARD);
#endif

#ifdef MOTOR_SERVO
    // turn on servo
    servo.attach(SERVO_PIN);
#endif
}

void loop() {
#ifdef MOTOR_DC
    Serial.println("DC FORWARD");
    motor.run(FORWARD);
    for (uint8_t i = 0; i < 255; i++) {
        motor.setSpeed(i);  
        delay(10);
    }
    for (uint8_t i = 255; i != 0; i--) {
        motor.setSpeed(i);  
        delay(10);
    }
  
    Serial.println("DC BACKWARD");
    motor.run(BACKWARD);
    for (uint8_t i = 0; i < 255; i++) {
        motor.setSpeed(i);  
        delay(10);
    }
    for (uint8_t i = 255; i != 0; i--) {
        motor.setSpeed(i);
        delay(10);
    }

    Serial.println("DC RELEASE");
    motor.run(RELEASE);
    delay(1000);
#endif

#ifdef MOTOR_SERVO
    Serial.println("SERVO");
    servo.write(0);
    delay(1000);
    servo.write(45);
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(135);
    delay(1000);
    servo.write(180);
    delay(1000);
#endif
}
#endif

