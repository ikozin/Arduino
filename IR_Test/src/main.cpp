#include <Arduino.h>
#define PIN 26

SemaphoreHandle_t updateEvent = xSemaphoreCreateBinary();

#define AlexGyver_NecDecoder
//#define Arduino_IRremote
//#define IR_ESP8266

#ifdef AlexGyver_NecDecoder
#include <NecDecoder.h>

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/freertos_idf.html#c.xSemaphoreCreateBinary

const int pinIR = PIN;
NecDecoder ir_recv;

IRAM_ATTR void ir_interrupt(void * param) {
    NecDecoder* reciver = reinterpret_cast<NecDecoder*>(param);
    reciver->tick();
    if (reciver->available()) {
        xSemaphoreGiveFromISR(updateEvent, nullptr);
    }
}

void setup() {
    Serial.begin(115200);
    attachInterruptArg(pinIR, ir_interrupt, &ir_recv, FALLING);
}

void loop() {
    xSemaphoreTake(updateEvent, portMAX_DELAY);      
    // выводим весь пакет (32 бита)
    Serial.print("0x");
    // Serial.println(ir_recv.readPacket(), HEX);
    // можно вывести только команду (8 бит)
    Serial.println(ir_recv.readCommand(), HEX);
}
#endif

#ifdef Arduino_IRremote

#define USE_CALLBACK_FOR_TINY_RECEIVER
#define IR_RECEIVE_PIN  PIN

#include "TinyIRReceiver.hpp" // include the code

void setup() {
    Serial.begin(115200);
    // Enables the interrupt generation on change of IR input signal
    if (!initPCIInterruptForTinyReceiver()) {
        Serial.println("No interrupt available for pin ");
        Serial.println(IR_RECEIVE_PIN);        
    }
}

void loop() {
    xSemaphoreTake(updateEvent, portMAX_DELAY);      
    if (TinyReceiverDecode()) {
        Serial.print("0x");
        Serial.print(TinyIRReceiverData.Command, HEX);
        if (TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT) {
            Serial.print(" Repeat");
        }
        Serial.println();
    }
}

#if defined(USE_CALLBACK_FOR_TINY_RECEIVER)
IRAM_ATTR void handleReceivedTinyIRData() {
    xSemaphoreGiveFromISR(updateEvent, nullptr);
}
#endif

#endif

#ifdef IR_ESP8266

#include <assert.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>

const uint16_t kRecvPin = PIN;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

#if DECODE_AC
// Some A/C units have gaps in their protocols of ~40ms. e.g. Kelvinator
// A value this large may swallow repeats of some protocols
const uint8_t kTimeout = 50;
#else   // DECODE_AC
// Suits most messages, while not swallowing many repeats.
const uint8_t kTimeout = 15;
#endif  // DECODE_AC

const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;  // kTolerance is normally 25%
#define LEGACY_TIMING_INFO false

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

void setup() {
    Serial.begin(kBaudRate);
    // Perform a low level sanity checks that the compiler performs bit field
    // packing as we expect and Endianness is as we expect.
    assert(irutils::lowLevelSanityCheck() == 0);
    Serial.printf("\n" D_STR_IRRECVDUMP_STARTUP "\n", kRecvPin);
#if DECODE_HASH
    // Ignore messages with less than minimum on or off pulses.
    irrecv.setUnknownThreshold(kMinUnknownSize);
#endif  // DECODE_HASH
    irrecv.setTolerance(kTolerancePercentage);  // Override the default tolerance.
    irrecv.enableIRIn();  // Start the receiver
}

// The repeating section of the code
void loop() {
  // Check if the IR code has been received.
  if (irrecv.decode(&results)) {
    // Display a crude timestamp.
    uint32_t now = millis();
    Serial.printf(D_STR_TIMESTAMP " : %06u.%03u\n", now / 1000, now % 1000);
    // Check if we got an IR message that was to big for our capture buffer.
    if (results.overflow)
      Serial.printf(D_WARN_BUFFERFULL "\n", kCaptureBufferSize);
    // Display the library version the message was captured with.
    Serial.println(D_STR_LIBRARY "   : v" _IRREMOTEESP8266_VERSION_STR "\n");
    // Display the tolerance percentage if it has been change from the default.
    if (kTolerancePercentage != kTolerance)
      Serial.printf(D_STR_TOLERANCE " : %d%%\n", kTolerancePercentage);
    // Display the basic output of what we found.
    Serial.print(resultToHumanReadableBasic(&results));
    // Display any extra A/C info if we have it.
    String description = IRAcUtils::resultAcToString(&results);
    if (description.length()) Serial.println(D_STR_MESGDESC ": " + description);
    yield();  // Feed the WDT as the text output can take a while to print.
#if LEGACY_TIMING_INFO
    // Output legacy RAW timing info of the result.
    Serial.println(resultToTimingInfo(&results));
    yield();  // Feed the WDT (again)
#endif  // LEGACY_TIMING_INFO
    // Output the results as source code
    Serial.println(resultToSourceCode(&results));
    Serial.println();    // Blank line between entries
    yield();             // Feed the WDT (again)
  }
}
#endif
