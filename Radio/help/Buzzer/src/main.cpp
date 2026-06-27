#include <Arduino.h>
#include "Melodies.h"

#ifndef ARDUINO_AVR_PRO
#error Select board: Arduino Pro Mini 
#endif

#define     TONE_PIN    (A2)

const char *playList[] = {
    song01,
    song02,
    song03,
    song04,
    song05,
    song06,
    song07,
    song08,
    song09,
    song10,
    song11,
    song12,
    song13,
    song14,
    song15,
    song16,
    song18,
    song19,
    song20,
    song21,
    song22,
    song23,
    song24,
};
const int playListSize = sizeof(playList) / sizeof(char*);

void play_rtttl(const char *song) {
    char *ptr = (char *)song;
    byte default_dur = 4;
    byte default_oct = 6;
    int bpm = 63;
    int num;
    long wholenote;
    long duration;
    byte note;
    byte scale;

    // format: d=N,o=N,b=NNN:
    // find the start (skip name, etc)

    while (pgm_read_byte_near(ptr) != ':') ptr++;   // ignore name
    ptr++;                     // skip ':'

    // get default duration
    if (pgm_read_byte_near(ptr) == 'd') {
        ptr++; ptr++;              // skip "d="
        num = 0;
        while (isdigit(pgm_read_byte_near(ptr))) {
            num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
        }
        if (num > 0) default_dur = num;
        ptr++;                   // skip comma
    }

    // get default octave
    if (pgm_read_byte_near(ptr) == 'o') {
        ptr++; ptr++;              // skip "o="
        num = pgm_read_byte_near(ptr++) - '0';
        if (num >= 3 && num <= 7) default_oct = num;
        ptr++;                   // skip comma
    }

    // get BPM
    if (pgm_read_byte_near(ptr) == 'b') {
        ptr++; ptr++;              // skip "b="
        num = 0;
        while (isdigit(pgm_read_byte_near(ptr))) {
            num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
        }
        bpm = num;
        ptr++;                   // skip colon
    }

    // BPM usually expresses the number of quarter notes per minute
    wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

    // now begin note loop
    while (pgm_read_byte_near(ptr)) {
        // first, get note duration, if available
        num = 0;
        while (isdigit(pgm_read_byte_near(ptr))) {
            num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
        }

        if (num) duration = wholenote / num;
        else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

        // now get the note
        note = 0;

        switch (pgm_read_byte_near(ptr)) {
            case 'c':
                note = 1;
                break;
            case 'd':
                note = 3;
                break;
            case 'e':
                note = 5;
                break;
            case 'f':
                note = 6;
                break;
            case 'g':
                note = 8;
                break;
            case 'a':
                note = 10;
                break;
            case 'b':
                note = 12;
                break;
            case 'p':
            default:
                note = 0;
        }
        ptr++;

        // now, get optional '#' sharp
        if (pgm_read_byte_near(ptr) == '#') {
            note++;
            ptr++;
        }

        // now, get optional '.' dotted note
        if (pgm_read_byte_near(ptr) == '.') {
            duration += duration / 2;
            ptr++;
        }

        // now, get scale
        if (isdigit(pgm_read_byte_near(ptr))) {
            scale = pgm_read_byte_near(ptr) - '0';
            ptr++;
        }
        else {
            scale = default_oct;
        }

        scale += OCTAVE_OFFSET;

        if (pgm_read_byte_near(ptr) == ',')
            ptr++;       // skip comma for next note (or we may be at the end)

        // now play the note

        if (note) {
            tone(TONE_PIN, notes[(scale - 4) * 12 + note]);
            delay(duration);
            noTone(TONE_PIN);
        }
        else {
            delay(duration);
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("Initialize buzzer"));
    pinMode(TONE_PIN, OUTPUT);
}

void loop() {
    static int play = 0;
    delay(1000);
    const char *song = playList[play++];
    play_rtttl(song);
    // Пауза в 1 секунду
    // Сохраняем номер след. музыки
    if (play >= playListSize) play = 0;
}
