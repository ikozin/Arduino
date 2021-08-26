#ifndef _K15533IE5_H_
#define _K15533IE5_H_

typedef union {
  struct {
    uint8_t C1      : 1; // 0
    uint8_t C2      : 1; // 1
    uint8_t R0      : 1; // 2
    uint8_t R1      : 1; // 3
    uint8_t Reserv  : 4; // 4
  };
  uint8_t value;
} K1533IE5_PA_t;

#define K1533IE5_PC_MASK  B1111

typedef union {
  struct {
    uint8_t D1      : 1;  // 0
    uint8_t D2      : 1;  // 1
    uint8_t D4      : 1;  // 0
    uint8_t D8      : 1;  // 1
    uint8_t Reverv  : 4;  // 2-7
  };
  uint8_t value;
} K1533IE5_PC_t;

#endif
