public class Brick implements IGameEngine
{
  private PApplet _papplet;

  private int _rowCount = 24;
  private int _colCount = 48;

  private int _cellW;
  private int _cellH;

  private char[][] _data;

  private boolean _isRunning;

  public Brick(PApplet papplet)
  {
    _papplet = papplet;

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
      {
        _data[row][col + shiftX] = '*';
      }
    }


    _isRunning = false;

    _cellW = width / _colCount;
    _cellH = height / _rowCount;
  }
  
  public void start()
  {
    _isRunning = true;
    _papplet.registerMethod("draw" , this);
    _papplet.registerMethod("keyEvent" , this);
    //_papplet.registerMethod("mouseEvent" , this);
  }
  
  public void stop()
  {
    _isRunning = false;
    //_papplet.unregisterMethod("mouseEvent" , this);
    _papplet.unregisterMethod("keyEvent" , this);
    _papplet.unregisterMethod("draw" , this);
  }

  public void draw()
  {
     displayScreen();
  }

  void displayScreen()
  {
    background(255);
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
    {
      if (_data[row][col] == ' ') continue;
      int x = col * _cellW;
      int y = row * _cellH;
      drawCell(row, col, 0);
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

  public void mouseEvent(MouseEvent mouseEvent)
  {
  }
  
  
  
}
