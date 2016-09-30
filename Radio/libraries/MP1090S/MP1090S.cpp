
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
// ������������� ������ ��� ������ � ������ I2C
// ������� ���������:
//           byte RST_PIN - ����� ����� �����/������ ������ Arduino (0, 1, 2...),
//                          � ������� ���������� ����� IN_RST ������ MP1090S
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
// ��������� ��������� ������
// ������� ���������:
//           byte Band - ��� ��������� ������
//           ����������� ��������: MHz87_5_108 - �������� �� 87,5 �� 108 ���;
//                                 MHz76_108 - �������� �� 76 �� 108 ���;
//                                 MHz76_90 - �������� �� 76 �� 90 ���.
//           �� ��������� ����� �������� �� 76 �� 108 ���.
void MP1090S::SetBand (byte Band)
{
   MP1090S_REGS [MP1090S_SYSCONFIG2] &= ~BAND_MASK;
   MP1090S_REGS [MP1090S_SYSCONFIG2] |= Band;
   
   Write (MP1090S_SYSCONFIG2);
}
//------------------------------------------------------------------------------
// void MP1090S::SetSpace (byte Space)
// ��������� ���� ������
// ������� ���������:
//           byte Space - ��� ���� ������
//           ����������� ��������: kHz200 - ��� 200 ���;
//                                 kHz100 - ��� 100 ���;
//                                 kHz50 - ��� 50 ���.
//           �� ��������� ����� ��� 100 ���.
void MP1090S::SetSpace (byte Space)
{
   MP1090S_REGS [MP1090S_SYSCONFIG2] &= ~SPACE_MASK;
   MP1090S_REGS [MP1090S_SYSCONFIG2] |= Space;
   
   Write (MP1090S_SYSCONFIG2);
}
//------------------------------------------------------------------------------
// void MP1090S::SetVolume (byte Volume)
// ��������� ���������
// ������� ���������:
//           byte Volume - �������� ���������: �� 0 �� 15.
//           �� ��������� ������ ��������� 0, �.�. ���� ��������.
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
// ��������� ������������
// ������� ���������:
//           long StationFrequency - ������� ������������ � ���
// �������� ���������:
//           true - ������������ �����������;
//           false - ������������ �� �����������.
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
// ������� �������������� ��������� ������
// �������� ��������� - ������� �������� ������:
//             �������� MHz87_5_108 - �������� ������ �� 87,5 �� 108 ���     
//             �������� MHz76_108   - �������� ������ �� 76 �� 108 ���
//             �������� MHz76_90    - �������� ������ �� 76 �� 90 ���
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
// ������� �������������� ���� ������
// �������� ���������: ������� ��� ������ (200, 100 ��� 50 (���)).
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
// ������� ������������� ���������
// �������� ���������: ������� ���������
byte MP1090S::GetVolume (void)
{
   return (byte (MP1090S_REGS [MP1090S_SYSCONFIG2] & VOLUME_MASK));
}
//------------------------------------------------------------------------------
// long MP1090S::GetStation (void)
// ������� ������������� ������������ � ���
// �������� ���������: �������� ������� ������� � ���
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
// �������������� ������� ������������ � ���
// ������� ���������:
//           long StationFrequency - ������� ������������ � ���
// �������� ���������: ��� �������
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
