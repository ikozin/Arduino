#ifndef _TestBoard_H_
#define _TestBoard_H_

#include "Game.h"

class TestBoard : public Game {
  public:
    TestBoard(TFT_eSPI* tft): Game(tft) {}
    
    virtual boolean init(void);
    virtual boolean loop(void);  

    virtual void clickButtonA();
    virtual void clickButtonB();
    virtual void clickButtonC();
    virtual void clickButtonU();
    virtual void clickButtonD();
    virtual void clickButtonL();
    virtual void clickButtonR();
};

#endif
