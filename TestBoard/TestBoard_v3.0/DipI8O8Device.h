#ifndef _DipI8O8Device_H_
#define _DipI8O8Device_H_

#include "Input8Out8Device.h"

class Dip14I8O8Device: public TInput8Out8Dev {
  private:
    const int _map[15] = {  0, 37, 36, 35, 34, 33, 32,  0, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip14I8O8Device::_map[value];
    }
};

class Dip14I8O8DeviceExt: public TInput8Out8DevExt {
  private:
    const int _map[15] = {  0, 37, 36, 35, 34, 33, 32,  0, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip14I8O8DeviceExt::_map[value];
    }
};

class Dip16I8O8Device: public TInput8Out8Dev {
  private:
    const int _map[17] = {  0, 37, 36, 35, 34, 33, 32, 31,  0, 28, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip16I8O8Device::_map[value];
    }
};

class Dip16I8O8DeviceExt: public TInput8Out8DevExt {
  private:
    const int _map[17] = {  0, 37, 36, 35, 34, 33, 32, 31,  0, 28, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip16I8O8DeviceExt::_map[value];
    }
};

#endif
