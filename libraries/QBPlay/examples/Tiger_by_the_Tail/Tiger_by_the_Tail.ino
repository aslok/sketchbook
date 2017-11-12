/*
 * Tiger_by_the_Tail.ino
 * Файл с примером использования библиотеки QBPlay
 * https://en.wikibooks.org/wiki/QBasic/Appendix#PLAY
 *
 * created 10.11.2017
 * modified 12.11.2017
 * with Arduino 1.8.3 (tested on Arduino Uno)
 *
 * Copyright 2017 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

#include "QBPlay.h"
QBPlay* play;
const byte speaker_pin = A3;

const char Tiger_by_the_Tail[] PROGMEM = "MNT200L8O2CL4EGL8FL4EDL2<AP4L8>AL4AAL8GL4FL2G.P4L4FL8FL4FL8EL4DGL8GL4GL8FL4EAL8AL4AGL8AL2B.P4L8CL4EGL8FL4EDL2<AP4L8>AL4AAL8GL4FL2G.P4L4FL8FL4FL8EL4DGL8GL4GL8FL4EAL8AL4AGL8AL2B.P4L4>CL8CL4CL8<GL4EFL2AP4L4BL8BL4BAL8GL2G.P8L8BL4>CL8CL4C.L8<GEFFL2AP8L8ABBBL4BAL8BL2>C.P4L4CL8CL4CL8<GL4EFL2AP4L4BL8BL4BAL8GL2G.P8L8BL4>CL8CL4C.L8<GEFFL2AP8L8ABBBL4BAL8BL2>C.P4L8<CL4EGL8FL4EDL2<AP4L8>AL4AAL8GL4FL2G.P4L4FL8FL4FL8EL4DGL8GL4GL8FL4EAL8AL4AGL8AL2B.P4L8CL4EGL8FL4EDL2<AP4L8>AL4AAL8GL4FL2G.P4L4FL8FL4FL8EL4DGL8GL4GL8FL4EAL8AL4AGL8AL2B.P4L4>CL8CL4CL8<GL4EFL2AP4L4BL8BL4BAL8GL2G.P8L8BL4>CL8CL4C.L8<GEFFL2AP8L8ABBBL4BAL8BL2>C.P4L4DL8DL4DL8<AL4F+GL2BP4L8>C+C+C+L4C+<BL8AL2A.P8L8>C+L4DL8DL4D.L8<AF+GGL2BP8L8B>C+C+C+L4C+<BL8>C+DP8<DDDP8>D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Tiger_by_the_Tail);
}

void loop(){
    play->touch();
}
