#ifndef _DipDevice_H_
#define _DipDevice_H_

#include "Device.h"

class Dip14: public TDevice {
  private:
    const int _map[15] = {  0, 37, 36, 35, 34, 33, 32,  0, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip14::_map[value];
    }
};

class Dip14Ext: public TDeviceExt {
  private:
    const int _map[15] = {  0, 37, 36, 35, 34, 33, 32,  0, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip14Ext::_map[value];
    }
};

class Dip16: public TDevice {
  private:
    const int _map[17] = {  0, 37, 36, 35, 34, 33, 32, 31,  0, 28, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip16::_map[value];
    }
};

class Dip16Ext: public TDeviceExt {
  private:
    const int _map[17] = {  0, 37, 36, 35, 34, 33, 32, 31,  0, 28, 27, 26, 25, 24, 23, 22,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip16Ext::_map[value];
    }
};

class Dip20: public TDevice {
  private:
    const int _map[21] = {  0, 49, 37, 36, 35, 34, 33, 32, 31, 30,  0, 29, 28, 27, 26, 25, 24, 23, 22, 48,  0};
  protected:
    virtual int getPin(int value) const {
      return Dip20::_map[value];
    }
};

#endif
