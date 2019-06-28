/*


bx
by
br

rx
ry
rw
rh


              ---
            /     \
            \     /
              ---
	 rw
    -------------
rh |             |
    -------------

*/



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
  

  public Brick(PApplet papplet)
  {
    super(papplet, 4, 9);
    _data = new char[_rowCount][_colCount];
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
      _data[row][col] = ' ';

    int brickLine = (int)random(_rowCount >> 2, _rowCount >> 1);
    for (int row = 0; row < brickLine; row++)
    {
      int brickCount = (int)random(_colCount >> 1, _colCount);
      int shiftX = (_colCount - brickCount) >> 1; 
      for (int col = 0; col < brickCount; col++)
        _data[row][col + shiftX] = '*';
    }
    _racketInterval = 100;
    _ballInterval = 100;

    _ballRadius = (min(_cellW, _cellH) >> 1) + 1;    
    _racketHeight = (_ballRadius >> 1) + 1;
    _racketWidth = _racketHeight << 3;
    _racketX = (width - _racketWidth) >> 1;
    _racketY = height - _racketHeight - 1;

    _ballX = width >> 1;
    _ballY = _racketY - _ballRadius - 1;
    
    _isWinner = false;
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
      int x = col * _cellW;
      int y = row * _cellH;
      drawCell(row, col, 0);
    }
  }

  @Override
  protected boolean interact()
  {
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
  
  protected void drawCell(int row, int col, int cellColor)
  {
    int x = col * _cellW;
    int y = row * _cellH;
    stroke(cellColor);
    fill(cellColor);
    rect (x + 1, y + 1, _cellW - 2, _cellH - 2);
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
          //_move = new TPoint(-1, 0);
          return;
        case 40:  // DOWN
          //_move = new TPoint(1, 0);
           return;
        case 37:  // LEFT
          //_move = new TPoint(0, -1);
          return;
        case 39:  // RIGHT
          //_move = new TPoint(0, 1);
          return;
      }
    }
  }
}
