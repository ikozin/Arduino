
#include <Wire.h>
#include "MP1090S.h"

static word MP1090S_REGS [12] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                                 0x0000, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000};
static byte MP1090S_RST_PIN;

MP1090S::MP1090S ()
{

}
//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
// void MP1090S::InitI2C (byte RST_PIN)
// инициализаци¤ модул¤ дл¤ работы в режиме I2C
// входные параметры:
//           byte RST_PIN - номер линии ввода/вывода модул¤ Arduino (0, 1, 2...),
//                          к которой подключена лини¤ IN_RST модул¤ MP1090S
void MP1090S::InitI2C (byte RST_PIN)
{
   pinMode(RST_PIN, OUTPUT);
   digitalWrite(RST_PIN, LOW);
   pinMode(SDA, OUTPUT);
   pinMode(SCL, OUTPUT);
   digitalWrite(SDA, LOW);
   digitalWrite(SCL, HIGH);
   delay (200);
    
   digitalWrite(RST_PIN, HIGH);
   delay (200);
   
   MP1090S_REGS [MP1090S_TEST1] = 0x8100;
   
   Wire.begin();
   
   Write (MP1090S_TEST1);
   delay (800);
      
   MP1090S_REGS [MP1090S_POWERCFG] = 0x4001;
   
   Write (MP1090S_POWERCFG);
   delay (300);
      
   MP1090S_REGS [MP1090S_SYSCONFIG2] = MHz76_108 | kHz100;
   Write (MP1090S_SYSCONFIG2);
 
   MP1090S_RST_PIN = RST_PIN;
}
//------------------------------------------------------------------------------
// void MP1090S::SetBand (byte Band)
// установка диапазона частот
// входные параметры:
//           byte Band - код диапазона частот
//           ѕринимаемые значени¤: MHz87_5_108 - диапазон от 87,5 до 108 ћ√ц;
//                                 MHz76_108 - диапазон от 76 до 108 ћ√ц;
//                                 MHz76_90 - диапазон от 76 до 90 ћ√ц.
//           ѕо умолчанию задан диапазон от 76 до 108 ћ√ц.
void MP1090S::SetBand (byte Band)
{
   MP1090S_REGS [MP1090S_SYSCONFIG2] &= ~BAND_MASK;
   MP1090S_REGS [MP1090S_SYSCONFIG2] |= Band;
   
   Write (MP1090S_SYSCONFIG2);
}
//------------------------------------------------------------------------------
// void MP1090S::SetSpace (byte Space)
// установка шага частот
// входные параметры:
//           byte Space - код шага частот
//           ѕринимаемые значени¤: kHz200 - шаг 200 к√ц;
//                                 kHz100 - шаг 100 к√ц;
//                                 kHz50 - шаг 50 к√ц.
//           ѕо умолчанию задан шаг 100 к√ц.
void MP1090S::SetSpace (byte Space)
{
   MP1090S_REGS [MP1090S_SYSCONFIG2] &= ~SPACE_MASK;
   MP1090S_REGS [MP1090S_SYSCONFIG2] |= Space;
   
   Write (MP1090S_SYSCONFIG2);
}
//------------------------------------------------------------------------------
// void MP1090S::SetVolume (byte Volume)
// установка громкости
// входные параметры:
//           byte Volume - значение громкости: от 0 до 15.
//           ѕо умолчанию задана громкость 0, т.е. звук выключен.
void MP1090S::SetVolume (byte Volume)
{
   if (Volume <= VOLUME_MASK)
   {
      MP1090S_REGS [MP1090S_SYSCONFIG2] &= ~VOLUME_MASK;
      MP1090S_REGS [MP1090S_SYSCONFIG2] |= Volume;
   
      Write (MP1090S_SYSCONFIG2);
   }
}
//------------------------------------------------------------------------------
// boolean MP1090S::SetStation (long StationFrequency)
// установка радиостанции
// входные параметры:
//           long StationFrequency - частота радиостанции в к√ц
// выходные параметры:
//           true - радиостанци¤ установлена;
//           false - радиостанци¤ не установлена.
boolean MP1090S::SetStation (long StationFrequency)
{
   word StationCode = GetStationCode (StationFrequency);
   
   if (StationCode != false)
   {      
      MP1090S_REGS [MP1090S_CHANNEL] = TUNE_BIT | StationCode;      
      Write (MP1090S_CHANNEL);
      
      do
      {
        delay (10);
        ReadStatus ();
      }       
      while ((MP1090S_REGS [MP1090S_STATUSRSSI] & STC_BIT) != STC_BIT);
      
      MP1090S_REGS [MP1090S_CHANNEL] = StationCode;
      Write (MP1090S_CHANNEL);
      return true;
   }

   else
      return false;
}
//------------------------------------------------------------------------------
// byte MP1090S::GetBand (void)
// возврат установленного диапазона частот
// выходные параметры - текущий диапазон частот:
//             значение MHz87_5_108 - диапазон частот от 87,5 до 108 ћ√ц     
//             значение MHz76_108   - диапазон частот от 76 до 108 ћ√ц
//             значение MHz76_90    - диапазон частот от 76 до 90 ћ√ц
byte MP1090S::GetBand (void)
{
   switch (MP1090S_REGS [MP1090S_SYSCONFIG2] & BAND_MASK)
   {  
      case MHz87_5_108:
         return MHz87_5_108;
      break;
      
      case MHz76_108:
         return MHz76_108;
      break;
      
      case MHz76_90:
         return MHz76_90;
      break;
      
      default:
         return 0;
      break;
   }
}
//------------------------------------------------------------------------------
// byte MP1090S::GetSpace (void)
// возврат установленного шага частот
// выходные параметры: текущий шаг частот (200, 100 или 50 (к√ц)).
byte MP1090S::GetSpace (void)
{
   switch (MP1090S_REGS [MP1090S_SYSCONFIG2] & SPACE_MASK)
   {  
      case kHz200:
         return 200;
      break;
      
      case kHz100:
         return 100;
      break;
      
      case kHz50:
         return 50;
      break;
      
      default:
         return 0;
      break;
   }
}
//------------------------------------------------------------------------------
// byte MP1090S::GetVolume (void)
// возврат установленной громкости
// выходные параметры: текуща¤ громкость
byte MP1090S::GetVolume (void)
{
   return (byte (MP1090S_REGS [MP1090S_SYSCONFIG2] & VOLUME_MASK));
}
//------------------------------------------------------------------------------
// long MP1090S::GetStation (void)
// возврат установленной радиостанции в к√ц
// выходные параметры: значение текущей частоты в к√ц
long MP1090S::GetStation (void)
{
   byte StationSpace = GetSpace ();
   byte Band = GetBand ();
   
   int StationCode = MP1090S_REGS [MP1090S_CHANNEL] & STATION_MASK;
   
   if (Band == MHz87_5_108)
      return (StationSpace * StationCode + 87500);
   
   else
      return (StationSpace * StationCode + 76000);
}

