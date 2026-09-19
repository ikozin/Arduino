#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

/*


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

*/


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x40);
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// And connect a DC motor to port M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);


void setup() {
    Serial.begin(115200);
    Serial.println("Start");

    if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
        Serial.println("Could not find Motor Shield. Check wiring.");
        while (1);
    }
    Serial.println("Motor Shield found.");

    // turn on motor M1
    motor1->setSpeed(200);
    motor1->run(RELEASE);
}

int i;
void loop() {
    motor1->run(RELEASE);
    motor1->setSpeed(250);
    motor1->run(FORWARD);
    delay(1000);
    motor1->setSpeed(100);
    delay(1000);
    motor1->run(RELEASE);
    motor1->setSpeed(250);
    motor1->run(BACKWARD);
    delay(1000); 
    motor1->setSpeed(100);
    delay(1000);
}
