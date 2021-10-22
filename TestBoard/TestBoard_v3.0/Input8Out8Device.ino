#include "Input8Out8Device.h"

char text[128];

void init_Input8Out8Dev(Input8Out8DevPin *pmap, size_t size) {
  for (size_t i = 0; i < size; i++) {

    for (int n = 0; n < 8; n++) {
      if (pmap->Input[n] == 0U) break;
      pinMode(pmap->Input[n], OUTPUT);
#ifdef DEBUG
      sprintf(text, "%d - OUTPUT ", pmap->Input[n]);
      Serial.print(text);
#endif
    }
    Serial.println();

    for (int n = 0; n < 8; n++) {
      if (pmap->Output[n] == 0U) break;
      pinMode(pmap->Output[n], INPUT_PULLUP);
#ifdef DEBUG
      sprintf(text, "%d - INPUT ", pmap->Output[n]);
      Serial.print(text);
#endif
    }
    Serial.println();
   
    pmap++;
  }
}

void done_Input8Out8Dev(void) {
  DDRA = B00000000;   // Set input mode
  DDRC = B00000000;   // Set input mode

  PORTA = B11111111;  // Set pullup mode
  PORTC = B11111111;  // Set pullup mode
}

int test_Input8Out8Dev(Input8Out8DevPin *pmap, Input8Out8DevVal *pvalue) {
#ifdef DEBUG
  Serial.println("\nInput:");
#endif
  for (int n = 0; n < 8; n++) {
    int pin = pmap->Input[n];
    if (pin == 0) break;
    int value = bitRead(pvalue->value, n);
#ifdef DEBUG
    sprintf(text, "%d = %d", pin, value);
    Serial.println(text);
#endif
    digitalWrite(pin, value);
  }
  
  delay(1);
#ifdef DEBUG
  Serial.println("Output:");
#endif
  int errorCount = 0;
  for (int n = 0; n < 8; n++) {
    int pin = pmap->Output[n];
    if (pin == 0) break;
    int result = digitalRead(pin);
    int expected = bitRead(pvalue->result, n);
    errorCount += (result != expected) ? 1 : 0;
#ifdef DEBUG
    sprintf(text, "%d = %d,%d", pin, result, expected);
    Serial.print(text);
    if (result != expected) Serial.print(" - ОШИБКА");
    Serial.println();
#endif
  }
  return errorCount;
}

void set_Input8Out8Dev(Input8Out8DevPin *pmap, size_t size, int value) {
  for (size_t i = 0; i < size; i++) {
    for (int n = 0; n < 8; n++) {
      if (pmap->Input[n] == 0) break;
      digitalWrite(pmap->Input[n], value);
    }
    pmap++;
  }
}

int check_Input8Out8Dev(Input8Out8DevPin *pmap, size_t map_size, Input8Out8DevVal *pvalue, size_t value_size) {
  int errorCount = 0;
#ifdef DEBUG
  Serial.println("----------");
#endif
  for (size_t i = 0; i < map_size; i++) {
    set_Input8Out8Dev(pmap, map_size, LOW);
    for (size_t n = 0; n < value_size; n++) {
      errorCount += test_Input8Out8Dev(&pmap[i], &pvalue[n]);
    }
  }
#ifdef DEBUG
  Serial.println("----------");
#endif
  for (size_t i = 0; i < map_size; i++) {
    set_Input8Out8Dev(pmap, map_size, HIGH);
    for (size_t n = 0; n < value_size; n++) {
      errorCount += test_Input8Out8Dev(&pmap[i], &pvalue[n]);
    }
  }
#ifdef DEBUG
  Serial.println("----------");
#endif
  return errorCount;
}
