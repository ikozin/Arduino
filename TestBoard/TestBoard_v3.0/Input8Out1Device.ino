#include "Input8Out1Device.h"

char text[128];

void init_Input8Out1Dev(Input8Out1DevPin *pmap, size_t size) {
  for (size_t i = 0; i < size; i++) {
    for (int n = 0; n < 8; n++) {
      if (pmap->Input[n] == 0U) break;
      pinMode(pmap->Input[n], OUTPUT);
#ifdef DEBUG
      sprintf(text, "%d - OUTPUT ", pmap->Input[n]);
      Serial.print(text);
#endif
    }
    pinMode(pmap->Output, INPUT);
#ifdef DEBUG
    sprintf(text, ", %d - INPUT", pmap->Output);
    Serial.println(text);
#endif
    pmap++;
  }
}

void done_Input8Out1Dev(void) {
  DDRA = B00000000;   // Set input mode
  DDRC = B00000000;   // Set input mode

  PORTA = B11111111;  // Set pullup mode
  PORTC = B11111111;  // Set pullup mode
}

bool test_Input8Out1Dev(Input8Out1DevPin *pmap, Input8Out1DevVal *pvalue) {
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
  int result = digitalRead(pmap->Output);
  int expected = pvalue->Result;
#ifdef DEBUG
  sprintf(text, "Output:\n%d = %d,%d", pmap->Output, result, expected);
  Serial.print(text);
  if (result != expected) Serial.print(" - ОШИБКА");
  Serial.println();
#endif
  return result == expected;
}

void set_Input8Out1Dev(Input8Out1DevPin *pmap, size_t size, int value) {
  for (size_t i = 0; i < size; i++) {
    for (int n = 0; n < 8; n++) {
      if (pmap->Input[n] == 0) break;
      digitalWrite(pmap->Input[n], value);
    }
    pmap++;
  }
}

int check_Input8Out1Dev(Input8Out1DevPin *pmap, size_t map_size, Input8Out1DevVal *pvalue, size_t value_size) {
  int errorCode = 0;
  for (size_t i = 0; i < map_size; i++) {
    set_Input8Out1Dev(pmap, map_size, LOW);
    for (size_t n = 0; n < value_size; n++) {
      if (!test_Input8Out1Dev(&pmap[i], &pvalue[n])) {
        errorCode++;
      }
    }
  }
  for (size_t i = 0; i < map_size; i++) {
    set_Input8Out1Dev(pmap, map_size, HIGH);
    for (size_t n = 0; n < value_size; n++) {
      if (!test_Input8Out1Dev(&pmap[i], &pvalue[n])) {
        errorCode++;
      }
    }
  }
  return errorCode;
}
