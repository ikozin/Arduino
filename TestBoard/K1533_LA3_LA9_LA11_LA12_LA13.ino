byte la39111213_in_data[]  = { B_00_00_00_00, B_01_01_01_01,  B_10_10_10_10,  B_11_11_11_11 };
byte la39111213_out_data[] = { B1111,         B1111,          B1111,          B0000 };
TemplCheckLogic la39111213 = { 4, .in_mask = B11111111, B00001111, .in_data = la39111213_in_data, la39111213_out_data };

void info_1533la39111213(void) {
  Serial.println(F("КР1533ЛА3                            "));
  Serial.println(F("КР1533ЛА9                            "));
  Serial.println(F("КР1533ЛА11 - открытый коллектор      "));
  Serial.println(F("КР1533ЛА12 - повышеннаая нагрузка    "));
  Serial.println(F("КР1533ЛА13 - открытый коллектор,     "));
  Serial.println(F("             повышеннаая нагрузка    "));
  Serial.println(F("КР1533ТЛ3  - триггер Шмитта          "));
  Serial.println(F("4 элемента 2И-НЕ                     "));
  Serial.println(F("DIP14                                "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA0(22) <-> 1 -| &   |               "));
  Serial.println(F("               |     o- 3 <-> PC0(37)"));
  Serial.println(F("PA1(23) <-> 2 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA2(24) <-> 4 -| &   |               "));
  Serial.println(F("               |     o- 6 <-> PC1(36)"));
  Serial.println(F("PA3(25) <-> 5 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA4(26) <-> 9 -| &   |               "));
  Serial.println(F("               |     o- 8 <-> PC2(35)"));
  Serial.println(F("PA5(27) <-> 10-|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA6(28) <-> 12-| &   |               "));
  Serial.println(F("               |     o- 11<-> PC3(34)"));
  Serial.println(F("PA7(29) <-> 13-|     |               "));
  Serial.println(F("                -----                "));
#endif
  Serial.println();
}

bool test_K1553_LA3_LA9_LA11_LA12_LA13() {
  return checkLogic(info_1533la39111213, &la39111213);
}
