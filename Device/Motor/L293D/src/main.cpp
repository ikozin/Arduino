#include <Arduino.h>

#define L293D
//#define AF_SHIELD_V1

#define MOTOR_DC
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


#define O1L     (3)     //PWM
#define O2L     (5)     //PWM

#define O1R     (6)     //PWM
#define O2R     (9)     //PWM

GyverMotor2<GM2::PWM_PWM_POWER> motor1(O1L, O2L);
GyverMotor2<GM2::PWM_PWM_POWER> motor2(O1R, O2R);

void setup() {
    Serial.begin(115200);
    Serial.println("Motor TEST");

    pinMode(O1L, OUTPUT);   // IN1
    pinMode(O2L, OUTPUT);   // IN2
    pinMode(O1R, OUTPUT);   // EN3
    pinMode(O2R, OUTPUT);   // IN4
}

void loop() {
#ifdef MOTOR_DC
    
    Serial.println("DC FORWARD");
    motor1.runSpeed(80);
    motor2.runSpeed(80);
    delay(1000);

    Serial.println("DC STOP");
    motor1.stop();
    motor2.stop();
    delay(1000);

    Serial.println("DC LEFT");
    motor1.runSpeed(80);
    motor2.runSpeed(-80);
    delay(1000);

    Serial.println("DC STOP");
    motor1.stop();
    motor2.stop();
    delay(1000);

    Serial.println("DC RIGHT");
    motor1.runSpeed(-80);
    motor2.runSpeed(80);
    delay(2000);

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

