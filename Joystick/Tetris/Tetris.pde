import processing.serial.*;

Serial port;

int _maxY = 24;
int _maxX = 10;

char[][] _screen = new char[_maxY][_maxX];

int _cellW;
int _cellH;

boolean _isRunning = true;
int _interval = 200;
int _lastRecordedTime = 0;

int _block = 0;
int _slide = 0;
int _x = 0;
int _y = 0;
int actionCode = -1;

void setup()
{
  println(Serial.list());
  //port = new Serial(this, "COM3", 9600);
  //port.bufferUntil('\r');  
  //port.clear();
  
  for (int row = 0; row < _maxY; row++)
  for (int col = 0; col < _maxX; col++)
    _screen[row][col] = ' ';
  
  size(101, 241);
  _cellW = width / _maxX;
  _cellH = height / _maxY;
  textAlign(CENTER);
  newBlock();  
}

void draw()
{
  displayScreen();
  if (_isRunning && Interact()) return;
  stroke(0);
  fill(200, 0, 0);
  textSize(16);
  text("GAME OVER!", width/2, height/2 );
  noLoop();    
}

boolean Interact()
{
  if (!clearBlock(_block, _slide, _x, _y)) return false;
  if (!nextLine()) return false;
  if (!proceedAction()) return false;
  if (!showBlock(_block, _slide, _x, _y)) return false;
  return true;
}


boolean nextLine()
{
  if (millis() - _lastRecordedTime > _interval)
  {
    _lastRecordedTime = millis();
    int posY = _y + 1;
    if (checkBlock(_block, _slide, _x, posY))
    {
      _y = posY;
    }
    else
    {
      showBlock(_block, _slide, _x, _y);
      newBlock();
    }
  }
  return true;
}

void newBlock()
{
  dropLines();
  _x = (byte)((_maxX >> 1) - 1);
  _y = 0;
  _block = (int)random(0, 7);
  _slide = (int)random(0, 4);
}

boolean dropLines()
{
  for (int y = 0; y < _maxY; y++)
  {
    int counter = 0;
    for (int x = 0; x < _maxX; x++)
      counter += _screen[y][x] == '*' ? 1 : 0;
    if (counter == _maxX)
    {
      for (int x = 0; x < _maxX; x++) _screen[y][x] = ' ';
      for (int n = y - 1; n > 0; n--)
        for (int x = 0; x < _maxX; x++) _screen[n + 1][x] = _screen[n][x];
    }
  }
  return true;
}

boolean clearBlock(int blockIndex, int slideIndex, int x, int y)
{
  return actionBlock(blockIndex, slideIndex, x, y, false, false);
}

boolean showBlock(int blockIndex, int slideIndex, int x, int y)
{
  return actionBlock(blockIndex, slideIndex, x, y, true, false);
}

boolean checkBlock(int blockIndex, int slideIndex, int x, int y)
{
  return actionBlock(blockIndex, slideIndex, x, y, true, true);
}

boolean actionBlock(int blockIndex, int slideIndex, int x, int y, boolean show, boolean check)
{
  int index = (blockIndex << 4) + (slideIndex << 2);
  int posY = y;

  for (int row = 0; row < 4; row++)
  {
    int posX = x;
    for (int mask = 0b0000_1000; mask > 0; mask >>= 1)
    {
      if ((unbinary(_blocks[index]) & mask) > 0)
      {
        if (posX < 0 || posY < 0) return false;
        if (posX >= _maxX || posY >= _maxY) return false;
        if (show && _screen[posY][posX] != ' ') return false;
        if (!check) _screen[posY][posX] = show ? '*' : ' ';
      }
      posX++;
    }
    posY++;
    index++;
  }
  return true;
}

boolean moveBlockToLeft()
{
  int posX = _x - 1;
  if (checkBlock(_block, _slide, posX, _y)) _x = posX;
  return true;
}

boolean moveBlockToRight()
{
  int posX = _x + 1;
  if (checkBlock(_block, _slide, posX, _y)) _x = posX;
  return true;
}

boolean rotateBlockToLeft()
{
  int nextSlide = abs((_slide + 1) % 4);
  if (checkBlock(_block, nextSlide, _x, _y)) _slide = nextSlide;
  return true;
}

boolean rotateBlockToRight()
{
  int nextSlide = abs((_slide - 1) % 4);
  if (checkBlock(_block, nextSlide, _x, _y)) _slide = nextSlide;
  return true;
}

