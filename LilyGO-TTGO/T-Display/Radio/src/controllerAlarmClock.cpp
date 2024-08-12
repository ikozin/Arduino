#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "controllerAlarmClock.h"

ControllerAlarmClock ctrlAlarmClock = ControllerAlarmClock("ctrlAlarm");

ControllerAlarmClock::ControllerAlarmClock(const char* name):
                        ControllerT(name, nullptr) {
    _alarmClockCount = 0;
    _timerList = nullptr;
    _alarmClockList = nullptr;
}

InitResponse_t ControllerAlarmClock::OnInit() {
    return OnInitResultStart;
}

IterationCode_t ControllerAlarmClock::OnIteration() {
    File f = SPIFFS.open(FS_ALARMLIST_FILE);
    if (f) {
        DynamicJsonDocument  doc(2048);
        DeserializationError error = deserializeJson(doc, f);
        if (error) {
            LOGN("Failed to read file, using default configuration");
        }
        else {
            JsonArray array = doc.as<JsonArray>();
            if (array.size() <= 16) {
                _alarmClockCount = array.size();
                _timerList = new TimerHandle_t[_alarmClockCount];
                _alarmClockList = new alarmClockItem_t[_alarmClockCount];

                for (int i = 0; i < _alarmClockCount; i++) {
                    JsonObject object = array[i].as<JsonObject>();
                    _timerList[i] = nullptr;

                    _alarmClockList[i].value = 0;
                    _alarmClockList[i].Hour = object["Hour"].as<int>();
                    _alarmClockList[i].Minute = object["Minute"].as<int>();
                    _alarmClockList[i].IsMute = object["Mute"].as<int>();
                    _alarmClockList[i].Volume = object["Volume"].as<int>();
                    _alarmClockList[i].Index = object["Index"].as<int>();

                    _alarmClockList[i].Monday = object["Mo"].as<int>();
                    _alarmClockList[i].Tuesday= object["Tu"].as<int>();
                    _alarmClockList[i].Wednesday = object["We"].as<int>();
                    _alarmClockList[i].Thursday = object["Th"].as<int>();
                    _alarmClockList[i].Friday = object["Fr"].as<int>();
                    _alarmClockList[i].Saturday = object["Sa"].as<int>();
                    _alarmClockList[i].Sunday = object["Su"].as<int>();
                }
            }
        }
        f.close();
    }
    for (int i = 0; i < _alarmClockCount; i++) {
        startTimer(i);    
    }
    return IterationCode_t::Stop;
}

void ControllerAlarmClock::startTimer(int index) {
    alarmClockItem_t alarm = _alarmClockList[index];
    LOGN("%s::startTimer [%d]=0x%llX", _name, index, alarm.value);
    TickType_t period = getTimerPeriod(&alarm);
    _timerList[index] = xTimerCreate("Timer", period, pdFALSE, reinterpret_cast<void *>(index), timerCallback);
    xTimerStart(_timerList[index], 0);
}

void ControllerAlarmClock::timerCallback(TimerHandle_t pxTimer) {
    int32_t index = (int32_t)pvTimerGetTimerID(pxTimer);
    xTimerDelete(pxTimer, 0);
    alarmClockItem_t alarm = ctrlAlarmClock._alarmClockList[index];
    LOGN("timerCallback [%d], alarm[%d]=0x%llX", index, index, alarm.value);
    if (ctrlAlarmClock._controller != nullptr) {
        if (alarm.IsMute)       ctrlAlarmClock._controller->setMute(true);
        if (alarm.Index != -1)  ctrlAlarmClock._controller->setRadioIndex(alarm.Index);
        if (alarm.Volume != -1) ctrlAlarmClock._controller->setVolume(alarm.Volume);
        if (!alarm.IsMute)      ctrlAlarmClock._controller->setMute(false);
    }
    ctrlAlarmClock.startTimer(index);
}

uint8_t ControllerAlarmClock::nextDay(uint8_t wday_mask, time_t* next) {
    wday_mask = (wday_mask << 1) & WEEK_MASK ;
    wday_mask = wday_mask ? wday_mask: 1;
    *next += 3600 * 24;
    return wday_mask;
}

TickType_t ControllerAlarmClock::getTimerPeriod(alarmClockItem_t* pAlarm) {
    time_t timer = time(nullptr);
    struct tm* t = localtime(&timer);
    t->tm_sec  = 0;
    t->tm_min  = pAlarm->Minute;
    t->tm_hour = pAlarm->Hour;
    time_t next = mktime(t);

    uint8_t days = pAlarm->value & WEEK_MASK;
    uint8_t wday_mask = 1 << (t->tm_wday ? t->tm_wday - 1 : 6);
    while (!(days & wday_mask)) {
        wday_mask = nextDay(wday_mask, &next);
    }
    if (next <= timer) {
        wday_mask = nextDay(wday_mask, &next);
        while (!(days & wday_mask)) {
            wday_mask = nextDay(wday_mask, &next);
        }
    }
#ifdef DEBUG_CONSOLE
    char text[64];
    strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", localtime(&next));
    Serial.printf("%s::getTimerPeriod %s\r\n", _name, text);
#endif
    return (next - timer) * 1000;
}
