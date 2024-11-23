#include "Radio.h"

void showSaveButtton()
{
	lcd.setCursor(6, 3);
	lcd.print(F("coxpa\xBD\xB8\xBF\xC4"));
}

boolean showDigitalEditor(char* text, int length, char space)
{
	bool result = false;
	int index = 0;
	int x = (lcdRows - length) >> 1;

	lcd.clear();
	lcd.setCursor(x, 1);
	lcd.print(text);
	showSaveButtton();
	lcd.setCursor(x, 1);
	lcd.blink();

	while (mode == MODE_SETTING)
	{
		delay(200);
		if (digitalRead(pinVolumeUp) == LOW)
		{
			if (index < 0 || index > length - 1)
			{
				result = true;
				break;
			}
			char c = text[index] - 1;
			c = constrain(c, '0', '9');
			text[index] = c;
			lcd.write(c);
			lcd.setCursor(x + index, 1);
		}
		if (digitalRead(pinVolumeDown) == LOW)
		{
			if (index < 0 || index > length - 1)
			{
				result = true;
				break;
			}
			char c = text[index] + 1;
			c = constrain(c, '0', '9');
			text[index] = c;
			lcd.write(c);
			lcd.setCursor(x + index, 1);
		}

		if (digitalRead(pinStationUp) == LOW)
		{
			index--;
			if (index < 0)
			{
				if (index == -1)
				{
					lcd.setCursor(6, 3);
					continue;
				}
				else index = 0;
			}
			else while (text[index] == space) index--;
			lcd.setCursor(x + index, 1);
		}
		if (digitalRead(pinStationDown) == LOW)
		{
			index++;
			if (index >= length)
			{
				if (index == length)
				{
					lcd.setCursor(6, 3);
					continue;
				}
				else index = length - 1;
			}
			else while (text[index] == space) index++;
			lcd.setCursor(x + index, 1);
		}
	}
	lcd.noBlink();
	return result;
}

boolean showWeekEditor(char* text)
{
	bool result = false;
	int index = 0;

	lcd.setCursor(0, 0);
	lcd.print(F("\xA8H BT CP \xABT \xA8T C\xA0 BC"));
	lcd.setCursor(0, 1);
	lcd.print(text);
	showSaveButtton();
    lcd.setCursor(0, 1);
	lcd.blink();

	while (mode == MODE_SETTING)
	{
		delay(200);
		if (digitalRead(pinVolumeUp) == LOW || digitalRead(pinVolumeDown) == LOW)
		{
			if (index < 0 || index > 19)
			{
				result = true;
				break;
			}
			char c = text[index] == ' ' ? '*' : ' ';
			text[index] = c;
			text[index + 1] = c;
			lcd.write(c);
			lcd.write(c);
			lcd.setCursor(index, 1);
		}

		if (digitalRead(pinStationUp) == LOW)
		{
			index -= 3;
			if (index < 0)
			{
				if (index == -3)
				{
					lcd.setCursor(6, 3);
					continue;
				}
				else index = 0;
			}
			lcd.setCursor(index, 1);
		}
		if (digitalRead(pinStationDown) == LOW)
		{
			index += 3;
			if (index > 18)
			{
				if (index == 21)
				{
					lcd.setCursor(6, 3);
					continue;
				}
				else index = 18;
			}
			lcd.setCursor(index, 1);
		}
	}
	lcd.noBlink();
	return result;
}

void showSettingsSelected(int selected)
{
	for (byte i = 0; i < 4; i++)
	{
		lcd.setCursor(0, i);
		lcd.write(0x20);
	}
	lcd.setCursor(0, selected);
	lcd.write('*');
}

void show_choice_list(byte actionCount, ActionInit pActionInit, ActionSelect pActionSelect1, ActionSelect pActionSelect2, ActionSelect pActionSelect3, ActionSelect pActionSelect4)
{
	int selected = 0;
	actionCount--;

	pActionInit(selected);
	while (mode == MODE_SETTING)
	{
		if (digitalRead(pinVolumeUp) == LOW)
		{
			selected++;
			selected = constrain(selected, 0, actionCount);
			showSettingsSelected(selected);
		}
		if (digitalRead(pinVolumeDown) == LOW)
		{
			selected--;
			selected = constrain(selected, 0, actionCount);
			showSettingsSelected(selected);
		}

		if (digitalRead(pinStationUp) == LOW || digitalRead(pinStationDown) == LOW)
		{
			switch (selected)
			{
			case 0:
				pActionSelect1();
				break;
			case 1:
				pActionSelect2();
				break;
			case 2:
				pActionSelect3();
				break;
			case 3:
				pActionSelect4();
				break;
			default:
				break;
			}
			mode = MODE_SETTING;
			pActionInit(selected);
		}
	}
}

