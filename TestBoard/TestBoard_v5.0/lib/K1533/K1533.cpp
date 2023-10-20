#include "K1533.h"

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

K1533_Pack::K1533_Pack(void): DevicePackage("K1533", (TDevice**)&k1533_list, sizeof(k1533_list)/sizeof(k1533_list[0])) {
}