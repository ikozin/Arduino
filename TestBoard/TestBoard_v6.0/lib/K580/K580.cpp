#include "K580.h"
#include "K580_IR82.h"
#include "K580_VA86.h"

TDevice* k580_list[] = { 
    new K580IR82(),
    new K580VA86(),
};

K580_Pack::K580_Pack(void): DevicePackage("K580", (TDevice**)&k580_list, sizeof(k580_list)/sizeof(k580_list[0])) {
}