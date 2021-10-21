#ifndef _Input8Out8Device_
#define _Input8Out8Device_

typedef struct {
  byte Input[8];
  byte Output[8];
} Input8Out8DevPin;

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
  union {
    struct {
      byte Out8  : 1;
      byte Out7  : 1;
      byte Out6  : 1;
      byte Out5  : 1;
      byte Out4  : 1;
      byte Out3  : 1;
      byte Out2  : 1;
      byte Out1  : 1;
    };
    byte result;
  };
} Input8Out8DevVal;


extern void init_Input8Out8Dev(Input8Out8DevPin *pmap, size_t size);
extern void done_Input8Out8Dev(void);
extern int test_Input8Out8Dev(Input8Out8DevPin *pmap, Input8Out8DevVal *pvalue);
extern void set_Input8Out8Dev(Input8Out8DevPin *pmap, size_t size, int value);
extern int check_Input8Out8Dev(Input8Out8DevPin *pmap, size_t map_size, Input8Out8DevVal *pvalue, size_t value_size);

#endif
