#include "controllerAlarmClock.h"

ControllerAlarmClock ctrlAlarmClock;

ControllerAlarmClock::ControllerAlarmClock() : Controller("CtrlAlarmClock") {
    _radio = NULL;
    _timerCount = 0;
    for (_alarmClockCount = 0; _alarmClockCount < MAX_ALARMCLOCK_COUNT; _alarmClockCount ++) {
        if (_alarmClockList[_alarmClockCount].value == 0) break;
    }
}

void ControllerAlarmClock::attachControllerRadio(ControllerRadio* radio) {
    _radio = radio;
}

void ControllerAlarmClock::OnHandle() {
    for (uint32_t i = 0; i < _timerCount; i++) {
        xTimerStop(_timerList[i], 0);
        xTimerDelete(_timerList[i], 0);
    }
    for (uint32_t i = 0; i < _alarmClockCount; i++) {
        startTimer(i);    
    }
    vTaskDelete(_task);
}

void ControllerAlarmClock::startTimer(int index) {
    alarmClockItem_t alarm = _alarmClockList[index];
    // Serial.printf("\r\nstartTimer[%d]=0x%llX\r\n", index, alarm.value);
    TickType_t period = getTimerPeriod(&alarm);
    _timerList[index] = xTimerCreate("Timer", period, pdFALSE, (void*)index, timerCallback);
    xTimerStart(_timerList[index], 0);
}

void ControllerAlarmClock::timerCallback(TimerHandle_t pxTimer) {
    int32_t index = (int32_t)pvTimerGetTimerID(pxTimer);
    xTimerDelete(pxTimer, 0);
    alarmClockItem_t alarm = ctrlAlarmClock._alarmClockList[index];
    // Serial.printf("timerCallback[%d], alarm[%d]=0x%llX\r\n", index, index, alarm.value);
    if (ctrlAlarmClock._radio != NULL) {
        if (alarm.IsMute)       ctrlAlarmClock._radio->setMute(true);
        if (alarm.Index != -1)  ctrlAlarmClock._radio->setRadioIndex(alarm.Index);
        if (alarm.Volume != -1) ctrlAlarmClock._radio->setVolume(alarm.Volume);
        if (!alarm.IsMute)      ctrlAlarmClock._radio->setMute(false);
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
    time_t timer = time(NULL);
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
    // char text[64];
    // strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", localtime(&next));
    // Serial.printf("%s\r\n", text);
    return (next - timer) * 1000;
}
