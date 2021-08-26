#ifndef _K15533KP2_H_
#define _K15533KP2_H_

typedef union K1533KP2_PL {
  struct {
    uint8_t S_0     : 1;  // 0
    uint8_t S_1     : 1;  // 1
    uint8_t Addr    : 2;  // 2-3
    uint8_t Reserv  : 4;  // 4-7
  };
  uint8_t value;
} K1533KP2_PL_t;

typedef union {
  struct {
    uint8_t D0_0 : 1; // 0
    uint8_t D1_0 : 1; // 1
    uint8_t D2_0 : 1; // 2
    uint8_t D3_0 : 1; // 3
    uint8_t D0_1 : 1; // 4
    uint8_t D1_1 : 1; // 5
    uint8_t D2_1 : 1; // 6
    uint8_t D3_1 : 1; // 7
  };
  uint8_t value;
} K1533KP2_PA_t;

#define K1533KP2_PC_MASK  B11

typedef union {
  struct {
    uint8_t Data_0  : 1;  // 0
    uint8_t Data_1  : 1;  // 1
    uint8_t Reserv  : 6;  // 2-7
  };
  uint8_t value;
} K1533KP2_PC_t;

#endif
