import processing.serial.*;
import processing.core.*;


public class PortSelector
{
  PApplet _parent;
  int _margin;      //10
  int _textHeight;  //16
  String[] _portList;
  Serial _port;
  boolean _isComplete;
  IKeyPressedAction _action;

  public PortSelector()
  {
    _margin = 10;
    _textHeight = 16;
  }

  public void setup(final PApplet parent, final IKeyPressedAction action)
  {
    _isComplete = false;
    _parent = parent;
    _action = action;
    _portList = Serial.list();
  }

  public boolean draw()
  {
    if (_isComplete) return false;
    StringList selectList = new StringList();
    int index = 0;
    for (String name : _portList)
    {
      if (index > 9) break;
      selectList.append(String.format("%s: %s", index++, name));
    }
    stroke(0);
    fill(0);
    textSize(_textHeight);
    int x = _margin; 
    int y = _margin + _textHeight;
    for (String item : selectList)
    {
      text(item, x, y);
      y += (_margin >> 1) + _textHeight;
    }
    return true;
  }

  public boolean keyPressed()
  {
    if (_isComplete) return false;
    switch (keyCode)
    {
      case 48:
      case 49:
      case 50:
      case 51:
      case 52:
      case 53:
      case 54:
      case 55:
      case 56:
      case 57:
        int index = keyCode - 48;
        if (index < _portList.length)
        {
          String name = _portList[index];
          println(name);
          _port = new Serial(_parent, name, 9600);
          _port.bufferUntil('\r');  
          _port.clear();
          _isComplete = true;
          redraw();
        }
        break;
        
       default:
        _isComplete = true;
        redraw();
        break;
    }
    return true;
  }

  public void serialEvent (final Serial port)
  {
    String data = port.readStringUntil('\r');  
    print(data);
    String values[] = split(data, ',');
    if (values.length == 3)
    {
      int x = int(trim(values[0]).substring(2));
      int y = int(trim(values[1]).substring(2));
      int btn = int(trim(values[2]).substring(4));
      if (_action != null) _action.SerialEventHandle(x, y, btn);
    }
  }  
}
