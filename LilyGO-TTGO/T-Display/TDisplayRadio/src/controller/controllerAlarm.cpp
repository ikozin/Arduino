#include "controller/controllerAlarm.h"
#include "controller/storageAlarm.h"
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

ControllerAlarm::ControllerAlarm(const char* name, StorageAlarm* storage):
                        Controller(name, portMAX_DELAY) {
    _storage = storage;
    _radio = nullptr;
}

bool ControllerAlarm::OnInit() {
    if (!_storage->load()) return false;
    for (int i = 0; i < _storage->GetSize(); i++) {
        alarmBlock_t* block = &_storage->GetData()[i];
        startTimer(block);
    }
    return true;
}

void ControllerAlarm::startTimer(alarmBlock_t* block) {
    LOGN("%s::startTimer 0x%016llX (%02d:%02d, Buzzer=%d, Index=%d, Volume=%d, Mute=%d)", _name, block->alarm.value, block->alarm.Hour, block->alarm.Minute, block->alarm.Buzzer, block->alarm.Index, block->alarm.Volume, block->alarm.IsMute);
    TickType_t period = getTimerPeriod(block);
    block->controller = this;
    block->timer = xTimerCreate("Timer", period, pdFALSE, reinterpret_cast<void *>(block), timerCallback);
    xTimerStart(block->timer, 0);
}

void ControllerAlarm::timerCallback(TimerHandle_t pxTimer) {
    alarmBlock_t* block = (alarmBlock_t*)pvTimerGetTimerID(pxTimer);
    xTimerDelete(pxTimer, 0);
    alarmItem_t alarm = block->alarm;
    LOGN("timerCallback 0x%016llX", alarm.value);
    ControllerAlarm* controller = static_cast<ControllerAlarm*>(block->controller);
    if (controller->_radio != nullptr) {
        if (alarm.IsMute)       controller->_radio->setMute(true);
        if (alarm.Index != -1)  controller->_radio->setRadioIndex(alarm.Index);
        if (alarm.Volume != -1) controller->_radio->setVolume(alarm.Volume);
        if (!alarm.IsMute)      controller->_radio->setMute(false);
    }
    controller->startTimer(block);
}

uint8_t ControllerAlarm::nextDay(uint8_t wday_mask, time_t* next) {
    wday_mask = (wday_mask << 1) & WEEK_MASK ;
    wday_mask = wday_mask ? wday_mask: 1;
    *next += 3600 * 24;
    return wday_mask;
}

TickType_t ControllerAlarm::getTimerPeriod(alarmBlock_t* block) {
    time_t timer = time(nullptr);
    struct tm* t = localtime(&timer);
    t->tm_sec  = 0;
    t->tm_min  = block->alarm.Minute;
    t->tm_hour = block->alarm.Hour;
    time_t next = mktime(t);

    uint8_t days = block->alarm.value & WEEK_MASK;
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
