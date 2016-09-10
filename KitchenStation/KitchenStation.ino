#include <Wire.h>
#include "DHT.h"
#include "hd44780_I2Cexp.h"
#include "DS1302.h"
#include <SoftwareSerial.h>

DHT dht(4, AM2301);

// LCD geometry
const int LCD_ROWS = 4;
const int LCD_COLS = 20;

hd44780_I2Cexp lcd;

DS1302 rtc(A2, A1, A0);

char buffer[32];

// Для перехода в режим управления AT коммандами, необходимо при включении питания удерживать кнопку на bluetooth устройстве, держать до выключения индикатора
SoftwareSerial btSerial(9, 8);
// пароль по умолчанию для связи с устройстом:1234

void setup()
{
  pinMode(11, OUTPUT);  // EN
  pinMode(12, INPUT);   // STATE
  pinMode(13, OUTPUT);
  digitalWrite(11, HIGH);
#define AT_MODE
#ifdef AT_MODE
  Serial.begin(38400);//38400
  btSerial.begin(38400);//38400
#else
  Serial.begin(9600);
  btSerial.begin(9600);
#endif

  dht.begin();
  lcd.begin(LCD_COLS, LCD_ROWS);

  rtc.begin();

//#define SET_DATE_TIME_JUST_ONCE
#ifdef SET_DATE_TIME_JUST_ONCE  

  // Fill these variables with the date and time.
  int seconds, minutes, hours, dayofweek, dayofmonth, month, year;

  // Example for april 15, 2013, 10:08, monday is 2nd day of Week.
  // Set your own time and date in these variables.
  seconds    = 0;
  minutes    = 51;
  hours      = 20;
  dayofweek  = 5;  // Day of week, any day can be first, counts 1...7
  dayofmonth = 8; // Day of month, 1...31
  month      = 9;  // month 1...12
  year       = 2016;

  // Set a time and date
  // This also clears the CH (Clock Halt) bit, 
  // to start the clock.

  ds1302_struct rtc_data;
  // Fill the structure with zeros to make 
  // any unused bits zero
  memset ((char *) &rtc_data, 0, sizeof(rtc_data));

  rtc_data.Seconds    = bin2bcd_l( seconds);
  rtc_data.Seconds10  = bin2bcd_h( seconds);
  rtc_data.CH         = 0;      // 1 for Clock Halt, 0 to run;
  rtc_data.Minutes    = bin2bcd_l( minutes);
  rtc_data.Minutes10  = bin2bcd_h( minutes);
  // To use the 12 hour format,
  // use it like these four lines:
  //    rtc_data.h12.Hour   = bin2bcd_l( hours);
  //    rtc_data.h12.Hour10 = bin2bcd_h( hours);
  //    rtc_data.h12.AM_PM  = 0;     // AM = 0
  //    rtc_data.h12.hour_12_24 = 1; // 1 for 24 hour format
  rtc_data.h24.Hour   = bin2bcd_l( hours);
  rtc_data.h24.Hour10 = bin2bcd_h( hours);
  rtc_data.h24.hour_12_24 = 0; // 0 for 24 hour format
  rtc_data.Date       = bin2bcd_l( dayofmonth);
  rtc_data.Date10     = bin2bcd_h( dayofmonth);
  rtc_data.Month      = bin2bcd_l( month);
  rtc_data.Month10    = bin2bcd_h( month);
  rtc_data.Day        = dayofweek;
  rtc_data.Year       = bin2bcd_l( year - 2000);
  rtc_data.Year10     = bin2bcd_h( year - 2000);
  rtc_data.WP = 0;  

  // Write all clock data at once (burst mode).
  rtc.burst_write( (uint8_t *) &rtc_data);
#endif  
}

void loop()
{
/*
  digitalWrite(13, 0);
  digitalWrite(6, 1);
  delay(100);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  delay(100);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
  delay(100);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  delay(100);
  digitalWrite(9, 0);
  digitalWrite(10, 1);
  delay(100);
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  delay(100);
  digitalWrite(11, 0);
  digitalWrite(12, 1);
  delay(100);
  digitalWrite(12, 0);
  digitalWrite(13, 1);
  delay(50);
*/
  char recvChar;
  digitalWrite(13, digitalRead(12));
  if(Serial.available())
  {
    recvChar  = Serial.read();
    btSerial.write(recvChar);
    Serial.write(recvChar);
  }
  if(btSerial.available())
  {
    recvChar = btSerial.read();
    Serial.write(recvChar);
  }

  lcd.setCursor(0,0);
  lcd.print(dht.readTemperature());
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print(dht.readHumidity());
  lcd.print(" H");

  ds1302_struct rtc_data;
  // Read all clock data at once (burst mode).
  rtc.burst_read( (uint8_t *) &rtc_data);

  lcd.setCursor(0,2);
  sprintf( buffer, "%02d:%02d:%02d",
    bcd2bin( rtc_data.h24.Hour10, rtc_data.h24.Hour),
    bcd2bin( rtc_data.Minutes10, rtc_data.Minutes),
    bcd2bin( rtc_data.Seconds10, rtc_data.Seconds)
  );
  lcd.print(buffer);

  lcd.setCursor(0,3);
  sprintf(buffer, "%02d.%02d.%04d,W=%d",
    bcd2bin( rtc_data.Date10, rtc_data.Date),
    bcd2bin( rtc_data.Month10, rtc_data.Month),
    2000 + bcd2bin( rtc_data.Year10, rtc_data.Year),
    rtc_data.Day
  );
  lcd.print( buffer);
}
