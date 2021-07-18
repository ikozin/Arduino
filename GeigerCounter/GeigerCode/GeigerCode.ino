#include "LiquidCrystal.h"

LiquidCrystal lcd(0);  // 0 = I2C LCD address 0x20, 1 = I2C LCD address 0x21

#define LOG_PERIOD 15000  
#define MAX_PERIOD 60000  

volatile unsigned long counts;
unsigned long cpm;
unsigned int multiplier;
unsigned long previousMillis;
float usv;

void tube_impulse() {
  counts++;
}

void setup() {
  Serial.begin(9600);

  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;
  attachInterrupt(0, tube_impulse, FALLING);

  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Start...");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.write(0xff);
    delay(250);
  }
}

void loop() {
  Serial.println(counts);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > LOG_PERIOD) {
    previousMillis = currentMillis;
    cpm = counts * multiplier;//
    usv = float(cpm) / 151;
    lcd.clear();
    lcd.print("CPM=");
    lcd.print(cpm);
    lcd.setCursor(0, 1);
    lcd.print(usv);
    lcd.print(" uSv/h");
    counts = 0;
    if (usv >= 10)
    {
      lcd.setCursor(9, 0);
      lcd.print("Danger!");
      delay(0.1);
    }
    else if (usv < 10 && usv >= 0.52)
    {
      lcd.setCursor(10, 0);
      lcd.print("Unsafe");
      delay(0.1);
    }
    else if (usv < 0.52)
    {
      lcd.setCursor(10, 0);
      lcd.print("Safety");
      delay(0.1);
    }
  }
}
