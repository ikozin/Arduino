#include <Arduino.h>

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#undef IR_RECEIVE_PIN
#define IR_RECEIVE_PIN  13

#define DECODE_NEC
#define SEND_PWM_BY_TIMER
#define NO_LED_FEEDBACK_CODE	

// #if !defined(RAW_BUFFER_LENGTH)
// // For air condition remotes it may require up to 750. Default is 200.
// #  if !((defined(RAMEND) && RAMEND <= 0x4FF) || (defined(RAMSIZE) && RAMSIZE < 0x4FF))
// #define RAW_BUFFER_LENGTH  730 // this allows usage of 16 bit raw buffer, for RECORD_GAP_MICROS > 20000
// #  endif
// #endif

/*
 * MARK_EXCESS_MICROS is subtracted from all marks and added to all spaces before decoding,
 * to compensate for the signal forming of different IR receiver modules. See also IRremote.hpp line 142.
 *
 * You can change this value accordingly to the receiver module you use.
 * The required value can be derived from the timings printed here.
 * Keep in mind that the timings may change with the distance
 * between sender and receiver as well as with the ambient light intensity.
 */
#define MARK_EXCESS_MICROS    20    // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.

//#define RECORD_GAP_MICROS 12000 // Default is 8000. Activate it for some LG air conditioner protocols
//#define DEBUG // Activate this for lots of lovely debug output from the decoders.

#include <IRremote.hpp>

//+=============================================================================
// Configure the Arduino
//
void setup() {
    Serial.begin(115200);   // Status message will be sent to PC at 9600 baud
    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

//+=============================================================================
// The repeating section of the code
//
void loop() {
    if (IrReceiver.decode()) {  // Grab an IR code
        // At 115200 baud, printing takes 200 ms for NEC protocol and 70 ms for NEC repeat
        IrReceiver.printIRResultShort(&Serial);
        // Check if the buffer overflowed
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            Serial.println(F("Try to increase the \"RAW_BUFFER_LENGTH\" value of " STR(RAW_BUFFER_LENGTH) " in " __FILE__));
            // see also https://github.com/Arduino-IRremote/Arduino-IRremote#compile-options--macros-for-this-library
        } else {
            if (IrReceiver.decodedIRData.protocol == NEC) {
                IrReceiver.printIRResultAsCVariables(&Serial);  // Output address and data as source code variables
            }
            else Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        }
        IrReceiver.resume();                            // Prepare for the next IR frame
    }
}
