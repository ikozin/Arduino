#define RAW_DATA 1
#include <DHT.h>

/*
https://ru.aliexpress.com/popular/am2301-temperature-humidity-sensor.html

Adafruit Unified Sensor
DHT sensor library

 DATA VCC GND
 __|___|___|__
|             |
|   AM2301    |
|_____________|

*/
#define PIN_DHT  12

DHT dht(PIN_DHT, AM2301);
long temp = 0;
long hum = 0;

void setup()
{
  dht.begin();
  Serial.begin(9600);
  while (!Serial) {}  
  Serial.println(F("Start"));
}

void loop()
{
  delay(1000);
  float h = dht.readHumidity(false);
  float t = dht.readTemperature(false);
#ifdef RAW_DATA
  Serial.print(t);
  Serial.print(F("C, "));
  Serial.print(h);
  Serial.print(F("%"));
  Serial.println();
#else
  if (!isnan(h) && !isnan(t))
  {
    temp = lrint(t);
    hum = lrint(h);
    Serial.print(temp);
    Serial.print(F("C, "));
    Serial.print(hum);
    Serial.print(F("%"));
    Serial.println();
  }
#endif
}
