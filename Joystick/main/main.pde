//import processing.serial.*;
//PortSelector selector = new PortSelector();

IGameEngine game;

void setup()
{
  frameRate(120);
  //size(241, 241);
  //game = new Snake(this);

  //size(101, 241);
  //game = new Tetris(this);

  size(420, 420);
  game = new Brick(this);

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
