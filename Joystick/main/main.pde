//import processing.serial.*;
//import controlP5.*;

//PortSelector selector = new PortSelector();
//Snake game;
Tetris game;

void setup()
{
  //size(241, 241);
  //game = new Snake(this);
  //game.start();

  size(101, 241);
  game = new Tetris(this);
  game.start();
}

void draw()
{
}

/*
void serialEvent (Serial port)
{
  selector.serialEvent(port);
}
*/
