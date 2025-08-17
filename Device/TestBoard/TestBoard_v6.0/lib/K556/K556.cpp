#include "K556.h"
#include "K556_RT4.h"

///////////////////////////////////////////////////////////////////
// https://forum.defence-force.org/viewtopic.php?t=1699&start=45 //
///////////////////////////////////////////////////////////////////

TDevice* k556_list[] = {
    new K556RT4(), 
};

K556_Pack::K556_Pack(void): DevicePackage("K556", (TDevice**)&k556_list, sizeof(k556_list)/sizeof(k556_list[0])) {
}