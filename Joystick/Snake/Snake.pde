import processing.serial.*;

Serial port;

int rowCount = 24;
int colCount = 24;

char[][] data = new char[rowCount][colCount];

int cellW;
int cellH;

TPoint[] _snake =
{
  new TPoint(0, 1),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
  new TPoint(0, 0),
}; 
int _snakeLength = 1;

TPoint _pos = new TPoint(rowCount/2, colCount/2);
TPoint _move = new TPoint(1, 0);

boolean _IsWinner = false;
boolean _IsGameRunning = true;

int moveInterval = 500;
int lastMoveTime = 0;

int eventInterval = 2000;
int lastEventTime = 0;

void setup() {
  println(Serial.list());
  //port = new Serial(this, "COM3", 9600);
  //port.bufferUntil('\r');  
  //port.clear();
  
  for (int row = 0; row < rowCount; row++)
  for (int col = 0; col < colCount; col++)
    data[row][col] = ' ';
  
  size(241, 241);
  cellW = width / colCount;
  cellH = height / rowCount;
  textAlign(CENTER);
  ellipseMode(CORNER);
}

void draw()
{
  displayScreen();
  if (_IsGameRunning && Interact()) return;
  stroke(0);
  fill(200, 0, 0);
  textSize(32);
  text(_IsWinner ? "YOU WIN!": "GAME OVER!", width/2, height/2 );
  noLoop();    
}

boolean Interact()
{
  if (!NextMove()) return false;
  return doEvent();
}

boolean doEvent()
{
  if (millis() - lastEventTime > eventInterval)
  {
    lastEventTime = millis();
    int count = int(random(10)) % 2;
    for (int i = 0; i < count; i++)
    {
      int x = int(random(rowCount));
      int y = int(random(colCount));
      data[x][y] = '$';
    }
  }
  return true;
}

void displayBody()
{
  TPoint curPos = _pos;
  for (int i = 0; i < _snake.length; i++)
  {
    data[curPos.X][curPos.Y] = '*';
    curPos = curPos.minus(_snake[i]);
  }
  data[curPos.X][curPos.Y] = ' ';
}

void displayScreen()
{
  background(255);
  for (int row = 0; row < rowCount; row++)
  {
    for (int col = 0; col < colCount; col++)
    {
      int x = col * cellW;
      int y = row * cellH;
      stroke(0);
      noFill();
      rect (x, y, cellW, cellH);
      if (data[row][col] == '$')
        drawEllipsa(row, col, 0);
      else 
        drawCell(row, col, data[row][col] == ' ' ? 255: 0);
    }
  }
}

void drawCell(int row, int col, int cellColor)
{
  int x = col * cellW;
  int y = row * cellH;
  stroke(cellColor);
  fill(cellColor);
  rect (x + 2, y + 2, cellW - 4, cellH - 4);
}

void drawEllipsa(int row, int col, int cellColor)
{
  int x = col * cellW;
  int y = row * cellH;
  stroke(cellColor);
  fill(cellColor);
  ellipse(x + 2, y + 2, cellW - 4, cellH - 4);
}


boolean CheckBound(TPoint p)
{
  return !(p.X < 0 || p.Y < 0 || p.X >= rowCount || p.Y >= colCount);
}

boolean NextMove()
{
  if (millis() - lastMoveTime > moveInterval)
  {
    lastMoveTime = millis();
    _pos = _pos.plus(_move);
    if (!CheckBound(_pos)) return false;
    if (!Action()) return false;
    displayBody();    
  }
  return true;  
}

boolean Action()
{
  switch (data[_pos.X][_pos.Y])
  {
    case '$':
      return ActionIncLength();
    case '*':
      return ActionFail();
    default:
      break;
  }
  return ActionContinue();
}

boolean ActionIncLength()
{
  _snakeLength += 1;
  if (_snakeLength == _snake.length)
  {
    _IsWinner = true;
    return false;
  }
  for (int i = _snakeLength - 1; i > 0 ; i--)
    _snake[i] = _snake[i - 1];
  _snake[0] = _move;
  if (_snakeLength == 3) moveInterval -= 150;
  if (_snakeLength == 10) moveInterval -= 200;
  return true;
}

boolean ActionFail()
{
  return false;
}

boolean ActionContinue()
{
  for (int i = _snakeLength - 1; i > 0 ; i--)
    _snake[i] = _snake[i - 1];
  _snake[0] = _move;
  return true;
}

void keyPressed()
{
  switch (keyCode)
  {
    case 27:
      _IsGameRunning = false;
      return;
    case 38:
      _move = new TPoint(-1, 0);
      return;
    case 40:
      _move = new TPoint(1, 0);
       return;
    case 37:
      _move = new TPoint(0, -1);
      return;
    case 39:
      _move = new TPoint(0, 1);
      return;
  }
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
    if (x < 100) _move = new TPoint(0, -1);
    if (x > 150) _move = new TPoint(0, 1);
    if (y < 100) _move = new TPoint(-1, 0);
    if (y > 150) _move = new TPoint(1, 0);
    if (btn == 1) _IsGameRunning = false;
  }
}
