// ----------------------------------------------------------------------------
// LCDiSpeed - LCD Interface Speed test
// ----------------------------------------------------------------------------
// This sketch is a wrapper sketch for the hd44780 library example LCDiSpeed.
// Note:
// This is not a normal sketch and should not be used as model or example
// of hd44780 library sketches.
// This sketch is simple wrapper that declares the needed lcd object for the
// hd44780 library sketch.
// It is provided as a convenient way to run a pre-configured sketch for
// the i/o sub library.
// The source code for this sketch lives in hd44780 examples:
// hd44780/examples/hd44780examples/LCDiSpeed/LCDiSpeed.ino
// From IDE:
// [File]->Examples-> hd44780/hd44780examples/LCDiSpeed
//

#include <Wire.h>		// can be omitted starting with IDE 1.6.7
#include <hd44780.h>		// can be omitted starting with IDE 1.6.7
#include <hd44780_I2Clcd.h>	// include i/o sub library header

// lcd i2c address
const uint8_t I2Clcd_Addr = 0x3e;

// declare the lcd object
hd44780_I2Clcd lcd(I2Clcd_Addr);

// tell the hd44780 sketch the lcd object has been declared
#define HD44780_LCDOBJECT

// include the hd44780 library LCDiSpeed sketch source code
#include <examples/hd44780examples/LCDiSpeed/LCDiSpeed.ino>
