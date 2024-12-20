//////////////////////////////////////////////////////////////////////////
//http://forum.arduino.cc/index.php?topic=185235.0
// Быстрая функция
//////////////////////////////////////////////////////////////////////////
uint8_t dec2bcd(uint8_t n)
{
 byte b = (n * 103) >> 10;
 return (b * 16 + n-(b*10));  
}
//////////////////////////////////////////////////////////////////////////
// Самая быстрая функция, но правильно работает только для диапазона 0..68
//////////////////////////////////////////////////////////////////////////
uint8_t dec2bcd_fast(uint8_t n)
{
  uint16_t a = n;
  byte b = (a*26) >> 8;
  return  n + b*6;
}

//////////////////////////////////////////////////////////////////////////
// Самая быстрая функция
//////////////////////////////////////////////////////////////////////////
uint8_t bcd2dec(uint8_t n)
{
  return n - 6 * (n/16); 
}

//////////////////////////////////////////////////////////////////////////
//bcd2dec:      1268
//dec2bcd:      1592
//dec2bcd_fast: 1396
//////////////////////////////////////////////////////////////////////////


volatile int dec;
volatile int bcd;;
uint32_t start;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}


  Serial.print("bcd2dec:\t");
  start = micros();
  for(int i=0; i< 1000; i++)
  {
    dec = bcd2dec(bcd);
  }
  Serial.println(micros() - start);

  Serial.print("dec2bcd:\t");
  start = micros();
  for(int i=0; i< 1000; i++)
  {
    bcd = dec2bcd(dec);
  }
  Serial.println(micros() - start);

  Serial.print("dec2bcd_fast:\t");
  start = micros();
  for(int i=0; i< 1000; i++)
  {
    bcd = dec2bcd_fast(dec);
  }
  Serial.println(micros() - start);

  Serial.println();
  for (int i = 0; i < 100; i++)
  {
    bcd = dec2bcd(i);
    dec = bcd2dec(bcd);
    Serial.print(bcd, HEX);
    Serial.print("=");
    Serial.print(dec);
    Serial.println();        
  }
}

void loop()
{
}
