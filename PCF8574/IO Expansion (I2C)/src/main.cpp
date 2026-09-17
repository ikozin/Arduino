// PCF8574A
// https://www.chipdip.ru/product/pcf8574an
// https://static.chipdip.ru/lib/368/DOC004368150.pdf

#include <Arduino.h>
#include <Wire.h>

#define  READ_DEMO
// #define  WRITE_DEMO

#ifdef READ_DEMO
#undef WRITE_DEMO
#endif
#ifdef WRITE_DEMO
#undef READ_DEMO
#endif

#define   ADDRESS_DEVICE        0x38
#define   INT_PIN               26
uint8_t data;
char    text[128];
volatile uint16_t counter = 0;
uint32_t last = 0;


void pinChanged(void) {
    if (millis() - last > 20) {
        counter++;
    }
    last = millis();
}

void setup() {
    pinMode(INT_PIN, INPUT_PULLUP);
    Wire.begin();
    Wire.beginTransmission(ADDRESS_DEVICE);
#ifdef READ_DEMO
    Wire.write(B11111111);
#endif
#ifdef WRITE_DEMO
    Wire.write(B00000000);
#endif
    Wire.endTransmission();
    attachInterrupt(INT_PIN, pinChanged, FALLING);

    Serial.begin(115200);
    Serial.println(F("Start"));
#ifdef READ_DEMO
    Serial.println(F("READ DEMO"));
#endif
#ifdef WRITE_DEMO
    Serial.println(F("WRITE DEMO"));
#endif
}

void loop() {
#ifdef WRITE_DEMO
    for (int i = 0; i < 8; i++) {
        delay(1000);
        data = bit(i);
        Wire.beginTransmission(ADDRESS_DEVICE);
        Wire.write(data);
        Wire.endTransmission();
        sprintf(text, "data=%02X, counter=%d", data, counter);
        Serial.println(text);
    }
#endif
#ifdef READ_DEMO
    delay(1000);
    Wire.requestFrom(ADDRESS_DEVICE, 1);
    data = Wire.read();
    sprintf(text, "data=%02X, counter=%d", data, counter);
    Serial.println(text);
#endif
}