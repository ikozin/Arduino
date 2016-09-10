#include "DS1302.h"

DS1302::DS1302(uint8_t pin_SCLK , uint8_t pin_IO, uint8_t pin_CE)
{
    _SCLK_PIN = pin_SCLK;
    _IO_PIN   = pin_IO;
    _CE_PIN   = pin_CE;
}

void DS1302::begin()
{
  _write (DS1302_ENABLE, 0);
  _write (DS1302_TRICKLE, 0x00);
}

// --------------------------------------------------------
// burst_read
//
// This function reads 8 bytes clock data in burst mode
// from the DS1302.
//
// This function may be called as the first function, 
// also the pinMode is set.
//
void DS1302::burst_read(uint8_t *p)
{
  int i;

  _start();

  // Instead of the address, 
  // the CLOCK_BURST_READ command is issued
  // the I/O-line is released for the data
  _togglewrite( DS1302_CLOCK_BURST_READ, true);  

  for( i=0; i<8; i++)
  {
    *p++ = _toggleread();
  }
  _stop();
}

// --------------------------------------------------------
// burst_write
//
// This function writes 8 bytes clock data in burst mode
// to the DS1302.
//
// This function may be called as the first function, 
// also the pinMode is set.
//
void DS1302::burst_write(uint8_t *p)
{
  int i;

  _start();

  // Instead of the address, 
  // the CLOCK_BURST_WRITE command is issued.
  // the I/O-line is not released
  _togglewrite( DS1302_CLOCK_BURST_WRITE, false);  

  for( i=0; i<8; i++)
  {
    // the I/O-line is not released
    _togglewrite( *p++, false);  
  }
  _stop();
}

// --------------------------------------------------------
// _read
//
// This function reads a byte from the DS1302 
// (clock or ram).
//
// The address could be like "0x80" or "0x81", 
// the lowest bit is set anyway.
//
// This function may be called as the first function, 
// also the pinMode is set.
//
uint8_t DS1302::_read(int address)
{
  uint8_t data;

  // set lowest bit (read bit) in address
  bitSet( address, DS1302_READBIT);  

  _start();
  // the I/O-line is released for the data
  _togglewrite( address, true);  
  data = _toggleread();
  _stop();

  return (data);
}


// --------------------------------------------------------
// _write
//
// This function writes a byte to the DS1302 (clock or ram).
//
// The address could be like "0x80" or "0x81", 
// the lowest bit is cleared anyway.
//
// This function may be called as the first function, 
// also the pinMode is set.
//
void DS1302::_write( int address, uint8_t data)
{
  // clear lowest bit (read bit) in address
  bitClear( address, DS1302_READBIT);   

  _start();
  // don't release the I/O-line
  _togglewrite( address, false); 
  // don't release the I/O-line
  _togglewrite( data, false); 
  _stop();  
}


// --------------------------------------------------------
// _start
//
// A helper function to setup the start condition.
//
// An 'init' function is not used.
// But now the pinMode is set every time.
// That's not a big deal, and it's valid.
// At startup, the pins of the Arduino are high impedance.
// Since the DS1302 has pull-down resistors, 
// the signals are low (inactive) until the DS1302 is used.
void DS1302::_start( void)
{
  digitalWrite( _CE_PIN, LOW); // default, not enabled
  pinMode( _CE_PIN, OUTPUT);  

  digitalWrite( _SCLK_PIN, LOW); // default, clock low
  pinMode( _SCLK_PIN, OUTPUT);

  pinMode( _IO_PIN, OUTPUT);

  digitalWrite( _CE_PIN, HIGH); // start the session
  delayMicroseconds( 4);           // tCC = 4us
}


// --------------------------------------------------------
// _stop
//
// A helper function to finish the communication.
//
void DS1302::_stop(void)
{
  // Set CE low
  digitalWrite( _CE_PIN, LOW);
  delayMicroseconds( 4);           // tCWH = 4us
}


// --------------------------------------------------------
// _toggleread
//
// A helper function for reading a byte with bit toggle
//
// This function assumes that the SCLK is still high.
//
uint8_t DS1302::_toggleread( void)
{
  uint8_t i, data;

  data = 0;
  for( i = 0; i <= 7; i++)
  {
    // Issue a clock pulse for the next databit.
    // If the 'togglewrite' function was used before 
    // this function, the SCLK is already high.
    digitalWrite( _SCLK_PIN, HIGH);
    delayMicroseconds( 1);

    // Clock down, data is ready after some time.
    digitalWrite( _SCLK_PIN, LOW);
    delayMicroseconds( 1);        // tCL=1000ns, tCDD=800ns

    // read bit, and set it in place in 'data' variable
    bitWrite( data, i, digitalRead( _IO_PIN)); 
  }
  return( data);
}


// --------------------------------------------------------
// _togglewrite
//
// A helper function for writing a byte with bit toggle
//
// The 'release' parameter is for a read after this write.
// It will release the I/O-line and will keep the SCLK high.
//
void DS1302::_togglewrite( uint8_t data, uint8_t release)
{
  int i;

  for( i = 0; i <= 7; i++)
  { 
    // set a bit of the data on the I/O-line
    digitalWrite( _IO_PIN, bitRead(data, i));  
    delayMicroseconds( 1);     // tDC = 200ns

    // clock up, data is read by DS1302
    digitalWrite( _SCLK_PIN, HIGH);     
    delayMicroseconds( 1);     // tCH = 1000ns, tCDH = 800ns

    if( release && i == 7)
    {
      // If this write is followed by a read, 
      // the I/O-line should be released after 
      // the last bit, before the clock line is made low.
      // This is according the datasheet.
      // I have seen other programs that don't release 
      // the I/O-line at this moment,
      // and that could cause a shortcut spike 
      // on the I/O-line.
      pinMode( _IO_PIN, INPUT);

      // For Arduino 1.0.3, removing the pull-up is no longer needed.
      // Setting the pin as 'INPUT' will already remove the pull-up.
      // digitalWrite (DS1302_IO, LOW); // remove any pull-up  
    }
    else
    {
      digitalWrite( _SCLK_PIN, LOW);
      delayMicroseconds( 1);       // tCL=1000ns, tCDD=800ns
    }
  }
}

