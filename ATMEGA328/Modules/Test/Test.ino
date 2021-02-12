
#define LED_DELAY   300

void setup() {
  Serial.begin(9600);
}

void loop() {
  checkLed();
  //checkBtnPullDown();
}

void checkBtnPullDown() {
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
  Serial.println("Press any buttons");

  DDRB = B00000000;
  for (int i = 0; i < 200; i++) {
    byte keys = 0;
    while (!(keys = PINB))
      Serial.println(keys, HEX);
    Serial.println(keys, HEX);
  }
}


void checkLed() {
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

  DDRB = B11111111;
  PORTB = 0;
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
