//import processing.serial.*;

//PortSelector selector = new PortSelector();

IGameEngine game;

private int _rowCount = 24;
private int _colCount = 48;

void setup()
{
  //size(241, 241);
  //game = new Snake(this);

  //size(101, 241);
  //game = new Tetris(this);

  size(577, 193);
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