boolean dropBlock()
{
  for ( ; ; )
  {
    int posY = _y + 1;
    if (!checkBlock(_block, _slide, _x, posY)) break;
    _y = posY;
  }
  showBlock(_block, _slide, _x, _y);
  newBlock();
  return true;
}

void displayScreen()
{
  background(255);
  for (int row = 0; row < _maxY; row++)
  for (int col = 0; col < _maxX; col++)
  {
    int x = col * _cellW;
    int y = row * _cellH;
    stroke(0);
    noFill();
    rect (x, y, _cellW, _cellH);
    drawCell(row, col, _screen[row][col] == ' ' ? 255: 0);
  }
}

void drawCell(int row, int col, int cellColor)
{
  int x = col * _cellW;
  int y = row * _cellH;
  stroke(cellColor);
  fill(cellColor);
  rect (x + 2, y + 2, _cellW - 4, _cellH - 4);
}

boolean proceedAction()
{
  boolean result = true;
  switch (actionCode)
  {
    case 27:  // ESC
      result = false; 
      break;
    case 38:  // UP
      result = rotateBlockToLeft();
      break;
    case 40:  // DOWN
      result = rotateBlockToRight();
      break;
    case 37:  // LEFT
      result = moveBlockToLeft();
      break;
    case 39:  // RIGHT
      result = moveBlockToRight();
      break;
    case 32:  // SPACE
      result = dropBlock();
      break;
  }
  actionCode = -1;
  return result;
}


// Получаем значения с ардуино
void serialEvent (Serial port)
{
  String data = port.readStringUntil('\r');  
  print(data);
  String values[] = split(data, ',');
  if (values.length == 3)
  {
    int x = int(trim(values[0]).substring(2));
    int y = int(trim(values[1]).substring(2));
    int btn = int(trim(values[2]).substring(4));
    if (x < 100) actionCode = 37;
    if (x > 150) actionCode = 39;
    if (y < 100) actionCode = 38;
    if (y > 150) actionCode = 40;
    if (btn == 1) actionCode = 32;
  }
}

void keyPressed()
{
  actionCode = keyCode;
}

void keyReleased()
{
  actionCode = -1;
}

String[] _blocks =
{
    /////////////////////////////////////////
    //
    // **
    // **
    //
    /////////////////////////////////////////
    "1100",
    "1100",
    "0000",
    "0000",

    "1100",
    "1100",
    "0000",
    "0000",

    "1100",
    "1100",
    "0000",
    "0000",

    "1100",
    "1100",
    "0000",
    "0000",

    /////////////////////////////////////////
    // *
    // **
    //  *
    //
    /////////////////////////////////////////
    "1000",
    "1100",
    "0100",
    "0000",

    "0110",
    "1100",
    "0000",
    "0000",

    "1000",
    "1100",
    "0100",
    "0000",

    "0110",
    "1100",
    "0000",
    "0000",

    /////////////////////////////////////////
    //  *
    // **
    // *
    //
    /////////////////////////////////////////
    "0100",
    "1100",
    "1000",
    "0000",

    "1100",
    "0110",
    "0000",
    "0000",

    "0100",
    "1100",
    "1000",
    "0000",

    "1100",
    "0110",
    "0000",
    "0000",

    /////////////////////////////////////////
    //  *
    //  *
    //  *
    //  *
    /////////////////////////////////////////
    "0100",
    "0100",
    "0100",
    "0100",

    "0000",
    "1111",
    "0000",
    "0000",

    "0100",
    "0100",
    "0100",
    "0100",

    "0000",
    "1111",
    "0000",
    "0000",


    /////////////////////////////////////////
    //  *
    // **
    //  *
    // 
    /////////////////////////////////////////
    "0100",
    "1100",
    "0100",
    "0000",

    "0000",
    "1110",
    "0100",
    "0000",

    "0100",
    "0110",
    "0100",
    "0000",

    "0100",
    "1110",
    "0000",
    "0000",

    /////////////////////////////////////////
    // **
    //  *
    //  *
    // 
    /////////////////////////////////////////
    "1100",
    "0100",
    "0100",
    "0000",

    "0000",
    "1110",
    "1000",
    "0000",

    "0100",
    "0100",
    "0110",
    "0000",

    "0010",
    "1110",
    "0000",
    "0000",

    /////////////////////////////////////////
    //  **
    //  *
    //  *
    // 
    /////////////////////////////////////////
    "0110",
    "0100",
    "0100",
    "0000",

    "1000",
    "1110",
    "0000",
    "0000",

    "0100",
    "0100",
    "1100",
    "0000",

    "0000",
    "1110",
    "0010",
    "0000",
};
