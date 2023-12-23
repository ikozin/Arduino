#include "K1533.h"

#ifndef EXPAND_CHIP

#include "K1533_AP6.h"
#include "K1533_ID4.h"
#include "K1533_IE5.h"
#include "K1533_IR33.h"
#include "K1533_KP2.h"
#include "K1533_LA1_LA6_LA7_LA22.h"
#include "K1533_LA3_LA9_LA11_LA12_LA13_TL3.h"
#include "K1533_LA4_LA10_LA24.h"
#include "K1533_LA8.h"
#include "K1533_LE1_LE5_LE6_LE10_LE11.h"
#include "K1533_LE4.h"
#include "K1533_LI1_LI2.h"
#include "K1533_LL1.h"
#include "K1533_LN1_LN2_LN3_LN5_LN8_TL2.h"
#include "K1533_LP5.h"
#include "K1533_TM2.h"
#include "K1533_TM7.h"
#include "K1533_TM8.h"

#else

#include "K1533_AP6.h"
#include "K1533_ID4.h"
#include "K1533_IE5.h"
#include "K1533_IR33.h"
#include "K1533_KP2.h"
#include "K1533_LA1.h"
#include "K1533_LA3.h"
#include "K1533_LA4.h"
#include "K1533_LA6.h"
#include "K1533_LA7.h"
#include "K1533_LA8.h"
#include "K1533_LA9.h"
#include "K1533_LA10.h"
#include "K1533_LA11.h"
#include "K1533_LA12.h"
#include "K1533_LA13.h"
#include "K1533_LA22.h"
#include "K1533_LA24.h"
#include "K1533_LE1.h"
#include "K1533_LE4.h"
#include "K1533_LE5.h"
#include "K1533_LE6.h"
#include "K1533_LE10.h"
#include "K1533_LE11.h"
#include "K1533_LI1.h"
#include "K1533_LI2.h"
#include "K1533_LL1.h"
#include "K1533_LN1.h"
#include "K1533_LN2.h"
#include "K1533_LN3.h"
#include "K1533_LN5.h"
#include "K1533_LN8.h"
#include "K1533_LP5.h"
#include "K1533_TL2.h"
#include "K1533_TL3.h"
#include "K1533_TM2.h"
#include "K1533_TM7.h"
#include "K1533_TM8.h"

#endif

#ifndef EXPAND_CHIP

TDevice* k1533_list[] = { 
    new K1533AP6(),
    new K1533ID4(),
    new K1533IE5(),
    new K1533IR33(),
    new K1533KP2(),
    new K1533LA1LA6LA7LA22(),
    new K1533LA3LA9LA11LA12LA13TL3(),
    new K1533LA4LA10LA24(),
    new K1533LA8(),
    new K1533LE1LE5LE6LE10LE11(),
    new K1533LE4(),
    new K1533LI1LI2(),
    new K1533LL1(),
    new K1533LN1LN2LN3LN5LN8TL2(),
    new K1533LP5(),
    new K1533TM2(),
    new K1533TM7(),
    new K1533TM8(),
};
#else
TDevice* k1533_list[] = { 
    new K1533AP6(),
    new K1533ID4(),
    new K1533IE5(),
    new K1533IR33(),
    new K1533KP2(),
    new K1533LA1(),
    new K1533LA3(),
    new K1533LA4(),
    new K1533LA6(),
    new K1533LA7(),
    new K1533LA8(),
    new K1533LA9(),
    new K1533LA10(),
    new K1533LA11(),
    new K1533LA12(),
    new K1533LA13(),
    new K1533LA22(),
    new K1533LA24(),
    new K1533LE1(),
    new K1533LE4(),
    new K1533LE5(),
    new K1533LE6(),
    new K1533LE10(),
    new K1533LE11(),
    new K1533LI1(),
    new K1533LI2(),
    new K1533LL1(),
    new K1533LN1(),
    new K1533LN2(),
    new K1533LN3(),
    new K1533LN5(),
    new K1533LN8(),
    new K1533LP5(),
    new K1533TL2(),
    new K1533TL3(),
    new K1533TM2(),
    new K1533TM7(),
    new K1533TM8(),
};
#endif

K1533_Pack::K1533_Pack(void): DevicePackage("K1533", (TDevice**)&k1533_list, sizeof(k1533_list)/sizeof(k1533_list[0])) {
}