
#define LED_DELAY   300

void setup() {
  Serial.begin(9600);
}

void loop() {
  checkLed();
  //checkBtnPullDown();
  //checkBtnPullUp();
}

void checkBtnPullUp() {
  DDRB = B00000000;
  PORTB = 0;

  Serial.println();
  Serial.println("Check Button Pull-Up Board");
  Serial.println("       +--------------+");
  Serial.println("       | BUTTON BOARD |");
  Serial.println("       +---++++++++---+");
  Serial.println("           ||||||||");
  Serial.println("+----------++++++++------+");
  Serial.println("|     XXXX XXXXXXXX      |");
  Serial.println("|   +-----------+        |");
  Serial.println("|   | ATMEGA328 |        |");
  Serial.println("|   +-----------+        |");
  Serial.println("|  XXXXXXXX    I2C       |");
  Serial.println("+------------------------+");
  
  byte keys = 0;
  for (int i = 10; i > 0; i--) {
    Serial.print("Press any buttons, check number: ");
    Serial.println(i);
    while ((keys = PINB) == 0xFF);
    Serial.println(keys, HEX);
    if (~keys & 0x01) Serial.println("Button 1");
    if (~keys & 0x02) Serial.println("Button 2");
    if (~keys & 0x04) Serial.println("Button 3");
    if (~keys & 0x08) Serial.println("Button 4");
    if (~keys & 0x10) Serial.println("Button 5");
    if (~keys & 0x20) Serial.println("Button 6");
    if (~keys & 0x40) Serial.println("Button 7");
    if (~keys & 0x80) Serial.println("Button 8");
    delay(1000);
  }
}

void checkBtnPullDown() {
  DDRB = B00000000;
  PORTB = 0;

  Serial.println();
  Serial.println("Check Button Pull-Down Board");
  Serial.println("       +--------------+");
  Serial.println("       | BUTTON BOARD |");
  Serial.println("       +---++++++++---+");
  Serial.println("           ||||||||");
  Serial.println("+----------++++++++------+");
  Serial.println("|     XXXX XXXXXXXX      |");
  Serial.println("|   +-----------+        |");
  Serial.println("|   | ATMEGA328 |        |");
  Serial.println("|   +-----------+        |");
  Serial.println("|  XXXXXXXX    I2C       |");
  Serial.println("+------------------------+");
  
  byte keys = 0;
  for (int i = 10; i > 0; i--) {
    Serial.print("Press any buttons, check number: ");
    Serial.println(i);
    while (!(keys = PINB));
    Serial.println(keys, HEX);
    if (keys & 0x01) Serial.println("Button 1");
    if (keys & 0x02) Serial.println("Button 2");
    if (keys & 0x04) Serial.println("Button 3");
    if (keys & 0x08) Serial.println("Button 4");
    if (keys & 0x10) Serial.println("Button 5");
    if (keys & 0x20) Serial.println("Button 6");
    if (keys & 0x40) Serial.println("Button 7");
    if (keys & 0x80) Serial.println("Button 8");
    delay(1000);
  }
}

void checkLed() {
  DDRB = B11111111;
  PORTB = 0;

  Serial.println();
  Serial.println("Check LED Board");
  Serial.println("        +------------+");
  Serial.println("        | LED BOARD  |");
  Serial.println("        +--++++++++--+");
  Serial.println("           ||||||||");
  Serial.println("+----------++++++++------+");
  Serial.println("|     XXXX XXXXXXXX      |");
  Serial.println("|   +-----------+        |");
  Serial.println("|   | ATMEGA328 |        |");
  Serial.println("|   +-----------+        |");
  Serial.println("|  XXXXXXXX    I2C       |");
  Serial.println("+------------------------+");
  Serial.println();

  delay(LED_DELAY);
  for (int n = 0; n < 8; n++) {
    PORTB = 1 << n;
    delay(LED_DELAY);
  }
  PORTB = 0x00;
  delay(LED_DELAY);
  for (int n = 0; n < 2; n++) {
    PORTB = 0x55;
    delay(LED_DELAY);
    PORTB = 0xAA;
    delay(LED_DELAY);
  }
  PORTB = 0x00;
  delay(LED_DELAY);
  for (int n = 0; n < 2; n++) {
    PORTB = 0x33;
    delay(LED_DELAY);
    PORTB = 0xCC;
    delay(LED_DELAY);
  }
  PORTB = 0x00;
  delay(LED_DELAY);
  for (int n = 0; n < 2; n++) {
    PORTB = 0x0F;
    delay(LED_DELAY);
    PORTB = 0xF0;
    delay(LED_DELAY);
  }
  PORTB = 0x00;
  delay(LED_DELAY);
  for (int n = 0; n < 4; n++) {
    PORTB = 0xFF;
    delay(LED_DELAY);
    PORTB = 0x00;
    delay(LED_DELAY);
  }
  PORTB = 0x00;
  delay(LED_DELAY);
}
