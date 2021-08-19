byte le156_in_data[]       = { B_00_00_00_00, B_01_01_01_01,  B_10_10_10_10,  B_11_11_11_11 };
byte le156_out_data[]      = { B1111,         B0000,          B0000,          B0000 };
TemplCheckLogic le156      = { 4, .in_mask = B11111111, B00001111, .in_data = le156_in_data, le156_out_data };

void info_1533le156(void) {
  Serial.println(F("КР1533ЛЕ1                            "));
  Serial.println(F("КР1533ЛЕ5  - повышеннаая нагрузка    "));
  Serial.println(F("КР1533ЛЕ6  - повышеннаая нагрузка    "));
  Serial.println(F("4 элемента 2ИЛИ-НЕ                   "));
  Serial.println(F("DIP14                                "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA0(22) <-> 2 -| 1   |               "));
  Serial.println(F("               |     o- 1 <-> PC0(37)"));
  Serial.println(F("PA1(23) <-> 3 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA2(24) <-> 5 -| 1   |               "));
  Serial.println(F("               |     o- 4 <-> PC1(36)"));
  Serial.println(F("PA3(25) <-> 6 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA4(26) <-> 8 -| 1   |               "));
  Serial.println(F("               |     o- 10<-> PC2(35)"));
  Serial.println(F("PA5(27) <-> 9 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA6(28) <-> 11-| 1   |               "));
  Serial.println(F("               |     o- 13<-> PC3(34)"));
  Serial.println(F("PA7(29) <-> 12-|     |               "));
  Serial.println(F("                -----                "));
#endif
  Serial.println();
}

bool test_K1553_LE1_LE5_LE6() {
  return checkLogic(info_1533le156, &le156);
}
