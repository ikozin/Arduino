#include "K555.h"
#include "K555_IR11A.h"

TDevice* k555_list[] = { 
    new K555IR11A(),
};

K555_Pack::K555_Pack(void): DevicePackage("K555", (TDevice**)&k555_list, sizeof(k555_list)/sizeof(k555_list[0])) {
}