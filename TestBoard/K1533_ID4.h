#ifndef _K15533ID4_H_
#define _K15533ID4_H_

typedef union {
  struct {
    uint8_t A1      : 1; // 0
    uint8_t A2      : 1; // 1
    uint8_t S0      : 1; // 2
    uint8_t S1      : 1; // 3
    uint8_t Reserv  : 4; // 4-7
  };
  uint8_t value;
} K1533ID4_PA_t;

#define K1533ID4_PC_MASK  B11111111

typedef union {
  struct {
    uint8_t D1_0  : 1;  // 0
    uint8_t D2_0  : 1;  // 1
    uint8_t D3_0  : 1;  // 2
    uint8_t D4_0  : 1;  // 3
    uint8_t D1_1  : 1;  // 4
    uint8_t D2_1  : 1;  // 5
    uint8_t D3_1  : 1;  // 6
    uint8_t D4_1  : 1;  // 7
  };
  uint8_t value;
} K1533ID4_PC_t;

#endif
