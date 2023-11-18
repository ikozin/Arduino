#include "K155.h"
#include "K155_RE3.h"

TDevice* k155_list[] = { 
    new K155RE3(),
};

K155_Pack::K155_Pack(void): DevicePackage("K155", (TDevice**)&k155_list, sizeof(k155_list)/sizeof(k155_list[0])) {
}