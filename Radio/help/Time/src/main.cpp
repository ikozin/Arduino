#include <Arduino.h>
#include <StringN.h>
#include <GyverDS3231Min.h>

GyverDS3231Min  rtc;
String64 text;

void setup() {
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);

    Serial.println(F("Initialize Date/Time"));
    setStampZone(3);  // часовой пояс
    rtc.begin(&Wire);
    if (!rtc.isOK()) {
        rtc.setTime(2026, 5, 9, 19, 43, 0);
    }
}

void loop() {
    Datime now = rtc.getTime();
    text = "";
    if (now.day < 10) text += '0';
    text += now.day;
    text += '.';
    if (now.month < 10) text += '0';
    text += now.month;
    text += '.';
    text += now.year;
    text += ' ';
    if (now.hour < 10) text += ' ';
    text += now.hour;
    text += ':';
    if (now.minute < 10) text += '0';
    text += now.minute;
    text += ':';
    if (now.second < 10) text += '0';
    text += now.second;
    Serial.println(text.c_str());
    delay(1000);
}
