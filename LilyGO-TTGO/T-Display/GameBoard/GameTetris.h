#ifndef _GameTetris_H_
#define _GameTetris_H_

#include "Game.h"

const int _tetris_rowCount = 30;
const int _tetris_colCount = 22;

class Tetris : public GameArea {
  public:
    Tetris(TFT_eSPI* tft): GameArea(tft) {}
    
    virtual boolean init(void);
    virtual void clickButtonC();
    virtual void clickButtonU();
    virtual void clickButtonD();
    virtual void clickButtonL();
    virtual void clickButtonR();

  protected:
    const uint16_t cellW = 10;
    const uint16_t cellH = 10;

    char _area[_tetris_rowCount][_tetris_colCount] = { };

    int _block = 0;
    int _slide = 0;
    int _x = 0;
    int _y = 0;
    int _actionCode = -1;

    boolean _isWinner = false;

  private:
    void init_area();
    boolean interact();
    boolean nextLine();
    void newBlock();
    boolean dropLines();
    boolean clearBlock(int blockIndex, int slideIndex, int x, int y);
    boolean showBlock(int blockIndex, int slideIndex, int x, int y);
    boolean checkBlock(int blockIndex, int slideIndex, int x, int y);
    boolean actionBlock(int blockIndex, int slideIndex, int x, int y, boolean show, boolean check);
    boolean moveBlockToLeft();
    boolean moveBlockToRight();
    boolean rotateBlockToLeft();
    boolean rotateBlockToRight();
    boolean dropBlock();
    boolean proceedAction();
    void displayScreen();
  protected:
    byte _blocks[112] =
{
    /////////////////////////////////////////
    //
    // **
    // **
    //
    /////////////////////////////////////////
    B1100,
    B1100,
    B0000,
    B0000,

    B1100,
    B1100,
    B0000,
    B0000,

    B1100,
    B1100,
    B0000,
    B0000,

    B1100,
    B1100,
    B0000,
    B0000,

    /////////////////////////////////////////
    // *
    // **
    //  *
    //
    /////////////////////////////////////////
    B1000,
    B1100,
    B0100,
    B0000,

    B0110,
    B1100,
    B0000,
    B0000,

    B1000,
    B1100,
    B0100,
    B0000,

    B0110,
    B1100,
    B0000,
    B0000,

    /////////////////////////////////////////
    //  *
    // **
    // *
    //
    /////////////////////////////////////////
    B0100,
    B1100,
    B1000,
    B0000,

    B1100,
    B0110,
    B0000,
    B0000,

    B0100,
    B1100,
    B1000,
    B0000,

    B1100,
    B0110,
    B0000,
    B0000,

    /////////////////////////////////////////
    //  *
    //  *
    //  *
    //  *
    /////////////////////////////////////////
    B0100,
    B0100,
    B0100,
    B0100,

    B0000,
    B1111,
    B0000,
    B0000,

    B0100,
    B0100,
    B0100,
    B0100,

    B0000,
    B1111,
    B0000,
    B0000,


    /////////////////////////////////////////
    //  *
    // **
    //  *
    // 
    /////////////////////////////////////////
    B0100,
    B1100,
    B0100,
    B0000,

    B0000,
    B1110,
    B0100,
    B0000,

    B0100,
    B0110,
    B0100,
    B0000,

    B0100,
    B1110,
    B0000,
    B0000,

    /////////////////////////////////////////
    // **
    //  *
    //  *
    // 
    /////////////////////////////////////////
    B1100,
    B0100,
    B0100,
    B0000,

    B0000,
    B1110,
    B1000,
    B0000,

    B0100,
    B0100,
    B0110,
    B0000,

    B0010,
    B1110,
    B0000,
    B0000,

    /////////////////////////////////////////
    //  **
    //  *
    //  *
    // 
    /////////////////////////////////////////
    B0110,
    B0100,
    B0100,
    B0000,

    B1000,
    B1110,
    B0000,
    B0000,

    B0100,
    B0100,
    B1100,
    B0000,

    B0000,
    B1110,
    B0010,
    B0000
};
    
};

#endif
