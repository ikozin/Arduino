  public class Demo
  {
    PApplet _papplet;

    public Demo(PApplet papplet)
    {
      _papplet = papplet;
      _papplet.registerMethod("draw" , this);
      _papplet.registerMethod("keyEvent" , this);
      _papplet.registerMethod("mouseEvent" , this);
    }
    
    public void draw()
    {
      println("Demo.draw");

      _papplet.unregisterMethod("draw" , this);
    }
    
    public void keyEvent(KeyEvent keyEvent)
    {
      if (keyEvent.getAction( ) == KeyEvent.PRESS)
      {
        char _key = keyEvent.getKey( );
        int _keyCode = keyEvent.getKeyCode( );
        println(_keyCode);
      }

      _papplet.unregisterMethod("keyEvent" , this);
    }
    
    public void mouseEvent(MouseEvent theMouseEvent)
    {
      println("Demo.mouseEvent");
      println(theMouseEvent);
      
      _papplet.unregisterMethod("mouseEvent" , this);
    }
    
  }
