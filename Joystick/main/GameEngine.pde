public abstract class GameEngine implements IGameEngine
{
  protected PApplet _papplet;
  protected boolean _isRunning;
  protected int _rowCount;
  protected int _colCount;  
  protected int _cellW;
  protected int _cellH;
  
  protected char[][] _data;

  public GameEngine(PApplet papplet, int row, int col)
  {
    _papplet = papplet;
    _rowCount = row;
    _colCount = col;  
    _cellW = width / _colCount;
    _cellH = height / _rowCount;
    _isRunning = false;
  }
  
  public void start()
  {
    _papplet.registerMethod("draw" , this);
    _papplet.registerMethod("keyEvent" , this);  
    _papplet.registerMethod("mouseEvent" , this);
    _isRunning = true;
  }  

  public void stop()
  {
    _isRunning = false;
    _papplet.unregisterMethod("mouseEvent" , this);
    _papplet.unregisterMethod("keyEvent" , this);
    _papplet.unregisterMethod("draw" , this);
  }  
  
  public void draw()
  {
    displayScreen();
    if (_isRunning && interact()) return;
    _isRunning = false;
    displayFinal();
  }  

  
  abstract protected void displayScreen();

  abstract protected boolean interact();

  abstract protected void displayFinal();

  public void keyEvent(KeyEvent keyEvent)
  {
  }
  
  public void mouseEvent(MouseEvent mouseEvent)
  {
  }
}
