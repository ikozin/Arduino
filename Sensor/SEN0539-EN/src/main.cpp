#include <Arduino.h>
#include <DFRobot_DF2301Q.h>


//I2C communication
DFRobot_DF2301Q_I2C asr;

void setup() {
    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);    //Init LED pin to output mode
    digitalWrite(BUILTIN_LED, LOW);  //Set LED pin to low 

    // Init the sensor
    while (!(asr.begin())) {
        Serial.println("Communication with device failed, please check connection");
        delay(3000);
    }
    Serial.println("Begin ok!");
    
    asr.setVolume(4);
    asr.setMuteMode(0);
    asr.setWakeTime(20);

    uint8_t wakeTime = 0;
    wakeTime = asr.getWakeTime();
    Serial.print("wakeTime = ");
    Serial.println(wakeTime);
    
    //asr.playByCMDID(23);  // Command word ID
}

void loop() {
    uint8_t CMDID = asr.getCMDID();
    switch (CMDID) {
        case 103:                                                  //If the command is “Turn on the light”
            digitalWrite(BUILTIN_LED, HIGH);                                 //Turn on the LED
            Serial.println("received'Turn on the light',command flag'103'");  //Serial transmits "received"Turn on the light",command flag"103
            break;

        case 104:                                                  //If the command is “Turn off the light”
            digitalWrite(BUILTIN_LED, LOW);                                  //Turn off the LED
            Serial.println("received'Turn off the light',command flag'104'");  //The serial transmits "received"Turn off the light",command flag"104""
            break;

        default:
            if (CMDID != 0) {
                Serial.print("CMDID = ");  //Printing command ID
                Serial.println(CMDID);
            }
    }
    delay(300);
}
