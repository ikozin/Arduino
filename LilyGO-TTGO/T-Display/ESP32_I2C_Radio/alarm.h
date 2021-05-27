
typedef union alarm {
  struct {
    uint8_t Monday    : 1;  // 0
    uint8_t Tuesday   : 1;  // 1
    uint8_t Wednesday : 1;  // 2
    uint8_t Thursday  : 1;  // 3
    uint8_t Friday    : 1;  // 4
    uint8_t Saturday  : 1;  // 5
    uint8_t Sunday    : 1;  // 6
    uint8_t IsMute    : 1;  // 7

    uint8_t Reserv;         // 8-15

    uint8_t Minute;         // 16-23

    uint8_t Hour;           // 24-31

    int16_t Index;          // 32-47
    int16_t Volume;         // 48-63

  };
  uint64_t value;
} alarm_t;
