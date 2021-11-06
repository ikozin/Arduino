#include "GameBoard.h"
#include "GameTetris.h"

void Tetris::init_area() {
  for (int row = 0; row < _tetris_rowCount; row++)
    for (int col = 0; col < _tetris_colCount; col++)
      _area[row][col] = ' ';   
}

boolean Tetris::interact() {
  if (!clearBlock(_block, _slide, _x, _y)) return false;
  if (!nextLine()) return false;
  if (!proceedAction()) return false;
  if (!showBlock(_block, _slide, _x, _y)) return false;
  return true;
}

boolean Tetris::nextLine() {
  if (millis() - _lastMoveTime > _moveInterval) {
    _lastMoveTime = millis();
    int posY = _y + 1;
    if (checkBlock(_block, _slide, _x, posY)) {
      _y = posY;
    }
    else {
      showBlock(_block, _slide, _x, _y);
      newBlock();
    }
  }
  return true;
}

void Tetris::newBlock() {
  dropLines();
  _x = (byte)((_tetris_colCount >> 1) - 1);
  _y = 0;
  _block = (int)random(0, 7);
  _slide = (int)random(0, 4);
}

boolean Tetris::dropLines() {
  for (int y = 0; y < _tetris_rowCount; y++) {
    int counter = 0;
    for (int x = 0; x < _tetris_colCount; x++)
      counter += _area[y][x] == '*' ? 1 : 0;
    if (counter == _tetris_colCount) {
      for (int x = 0; x < _tetris_colCount; x++) _area[y][x] = ' ';
      for (int n = y - 1; n > 0; n--)
        for (int x = 0; x < _tetris_colCount; x++) _area[n + 1][x] = _area[n][x];
    }
  }
  return true;
}

boolean Tetris::clearBlock(int blockIndex, int slideIndex, int x, int y) {
  return actionBlock(blockIndex, slideIndex, x, y, false, false);
}

boolean Tetris::showBlock(int blockIndex, int slideIndex, int x, int y) {
  return actionBlock(blockIndex, slideIndex, x, y, true, false);
}

boolean Tetris::checkBlock(int blockIndex, int slideIndex, int x, int y) {
  return actionBlock(blockIndex, slideIndex, x, y, true, true);
}

boolean Tetris::actionBlock(int blockIndex, int slideIndex, int x, int y, boolean show, boolean check) {
  int index = (blockIndex << 4) + (slideIndex << 2);
  int posY = y;

  for (int row = 0; row < 4; row++) {
    int posX = x;
    for (int mask = B00001000; mask > 0; mask >>= 1) {
      if ((_blocks[index] & mask) > 0) {
        if (posX < 0 || posY < 0) return false;
        if (posX >= _tetris_colCount || posY >= _tetris_rowCount) return false;
        if (show && _area[posY][posX] != ' ') return false;
        if (!check) _area[posY][posX] = show ? '*' : ' ';
      }
      posX++;
    }
    posY++;
    index++;
  }
  return true;
}

boolean Tetris::moveBlockToLeft() {
  int posX = _x - 1;
  if (checkBlock(_block, _slide, posX, _y)) _x = posX;
  return true;
}

boolean Tetris::moveBlockToRight() {
  int posX = _x + 1;
  if (checkBlock(_block, _slide, posX, _y)) _x = posX;
  return true;
}

boolean Tetris::rotateBlockToLeft() {
  int nextSlide = abs((_slide + 1) % 4);
  if (checkBlock(_block, nextSlide, _x, _y)) _slide = nextSlide;
  return true;
}

boolean Tetris::rotateBlockToRight() {
  int nextSlide = abs((_slide - 1) % 4);
  if (checkBlock(_block, nextSlide, _x, _y)) _slide = nextSlide;
  return true;
}

boolean Tetris::dropBlock() {
  for ( ; ; ) {
    int posY = _y + 1;
    if (!checkBlock(_block, _slide, _x, posY)) break;
    _y = posY;
  }
  showBlock(_block, _slide, _x, _y);
  newBlock();
  return true;
}

boolean Tetris::proceedAction() {
  boolean result = true;
  switch (_actionCode) {
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

void Tetris::displayScreen() {
  _tft->setCursor(0,0);
  for (int row = 0; row < _tetris_rowCount; row++) {
    for (int col = 0; col < _tetris_colCount; col++) {
      _tft->print(_area[row][col]);  
    }
    _tft->println();
  }
}

boolean Tetris::init() {
  _tft->setRotation(0);
  _tft->fillScreen(TFT_BLACK);
  _tft->setTextColor(TFT_GREEN, TFT_BLACK);

  _block = 0;
  _slide = 0;
  _x = 0;
  _y = 0;
  _actionCode = -1;
  _moveInterval = 500;
  _lastMoveTime = 0;

  debug_printf("Start, _block = %d, _slide = %d\r\n", _block, _slide);  
  debug_printf("Start, _x = %d, _y = %d\r\n", _x, _y);  
  debug_printf("Start, _actionCode = %d\r\n", _actionCode);  

  init_area();

  _isWinner = false;
  _isGameRunning = true;
  
  return true;
}

void Tetris::clickButtonC() {
  if (!_isGameRunning) return;
  _actionCode = 32;

  debug_printf("ButtonC, _actionCode = %d\r\n", _actionCode);  
}

void Tetris::clickButtonU() {
  if (!_isGameRunning) return;
  _actionCode = 39;

  debug_printf("ButtonU, _actionCode = %d\r\n", _actionCode);  
}

void Tetris::clickButtonD() {
  if (!_isGameRunning) return;
  _actionCode = 37;
  
  debug_printf("ButtonD, _actionCode = %d\r\n", _actionCode);  
}

void Tetris::clickButtonL() {
  if (!_isGameRunning) return;
  _actionCode = 38;

  debug_printf("ButtonL, _actionCode = %d\r\n", _actionCode);  
}

void Tetris::clickButtonR() {
  if (!_isGameRunning) return;
  _actionCode = 40;

  debug_printf("ButtonR, _actionCode = %d\r\n", _actionCode);  
}