//------------------------------------------------------------------------------
// PRIVATE FUNCTIONS
//------------------------------------------------------------------------------
void MP1090S::Write (byte Reg)
{
   Wire.beginTransmission(MP1090S_ADDRESS);
   for (int i=2; i<=Reg; i++)
   {
      Wire.write (highByte(MP1090S_REGS [i]));
      Wire.write (lowByte(MP1090S_REGS [i]));
   }
   Wire.endTransmission();
}
//------------------------------------------------------------------------------
void MP1090S::ReadStatus (void)
{
   byte ReadVals [2];
   int k = 0;
   
   Wire.requestFrom(MP1090S_ADDRESS, 2);
   while(Wire.available())
   {   
      ReadVals [k] = byte(Wire.read());
      k++;
   }
   
   MP1090S_REGS [MP1090S_STATUSRSSI] = word (ReadVals [0], ReadVals [1]);
}
//------------------------------------------------------------------------------
// word MP1090S::GetStationCode (long StationFrequency)
// преобразование частоты радиостанции в код
// входные параметры:
//           long StationFrequency - частота радиостанции в к√ц
// выходные параметры: код станции
word MP1090S::GetStationCode (long StationFrequency) //kHz
{
   byte StationSpace = GetSpace ();
   byte Band = GetBand ();
   
   if ((StationFrequency >= 87500) && (StationFrequency <= 108000) && (Band == MHz87_5_108))
      return (word ((StationFrequency - 87500) / StationSpace));
      
   else if ((StationFrequency >= 76000) && (StationFrequency <= 108000) && (Band == MHz76_108))
      return (word ((StationFrequency - 76000) / StationSpace));
      
   else if ((StationFrequency >= 76000) && (StationFrequency <= 90000) && (Band == MHz76_90))
      return (word ((StationFrequency - 76000) / StationSpace));
   
   else
      return false;
}
//------------------------------------------------------------------------------



MP1090S MP1090S_RADIO = MP1090S ();
