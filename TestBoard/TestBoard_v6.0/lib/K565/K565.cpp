#include "K565.h"
#include "K565_RU5.h"
#include "K565_RU7.h"

TDevice* k565_list[] = { 
    new K565RU5(),
    new K565RU7(),
};

K565_Pack::K565_Pack(void): DevicePackage("K565", (TDevice**)&k565_list, sizeof(k565_list)/sizeof(k565_list[0])) {
}