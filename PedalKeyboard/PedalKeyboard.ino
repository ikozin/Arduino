#include <Keyboard.h>

void setup()
{
	// initialize control over the keyboard:
	Keyboard.begin();
}

void loop()
{
	delay(5000);
	Keyboard.print("Hello World!");
	while (1) {}
}
