//import processing.serial.*;

//PortSelector selector = new PortSelector();

IGameEngine game;

void setup()
{
  size(241, 241);
  game = new Snake(this);

  //size(101, 241);
  //game = new Tetris(this);

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
