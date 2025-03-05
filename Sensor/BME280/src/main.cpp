#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BME680.h>
#include <bme68xLibrary.h>
#include <GyverBME280.h>

GyverBME280 bme;

void setup() {
    Serial.begin(115200);
    while(!Serial)  delay(1000);
    Serial.println("Start");

    bool status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        while (true) delay(1000);
    }
    Serial.println();
}

void loop() {
    Serial.print("Temperature: ");
    Serial.print(bme.readTemperature());        // Выводим темперутуру в [*C]
    Serial.println(" *C");
  
    Serial.print("Humidity: ");
    Serial.print(bme.readHumidity());           // Выводим влажность в [%]
    Serial.println(" %");
  
    float pressure = bme.readPressure();        // Читаем давление в [Па]
    Serial.print("Pressure: ");
    Serial.print(pressure / 100.0F);            // Выводим давление в [гПа]
    Serial.print(" hPa , ");
    Serial.print(pressureToMmHg(pressure));     // Выводим давление в [мм рт. столба]
    Serial.println(" mm Hg");
    Serial.print("Altitide: ");
    Serial.print(pressureToAltitude(pressure)); // Выводим высоту в [м над ур. моря]
    Serial.println(" m");
    Serial.println("");
    delay(1000);
}
