#ifndef _Input8Out1Device_
#define _Input8Out1Device_

typedef struct {
  byte Input[8];
  byte Output;
} Input8Out1DevPin;

typedef struct {
  union {
    struct {
      byte Data8  : 1;
      byte Data7  : 1;
      byte Data6  : 1;
      byte Data5  : 1;
      byte Data4  : 1;
      byte Data3  : 1;
      byte Data2  : 1;
      byte Data1  : 1;
    };
    byte value;
  };
  byte Result;
} Input8Out1DevVal;


extern void init_Input8Out1Dev(Input8Out1DevPin *pmap, size_t size);
extern void done_Input8Out1Dev(void);
extern bool test_Input8Out1Dev(Input8Out1DevPin *pmap, Input8Out1DevVal *pvalue);
extern void set_Input8Out1Dev(Input8Out1DevPin *pmap, size_t size, int value);
extern int check_Input8Out1Dev(Input8Out1DevPin *pmap, size_t map_size, Input8Out1DevVal *pvalue, size_t value_size);

#endif