void showSettingsInit(int selected)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(F(" \xA9""c\xBF""a\xBDo\xB3\xBA""a \xE3""a\xBF\xC3"));
	lcd.setCursor(0, 1);
	lcd.print(F(" \xA9""c\xBF""a\xBDo\xB3\xBA""a \xB3pe\xBC""e\xBD\xB8"));
	lcd.setCursor(0, 2);
	lcd.print(F(" Koppe\xBA\xE5\xB8\xC7 \xB3pe\xBC""e\xBD\xB8"));
	lcd.setCursor(0, 3);
	lcd.print(F(" \xA0y\xE3\xB8\xBB\xC4\xBD\xB8\xBA"));
	showSettingsSelected(selected);
}

void subselect_date()
{
	DateTime now = rtc.now();

	char text[16];
	int  length = sprintf(text, "%04d %02d %02d", now.year(), now.month(), now.day());
	if (showDigitalEditor(text, length, ' '))
	{
		int year = (text[0] - '0') * 1000 + (text[1] - '0') * 100 + (text[2] - '0') * 10 + (text[3] - '0');
		int month = (text[5] - '0') * 10 + (text[6] - '0');
		int day = (text[8] - '0') * 10 + (text[9] - '0');
		byte maxDays[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (year >= 1900 && year < 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
		{
			if (maxDays[month - 1] >= day)
			{
				if (month != 2)
				{
					now = rtc.now();
					rtc.adjust(DateTime(year, month, day, now.hour(), now.minute(), now.second()));
					return;
				}
				else
				{
					boolean isleap = ((year % 4 == 0 and year % 100 != 0) or (year % 400 == 0));
					if (isleap || (!isleap && day <= 28))
					{
						now = rtc.now();
						rtc.adjust(DateTime(year, month, day, now.hour(), now.minute(), now.second()));
						return;
					}
				}
			}
		}
		tone(TONE_PIN, notes[1], 500);
	}
}

void subselect_time()
{
	DateTime now = rtc.now();

	char text[16];
	int  length = sprintf(text, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
	if (showDigitalEditor(text, length, ':'))
	{
		int hour = (text[0] - '0') * 10 + (text[1] - '0');
		int minute = (text[3] - '0') * 10 + (text[4] - '0');
		int second = (text[6] - '0') * 10 + (text[7] - '0');
		if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
		{
			now = rtc.now();
			rtc.adjust(DateTime(now.year(), now.month(), now.day(), hour, minute, second));
			return;
		}
		tone(TONE_PIN, notes[1], 500);
	}
}

void subselect_correct()
{
	int x = 1;
	int selected = 0;
	char c = abs(corrSec) + '0';
	char sign = ' ';
	sign = (corrSec > 0) ? '+' : sign;
	sign = (corrSec < 0) ? '-' : sign;

	lcd.clear();

	lcd.setCursor(0, 1);
	lcd.print(F("Koppe\xBA\xE5\xB8\xC7 \xBD\x61:"));
	lcd.print(sign);
	lcd.print(c);
	lcd.print(F(" ce\xBA."));
	showSaveButtton();
	lcd.setCursor(10, 1);

	lcd.blink();

	while (mode == MODE_SETTING)
	{
		if (digitalRead(pinVolumeUp) == LOW)
		{
			selected++;
			selected = constrain(selected, 0, 1);
		}
		if (digitalRead(pinVolumeDown) == LOW)
		{
			selected--;
			selected = constrain(selected, 0, 1);
		}
		if (digitalRead(pinStationUp) == LOW)
		{
			if (selected == 0)
			{
				corrSec = constrain(corrSec - 1, -9, 9);
				c = abs(corrSec) + '0';
				sign = ' ';
				sign = (corrSec > 0) ? '+' : sign;
				sign = (corrSec < 0) ? '-' : sign;
				lcd.setCursor(13, 1);
				lcd.print(sign);
				lcd.write(c);
			}
			else
			{
				EEPROM.write(EEPROM_ADDR_CORRECTION_SEC, corrSec);
				break;
			}
		}
		if (digitalRead(pinStationDown) == LOW)
		{
			if (selected == 0)
			{
				corrSec = constrain(corrSec + 1, -9, 9);
				c = abs(corrSec) + '0';
				sign = ' ';
				sign = (corrSec > 0) ? '+' : sign;
				sign = (corrSec < 0) ? '-' : sign;
				lcd.setCursor(13, 1);
				lcd.print(sign);
				lcd.write(c);
			}
			else
			{
				EEPROM.write(EEPROM_ADDR_CORRECTION_SEC, corrSec);
				break;
			}
		}
		x = (selected == 0) ? 14 : 6;
		lcd.setCursor(x, (selected << 1) + 1);
		delay(200);
	}
	lcd.noBlink();
}

void showSettingsInitAlarmList(int selected, AlarmItem list[])
{
	char text[21];
	for (byte i = 0; i < 4; i++)
	{
		AlarmItem* pAlarmData = &list[i];
		lcd.setCursor(0, i);
		sprintf(text, "  %02d:%02d:%02d   %c%c%c%c%c%c%c",
			pAlarmData->hour,
			pAlarmData->minute,
			pAlarmData->second,
			pAlarmData->week & FLAG_MONDAY ? '\xFF' : ' ',
			pAlarmData->week & FLAG_TUESDAY ? '\xFF' : ' ',
			pAlarmData->week & FLAG_WEDNESDAY ? '\xFF' : ' ',
			pAlarmData->week & FLAG_THURSDAY ? '\xFF' : ' ',
			pAlarmData->week & FLAG_FRIDAY ? '\xFF' : ' ',
			pAlarmData->week & FLAG_SATURDAY ? '\xFF' : ' ',
			pAlarmData->week & FLAG_SUNDAY ? '\xFF' : ' '
		);
		lcd.print(text);
	}
	showSettingsSelected(selected);
}

void showSettingsInitAlarmType(int selected)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(F(" B\xBA\xBB\xC6\xC0\xB8\xBF\xC4"));
	lcd.setCursor(0, 1);
	lcd.print(F(" B\xC3\xBA\xBB\xC6\xC0\xB8\xBF\xC4"));
	showSettingsSelected(selected);
}

void subselect_alarm(uint16_t address, AlarmItem* pAlarmData)
{
	char text[16];
	int  length = sprintf(text, "%02d:%02d:%02d", pAlarmData->hour, pAlarmData->minute, pAlarmData->second);
	if (showDigitalEditor(text, length, ':'))
	{
		int hour = (text[0] - '0') * 10 + (text[1] - '0');
		int minute = (text[3] - '0') * 10 + (text[4] - '0');
		int second = (text[6] - '0') * 10 + (text[7] - '0');
		if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
		{
			char text[21] = "                    ";
			for (int i = 0; i < 7; i++)
				if (pAlarmData->week & (1 << i))
				{
					text[i * 3] = '*';
					text[i * 3 + 1] = '*';
				}
			if (showWeekEditor(text))
			{
				pAlarmData->week = 0;
				for (int i = 0; i < 7; i++)
					if (text[i * 3] == '*')
						pAlarmData->week |= (1 << i);

				pAlarmData->hour = hour;
				pAlarmData->minute = minute;
				pAlarmData->second = second;
				saveAlarmData(address, pAlarmData);
			}
			return;
		}
		tone(TONE_PIN, notes[1], 500);
	}
}

void showSettingsInitAlarmOn(int selected)
{
	showSettingsInitAlarmList(selected, alarmOn);
}

void select_alarm_on1()
{
	subselect_alarm(EEPROM_ADDR_ALARM_ON1, &alarmOn[0]);
}

void select_alarm_on2()
{
	subselect_alarm(EEPROM_ADDR_ALARM_ON2, &alarmOn[1]);
}

void select_alarm_on3()
{
	subselect_alarm(EEPROM_ADDR_ALARM_ON3, &alarmOn[2]);
}

void select_alarm_on4()
{
	subselect_alarm(EEPROM_ADDR_ALARM_ON4, &alarmOn[3]);
}

void select_alarm_list_on()
{
	show_choice_list(4, showSettingsInitAlarmOn, select_alarm_on1, select_alarm_on2, select_alarm_on3, select_alarm_on4);
}

void showSettingsInitAlarmOff(int selected)
{
	showSettingsInitAlarmList(selected, alarmOff);
}

void select_alarm_off1()
{
	subselect_alarm(EEPROM_ADDR_ALARM_OFF1, &alarmOff[0]);
}

void select_alarm_off2()
{
	subselect_alarm(EEPROM_ADDR_ALARM_OFF2, &alarmOff[1]);
}

void select_alarm_off3()
{
	subselect_alarm(EEPROM_ADDR_ALARM_OFF3, &alarmOff[2]);
}

void select_alarm_off4()
{
	subselect_alarm(EEPROM_ADDR_ALARM_OFF4, &alarmOff[3]);
}

void select_alarm_list_off()
{
	show_choice_list(4, showSettingsInitAlarmOff, select_alarm_off1, select_alarm_off2, select_alarm_off3, select_alarm_off4);
}

void subselect_alarm()
{
	// 0 - ��������
	// 1 - ���������
	show_choice_list(2, showSettingsInitAlarmType, select_alarm_list_on, select_alarm_list_off, NULL, NULL);
}

void loopSettings()
{
	// 0 - ��������� ����
	// 1 - ��������� �������
	// 2 - ��������� �������
	// 3 - ���������
	show_choice_list(4, showSettingsInit, subselect_date, subselect_time, subselect_correct, subselect_alarm);
}

void loadAlarmData(uint16_t address, AlarmItem* pAlarmData)
{
	pAlarmData->week = EEPROM.read(address++);
	pAlarmData->hour = EEPROM.read(address++);
	pAlarmData->minute = EEPROM.read(address++);
	pAlarmData->second = EEPROM.read(address);
}

void saveAlarmData(uint16_t address, AlarmItem* pAlarmData)
{
	EEPROM.write(address++, pAlarmData->week);
	EEPROM.write(address++, pAlarmData->hour);
	EEPROM.write(address++, pAlarmData->minute);
	EEPROM.write(address, pAlarmData->second);
}

