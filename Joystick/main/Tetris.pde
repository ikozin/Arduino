public class Tetris extends GameEngine
{
  private int _interval;
  private int _lastRecordedTime;

  private int _block;
  private int _slide;
  private int _x;
  private int _y;
  private int _actionCode;
  private int _dropedLines;

  public Tetris(PApplet papplet)
  {
    super(papplet, 24, 10);
    _data = new char[_rowCount][_colCount];
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
      _data[row][col] = ' ';
    _interval = 200;
    _lastRecordedTime = 0;
    _block = 0;
    _slide = 0;
    _x = 0;
    _y = 0;
    _actionCode = -1;
    _dropedLines = 0;
  }
  
  @Override
  public void start()
  {
    super.start();
    newBlock();
  }
  
  @Override
  protected void displayScreen()
  {
    background(255);
    for (int row = 0; row < _rowCount; row++)
    for (int col = 0; col < _colCount; col++)
    {
      int x = col * _cellW;
      int y = row * _cellH;
      stroke(0);
      noFill();
      rect (x, y, _cellW, _cellH);
      drawCell(row, col, _data[row][col] == ' ' ? 255: 0);
    }
  }
  
  @Override
  protected boolean interact()
  {
    if (!clearBlock(_block, _slide, _x, _y)) return false;
    if (!nextLine()) return false;
    if (!proceedAction()) return false;
    if (!showBlock(_block, _slide, _x, _y)) return false;
    return true;
  }
  
  @Override
  protected void displayFinal()
  {
    textAlign(CENTER);
    stroke(0);
    fill(200, 0, 0);
    textSize(16);
    text("GAME OVER!", width >> 1, height >> 1);
  }

  protected boolean nextLine()
  {
    while (_dropedLines > 5)
    {
      if (_interval > 0) _interval -= 20;
      _dropedLines --;
    }
    if (millis() - _lastRecordedTime > _interval)
    {
      _lastRecordedTime = millis();
      println(_interval);
      int posY = _y + 1;
      if (checkBlock(_block, _slide, _x, posY))
      {
        _y = posY;
      }
      else
      {
        showBlock(_block, _slide, _x, _y);
        newBlock();
      }
    }
    return true;
  }
  
  protected void newBlock()
  {
    dropLines();
    _x = (byte)((_colCount >> 1) - 1);
    _y = 0;
    _block = (int)random(0, 7);
    _slide = (int)random(0, 4);
  }
  
  protected boolean dropLines()
  {
    for (int y = 0; y < _rowCount; y++)
    {
      int counter = 0;
      for (int x = 0; x < _colCount; x++)
        counter += _data[y][x] == '*' ? 1 : 0;
      if (counter == _colCount)
      {
        _dropedLines ++;
        for (int x = 0; x < _colCount; x++) _data[y][x] = ' ';
        for (int n = y - 1; n > 0; n--)
          for (int x = 0; x < _colCount; x++) _data[n + 1][x] = _data[n][x];
      }
    }
    return true;
  }
  
  protected boolean clearBlock(int blockIndex, int slideIndex, int x, int y)
  {
    return actionBlock(blockIndex, slideIndex, x, y, false, false);
  }
  
  protected boolean showBlock(int blockIndex, int slideIndex, int x, int y)
  {
    return actionBlock(blockIndex, slideIndex, x, y, true, false);
  }
  
  protected boolean checkBlock(int blockIndex, int slideIndex, int x, int y)
  {
    return actionBlock(blockIndex, slideIndex, x, y, true, true);
  }
  
  protected boolean actionBlock(int blockIndex, int slideIndex, int x, int y, boolean show, boolean check)
  {
    int index = (blockIndex << 4) + (slideIndex << 2);
    int posY = y;
  
    for (int row = 0; row < 4; row++)
    {
      int posX = x;
      for (int mask = 0b0000_1000; mask > 0; mask >>= 1)
      {
        if ((unbinary(_blocks[index]) & mask) > 0)
        {
          if (posX < 0 || posY < 0) return false;
          if (posX >= _colCount || posY >= _rowCount) return false;
          if (show && _data[posY][posX] != ' ') return false;
          if (!check) _data[posY][posX] = show ? '*' : ' ';
        }
        posX++;
      }
      posY++;
      index++;
    }
    return true;
  }
  
  protected boolean moveBlockToLeft()
  {
    int posX = _x - 1;
    if (checkBlock(_block, _slide, posX, _y)) _x = posX;
    return true;
  }
  
  protected boolean moveBlockToRight()
  {
    int posX = _x + 1;
    if (checkBlock(_block, _slide, posX, _y)) _x = posX;
    return true;
  }
  
  protected boolean rotateBlockToLeft()
  {
    int nextSlide = abs((_slide + 1) % 4);
    if (checkBlock(_block, nextSlide, _x, _y)) _slide = nextSlide;
    return true;
  }
  
  protected boolean rotateBlockToRight()
  {
    int nextSlide = abs((_slide - 1) % 4);
    if (checkBlock(_block, nextSlide, _x, _y)) _slide = nextSlide;
    return true;
  }
  
  protected boolean dropBlock()
  {
    for ( ; ; )
    {
      int posY = _y + 1;
      if (!checkBlock(_block, _slide, _x, posY)) break;
      _y = posY;
    }
    showBlock(_block, _slide, _x, _y);
    newBlock();
    return true;
  }
  
  protected void drawCell(int row, int col, int cellColor)
  {
    int x = col * _cellW;
    int y = row * _cellH;
    stroke(cellColor);
    fill(cellColor);
    rect (x + 2, y + 2, _cellW - 4, _cellH - 4);
  }
  
  protected boolean proceedAction()
  {
    boolean result = true;
    switch (_actionCode)
    {
      case 27:  // ESC
        result = false; 
        break;
      case 38:  // UP
        result = rotateBlockToLeft();
        break;
      case 40:  // DOWN
        result = rotateBlockToRight();
        break;
      case 37:  // LEFT
        result = moveBlockToLeft();
        break;
      case 39:  // RIGHT
        result = moveBlockToRight();
        break;
      case 32:  // SPACE
        result = dropBlock();
        break;
    }
    _actionCode = -1;
    return result;
  }
  
  @Override
  public void keyEvent(KeyEvent keyEvent)
  {
    if (keyEvent.getAction() == KeyEvent.PRESS)
    {
      _actionCode = keyEvent.getKeyCode();
    }
  }

  private String[] _blocks =
  {
      /////////////////////////////////////////
      //
      // **
      // **
      //
      /////////////////////////////////////////
      "1100",
      "1100",
      "0000",
      "0000",
  
      "1100",
      "1100",
      "0000",
      "0000",
  
      "1100",
      "1100",
      "0000",
      "0000",
  
      "1100",
      "1100",
      "0000",
      "0000",
  
      /////////////////////////////////////////
      // *
      // **
      //  *
      //
      /////////////////////////////////////////
      "1000",
      "1100",
      "0100",
      "0000",
  
      "0110",
      "1100",
      "0000",
      "0000",
  
      "1000",
      "1100",
      "0100",
      "0000",
  
      "0110",
      "1100",
      "0000",
      "0000",
  
      /////////////////////////////////////////
      //  *
      // **
      // *
      //
      /////////////////////////////////////////
      "0100",
      "1100",
      "1000",
      "0000",
  
      "1100",
      "0110",
      "0000",
      "0000",
  
      "0100",
      "1100",
      "1000",
      "0000",
  
      "1100",
      "0110",
      "0000",
      "0000",
  
      /////////////////////////////////////////
      //  *
      //  *
      //  *
      //  *
      /////////////////////////////////////////
      "0100",
      "0100",
      "0100",
      "0100",
  
      "0000",
      "1111",
      "0000",
      "0000",
  
      "0100",
      "0100",
      "0100",
      "0100",
  
      "0000",
      "1111",
      "0000",
      "0000",
  
  
      /////////////////////////////////////////
      //  *
      // **
      //  *
      // 
      /////////////////////////////////////////
      "0100",
      "1100",
      "0100",
      "0000",
  
      "0000",
      "1110",
      "0100",
      "0000",
  
      "0100",
      "0110",
      "0100",
      "0000",
  
      "0100",
      "1110",
      "0000",
      "0000",
  
      /////////////////////////////////////////
      // **
      //  *
      //  *
      // 
      /////////////////////////////////////////
      "1100",
      "0100",
      "0100",
      "0000",
  
      "0000",
      "1110",
      "1000",
      "0000",
  
      "0100",
      "0100",
      "0110",
      "0000",
  
      "0010",
      "1110",
      "0000",
      "0000",
  
      /////////////////////////////////////////
      //  **
      //  *
      //  *
      // 
      /////////////////////////////////////////
      "0110",
      "0100",
      "0100",
      "0000",
  
      "1000",
      "1110",
      "0000",
      "0000",
  
      "0100",
      "0100",
      "1100",
      "0000",
  
      "0000",
      "1110",
      "0010",
      "0000",
    };
};
