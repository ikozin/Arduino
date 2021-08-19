byte ln12358_in_data[]      = { B00000000, B00111111 };
byte ln12358_out_data[]     = { B00111111, B00000000 };
TemplCheckLogic ln12358     = { 2, .in_mask = B00111111, B00111111, .in_data = ln12358_in_data, ln12358_out_data };

void info_1533ln12358(void) {
  Serial.println(F("КР1533ЛН1                            "));
  Serial.println(F("КР1533ЛН2  - открытый коллектор      "));
  Serial.println(F("КР1533ЛН3  - открытый коллектор      "));
  Serial.println(F("КР1533ЛН5  - открытый коллектор      "));
  Serial.println(F("КР1533ЛН8  - повышеннаая нагрузка    "));
  Serial.println(F("6 элементов НЕ                        "));
  Serial.println(F("DIP14                                "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("PA0(22) <-> 1 -|     o- 2 <-> PC0(37)"));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("PA1(23) <-> 3 -|     o- 4 <-> PC1(36)"));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("PA2(24) <-> 5 -|     o- 6 <-> PC2(35)"));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("PA3(25) <-> 9 -|     o- 8 <-> PC3(34)"));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("PA4(26) <->11 -|     o- 10<-> PC4(33)"));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("               | 1   |               "));
  Serial.println(F("PA5(27) <->13 -|     o- 12<-> PC5(32)"));
  Serial.println(F("               |     |               "));
  Serial.println(F("                -----                "));
#endif
  Serial.println();
}

bool test_K1553_LN1_LN2_LN3_LN5_LN8() {
  return checkLogic(info_1533ln12358, &ln12358);
}
