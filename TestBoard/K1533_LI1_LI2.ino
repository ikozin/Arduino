byte li12_in_data[]        = { B_00_00_00_00, B_01_01_01_01,  B_10_10_10_10,  B_11_11_11_11 };
byte li12_out_data[]       = { B0000,         B0000,          B0000,          B1111 }; 
TemplCheckLogic li12       = { 4, .in_mask = B11111111, B00001111, .in_data = li12_in_data, li12_out_data };

void info_1533li12(void) {
  Serial.println(F("КР1533ЛИ1                            "));
  Serial.println(F("КР1533ЛИ2  - открытый коллектор      "));
  Serial.println(F("4 элемента 2И                        "));
  Serial.println(F("DIP14                                "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA0(22) <-> 1 -| &   |               "));
  Serial.println(F("               |     |- 3 <-> PC0(37)"));
  Serial.println(F("PA1(23) <-> 2 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA2(24) <-> 4 -| &   |               "));
  Serial.println(F("               |     |- 6 <-> PC1(36)"));
  Serial.println(F("PA3(25) <-> 5 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA4(26) <-> 9 -| &   |               "));
  Serial.println(F("               |     |- 8 <-> PC2(35)"));
  Serial.println(F("PA5(27) <-> 10-|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA6(28) <-> 12-| &   |               "));
  Serial.println(F("               |     |- 11<-> PC3(34)"));
  Serial.println(F("PA7(29) <-> 13-|     |               "));
  Serial.println(F("                -----                "));
#endif
  Serial.println();
}

bool test_K1553_LI1_LI2() {
  return checkLogic(info_1533li12, &li12);
}
