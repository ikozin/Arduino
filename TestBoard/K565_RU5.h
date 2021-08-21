#ifndef _K565RU5_H_
#define _K565RU5_H_

#define K565RU5_PL_RAS_MASK       B00000010
#define K565RU5_PL_CAS_MASK       B00000100
#define K565RU5_PL_WE_MASK        B00001000

#define K565RU5_PL_RAS_MASK_NOT   B11111101
#define K565RU5_PL_CAS_MASK_NOT   B11111011
#define K565RU5_PL_WE_MASK_NOT    B11110111

typedef union {
  struct {
    uint8_t DI : 1;     // 0
    uint8_t RAS : 1;    // 1
    uint8_t CAS : 1;    // 2
    uint8_t WE : 1;     // 3
    uint8_t Reserv : 4; // 4-7
  };
  uint8_t value;
} K565RU5_PL_t;

typedef union {
  struct {
    uint8_t A0 : 1; // 0
    uint8_t A1 : 1; // 1
    uint8_t A2 : 1; // 2
    uint8_t A3 : 1; // 3
    uint8_t A4 : 1; // 4
    uint8_t A5 : 1; // 5
    uint8_t A6 : 1; // 6
    uint8_t A7 : 1; // 7
  };
  uint8_t value;
} K565RU5_PA_t;

typedef union {
  struct {
    uint8_t DO : 1; // 0
    uint8_t Reverv : 7; // 1-7
  };
  uint8_t value;
} K565RU5_PC_t;

#endif
