public class Brick extends GameEngine
{
  private boolean _isWinner;

  public Brick(PApplet papplet)
  {
    super(papplet, 24, 48);
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
    rect (x + 2, y + 2, _cellW - 4, _cellH - 4);
  }

  @Override
  public void keyEvent(KeyEvent keyEvent)
  {
    if (keyEvent.getAction() == KeyEvent.PRESS)
    {
      int _keyCode = keyEvent.getKeyCode();
      switch (_keyCode)
      {
        case 27:
          _isRunning = false;
          return;
        case 38:
          //_move = new TPoint(-1, 0);
          return;
        case 40:
          //_move = new TPoint(1, 0);
           return;
        case 37:
          //_move = new TPoint(0, -1);
          return;
        case 39:
          //_move = new TPoint(0, 1);
          return;
      }
    }
  }
}
