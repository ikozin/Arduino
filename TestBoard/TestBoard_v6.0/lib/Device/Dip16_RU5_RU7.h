#ifndef _Dip16_RU5_RU7_H_
#define _Dip16_RU5_RU7_H_

#include "Device.h"

///////////////////////////////////////////////////////////

#define DI_PORT_C      (B00000010) 
#define RAS_PORT_C     (B00001000) 
#define CAS_PORT_A     (B00000001) 
#define WE_PORT_C      (B00000100) 
#define DO_PORT_A      (B00000010) 

const uint8_t portA[] = {
  B10000011, B10000011, B10000011, B10000011, B10000011, B10000011, B10000011, B10000011, B10001011, B10001011, B10001011, B10001011, B10001011, B10001011, B10001011, B10001011,
  B10010011, B10010011, B10010011, B10010011, B10010011, B10010011, B10010011, B10010011, B10011011, B10011011, B10011011, B10011011, B10011011, B10011011, B10011011, B10011011,
  B10100011, B10100011, B10100011, B10100011, B10100011, B10100011, B10100011, B10100011, B10101011, B10101011, B10101011, B10101011, B10101011, B10101011, B10101011, B10101011,
  B10110011, B10110011, B10110011, B10110011, B10110011, B10110011, B10110011, B10110011, B10111011, B10111011, B10111011, B10111011, B10111011, B10111011, B10111011, B10111011,
  B10000111, B10000111, B10000111, B10000111, B10000111, B10000111, B10000111, B10000111, B10001111, B10001111, B10001111, B10001111, B10001111, B10001111, B10001111, B10001111,
  B10010111, B10010111, B10010111, B10010111, B10010111, B10010111, B10010111, B10010111, B10011111, B10011111, B10011111, B10011111, B10011111, B10011111, B10011111, B10011111,
  B10100111, B10100111, B10100111, B10100111, B10100111, B10100111, B10100111, B10100111, B10101111, B10101111, B10101111, B10101111, B10101111, B10101111, B10101111, B10101111,
  B10110111, B10110111, B10110111, B10110111, B10110111, B10110111, B10110111, B10110111, B10111111, B10111111, B10111111, B10111111, B10111111, B10111111, B10111111, B10111111,
  B11000011, B11000011, B11000011, B11000011, B11000011, B11000011, B11000011, B11000011, B11001011, B11001011, B11001011, B11001011, B11001011, B11001011, B11001011, B11001011,
  B11010011, B11010011, B11010011, B11010011, B11010011, B11010011, B11010011, B11010011, B11011011, B11011011, B11011011, B11011011, B11011011, B11011011, B11011011, B11011011,
  B11100011, B11100011, B11100011, B11100011, B11100011, B11100011, B11100011, B11100011, B11101011, B11101011, B11101011, B11101011, B11101011, B11101011, B11101011, B11101011,
  B11110011, B11110011, B11110011, B11110011, B11110011, B11110011, B11110011, B11110011, B11111011, B11111011, B11111011, B11111011, B11111011, B11111011, B11111011, B11111011,
  B11000111, B11000111, B11000111, B11000111, B11000111, B11000111, B11000111, B11000111, B11001111, B11001111, B11001111, B11001111, B11001111, B11001111, B11001111, B11001111,
  B11010111, B11010111, B11010111, B11010111, B11010111, B11010111, B11010111, B11010111, B11011111, B11011111, B11011111, B11011111, B11011111, B11011111, B11011111, B11011111,
  B11100111, B11100111, B11100111, B11100111, B11100111, B11100111, B11100111, B11100111, B11101111, B11101111, B11101111, B11101111, B11101111, B11101111, B11101111, B11101111,
  B11110111, B11110111, B11110111, B11110111, B11110111, B11110111, B11110111, B11110111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, 

  B10000011, B10000011, B10000011, B10000011, B10000011, B10000011, B10000011, B10000011, B10001011, B10001011, B10001011, B10001011, B10001011, B10001011, B10001011, B10001011,
  B10010011, B10010011, B10010011, B10010011, B10010011, B10010011, B10010011, B10010011, B10011011, B10011011, B10011011, B10011011, B10011011, B10011011, B10011011, B10011011,
  B10100011, B10100011, B10100011, B10100011, B10100011, B10100011, B10100011, B10100011, B10101011, B10101011, B10101011, B10101011, B10101011, B10101011, B10101011, B10101011,
  B10110011, B10110011, B10110011, B10110011, B10110011, B10110011, B10110011, B10110011, B10111011, B10111011, B10111011, B10111011, B10111011, B10111011, B10111011, B10111011,
  B10000111, B10000111, B10000111, B10000111, B10000111, B10000111, B10000111, B10000111, B10001111, B10001111, B10001111, B10001111, B10001111, B10001111, B10001111, B10001111,
  B10010111, B10010111, B10010111, B10010111, B10010111, B10010111, B10010111, B10010111, B10011111, B10011111, B10011111, B10011111, B10011111, B10011111, B10011111, B10011111,
  B10100111, B10100111, B10100111, B10100111, B10100111, B10100111, B10100111, B10100111, B10101111, B10101111, B10101111, B10101111, B10101111, B10101111, B10101111, B10101111,
  B10110111, B10110111, B10110111, B10110111, B10110111, B10110111, B10110111, B10110111, B10111111, B10111111, B10111111, B10111111, B10111111, B10111111, B10111111, B10111111,
  B11000011, B11000011, B11000011, B11000011, B11000011, B11000011, B11000011, B11000011, B11001011, B11001011, B11001011, B11001011, B11001011, B11001011, B11001011, B11001011,
  B11010011, B11010011, B11010011, B11010011, B11010011, B11010011, B11010011, B11010011, B11011011, B11011011, B11011011, B11011011, B11011011, B11011011, B11011011, B11011011,
  B11100011, B11100011, B11100011, B11100011, B11100011, B11100011, B11100011, B11100011, B11101011, B11101011, B11101011, B11101011, B11101011, B11101011, B11101011, B11101011,
  B11110011, B11110011, B11110011, B11110011, B11110011, B11110011, B11110011, B11110011, B11111011, B11111011, B11111011, B11111011, B11111011, B11111011, B11111011, B11111011,
  B11000111, B11000111, B11000111, B11000111, B11000111, B11000111, B11000111, B11000111, B11001111, B11001111, B11001111, B11001111, B11001111, B11001111, B11001111, B11001111,
  B11010111, B11010111, B11010111, B11010111, B11010111, B11010111, B11010111, B11010111, B11011111, B11011111, B11011111, B11011111, B11011111, B11011111, B11011111, B11011111,
  B11100111, B11100111, B11100111, B11100111, B11100111, B11100111, B11100111, B11100111, B11101111, B11101111, B11101111, B11101111, B11101111, B11101111, B11101111, B11101111,
  B11110111, B11110111, B11110111, B11110111, B11110111, B11110111, B11110111, B11110111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, 
};

const uint8_t portC[] = {
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110,
  B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, B10001110, B10011110, B11001110, B11011110, B10101110, B10111110, B11101110, B11111110, 

  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111,
  B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, B10001111, B10011111, B11001111, B11011111, B10101111, B10111111, B11101111, B11111111, 
};

//https://github.com/MCbx/ictester-standalone/blob/master/main_tester/main_tester.ino
//https://forum.defence-force.org/viewtopic.php?t=1699&start=30
//https://forum.defence-force.org/download/file.php?id=3324&sid=2f21f030ddb05d4aecf28865dc03ad55
class Dip16_RU5_RU7: public TDevice {
  private:
    const int _map[17] = {  0, 37, 36, 35, 34, 33, 32, 31,  0, 28, 27, 26, 25, 24, 23, 22};
  protected:
    int _rows;
    int _cols;

  protected:
    virtual int getPin(int value) const {
      return Dip16_RU5_RU7::_map[value];
    }

    long inline checkByte(uint8_t value);    
    void inline write(int row, int col, uint8_t value);
    uint8_t inline read(int row, int col);
    void inline refresh(void);
  public:
    virtual int check_devices(GyverDisplay& display);
};
#endif