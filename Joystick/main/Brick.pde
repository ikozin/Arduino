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

    _isRunning = false;
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
