import processing.serial.*;

PortSelector selector = new PortSelector(this);

void setup()
{
  size(320, 240);
  selector.setup();
}

void draw()
{
  if (selector.draw()) return;
}

void keyPressed()
{
  if (selector.keyPressed()) return;
}

void serialEvent (Serial port)
{
  selector.serialEvent(port);
}
