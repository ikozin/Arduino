byte la167_in_data[]       = { B_0000_0000, B_0001_0001,  B_0010_0010,  B_0011_0011,  B_0100_0100,  B_0101_0101,  B_0110_0110,  B_0111_0111,  B_1000_1000,  B_1001_1001,  B_1010_1010,  B_1011_1011,  B_1100_1100,  B_1101_1101,  B_1110_1110,  B_1111_1111 };
byte la167_out_data[]      = { B11,         B11,          B11,          B11,          B11,          B11,          B11,          B11,          B11,          B11,          B11,          B11,          B11,          B11,          B11,          B00 };
TemplCheckLogic la167      = { 16, .in_mask = B11111111, B00000011, .in_data = la167_in_data, la167_out_data };

void info_1533la167(void) {
  Serial.println(F("КР1533ЛА1                            "));
  Serial.println(F("КР1533ЛА6 - повышеннаая нагрузка     "));
  Serial.println(F("КР1533ЛА7 - открытый коллектор       "));
  Serial.println(F("2 элемента 4И-НЕ                     "));
  Serial.println(F("DIP14                                "));
#ifdef DETAIL_GRAPHIC
  Serial.println(F("              14 - +5V               "));
  Serial.println(F("               7 - GND               "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA0(22) <-> 1 -| &   |               "));
  Serial.println(F("               |     |               "));
  Serial.println(F("PA1(23) <-> 2 -|     |               "));
  Serial.println(F("               |     o- 6 <-> PC0(37)"));
  Serial.println(F("PA2(24) <-> 4 -|     |               "));
  Serial.println(F("               |     |               "));
  Serial.println(F("PA3(25) <-> 5 -|     |               "));
  Serial.println(F("                -----                "));
  Serial.println(F("            3 - NC                   "));
  Serial.println(F("                -----                "));
  Serial.println(F("PA4(26) <-> 9 -| &   |               "));
  Serial.println(F("               |     |               "));
  Serial.println(F("PA5(27) <->10 -|     |               "));
  Serial.println(F("               |     o- 8 <-> PC1(36)"));
  Serial.println(F("PA6(28) <->12 -|     |              "));
  Serial.println(F("               |     |              "));
  Serial.println(F("PA7(29) <->13 -|     |              "));
  Serial.println(F("                -----               "));
  Serial.println(F("           11 - NC                  "));
#endif
  Serial.println();
}

bool test_K1553_LA1_LA6_LA7() {
  return checkLogic(info_1533la167, &la167);
}
