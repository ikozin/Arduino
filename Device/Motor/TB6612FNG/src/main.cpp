#include <Arduino.h>
#include <SparkFun_TB6612.h>
/*
┌─────────────────────────────────────────┐
│      ┌───┐                   ┌───┐      │
│   VM ┤   │                   │   ├ PWMA │
│      ├───┤                   ├───┤      │
│  VCC ┤   │                   │   ├ AIN2 │
│      ├───┤                   ├───┤      │
│  GND ┤   │                   │   ├ AIN1 │
│      ├───┤                   ├───┤      │
│  AO1 ┤   │                   │   ├ STBY │
│      ├───┤                   ├───┤      │
│  AO2 ┤   │                   │   ├ BIN1 │
│      ├───┤                   ├───┤      │
│  BO2 ┤   │                   │   ├ BIN2 │
│      ├───┤                   ├───┤      │
│  BO1 ┤   │                   │   ├ PWMB │
│      ├───┤                   ├───┤      │
│  GND ┤   │                   │   ├ GND  │
│      └───┘                   └───┘      │
└─────────────────────────────────────────┘
*/

#define AIN1 2
#define AIN2 4
#define PWMA 3

#define BIN1 7
#define BIN2 8
#define PWMB 6

#define STBY 9

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
    Serial.begin(115200);
}

void loop() {
    //Use of the drive function which takes as arguements the speed
    //and optional duration.  A negative speed will cause it to go
    //backwards.  Speed can be from -255 to 255.  Also use of the 
    //brake function which takes no arguements.
    motor1.drive(255, 1000);
    motor1.drive(-255, 1000);
    motor1.brake();
    delay(1000);

    //Use of the drive function which takes as arguements the speed
    //and optional duration.  A negative speed will cause it to go
    //backwards.  Speed can be from -255 to 255.  Also use of the 
    //brake function which takes no arguements.
    motor2.drive(255, 1000);
    motor2.drive(-255, 1000);
    motor2.brake();
    delay(1000);

    //Use of the forward function, which takes as arguements two motors
    //and optionally a speed.  If a negative number is used for speed
    //it will go backwards
    forward(motor1, motor2, 150);
    delay(1000);

    //Use of the back function, which takes as arguments two motors 
    //and optionally a speed.  Either a positive number or a negative
    //number for speed will cause it to go backwards
    back(motor1, motor2, -150);
    delay(1000);

    //Use of the brake function which takes as arguments two motors.
    //Note that functions do not stop motors on their own.
    brake(motor1, motor2);
    delay(1000);

    //Use of the left and right functions which take as arguements two
    //motors and a speed.  This function turns both motors to move in 
    //the appropriate direction.  For turning a single motor use drive.
    left(motor1, motor2, 100);
    delay(1000);
    right(motor1, motor2, 100);
    delay(1000);

    //Use of brake again.
    brake(motor1, motor2);
    delay(1000);
 }
