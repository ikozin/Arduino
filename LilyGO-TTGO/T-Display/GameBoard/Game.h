#ifndef _Game_H_
#define _Game_H_

typedef union {
  struct {
    int8_t y;
    int8_t x;
  };
  uint16_t value;
} TPoint;

class Game {
  public:
    Game(TFT_eSPI* tft) {
      _tft = tft;
    }
  protected:
    TFT_eSPI* _tft;
  public:
    virtual boolean init(void) = 0;
    virtual boolean loop(void) = 0;

    virtual void clickButtonA() = 0;
    virtual void clickButtonB() = 0;
    virtual void clickButtonC() = 0;
    virtual void clickButtonU() = 0;
    virtual void clickButtonD() = 0;
    virtual void clickButtonL() = 0;
    virtual void clickButtonR() = 0;
};

class GameArea : public Game {
  public:
    GameArea(TFT_eSPI* tft): Game(tft) {}
  protected:
    long _moveInterval;
    long _lastMoveTime;

    boolean _isGameRunning;
    
    virtual boolean interact() = 0;
    virtual void displayScreen() = 0;
  public:
    virtual boolean loop(void) {
      displayScreen();
      if (_isGameRunning && interact()) return true;
      debug_printf("stop\r\n");
      return false;
    }

    virtual void clickButtonA() {
      _isGameRunning = false;
    }
    
    virtual void clickButtonB() {
      _isGameRunning = false;
    }

    virtual boolean init(void) = 0;
    virtual void clickButtonC() = 0;
    virtual void clickButtonU() = 0;
    virtual void clickButtonD() = 0;
    virtual void clickButtonL() = 0;
    virtual void clickButtonR() = 0;
};


#endif
