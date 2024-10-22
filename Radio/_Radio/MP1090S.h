#ifndef MP1090S_h
#define MP1090S_h

#include "Arduino.h"


//==============================================================================
#define   MP1090S_ADDRESS      0x10
//=============================Регистры=========================================
#define   MP1090S_DEVICEID     0x00
#define   MP1090S_CHIPID       0x01
#define   MP1090S_POWERCFG     0x02
#define   MP1090S_CHANNEL      0x03
#define   MP1090S_SYSCONFIG1   0x04
#define   MP1090S_SYSCONFIG2   0x05
#define   MP1090S_SYSCONFIG3   0x06
#define   MP1090S_TEST1        0x07
#define   MP1090S_TEST2        0x08
#define   MP1090S_BOOTCONFIG   0x09
#define   MP1090S_STATUSRSSI   0x0A
#define   MP1090S_READCHAN     0x0B
//------------------------------------------------------------------------------
#define   BAND_MASK       (3<<6)
#define   MHz87_5_108     (0<<6)
#define   MHz76_108       (1<<6)
#define   MHz76_90        (2<<6)
//------------------------------------------------------------------------------
#define   SPACE_MASK      (3<<4)
#define   kHz200          (0<<4)
#define   kHz100          (1<<4)
#define   kHz50           (2<<4)
//------------------------------------------------------------------------------
#define   VOLUME_MASK     0xF
#define   STATION_MASK    0x3FF
//------------------------------------------------------------------------------
#define   STC_BIT         (1<<14)
#define   TUNE_BIT        (1<<15)



class MP1090S
{
  public:
     MP1090S ();
     static void InitI2C (byte RST_PIN);
     static void SetBand (byte Band);
     static void SetSpace (byte Space);
     static void SetVolume (byte Volume);
     static boolean SetStation (long StationFrequency);
     static byte GetBand (void);
     static byte GetSpace (void);
     static byte GetVolume (void);
     static long GetStation (void);
     
  private:
     static void Write (byte Reg);
     static void ReadStatus (void);
     static word GetStationCode (long StationFrequency);
     
};

extern MP1090S MP1090S_RADIO;

#endif
