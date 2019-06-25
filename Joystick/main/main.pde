import processing.serial.*;
import controlP5.*;

PortSelector selector = new PortSelector();
Snake game = new Snake();
Demo demo;

void setup()
{
  size(320, 240);
  game.setup();
  selector.setup(this, game);
  demo = new Demo(this);
}

void draw()
{
  //println("draw");
  if (selector.draw()) return;
  if (game.draw()) return;
  noLoop();
}

void keyPressed()
{
  if (selector.keyPressed()) return;
  if (game.keyPressed()) return;
}

void serialEvent (Serial port)
{
  selector.serialEvent(port);
}
