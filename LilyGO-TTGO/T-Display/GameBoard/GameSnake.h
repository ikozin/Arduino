#ifndef _GameSnake_H_
#define _GameSnake_H_

#include "Game.h"

const int _snake_rowCount = 17;
const int _snake_colCount = 40;

const int _snakeCount = 50;

class Snake : public GameArea {
  public:
    Snake(TFT_eSPI* tft): GameArea(tft) {}
    
    virtual boolean init(void);
    virtual void clickButtonC();
    virtual void clickButtonU();
    virtual void clickButtonD();
    virtual void clickButtonL();
    virtual void clickButtonR();
  protected:
    
    const TPoint start_pos    = { .value = 0x0810 };
    const TPoint start_move   = { .value = 0x0001 };
    const TPoint empty_point  = { .value = 0x0000 };

    const uint16_t cellW = 10;
    const uint16_t cellH = 10;

    char _area[_snake_rowCount][_snake_colCount] = { };

    TPoint _snake[_snakeCount] = {}; 
    int _snakeSize = 1;

    TPoint _pos;
    TPoint _move;

    long _eventInterval = 2000;
    long _lastEventTime = 0;

    boolean _isWinner = false;

private:
    void init_area();
    void init_snake();
    boolean actionIncLength();
    boolean actionFail();
    boolean actionContinue();
    boolean action();
    boolean checkBound();
    boolean nextMove();
    boolean interact();
    boolean doEvent();
    void displayBody();
    void displayScreen();
};

#endif
