public class Brick extends GameEngine
{
  private boolean _isWinner;

  private int _ballInterval;
  private int _lastBallTime;

  private int _racketInterval;
  private int _lastRacketTime;

  private float _ballX;
  private float _ballY;
  private float _ballRadius;
  
  private float _vectorX;
  private float _vectorY;
  
  private float _racketX;
  private float _racketY;
  private float _racketWidth;
  private float _racketHeight;
  private float _racketStep;

  private boolean _isSticked;
  private int _actionCode;

  public Brick(PApplet papplet)
  {
    super(papplet, 11, 11);
    _data = new char[_rowCount][_colCount];
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
      _data[row][col] = ' ';

    _ballInterval = 0;
    _racketInterval = 0;

    _ballRadius = _cellH / 2;    
    _racketHeight = _ballRadius;
    _racketWidth = _racketHeight * 6;
    _racketX = (width - _racketWidth) / 2;
    _racketY = height - _racketHeight;
    _ballX = width / 2;
    _ballY = _racketY - _racketHeight - 1;

	  _vectorX = 0;
	  _vectorY = 0;

    _actionCode = -1;
    _isWinner = false;
    
    actionRacketStop();
    actionBallStop();
    actionNewBricks();

    //println(_cellW);
    //println(_cellH);
    //println(_ballRadius);
    //println(_racketWidth);
    //println(_racketHeight);
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
    if (!proceedRacket()) return false;
    if (!proceedBall()) return false;
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
    circle(_ballX, _ballY, _ballRadius + _ballRadius);
  }

  protected boolean proceedAction()
  {
    switch (_actionCode)
    {
      case -1:
        return actionRacketStop();
      case 27:  // ESC
        return actionExit();
      case 32:  // SPACE
        return actionNewBricks();
      case 37:  // LEFT
        return actionRacketMoveLeft();
      case 38:  // UP
        return actionBallStart();
      case 39:  // RIGHT
        return actionRacketMoveRight();
      case 40:  // DOWN
        return actionBallStop();
    }
    return false;
  }

  protected boolean actionExit()
  {
    return false;
  }
  
  protected boolean actionNewBricks()
  {
    newBricks();
    return true;
  }
  
  protected boolean actionRacketStop()
  {
    _racketStep = 0;
    return true;
  }
  
  protected boolean actionRacketMoveLeft()
  {
    _racketStep = -5;
    return true;
  }
  
  protected boolean actionRacketMoveRight()
  {
    _racketStep = 5;
    return true;
  }
  
  protected boolean actionBallStart()
  {
    if (_vectorX == 0 && _vectorX == _vectorY)
    {
      _isSticked = false;
      _vectorX = random(1, 5);
      _vectorY = - random(1, 5);
      if (random(1, 100) > 50)
      {
        _vectorX = -_vectorX;
      }
    }
    return true;
  }

  protected boolean actionBallStop()
  {
    float centerY = _racketY - _racketHeight - 1; 
    if (centerY + _ballRadius > _ballY && centerY - _ballRadius < _ballY)
    {
      _isSticked = true;
      _vectorX = _vectorY = 0;
      _ballY = centerY;
    }
    return true;
  }
  
  
  protected boolean proceedRacket()
  {
    if (millis() - _lastRacketTime > _racketInterval)
    {
      _lastRacketTime = millis();
      float x = _racketX + _racketStep;
      if (checkRocketBounds(x))
      {
        _racketX = x;
        if (_isSticked) _ballX += _racketStep;
      }
    }
    return true;
  }

  protected boolean checkRocketBounds(float x)
  {
    return (x >= 0) && ((x + _racketWidth <= width));
  }

  protected boolean proceedBall()
  {
    if (millis() - _lastBallTime > _ballInterval)
    {
      _lastBallTime = millis();
      float x = _ballX + _vectorX;
      if (x <= _ballRadius || x >= width - _ballRadius)
        _vectorX = -_vectorX;

      float y = _ballY + _vectorY;
      if (y <= _ballRadius || y >= height - _ballRadius)
        _vectorY = -_vectorY;

      _ballX += _vectorX;
      _ballY += _vectorY;
    }
    return true;
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
