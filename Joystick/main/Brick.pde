public class Brick extends GameEngine
{
  private boolean _isWinner;
  
  private int _racketInterval;
  private int _lastRacketTime;
  
  private int _ballInterval;
  private int _lastBallTime;

  private float _ballX;
  private float _ballY;
  private int _ballRadius;
  
  private float _vectorX;
  private float _vectorY;
  
  private int _racketX;
  private int _racketY;
  private int _racketWidth;
  private int _racketHeight;

  private int _actionCode;

  public Brick(PApplet papplet)
  {
    super(papplet, 11, 11);
    _data = new char[_rowCount][_colCount];
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
      _data[row][col] = ' ';
    newBricks();

    _racketInterval = 100;
    _ballInterval = 100;

    _ballRadius = _cellH >> 2;    
    _racketHeight = _ballRadius;
    _racketWidth = (_racketHeight << 3)  + (_racketHeight << 2);
    _racketX = (width - _racketWidth) >> 1;
    _racketY = height - _racketHeight - 1;
    _ballX = width >> 1;
    _ballY = _racketY - _ballRadius - 1;

    _actionCode = -1;
    _isWinner = false;

    println(_cellW);
    println(_cellH);
    println(_ballRadius);
    println(_racketWidth);
    println(_racketHeight);
  }

  @Override
  protected void displayScreen()
  {
    background(255);
    stroke(0);
    noFill();
    rect(1, 1, width - 2, height - 2);
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
    {
      if (_data[row][col] == ' ') continue;
      drawCell(row, col, 0);
    }
  }

  @Override
  protected boolean interact()
  {
    if (!proceedAction()) return false;
    drawBall();
    drawRacket();

    return true;
  }
  
  @Override
  protected void displayFinal()
  {
    textAlign(CENTER);
    stroke(0);
    fill(200, 0, 0);
    textSize(32);
    text(_isWinner ? "YOU WIN!": "GAME OVER!", width >> 1, height >> 1);
  }

  protected void newBricks()
  {
    int brickLine = (int)random(_rowCount >> 2, _rowCount >> 1);
    for (int row = 0; row < brickLine; row++)
    {
      int brickCount = (int)random(_colCount >> 1, _colCount);
      int shiftX = (_colCount - brickCount) >> 1; 
      for (int col = 0; col <= brickCount; col++)
        _data[row][col + shiftX] = '*';
    }
  }
  
  protected void drawCell(int row, int col, int cellColor)
  {
    int x = col * _cellW;
    int y = row * _cellH;
    stroke(cellColor);
    fill(cellColor);
    rect (x + 1, y + 1, _cellW - 2, _cellH - 2, 5, 5, 5, 5);
  }

  protected void drawRacket()
  {
    stroke(#000000);
    fill(#000000);
    rect (_racketX, _racketY, _racketWidth, _racketHeight);
  }

  protected void drawBall()
  {
    stroke(#000000);
    fill(#000000);
    circle(_ballX, _ballY, _ballRadius << 1);
  }

  protected boolean proceedAction()
  {
    boolean result = true;
    switch (_actionCode)
    {
      case 27:  // ESC
      {
        result = false; 
        break;
      }
      case 32:  // SPACE
      {
        newBricks();
        _actionCode = -1;
        break;
      }
      case 37:  // LEFT
      {
        int x = _racketX - 3;
        if (checkRocketBounds(x))
          _racketX = x;
        break;
      }
      case 38:  // UP
        break;
      case 39:  // RIGHT
      {
        int x = _racketX + 3;
        if (checkRocketBounds(x))
          _racketX = x;
        break;
      }
      case 40:  // DOWN
        break;
    }
    return result;
  }

  protected boolean checkRocketBounds(int x)
  {
    return (x > 0) && ((x + _racketWidth < width));
  }

  @Override
  public void keyEvent(KeyEvent event)
  {
    if (event.getAction() == KeyEvent.RELEASE && event.getKeyCode() == _actionCode)
    {
      _actionCode = -1;
      return;
    }
    if (event.getAction() == KeyEvent.PRESS)
    {
      int _keyCode = event.getKeyCode();
      switch (_keyCode)
      {
        case 27:  // ESC
        case 32:  // SPACE
        case 37:  // LEFT
        case 38:  // UP
        case 39:  // RIGHT
        case 40:  // DOWN
          _actionCode = _keyCode;
          return;
      }
    }
  }
}
