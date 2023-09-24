//#define	LOG_CONSOLE

#ifndef ARDUINO_AVR_ATmega328P_BB8
	#error Select: board = ATmega328P BB 8Mhz
#endif

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <MsTimer2.h>
#include "LedDisplay.h"
#include "DS3231.h"

DS3231 ds3231;
DHT dht(7, AM2301);
LedSegmentDisplay led;
void updateInfo(void);

byte cnt = 0;
uint16_t time;
long temp = 0;
long hum = 0;

void setup() {
	// Initialize device.
#ifdef LOG_CONSOLE
	Serial.begin(57600);
	while (!Serial); // wait for serial port to connect. Needed for native USB
	Serial.println("Start");
#endif
	ds3231.begin();
	dht.begin();
	led.begin();

	MsTimer2::set(4, updateInfo); // 4ms period (5ms = 50Hz)
	MsTimer2::start();

  //ds3231.setDate(24, 9, 2023);  //day, month, year
  //ds3231.setTime(30, 23, 11);    //second, minute, hour
  //ds3231.setAgingOffset(0);
}

void updateInfo(void) {
	led.display();
}


void displayInfo() {
	if (cnt & 0x08) {
		if (cnt & 0x04) {
			led.setHumidity(hum);
		}
		else {
			led.setTemperature(temp);
		}
	}
	else {
		led.setTime(time);
	}
}

void loop() {
	time = ds3231.getTime();
	if (cnt & 0x04) {
		float h = dht.readHumidity();
		float t = dht.readTemperature();
		if (!isnan(h) && !isnan(t)) {
			temp = lrint(t);
			hum = lrint(h);
		}
	}

#ifdef LOG_CONSOLE
	Serial.println(time, HEX);
	Serial.print(ds3231.getTextDate());
	Serial.print(", ");
	Serial.print(ds3231.getTextTime());
	Serial.println();
	Serial.print(temp);
	Serial.println(" C");
	Serial.print(hum);
	Serial.println(" H");
#endif

	displayInfo();
	delay(500);
	cnt++;
}
