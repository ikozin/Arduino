#include <SoftwareSerial.h>

/*
При включени удерживаем кнопку на модуле, это переведет его в режим AT команд
---------------------------
|                -> STATE |-
|     LEVEL:3.3V <- RXD   |-
|     LEVEL:3.3V -> TXD   |-
|  POWER:3.6V-6V <- GND   |-
|                <- VCC   |-
|         ZS-040 <- EN    |-
---------------------------
*/

#define PIN_STATE 12
#define PIN_RXD   9
#define PIN_TXD   8
#define PIN_GND
#define PIN_VCC
#define PIN_EN    11

SoftwareSerial btSerial(PIN_RXD, PIN_TXD);

#define LED_PIN   13
char btName[8];
char btPswd[8];
void sendCmd(char *pszCommand, int msDelay);
void recvText(char *pszMessage, char *pszText, int len);
char text[128];

void setup() {
  pinMode(PIN_EN, OUTPUT);
  pinMode(PIN_STATE, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(PIN_EN, HIGH);
  Serial.begin(38400);
  btSerial.begin(38400);  //9600

  delay(500);
  while (Serial.available()) Serial.read();
  Serial.println("");
  Serial.println("Setup bluetooth module HC-05 as Slave");
  Serial.println("WARNING: PowerOn with pressed key on module");
  Serial.println("WARNING: if quickly blinking that mean not in AT-mode (error mode)");
  Serial.println("---------------------------");
  Serial.println("|                -> STATE |");
  Serial.println("|     LEVEL:3.3V <- RXD   |");
  Serial.println("|     LEVEL:3.3V -> TXD   |");
  Serial.println("|  POWER:3.6V-6V <- GND   |");
  Serial.println("|                <- VCC   |");
  Serial.println("|         ZS-040 <- EN    |");
  Serial.println("---------------------------");
  Serial.println("HINT: to Slave-Loop");
  Serial.println("HINT:     AT+ROLE=2");
  Serial.println("HINT:     AT+RESET");
  Serial.println("Press any key to continue ...");
  delay(100);
  recvText("Enter name:", btName, sizeof(btName)/sizeof(char));
  recvText("Enter password:", btPswd, sizeof(btPswd)/sizeof(char));
  Serial.println("");
  sendCmd("AT", 1000);
  sendCmd("AT", 1000);
  sendCmd("AT+ORGL", 1000);       // Сброс предыдущих настроек
  sendCmd("AT+RMAAD", 1000);      // Сброс спаренных устройств
  sprintf(text, "AT+NAME=%s", btName);
  sendCmd(text, 1000);
  sprintf(text, "AT+PSWD=%s", btPswd);
  sendCmd(text, 1000);
  sendCmd("AT+CLASS=7936", 1000); // Видимость для Андроида
  sendCmd("AT+VERSION?", 1000);
  sendCmd("AT+UART?", 1000);
  sendCmd("AT+ROLE?", 1000);
  sendCmd("AT+ADDR?", 1000);
  sendCmd("AT+STATE?", 1000);

  Serial.println("Press '0' to exit from AT-mode command ...");
  delay(100);
  while (Serial.available() == 0);
  if (Serial.read() == '0')
  {
    sendCmd("AT+RESET", 1000);
    Serial.println("--- END ---");
    for (;;);
  }
  while (Serial.available()) Serial.read();
  Serial.println("AT-mode");
  delay(100);
}

void sendCmd(char *pszCommand, int msDelay)
{
  Serial.println(pszCommand);
  btSerial.println(pszCommand);
  delay(msDelay);
  int len = btSerial.available();
  for (int i = 0; i < len; i++)
  {
    char recvChar = btSerial.read();
    Serial.write(recvChar);
  }
}

void recvText(char *pszMessage, char *pszText, int len)
{
  char recvChar = 0;
  while (Serial.available()) Serial.read();
  memset(pszText, 0, len);
  len = len - 1;
  Serial.print(pszMessage);
  Serial.print(" (Max=");
  Serial.print(len);
  Serial.println(")");
  delay(100);
  for(int i = 0; i < len; i++)
  {
    while (!Serial.available());
    recvChar = Serial.read();
    if (recvChar == 13) continue;
    if (recvChar == 10) break;    
    pszText[i]  = recvChar;
  }
  while (Serial.available()) Serial.read();
  Serial.println(pszText);  
}

void loop()
{
  char recvChar;
  digitalWrite(LED_PIN, digitalRead(PIN_STATE));
  if(Serial.available())
  {
    recvChar  = Serial.read();
    btSerial.write(recvChar);
    Serial.write(recvChar);
  }
  if(btSerial.available())
  {
    recvChar = btSerial.read();
    Serial.write(recvChar);
  }
}

