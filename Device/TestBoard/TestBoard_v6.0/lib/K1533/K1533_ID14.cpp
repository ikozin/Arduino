#include "K1533_ID14.h"

const static TDevicePin PROGMEM pin_map_1533_id14_1[] = {
    // Входы      1   2   S                    Выходы      0   1   2   3
    { .Input = {  2,  3,  1, 0, 0, 0, 0, 0 }, .Output = {  4,  5,  6,  7, 0, 0, 0, 0 }},
};

const static TDevicePin PROGMEM pin_map_1533_id14_2[] = {
    // Входы      1   2   S                    Выходы      0   1   2   3
    { .Input = { 14, 13, 15, 0, 0, 0, 0, 0 }, .Output = { 12, 11, 10,  9, 0, 0, 0, 0 }},
};

const static TDeviceVal PROGMEM values_1533_id14[] = {  
    { .value = (uint16_t)B_1_0_0, .result = (uint16_t)B_1_1_1_1 },
    { .value = (uint16_t)B_1_0_1, .result = (uint16_t)B_1_1_1_1 },
    { .value = (uint16_t)B_1_1_0, .result = (uint16_t)B_1_1_1_1 },
    { .value = (uint16_t)B_1_1_1, .result = (uint16_t)B_1_1_1_1 },

    { .value = (uint16_t)B_0_0_0, .result = (uint16_t)B_1_1_1_0 },
    { .value = (uint16_t)B_0_0_1, .result = (uint16_t)B_1_1_0_1 },
    { .value = (uint16_t)B_0_1_0, .result = (uint16_t)B_1_0_1_1 },
    { .value = (uint16_t)B_0_1_1, .result = (uint16_t)B_0_1_1_1 },
};

const __FlashStringHelper * K1533ID14::menu(void) {
    return F("ИД14 (Дешифратор)");
}

const __FlashStringHelper * K1533ID14::description(void) {
    return F(
"KP1533ИД14\r\n"
"2 Дешифратора\r\n"
"DIP16\r\n"
"\t         16 - +5V        \r\n"
"\t          8 - GND        \r\n"
"\t      --------------     \r\n"
"\t  2 -| 1  | DC |  0 o- 4 \r\n"
"\t  3 -| 2  |    |  1 o- 5 \r\n"
"\t     |----|    |  2 o- 6 \r\n"
"\t  1 -o S  |    |  3 o- 7 \r\n"
"\t      --------------     \r\n"
"\t      --------------     \r\n"
"\t 14 -| 1  |    |  0 o-12 \r\n"
"\t 13 -| 2  |    |  1 o-11 \r\n"
"\t     |----|    |  2 o-10 \r\n"
"\t 15 -o S  |    |  3 o- 9 \r\n"
"\t      --------------     \r\n"
    );
}

const __FlashStringHelper * K1533ID14::title(void) {
    return F("KP1533ИД14\r\n2 Дешифратора\r\nDIP16\r\n");
}

K1533ID14_SubDev sub_1533_id14_dev1(pin_map_1533_id14_1, values_1533_id14, sizeof(values_1533_id14)/sizeof(values_1533_id14[0]));
K1533ID14_SubDev sub_1533_id14_dev2(pin_map_1533_id14_2, values_1533_id14, sizeof(values_1533_id14)/sizeof(values_1533_id14[0]));
TDevice * composite_1533_id14[] { &sub_1533_id14_dev1, &sub_1533_id14_dev2 };

K1533ID14::K1533ID14(): TDeviceComposite(composite_1533_id14, sizeof(composite_1533_id14)/sizeof(composite_1533_id14[0])) {
}
