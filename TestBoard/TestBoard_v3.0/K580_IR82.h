#ifdef K580_IR82

#ifndef _K580_IR82_H_
#define _K580_IR82_H_

#include "DipDevice.h"

class K580IR82: public Dip20 {
  public:
    K580IR82();
  protected:
    virtual void info(void);
};

#endif

#endif
