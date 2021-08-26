#ifndef _K15533TM2_H_
#define _K15533TM2_H_

typedef union {
  struct {
    uint8_t R0 : 1; // 0
    uint8_t D0 : 1; // 1
    uint8_t C0 : 1; // 2
    uint8_t S0 : 1; // 3
    uint8_t R1 : 1; // 0
    uint8_t D1 : 1; // 1
    uint8_t C1 : 1; // 2
    uint8_t S1 : 1; // 3
  }  TT;
  uint8_t      value;
} K1533TM2_PA_t;

#define K1533TM2_PC_MASK  B1111

typedef union {
  struct {
    uint8_t Data_0    : 1;  // 0
    uint8_t DataNot_0 : 1;  // 1
    uint8_t Data_1    : 1;  // 2
    uint8_t DataNot_1 : 1;  // 3
    uint8_t Reserv    : 4;
  };
  uint16_t value;
} K1533TM2_PC_t;

#endif
