#pragma once

#include <Arduino.h>

#define OCTAVE_OFFSET 0
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

const int notes[] = { 0,
					  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
					  NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
					  NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
					  NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

/*
  http://ez4mobile.com/nokiatone/rtttf.htm
*/

const char song01[] PROGMEM = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
const char song02[] PROGMEM = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
const char song03[] PROGMEM = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
const char song04[] PROGMEM = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
const char song05[] PROGMEM = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
const char song06[] PROGMEM = "Pacman:d=4,o=5,b=112:32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32c6,32p,32c7,32p,32g6,32p,32e6,32p,32c7,32g6,16p,16e6,16p,32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32d#6,32e6,32f6,32p,32f6,32f#6,32g6,32p,32g6,32g#6,32a6,32p,32b.6";
const char song07[] PROGMEM = "Terminator II:d=4,o=5,b=90:32d6,16e6,2f6,8e6,8c6,2f,16p,32d6,16e6,2f6,8e6,8c6,2a6,2g6";
const char song08[] PROGMEM = "Toccata:d=4,o=5,b=160:16a4,16g4,1a4,16g4,16f4,16d4,16e4,2c#4,16p,d.4,2p,16a4,16g4,1a4,8e.4,8f.4,8c#.4,2d4";
const char song09[] PROGMEM = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6";
const char song10[] PROGMEM = "Tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
const char song11[] PROGMEM = "AxelF:d=4,o=5,b=125:32p,8g,8p,16a#.,8p,16g,16p,16g,8c6,8g,8f,8g,8p,16d.6,8p,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g,p,ss,16f6,8d6,8c6,8a#,g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g";
const char song12[] PROGMEM = "girl:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
const char song13[] PROGMEM = "careaboutus:d=4,o=5,b=125:16f,16e,16f,16e,16f,16e,8d,16e,16d,16e,16d,16e,16d,16c,16d,d";
const char song14[] PROGMEM = "Scatman:d=4,o=5,b=200:8b,16b,32p,8b,16b,32p,8b,2d6,16p,16c#.6,16p.,8d6,16p,16c#6,8b,16p,8f#,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8f#,2p,32p,2d6,16p,16c#6,8p,16d.6,16p.,16c#6,16a.,16p.,8e,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8b,16b,32p,8b,16b,32p,8b,2d6,16p,16c#.6,16p.,8d6,16p,16c#6,8b,16p,8f#,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8f#,2p,32p,2d6,16p,16c#6,8p,16d.6,16p.,16c#6,16a.,16p.,8e,2p.,16c#6,8p,16d.6,16p.,16c#6,16a,8p,8e,2p,32p,16f#.6,16p.,16b.,16p.";
const char song15[] PROGMEM = "Smoke:d=4,o=5,b=112:c,d#,f.,c,d#,8f#,f,p,c,d#,f.,d#,c,2p,8p,c,d#,f.,c,d#,8f#,f,p,c,d#,f.,d#,c,p";
const char song16[] PROGMEM = "countdown:d=4,o=5,b=125:p,8p,16b,16a,b,e,p,8p,16c6,16b,8c6,8b,a,p,8p,16c6,16b,c6,e,p,8p,16a,16g,8a,8g,8f#,8a,g.,16f#,16g,a.,16g,16a,8b,8a,8g,8f#,e,c6,2b.,16b,16c6,16b,16a,1b";
//const char song17[] PROGMEM = "VanessaMae:d=4,o=6,b=70:32c7,32b,16c7,32g,32p,32g,32p,32d#,32p,32d#,32p,32c,32p,32c,32p,32c7,32b,16c7,32g#,32p,32g#,32p,32f,32p,16f,32c,32p,32c,32p,32c7,32b,16c7,32g,32p,32g,32p,32d#,32p,32d#,32p,32c,32p,32c,32p,32g,32f,32d#,32d,32c,32d,32d#,32c,32d#,32f,16g,8p,16d7,32c7,32d7,32a#,32d7,32a,32d7,32g,32d7,32d7,32p,32d7,32p,32d7,32p,16d7,32c7,32d7,32a#,32d7,32a,32d7,32g,32d7,32d7,32p,32d7,32p,32d7,32p,32g,32f,32d#,32d,32c,32d,32d#,32c,32d#,32f,16c";
const char song18[] PROGMEM = "Verve:d=4,o=5,b=180:e,g,e,f,d,2f,a#,f,2a#,a,f,2a,p,e,g,e,f,d,2f,a#,f,2a#,a,f,2a,p";
const char song19[] PROGMEM = "Wannabe:d=4,o=5,b=125:16g,16g,16g,16g,8g,8a,8g,8e,8p,16c,16d,16c,8d,8d,8c,e,p,8g,8g,8g,8a,8g,8e,8p,c6,8c6,8b,8g,8a,16b,16a,g";
const char song20[] PROGMEM = "Yaketysax:d=4,o=5,b=125:8d.,16e,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8a4,16a4,16a#4,16b4,16d,16e,16d,g,p,16d,16e,16d,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8d,16d,16d,16f#,16a,8f,d,p,16d,16e,16d,8g,16g,16g,8g,16g,16g,8g,8g,16e,8e.,8c,8c,8c,8c,16e,16g,16a,16g,16a#,8g,16a,16b,16a#,16b,16a,16b,8d6,16a,16b,16d6,8b,8g,8d,16e6,16b,16b,16d,8a,8g,g";
const char song21[] PROGMEM = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
const char song22[] PROGMEM = "StWars:d=4,o=5,b=180:8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6,p,8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6";
const char song23[] PROGMEM = "Cantina:d=4,o=5,b=250:8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,a,8a,8g#,8a,g,8f#,8g,8f#,f.,8d.,16p,p.,8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,8a,8p,8g,8p,g.,8f#,8g,8p,8c6,a#,a,g";
const char song24[] PROGMEM = "SWEnd:d=4,o=5,b=225:2c,1f,2g.,8g#,8a#,1g#,2c.,c,2f.,g,g#,c,8g#.,8c.,8c6,1a#.,2c,2f.,g,g#.,8f,c.6,8g#,1f6,2f,8g#.,8g.,8f,2c6,8c.6,8g#.,8f,2c,8c.,8c.,8c,2f,8f.,8f.,8f,2f";
