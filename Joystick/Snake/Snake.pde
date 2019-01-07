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

int _step = 0;
boolean _IsWinner = false;
boolean _IsGameRunning = true;

int interval = 500;
int lastRecordedTime = 0;

void setup() {
  println(Serial.list());
  port = new Serial(this, "COM3", 9600);
  port.bufferUntil('\r');  
  port.clear();
  
  for (int row = 0; row < rowCount; row++)
  for (int col = 0; col < colCount; col++)
    data[row][col] = ' ';
  
  size(768, 768);
  cellW = width / colCount;
  cellH = height / rowCount;
  textAlign(CENTER);
  stroke(204, 102, 0);    
}

void draw()
{
  if (_IsGameRunning)
  {
    if (millis() - lastRecordedTime > interval)
    {
      lastRecordedTime = millis();
      if (Interact()) return;
    }
    else return;
  }
  _IsGameRunning = false;
  text(_IsWinner ? "YOU WIN!": "GAME OVER!", width/2, height/2 );
  noLoop();    
}

boolean Interact()
{
  if (NextMove())
  {
    if (Action())
    {
      doEvent();
      displayBody();
      displayScreen();
      return true;
    }
  }
  return false;
}

void doEvent()
{
  _step += 1;
  if (_step % 4 == 0)
  {
    int count = int(random(10)) % 2;
    for (int i = 0; i < count; i++)
    {
      int x = int(random(rowCount));
      int y = int(random(colCount));
      data[x][y] = '$';
    }
  }
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
  background(0);
  for (int row = 0; row < rowCount; row++)
  {
    for (int col = 0; col < colCount; col++)
    {
      int x = col * cellW;
      int y = row * cellH;
      fill(255);
      rect (x, y, cellW, cellH);
      fill(0);
      text(data[row][col], x + cellW/2, y + cellH/2 );
    }
  }
}

boolean CheckBound(TPoint p)
{
  return !(p.X < 0 || p.Y < 0 || p.X >= rowCount || p.Y >= colCount);
}

boolean NextMove()
{
  _pos = _pos.plus(_move);
  return CheckBound(_pos);
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
  if (_snakeLength == 3) interval -= 150;
  if (_snakeLength == 10) interval -= 200;
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
