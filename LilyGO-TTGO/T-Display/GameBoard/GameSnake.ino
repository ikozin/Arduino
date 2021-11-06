#include "GameBoard.h"
#include "GameSnake.h"

void Snake::init_area() {
  for (int row = 0; row < _snake_rowCount; row++)
    for (int col = 0; col < _snake_colCount; col++)
      _area[row][col] = ' ';   
}

void Snake::init_snake() {
  for (int i = 0; i < _snakeCount; i++)
    _snake[i] =  empty_point;
  _snake[0] =  start_move;    
}

boolean Snake::actionIncLength() {
  _snakeSize += 1;
  
  debug_printf("_snakeSize = %d\r\n", _snakeSize);  

  if (_snakeSize == _snakeCount) {
    _isWinner = true;
    return false;
  }
  for (int i = _snakeSize - 1; i > 0 ; i--)
    _snake[i] = _snake[i - 1];
  _snake[0] = _move;

  for (int i = 0; i < _snakeSize; i++)
    debug_printf("snake[%d], x = %d, y = %d\r\n", i, _snake[i].x, _snake[i].y);

  if (_snakeSize == 3) _moveInterval -= 150;
  if (_snakeSize == 10) _moveInterval -= 200;
  return true;
}

boolean Snake::actionFail() {
  debug_printf("Fail\r\n");
  for (int i = 0; i < _snakeSize; i++)
    debug_printf("snake[%d], x = %d, y = %d\r\n", i, _snake[i].x, _snake[i].y);

  return false;
}

boolean Snake::actionContinue() {
  for (int i = _snakeSize - 1; i > 0 ; i--)
    _snake[i] = _snake[i - 1];
  _snake[0] = _move;
  return true;
}

boolean Snake::action() {
  switch (_area[_pos.x][_pos.y]) {
    case '$': return actionIncLength();
    case '*': return actionFail();
    default:
      return actionContinue();
  }
}

inline boolean Snake::checkBound() {
  return !(_pos.x < 0 || _pos.y < 0 || _pos.x >= _snake_rowCount || _pos.y >= _snake_colCount);
}

boolean Snake::nextMove() {
  if (millis() - _lastMoveTime > _moveInterval) {
    _lastMoveTime = millis();
    _pos.x += _move.x;
    _pos.y += _move.y;

    debug_printf("_pos.x = %d, _pos.y = %d\r\n", _pos.x, _pos.y);  
    
    if (!checkBound()) return false;
    if (!action()) return false;
    displayBody();    
  }
  return true;  
}

boolean Snake::interact() {
  if (!nextMove()) return false;
  return doEvent();
}

boolean Snake::doEvent() {
  if (millis() - _lastEventTime > _eventInterval) {
    _lastEventTime = millis();
    int count = int(random(10)) % 2;
    for (int i = 0; i < count; i++) {
      int x = int(random(_snake_rowCount));
      int y = int(random(_snake_colCount));
      _area[x][y] = '$';
    }
  }
  return true;
}

void Snake::displayBody() {
  TPoint cur = _pos;
  for (int i = 0; i < _snakeSize; i++) {
    _area[cur.x][cur.y] = '*';
    cur.x -=_snake[i].x;
    cur.y -=_snake[i].y;
  }
  _area[cur.x][cur.y] = ' ';
}

void Snake::displayScreen() {
  _tft->setCursor(0,0);
  for (int row = 0; row < _snake_rowCount; row++) {
    for (int col = 0; col < _snake_colCount; col++) {
      _tft->print(_area[row][col]);
    }
    _tft->println();
  }
}

boolean Snake::init() {
  _tft->setRotation(1);
  _tft->fillScreen(TFT_BLACK);
  _tft->setTextColor(TFT_GREEN, TFT_BLACK);

  _moveInterval = 500;
  _lastMoveTime = 0;

  _eventInterval = 2000;
  _lastEventTime = 0;
  
  _pos = start_pos;
  _move = start_move;
  _snakeSize = 1;
    
  debug_printf("Start, _pos.x = %d, _pos.y = %d\r\n", _pos.x, _pos.y);  
  debug_printf("Start, _move.x = %d, _move.y = %d\r\n", _move.x, _move.y);  
  debug_printf("Start, _snakeSize = %d\r\n", _snakeSize);  
  
  init_area();
  init_snake();

  _isWinner = false;
  _isGameRunning = true;
  
  return true;
}

boolean Snake::loop() {
  displayScreen();
  if (_isGameRunning && interact()) return true;

  debug_printf("stop");
  while (true) {};
  return true;
 
}

void Snake::clickButtonA() {
  _isGameRunning = false;
}

void Snake::clickButtonB() {
  _isGameRunning = false;
}

void Snake::clickButtonC() {
}

void Snake::clickButtonU() {
  if (!_isGameRunning) return;

  TPoint value = { .value = 0xFF00 };
  _move = value;

  debug_printf("ButtonU, _move.x = %d, _move.y = %d\r\n", _move.x, _move.y);  
}

void Snake::clickButtonD() {
  if (!_isGameRunning) return;

  TPoint value = { .value = 0x0100 };
  _move = value;

  debug_printf("ButtonD, _move.x = %d, _move.y = %d\r\n", _move.x, _move.y);  
}

void Snake::clickButtonL() {
  if (!_isGameRunning) return;

  TPoint value = { .value = 0x00FF };
  _move = value;

  debug_printf("ButtonL, _move.x = %d, _move.y = %d\r\n", _move.x, _move.y);  
}

void Snake::clickButtonR() {
  if (!_isGameRunning) return;

  TPoint value = { .value = 0x0001 };
  _move = value;

  debug_printf("ButtonR, _move.x = %d, _move.y = %d\r\n", _move.x, _move.y);  
}
