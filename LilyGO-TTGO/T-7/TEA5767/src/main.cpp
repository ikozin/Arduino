#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>

/// The band that will be tuned by this sketch is FM.
#define FIX_BAND RADIO_BAND_FM

/// The station that will be tuned by this sketch is 89.30 MHz.
#define FIX_STATION 10180

TEA5767 radio;
////////////////
// BUS -> GND //
////////////////

/// Setup a FM only radio configuration
/// with some debugging on the Serial port
void setup() {
    // open the Serial port
    Serial.begin(115200);
    Serial.println("Radio...");
    delay(200);

    // Initialize the Radio 
    radio.init();

    // Enable information to the Serial port
    radio.debugEnable();

    // HERE: adjust the frequency to a local sender
    radio.setBandFrequency(FIX_BAND, FIX_STATION); // hr3 nearby Frankfurt in Germany
    radio.setVolume(2);
    radio.setMono(false);
} // setup


/// show the current chip data every 3 seconds.
void loop() {
    char s[12];
    radio.formatFrequency(s, sizeof(s));
    Serial.print("Station:"); 
    Serial.println(s);

    Serial.print("Radio:"); 
    radio.debugRadioInfo();

    Serial.print("Audio:"); 
    radio.debugAudioInfo();

    delay(3000);
} // loop
