TimerHandle_t timerList[MaxSettingsCount];
uint16_t timerCount = 0;

#if defined(DEBUG_CONSOLE)
char s[80] = { 0 };
#endif

uint8_t nextDay(uint8_t wday_mask, time_t* next) {
  wday_mask = (wday_mask << 1) & WEEK_MASK ;
  wday_mask = wday_mask ? wday_mask: 1;
  *next += 3600 * 24;
  return wday_mask;
}

TickType_t getTimerPeriod(alarm_t* pAlarm) {
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
#if defined(DEBUG_CONSOLE)
  strftime(s, 80, "%d.%m.%Y %H:%M:%S ", localtime(&next));
  debug_printf("%s\r\n", s);
#endif
  return (next - timer) * 1000;
}

void startTimer(int index) {
  debug_printf("StartTimer[%d]=", index);
  alarm_t alarm = settings[index];
  TickType_t period = getTimerPeriod(&alarm);
  timerList[index] = xTimerCreate("Timer", period, pdFALSE, (void*)index, timerCallback);
  xTimerStart(timerList[index], 0);
}

void timerCallback(TimerHandle_t pxTimer) {
  int32_t index = (int32_t)pvTimerGetTimerID(pxTimer);
  xTimerDelete(pxTimer, 0);
  alarm_t alarm = settings[index];
  debug_printf("timerCallback[%d], alarm[%d]=0x%llX\r\n", index, index, alarm.value);
  if (alarm.IsMute)   handleMute(true);
  if (alarm.Index != -1)  handleSetRadio(alarm.Index);
  if (alarm.Volume != -1) handleSetVolume(alarm.Volume);
  if (!alarm.IsMute)  handleMute(false);
  startTimer(index);
}

void setTimers(uint16_t count) {
  debug_printf("setTimer(%d)\r\n", count);
  for (uint32_t i = 0; i < timerCount; i++) {
    xTimerStop(timerList[i], 0);
    xTimerDelete(timerList[i], 0);
  }
  timerCount = count;
  for (uint32_t i = 0; i < timerCount; i++) {
    startTimer(i);    
  }  
}
