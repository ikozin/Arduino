#include <Wire.h>
/*
http://tixer.ru/catalog/modules/rtc-modules/chasy_r_v_rtc_na_ds1302/

*/
void setup()
{
  Serial.begin(9600);
  Serial.println(F("Start"));
  Wire.begin();
}

void loop()
{
  Serial.println(getDate());
  Serial.println(getTime());
  delay(5000);
}
