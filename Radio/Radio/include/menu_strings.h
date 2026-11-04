#pragma once

#include <Arduino.h>
#include <strings.h>

#define S_EXIT        F(menu_exit)  // "Выход"
#define S_SAVE        F(menu_save)  // "Сохранить"
#define S_BACK        F(mune_back)  // "Назад"

#define S_ALARM_MENU  F(menu_alarm)
#define S_DATE        F(menu_date)
#define S_TIME        F(mune_time)
#define S_ALARM       F(menu_alarm)
#define S_ON          F(menu_on)
#define S_ENABLE      F(menu_alarm)
#define S_VOICE       F(menu_voice_on)
#define S_MUTE        F(menu_voice_off)
#define S_MUTE_LABEL  F(menu_empty)
#define S_SEPARATOR   F("----------------")
#define S_RADIO       F(menu_radio)
#define S_MODE        F(menu_mode)

#define S_YEAR        F(menu_year)
#define S_MONTH       F(menu_month)
#define S_DAY         F(menu_day)
#define S_HOUR        F(menu_hour)
#define S_MINUTE      F(menu_minute)
#define S_SECOND      F(menu_second)
#define S_VOLUME      F(menu_volume)
#define S_STATION     F(menu_station)

#define S_MONDAY      F(menu_week_monday)
#define S_TUESDAY     F(menu_week_tuesday)
#define S_WEDNESDAY   F(menu_week_wednesday)
#define S_THURSDAY    F(menu_week_thursday)
#define S_FRIDAY      F(menu_week_friday)
#define S_SATURDAY    F(menu_week_saturday)
#define S_SUNDAY      F(menu_week_sunday)

// FlashString helper для getAlarmTitle
inline const __FlashStringHelper* getAlarmLabel(bool state, bool mode) {
    if (!state) return S_MUTE_LABEL;
    return mode ? S_VOICE : S_MUTE;
}
