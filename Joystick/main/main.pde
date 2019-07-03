//import processing.serial.*;

//PortSelector selector = new PortSelector();

IGameEngine game;

void setup()
{
  //size(241, 241);
  //game = new Snake(this);

  //size(101, 241);
  //game = new Tetris(this);

  size(420, 210);
  game = new Brick(this);

  game.start();
  
  //for (int i = 0; i < 100; i++)
  //  println((int)random(1, 10));

  
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
