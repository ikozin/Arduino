#include <Arduino.h>
#include "LiquidCrystal.h"
#include "pitches.h"

#ifndef __AVR_ATmega328P__
#error Select board "Arduino Pro or Pro Mini"
#endif

//#define DEBUG

#define BEEP_ON_START

//////////////////////////////////
// Board: "Arduino Pro or Pro Mini"
// UART: 57600
////////////////////////////////

#if defined(DEBUG)
#define debug_print(...)   Serial.print(__VA_ARGS__)
#define debug_println(...)   Serial.println(__VA_ARGS__)
#else
#define debug_print(...)
#define debug_println(...)
#endif

/*
Скетч использует 9912 байт (32%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 584 байт (28%) динамической памяти, оставляя 1464 байт для локальных переменных. Максимум: 2048 байт.

Скетч использует 9314 байт (30%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 582 байт (28%) динамической памяти, оставляя 1466 байт для локальных переменных. Максимум: 2048 байт.

Скетч использует 8520 байт (27%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 399 байт (19%) динамической памяти, оставляя 1649 байт для локальных переменных. Максимум: 2048 байт.

*/

LiquidCrystal lcd(0);  // 0 = I2C LCD address 0x20, 1 = I2C LCD address 0x21

#define BUZZER_PIN  8
int melody[] =   { 0, NOTE_A4, NOTE_D4, 0, NOTE_A4, NOTE_D4, 0, NOTE_A4, NOTE_D4 };
unsigned int duration[] = { 0, 200, 200, 1000, 200, 200, 1000, 200, 200 };
int currentNote;
unsigned long previousMelody;
#define MELODY_SIZE   (int)(sizeof(melody)/sizeof(melody[0]))

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
#ifdef DEBUG
  Serial.begin(57600);
  debug_println("\r\nStart...");
#endif

  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;
  attachInterrupt(0, tube_impulse, FALLING);

#ifdef BEEP_ON_START
  debug_println("Beep");
  tone(BUZZER_PIN, NOTE_E4, 100);
#endif

  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Start...");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.write(0xff);
    delay(900);
  }
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > LOG_PERIOD) {
    previousMillis = currentMillis;
    cpm = counts * multiplier;//
    usv = float(cpm) / 151;

    lcd.setCursor(0, 0);
    lcd.print("CPM=");
    lcd.print(cpm);
    lcd.print("  ");
    
    lcd.setCursor(0, 1);
    lcd.print(usv);
    lcd.print(" uSv/h  ");

    debug_print(F("Counts = "));
    debug_print(counts);
    debug_print(F(", CPM="));
    debug_print(cpm);
    debug_print(F(", "));
    debug_print(usv);
    debug_print(F(" uSv/h"));

    counts = 0;
    if (usv >= 10) {
      lcd.setCursor(9, 0);
      lcd.print("Danger!");
      debug_println(F(", Danger"));
      startPlay();
    }
    else if (usv < 10 && usv >= 0.52) {
      lcd.setCursor(10, 0);
      lcd.print("Unsafe");
      debug_println(F(", Unsafe"));
      startPlay();
    }
    else if (usv < 0.52) {
      lcd.setCursor(10, 0);
      lcd.print("Safety");
      debug_println(F(", Safety"));
      stopPlay();
    }
  }
  play();
}

void startPlay() {
  currentNote = 0;
  previousMelody = millis();
}

void stopPlay() {
  noTone(BUZZER_PIN);
  currentNote = -1;
  previousMelody = 0;
}

void play() {
  if (currentNote == -1) return;
  unsigned long currentMelody = millis();
  if (currentMelody - previousMelody > duration[currentNote]) {
    previousMelody = currentMelody;
    currentNote ++;
    if (currentNote >= MELODY_SIZE) currentNote = 0;
    int note = melody[currentNote];
    if (note == 0) noTone(BUZZER_PIN);
    else tone(BUZZER_PIN, note);    
  }
}
