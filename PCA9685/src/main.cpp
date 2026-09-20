#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

/*
Adafruit Motor Shield v2 for arduino (TB6612FNG)

  ┌───────────────────────────────────┐
  │                                   │
  │                              ┌────┤
  │                              │ 15 ├─
  │                              ├────┤
  │                              │ 14 ├─
  │                              ├────┤
  │                              │ 13 ├─ PWMB ─┐
  │                              ├────┤        │
  │                              │ 12 ├─ BIN2 ─┤
  │                              └────┤        ├ ─ Motor 1
  │                                   │        │
  │                              ┌────┤        │
  │                              │ 11 ├─ BIN1 ─┘
  │                              ├────┤
  │                              │ 10 ├─ AIN1 ─┐
  │                              ├────┤        │
  │                              │  9 ├─ AIN2 ─┼─ Motor 0
  │                              ├────┤        │
  │                              │  8 ├─ PWMA ─┘
  │                              └────┤
  │                                   │
  │                              ┌────┤
  │                              │  7 ├─ PWMB ─┐
  │                              ├────┤        │
  │                              │  6 ├─ BIN2 ─┼─ Motor 3
  │                              ├────┤        │
  │                              │  5 ├─ BIN1 ─┘
  │                              ├────┤
  │                              │  4 ├─ AIN1 ─┐
  │                              └────┤        │
  │                                   │        │
  │                              ┌────┤        ├─ Motor 2
  │                              │  3 ├─ AIN2 ─┤
  │                              ├────┤        │
  │                              │  2 ├─ PWMA ─┘
  │                              ├────┤
  │                              │  1 ├─
  │                              ├────┤
  │                              │  0 ├─
  │                              └────┤
  │                                   │
  ├─────┬─────┬─────┬─────┬─────┬─────┤
  │ GND │  OE │ SCL │ SDA │ VCC │  V+ │
  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┘
     │     │     │     │     │     │
    GND   GND    A5    A4   +5V   VBAT


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
│                ┌───┬───┬───┬───┬───┐               │
│                │VCC│ A-│ A+│ B-│ B+│               │     
│                └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘               │
└────────────────────────────────────────────────────┘

*/


Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x40);
Adafruit_DCMotor *motor = AFMS.getMotor(2);

void setup() {
    Serial.begin(115200);
    Serial.println("Start");

    // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
    // some i2c devices dont like this so much so if you're sharing the bus, watch
    // out for this!
    Wire.setClock(400000);

    if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
        Serial.println("Could not find Motor Shield. Check wiring.");
        while (1);
    }
    Serial.println("Motor Shield found.");

    motor->setSpeed(200);
    motor->run(RELEASE);
}

void loop() {
    motor->run(RELEASE);
    motor->setSpeed(250);
    motor->run(FORWARD);
    delay(1000);
    motor->setSpeed(100);
    delay(1000);

    motor->run(RELEASE);
    motor->setSpeed(250);
    motor->run(BACKWARD);
    delay(1000); 
    motor->setSpeed(100);
    delay(1000);
}
