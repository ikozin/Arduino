public class Snake implements IKeyPressedAction
{
  public void setup()
  {
  }

  public boolean draw()
  {  
    background(100, 100, 100);
    return true;
  }

  public boolean keyPressed()
  {
   return true;
  }

  public void SerialEventHandle(final int x, final int y, final int btn)
  {
  } 
}
