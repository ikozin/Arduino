public class Snake extends GameEngine
{
  private TPoint[] _snake;
  private int _snakeLength = 1;

  private TPoint _pos;
  private TPoint _move;
  private boolean _isWinner;
  private int _moveInterval;
  private int _lastMoveTime;
  private int _eventInterval;
  private int _lastEventTime;
  
  public Snake(PApplet papplet)
  {
    super(papplet, 24, 24);
    _data = new char[_rowCount][_colCount];
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
      _data[row][col] = ' ';
    _snake = new TPoint[_rowCount + _colCount];
    for (int i = 1; i < _snake.length; i++)
      _snake[i] = new TPoint(0, 0);
     _snake[0] = new TPoint(0, 1);
    _snakeLength = 1;
    _pos = new TPoint(_rowCount >> 1, _colCount >> 1);
    _move = new TPoint(1, 0);
    _isWinner = false;
    _moveInterval = 500;
    _lastMoveTime = 0;
    _eventInterval = 2000;
    _lastEventTime = 0;
  }
  
  @Override
  protected void displayScreen()
  {
    textAlign(CENTER);
    ellipseMode(CORNER);
    background(255);
    for (int row = 0; row < _rowCount; row++)
    {
      for (int col = 0; col < _colCount; col++)
      {
        int x = col * _cellW;
        int y = row * _cellH;
        stroke(0);
        noFill();
        rect (x, y, _cellW, _cellH);
        if (_data[row][col] == '$')
          drawEllipsa(row, col, 0);
        else 
          drawCell(row, col, _data[row][col] == ' ' ? 255: 0);
      }
    }
  }

  @Override
  protected boolean interact()
  {
    if (!nextMove()) return false;
    return doEvent();
  }

  @Override
  protected void displayFinal()
  {
    stroke(0);
    fill(200, 0, 0);
    textSize(32);
    text(_isWinner ? "YOU WIN!": "GAME OVER!", width >> 1, height >> 1);
  }
  
  protected boolean doEvent()
  {
    if (millis() - _lastEventTime > _eventInterval)
    {
      _lastEventTime = millis();
      int count = int(random(10)) % 2;
      for (int i = 0; i < count; i++)
      {
        int x = int(random(_rowCount));
        int y = int(random(_colCount));
        _data[x][y] = '$';
      }
    }
    return true;
  }
  
  protected void displayBody()
  {
    TPoint curPos = _pos;
    for (int i = 0; i < _snake.length; i++)
    {
      _data[curPos.X][curPos.Y] = '*';
      curPos = curPos.minus(_snake[i]);
    }
    _data[curPos.X][curPos.Y] = ' ';
  }
  
  protected void drawCell(int row, int col, int cellColor)
  {
    int x = col * _cellW;
    int y = row * _cellH;
    stroke(cellColor);
    fill(cellColor);
    rect (x + 2, y + 2, _cellW - 4, _cellH - 4);
  }
  
  protected void drawEllipsa(int row, int col, int cellColor)
  {
    int x = col * _cellW;
    int y = row * _cellH;
    stroke(cellColor);
    fill(cellColor);
    ellipse(x + 2, y + 2, _cellW - 4, _cellH - 4);
  }
  
  protected boolean checkBound(TPoint p)
  {
    return !(p.X < 0 || p.Y < 0 || p.X >= _rowCount || p.Y >= _colCount);
  }
  
  protected boolean nextMove()
  {
    if (millis() - _lastMoveTime > _moveInterval)
    {
      _lastMoveTime = millis();
      _pos = _pos.plus(_move);
      if (!checkBound(_pos)) return false;
      if (!action()) return false;
      displayBody();    
    }
    return true;  
  }
  
  protected boolean action()
  {
    switch (_data[_pos.X][_pos.Y])
    {
      case '$':
        return actionIncLength();
      case '*':
        return actionFail();
      default:
        break;
    }
    return actionContinue();
  }
  
  protected boolean actionIncLength()
  {
    _snakeLength += 1;
    if (_snakeLength == _snake.length)
    {
      _isWinner = true;
      return false;
    }
    for (int i = _snakeLength - 1; i > 0 ; i--)
      _snake[i] = _snake[i - 1];
    _snake[0] = _move;
    if (_snakeLength == 3) _moveInterval -= 150;
    if (_snakeLength == 10) _moveInterval -= 200;
    return true;
  }
  
  protected boolean actionFail()
  {
    return false;
  }
  
  protected boolean actionContinue()
  {
    for (int i = _snakeLength - 1; i > 0 ; i--)
      _snake[i] = _snake[i - 1];
    _snake[0] = _move;
    return true;
  }
  
  @Override
  public void keyEvent(KeyEvent keyEvent)
  {
    if (keyEvent.getAction() == KeyEvent.PRESS)
    {
      int _keyCode = keyEvent.getKeyCode();
      switch (_keyCode)
      {
        case 27:  // ESC
          _isRunning = false;
          return;
        case 38:  // UP
          _move = new TPoint(-1, 0);
          return;
        case 40:  // DOWN
          _move = new TPoint(1, 0);
           return;
        case 37:  // LEFT
          _move = new TPoint(0, -1);
          return;
        case 39:  // RIGHT
          _move = new TPoint(0, 1);
          return;
      }
    }
  }
}

public class TPoint
{
  private int X;
  private int Y;
  
  public TPoint(int x, int y)
  {
    X = x;
    Y = y;
  }
    
  public TPoint plus (TPoint other)
  {
    return new TPoint(X + other.X, Y + other.Y);
  }

  public TPoint minus (TPoint other)
  {
    return new TPoint(X - other.X, Y - other.Y);
  }
}
